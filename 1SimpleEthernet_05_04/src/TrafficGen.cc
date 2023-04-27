//assegnare un nome al flusso che trasmettiamo
//perchè così possiamo calcolare le statistiche per nome

#include "TrafficGen.h"
#include "ApplicationPackets_m.h"
Define_Module(TrafficGen);

void TrafficGen::initialize()
{
    //eseguita appena parte il simulatore
    //si settano tutti i parametri + prima azione al tempo zero
    //vedere se start time è != da -1
    //i parametri si leggono con par
    simtime_t st = par("startTime");
    if( st >= 0){
        //è un nodo trasmettitore
        txTimer = new cMessage("TxTimer");
        //per inviare un messaggio usare send
        //per inviare un messaggio a se stesso
        scheduleAt(st, txTimer);
    }
    //else non facciamo niente
    //prendo un cMessage lo metto nella coda degli eventi
    //ogni evento ha un tempo per essere eseguito
    sigE2eDelay = registerSignal("sigE2eDelay");
    sigBurstE2eDelay = registerSignal("sigBurstE2eDelay");
    sigThroughput = registerSignal("Throughput");

    totBit = 0;
//il burst delay lo possiamo calcolare solo se
}

void TrafficGen::handleMessage(cMessage *msg)
{
//gestione eventi
//può arrivare l'evento autogenerato ovvero il timer
//gestiamo il timer
    //controllo se il messaggio è stato autogenerato
    if(msg -> isSelfMessage()){
        //possiamo avere più di un messaggio autogenerato
        if(strcmp(msg->getName(),"TxTimer") == 0){
            //quando scatta il timer si chiama il metodo per trasmettere pacchetti
            generate();
            //dobbiamo rischedulare il tempo del timer
            //al tempo di ora più il periodo
            scheduleAt(simTime() + par("period"), msg);
            return;
        }
    }
    //template
    DataPacket *pkt = dynamic_cast<DataPacket *>(msg);
    double delay = (simTime() - pkt->getGenTime()).dbl(); //delay singolo pacchetto
    // esprimio il delay come segnale
    emit(sigE2eDelay, delay);

    //calcolo throughput
    totBit += pkt->getBitLength();
    double thr = (double)totBit/simTime().dbl();
    emit(sigThroughput, thr);

    if(pkt->getLastBurstPacket()){
        //primo e ultimo vengono generati tutti insieme
        double delay = (simTime() - pkt->getGenTime()).dbl(); //delay singolo pacchetto
            // esprimio il delay come segnale
        emit(sigBurstE2eDelay, delay);
    }

    //ora che abbiamo finito bisogno distruggere il messaggio

    delete pkt;

}
void TrafficGen::generate(){
    //immaginando di usare i socket
    //oltre ai dati da trasmettere passiamo
    //ai livelli sottostanti altre informazioni
    //ad esempio l'indirizzo di destinazione
    //in omnett
    //definire il messaggio applicativo e
    //agganciare al messaggio applicativo le nuove informazioni
    DataPacket *pkt;
    DataControlInfo *ci;
    int i;
    int burst = par("burstSize");

    for(i=0; i< burst; i++){
        pkt = new DataPacket(par("flow").stringValue());
        //nel caso di stringhe par restituisce stringhe
        //mentre negli altri casi adatta il carattere(?)
        pkt->setGenTime(simTime());
        if(1 == (burst-1)){
            pkt->setLastBurstPacket(true);
        }
        pkt-> setByteLength(par("payloadLength"));
    }
    //per il controllo

    ci = new DataControlInfo();
    ci->setDestination(par("destination").stringValue());

    //aggiunta del pacchetto
    pkt->setControlInfo(ci);

    //dobbiamo inviarlo sotto
    send(pkt, "lowerLayerOut");






}
