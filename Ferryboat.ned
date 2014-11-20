//
//
//
simple Ferryboat
{
    parameters:
        volatile double getOnTime @unit(s); //czas wsiadania
        volatile double truncCrossingTime @unit(s); //minimalny czas trwania przeprawy
        volatile double crossingTimeA @unit(s); //dodatkowy czas trwania przeprawy
        int maxPassengers; //liczba miejsc na promie
        @display("i=block/transport");
    gates:
        inout ioA; //brama we/wy. z A
        inout ioB; //brama we/wy. z B
}
