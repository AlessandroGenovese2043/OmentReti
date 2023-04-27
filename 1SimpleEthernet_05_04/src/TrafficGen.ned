

package simpleethernet_05_04;

//
// TODO auto-generated module
//
simple TrafficGen
{
    parameters:
    	@display("i=abstract/opticalswitch");
    	int payloadLength @unit(B); //unità di misura byte
    	//non abbiamo dato valore di default
    	volatile double period @unit(s);
    	//siccome vogliamo generare anche traffico aperiodico
    	//ogni volta che leggo un parametro cambia valore : volatile
    	string destination; 
    	//come mai uso una stringa e non i 6 byte dell'indirizzo MAC?
    	//A noi non cambia nulla, alla fine delle statistiche non cambia l'identificativo
    	double startTime @unit(s) = default(-1s);
    	//se start time uguale a -1 non generare traffico
    	int burstSize = default(1);
    	//1 frame alla volta
    	string flow; //nome del flusso
    	//impostati tutti i parametri imposto i gate
    	
    	@signal[E2eDelay];
    	@signal[BurstE2eDelay];
    	@signal[Throughput];
    	@statistic[E2eDelay];
    	@statistic[BurstE2eDelay];
    	@statistic[Throughput];
    	
    	//per vedere se tutto funziona è andare a crearci una nuova rete
    	gates:
    	    //comunicazione livello sottostante lower
    	    output lowerLayerOut;
    	    input lowerLayerIn;
    	    //abbiamo impostato tutto per il modulo semplice
    	    //dobbiamo implementare il comportamento 
    	
    	
    	
    	
}
