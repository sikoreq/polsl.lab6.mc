
#include "Ferryboat.h"

Define_Module(Ferryboat);

Ferryboat::Ferryboat()
{
	ferryEndMsg = NULL;
}

Ferryboat::~Ferryboat()
{
	cancelAndDelete(ferryEndMsg);
}

void Ferryboat::initialize()
{
    getOnTime = par("getOnTime");
	maxPass = par("maxPassengers");
	noPass = 0;
	noLeftPass = 0;
	ferryState = 3;
	truncCT=par("truncCrossingTime");
	ferryEndMsg = new cMessage("ferry end of state");
	scheduleAt(0.0, ferryEndMsg);
	histA.setName("passengers from A");
	histA.setRange(0, maxPass+1);
	histB.setName("passengers from B");
	histB.setRange(0, maxPass+1);
	vectorNoPassA.setName("A->B");
	vectorNoPassB.setName("B->A");
	vectorNoLeftPassA.setName("Left A->B");
	vectorNoLeftPassB.setName("Left B->A");
}

void Ferryboat::handleMessage(cMessage *msg)
{
	if (msg == ferryEndMsg) // zmiana stanu promu (przyp³yniêcie, odp³yniêcie)
	{
		changeState( ferryEndMsg );
	}
	else // wejscie pasa¿erów
	{
	    MyMessage* mymsg = (MyMessage*) msg;

	    //jesli mamy miejsca do przyjmujemy pasazerow
	    if(mymsg->getNoPass()+noPass <= maxPass) {
	        noPass += mymsg->getNoPass();
	        noLeftPass = mymsg->getNoLeftPass();
	    }
	    else {
	        noPass = maxPass;
	        noLeftPass = mymsg->getNoLeftPass();
	    }

        if(noPass == maxPass) {
            // ODPLYWAMY!
            cancelEvent(ferryEndMsg);
            scheduleAt(simTime(), ferryEndMsg);
        }

        delete mymsg;
	}
}

void Ferryboat::finish()
{
    histA.record();
    histB.record();
//    FILE *f;
//    f=fopen("hist.dat","a");
//    histA.saveToFile(f);
//    histB.saveToFile(f);
//    fclose(f);
}

void Ferryboat::changeState(cMessage *msg)
{
	char buf[32];
	ferryState = (ferryState+1)%4;

	MyMessage* przyplyniecie;

	switch( ferryState ){
	case 0: //A
			if (ev.isGUI()) {
				getDisplayString().setTagArg("p",0,192);
				getDisplayString().setTagArg("t",0,"");
			}
			// do wype³nienia

			// zaplanowanie odplyniecia
			scheduleAt(simTime()+getOnTime, ferryEndMsg);

			noPass = 0;
			//przekazujemy informacje i ilosci wolnych miejsc na brzeg
			noLeftPass = maxPass;

			przyplyniecie = new MyMessage();
            //przyplyniecie->setNoPass(noPass);
            przyplyniecie->setNoLeftPass(maxPass);
			send(przyplyniecie, "ioA$o");

			break;
 	case 1: //A -> B
			if (ev.isGUI()) {
				getDisplayString().setTagArg("p",0,247);
				sprintf(buf,"--> pass: %ld", noPass);
				getDisplayString().setTagArg("t",0,buf);
			}

			// odplyniecie
			// zaplanowanie przyplyniecia
			scheduleAt(simTime()+truncCT + par("crossingTimeA"), ferryEndMsg);

			//Wysylamy informacje, ze nie ma juz wolnych miejsc (prom odplynal)
			przyplyniecie = new MyMessage();
            przyplyniecie->setNoPass(0);
            przyplyniecie->setNoLeftPass(0);
            send(przyplyniecie, "ioA$o");

            // statystyki
            histA.collect(noPass);
            vectorNoPassA.record(noPass);
            vectorNoLeftPassA.record(noLeftPass);

			break;
  	case 2: //B
			if (ev.isGUI()) {
				getDisplayString().setTagArg("p",0,302);
				getDisplayString().setTagArg("t",0,"");
			}
			// do wype³nienia

            // zaplanowanie odplyniecia
            scheduleAt(simTime()+getOnTime, ferryEndMsg);

            noPass = 0;
            //przekazujemy informacje i ilosci wolnych miejsc na brzeg
            noLeftPass = maxPass;

            przyplyniecie = new MyMessage();
            //przyplyniecie->setNoPass(noPass);
            przyplyniecie->setNoLeftPass(maxPass);
            send(przyplyniecie, "ioB$o");

			break;
 	case 3: //B -> A
			if (ev.isGUI()) {
				getDisplayString().setTagArg("p",0,247);
				sprintf(buf,"<-- pass: %ld", noPass);
				getDisplayString().setTagArg("t",0,buf);
			}
			// do wype³nienia

            // odplyniecie
            // zaplanowanie przyplyniecia
            scheduleAt(simTime()+truncCT + par("crossingTimeA"), ferryEndMsg);

            przyplyniecie = new MyMessage();
            przyplyniecie->setNoPass(0);
            przyplyniecie->setNoLeftPass(0);
            send(przyplyniecie, "ioB$o");

            // statystyki
            histB.collect(noPass);
            vectorNoPassB.record(noPass);
            vectorNoLeftPassB.record(noLeftPass);

			break;
	}
}
