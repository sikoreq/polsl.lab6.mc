//
#include <omnetpp.h>
#include "mymessage_m.h"

/**
 * TODO - Generated class
 */
class Ferryboat : public cSimpleModule
{
private:
  long getOnTime;
  long noPass, noLeftPass, maxPass;
        int ferryState; //0 - A, 1 - z A do B, 2 - B, 3 - z B do A
        simtime_t truncCT;
        cLongHistogram histA, histB;
        cOutVector vectorNoPassA, vectorNoPassB;
        cOutVector vectorNoLeftPassA, vectorNoLeftPassB;

protected:
  cMessage *ferryEndMsg;//Message end of state

public:
  Ferryboat();
  virtual ~Ferryboat();

protected:
  virtual void initialize();
  virtual void finish();
  virtual void handleMessage(cMessage *msg);
  virtual void changeState(cMessage *msg);
  //virtual void changeCapacity(int capacity, const char *gatename);
  //virtual void getOnPass(cMessage *msg);
};
