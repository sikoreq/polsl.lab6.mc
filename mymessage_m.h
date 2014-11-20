//
// Generated file, do not edit! Created by opp_msgc 4.5 from mymessage.msg.
//

#ifndef _MYMESSAGE_M_H_
#define _MYMESSAGE_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>mymessage.msg</tt> by opp_msgc.
 * <pre>
 * message MyMessage {
 *     int noPass;
 *     int noLeftPass;
 * };
 * </pre>
 */
class MyMessage : public ::cMessage
{
  protected:
    int noPass_var;
    int noLeftPass_var;

  private:
    void copy(const MyMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const MyMessage&);

  public:
    MyMessage(const char *name=NULL, int kind=0);
    MyMessage(const MyMessage& other);
    virtual ~MyMessage();
    MyMessage& operator=(const MyMessage& other);
    virtual MyMessage *dup() const {return new MyMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getNoPass() const;
    virtual void setNoPass(int noPass);
    virtual int getNoLeftPass() const;
    virtual void setNoLeftPass(int noLeftPass);
};

inline void doPacking(cCommBuffer *b, MyMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, MyMessage& obj) {obj.parsimUnpack(b);}


#endif // _MYMESSAGE_M_H_
