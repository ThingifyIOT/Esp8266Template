#include <Arduino.h>
#include <ContiEsp.h>
#include <DebugNodesModule.h>

ContiEsp thing("<enter token>", "Sample Thing");

bool OnRelayValueChanged(void*_, Node *node)
{
	return true;
}

void setup()
{
	Serial.begin(500000);

	thing.AddAp("<wifi_name>", "<password>");

	auto debugNodes = new DebugNodesModule(thing);
	debugNodes->UpdateIntervalInMs = 1000;
	thing.AddModule(debugNodes);
	thing.WatchdogEnabled = true;

	thing.Start();
}



void loop()
{
	thing.Loop();
}
