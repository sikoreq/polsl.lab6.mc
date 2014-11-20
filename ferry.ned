network ferry
{
    parameters:
        @display("bgb=504,100");
    submodules:
        genA: Source {
            parameters:
                @display("p=35,48");
        }
        genB: Source {
            parameters:
                @display("p=454,48");
        }
        bankA: Bank {
            parameters:
                @display("p=115,48");
        }
        bankB: Bank {
            parameters:
                @display("p=379,48");
        }
        ferryboat: Ferryboat {
            parameters:
                @display("i=block/transport_l;p=245,48");
        }
    connections:
        genA.out --> bankA.inS;
        genB.out --> bankB.inS;
        bankA.io <--> ferryboat.ioA;
        bankB.io <--> ferryboat.ioB;
}
