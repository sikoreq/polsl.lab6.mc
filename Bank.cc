
#include "Bank.h"

Define_Module(Bank);

Bank::Bank()
{
}

Bank::~Bank()
{
}

void Bank::initialize()
{
	noPassengers=0;
	maxPassengers=0;
}

void Bank::handleMessage(cMessage *msg)
{
	if (msg->arrivedOn("inS")) // przybycie pasa¿era
	{
		// do wype³nienia
	    delete msg;

        noPassengers += 1;
        sendPassengers();

	}
	else // przyp³yniêcie lub odp³yniêcie promu
	{
        maxPassengers = ((MyMessage*)msg)->getNoLeftPass();
        delete msg;

        sendPassengers();
		// do wype³nienia
	}
}

void Bank::sendPassengers() {
    if(noPassengers > 0) {
        if(maxPassengers > 0) {
            MyMessage* msg = new MyMessage();

            if(noPassengers > maxPassengers) {
                msg->setNoPass(maxPassengers);
                noPassengers -= maxPassengers;
                maxPassengers = 0;
            }
            else {
                msg->setNoPass(noPassengers);
                noPassengers = 0;
                maxPassengers -= noPassengers;
            }

            msg->setNoLeftPass(noPassengers);

            send(msg, "io$o");
        }
    }
}
