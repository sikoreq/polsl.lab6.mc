
#ifndef __FERRY_SOURCE_H_
#define __FERRY_SOURCE_H_

#include <omnetpp.h>

/**
 * TODO - Generated class
 */
class Source : public cSimpleModule
{
  private:
    cMessage *sendMessageEvent;

  public:
     Source();
     virtual ~Source();

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
