

package simpleethernet_05_04.simulations;

import simpleethernet_05_04.TrafficGen;


network SimpleEthernetNet
{
    @display("bgb=607,215");
    submodules:
        tg1: TrafficGen {
            @display("p=55,77");
        }
        tg2: TrafficGen {
            @display("p=443,72");
        }
    connections:
        tg1.lowerLayerOut --> tg2.lowerLayerIn;
        tg2.lowerLayerOut --> tg1.lowerLayerIn;
}
