
#include "Source.h"

Define_Module(Source);

Source::Source()
{
	sendMessageEvent = NULL;
}

Source::~Source()
{
	cancelAndDelete(sendMessageEvent);
}

void Source::initialize()
{
	sendMessageEvent = new cMessage("sendMessageEvent");
	scheduleAt(0.0, sendMessageEvent);
}

void Source::handleMessage(cMessage *msg)
{
	ASSERT(msg==sendMessageEvent);

	cMessage *m = new cMessage("passenger");
	send(m, "out");

	scheduleAt(simTime()+par("sendIaTime"), sendMessageEvent);
}
