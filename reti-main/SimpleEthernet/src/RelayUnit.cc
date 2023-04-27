#include "RelayUnit.h"

Define_Module(RelayUnit);

void RelayUnit::initialize()
{
    //dobbiamo implementare la tabella di relay contenuta nello switch
    //(ad ogni destinazione corrisponde un indice della porta o da dove e' arrivata o da dove la dobbiamo trasmettere)
    // --> FATTO NEL FILE .h

    StaticRelayEntries *te = check_and_cast<StaticRelayEntries *>par("staticEntries").objectValue();
    for(int i = 0; i < te->getEntriesArraySize(); i++){
       RelayTableEntry rte = te->getEntries(i);
       RelayTableEntry *nrte = new RelayTableEntry;
       nrte->addr = rte.addr;
       nrt->port = rte.port;
       nrte->staticEntry= true;
       nrte->updateTime = simTime();
       relayTable.push_back(nrte);

    }
}

void RelayUnit::handleMessage(cMessage *msg)
{
    int idx = msg->getArrivalGate()->getIndex();
    EthernetFrame *frame = check_and_cast<EthernetFrame *>(msg);

    updateTableEntry(idx, frame->getSrc());
    int didx = getPortFromAddr(frame->getDist));
    if(didx <0){//restituisce -1 se non abbiamo entry nella tabella e quindi la inviamo a tutti tranne a quello che l'ha inviata-> broadcast
        for(int i = 0; i<gate("lowerLayerOut")->size();i++){
            if(i!=idx){
            send(frame->dup(), "lowerLayerOut",i);
            }
        }
        delete frame;
        return;
    }
    send(frame,"lowerLayerOut", didx);

}

int RelayUnit::getPortFromAddr(const char* addr) {
    for(int i=0; i <relayTable.size(); i++) {
        if (strcmp(addr,relayTable[i]->addr.c_str()) == 0) {
            return relayTable[i]->port;
        }
    }
    return -1; //la porta cercata non c'e' (non c'e' la corrispondenza indirizzo-porta, cioe' la entry nella tabella)
}

void RelayUnit::updateTableEntry(int port, const char* addr) {
    int p = getPortFromAddr(addr);
    if (p < 0) { //se non abbiamo trovato l'entry, la dobbiamo aggiungere
        table_entry_t* entry = new table_entry_t;
        entry->addr = std::string(addr);
        entry->port = port;
        entry->updateTime = simTime();
        entry->staticEntry = false;
        relayTable.push_back(entry);
        return;
    }

    //abbiamo trovato l'entry: dobbiamo aggiornarla, se non statica
    for(int i=0; i <relayTable.size(); i++) {
        if (strcmp(addr,relayTable[i]->addr.c_str()) == 0) {
            if(!relayTable[i].staticEntry)
                relayTable[i]->port = port;
                relayTable[i]->updateTime = SimTime();
            }
        }
    }
}
