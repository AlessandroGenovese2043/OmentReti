
#ifndef __SIMPLEETHERNET_05_04_TRAFFICGEN_H_
#define __SIMPLEETHERNET_05_04_TRAFFICGEN_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class TrafficGen : public cSimpleModule
{
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    //per trasmettere l'intero burst di dati
    virtual void generate();

    //ci serve un timer
    cMessage *txTimer;

    simsignal_t sigE2eDelay;//frame
    simsignal_t sigBurstE2eDelay; //burst
    simsignal_t sigThroughput;

    uint64_t totBit; //controllo sul numero di bit
    //unsigned int a 64 bit
};

#endif
