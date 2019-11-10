#include <Arduino.h>
#include <ThingifyEsp.h>
#include <DebugNodesModule.h>

ThingifyEsp thing("<token>", "Sample Thing");


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

NodeValue FunctionExecuted(void* context, FunctionArguments &args)
{
	return NodeValue::String("Hello from function!");
}


void setup()
{
	Serial.begin(500000);

	auto debugNodes = new DebugNodesModule(thing);
	debugNodes->UpdateIntervalInMs = 1000;
	thing.AddModule(debugNodes);
	thing.WatchdogEnabled = true;

  thing.AddBoolean("bool")->OnChanged(OnNodeValueChanged);
  thing.AddFunction("Function", FunctionExecuted);
  thing.AddInt("integer", ThingifyUnit::Volt)->SetValue(NodeValue::Int(220));
  thing.AddRange("range", 10, 30, 2, ThingifyUnit::Percent)->OnChanged(OnNodeValueChanged);
  thing.AddColor("Color")->OnChanged(OnNodeValueChanged);
	thing.Start();
}



void loop()
{
	thing.Loop();
}
