
#ifndef __FERRY_BANK_H_
#define __FERRY_BANK_H_

#include <omnetpp.h>
#include "mymessage_m.h"

/**
 * TODO - Generated class
 */
class Bank : public cSimpleModule
{
  private:
    long noPassengers, maxPassengers;

  public:
    Bank();
    virtual ~Bank();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void sendPassengers();
};

#endif
