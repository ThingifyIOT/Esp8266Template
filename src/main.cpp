#include <Arduino.h>
#include <ContiEsp.h>
#include <DebugNodesModule.h>

ContiEsp thing("<token>", "Sample Thing");


bool OnBoolChanged(void*_, Node *node)
{
  bool value = node->Value.AsBool();
  if(value)
  {
    Serial.printf("Bool node changed to true");
  }
  else
  {
    Serial.printf("Bool node changed to false");
  }
  

	return true;
}

bool OnNodeValueChanged(void*_, Node *node)
{
  Serial.printf("'%s' node changed value to '%s'\n", node->name(), node->Value.toString().c_str());
	return true;
}

NodeValue RapidIgnitionFired(void* context, FunctionArguments &args)
{
	return NodeValue::String("Ignited");
}


void setup()
{
	Serial.begin(500000);

	auto debugNodes = new DebugNodesModule(thing);
	debugNodes->UpdateIntervalInMs = 1000;
	thing.AddModule(debugNodes);
	thing.WatchdogEnabled = true;

  thing.AddBoolean("bool")->OnChanged(OnNodeValueChanged);
  thing.AddFunction("Function", RapidIgnitionFired);
  thing.AddInt("integer", ContiUnit::Volt)->SetValue(NodeValue::Int(220));
  thing.AddRange("range", 10, 30, 2, ContiUnit::Percent)->OnChanged(OnNodeValueChanged);
  thing.AddColor("Color")->OnChanged(OnNodeValueChanged);
	thing.Start();
}



void loop()
{
	thing.Loop();
}
