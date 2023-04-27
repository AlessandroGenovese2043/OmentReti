packet DataPacket{
	simtime_t genTime; //generazione pacchetto
	//dato che stiamo trasmettendo un burst ci interessa sapere
	//qual è l'ultimo pacchetto
	bool lastBurstPacket = false;
	//lunghezza?
	//dobbiamo crearci un messaggio che contenga le informazioni
	//per i livelli sottostanti
};

message DataControlInfo{
    //name = "DataControlInfo";
  	string destination;  
};