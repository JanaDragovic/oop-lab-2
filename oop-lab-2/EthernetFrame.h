#include "CrcBlock.h"

class EthernetFrame
{
    CrcBlock crc;
    int payloadLength;
    int* payload;
    int frameLength;
    char destinationMACprint[17];
    char sourceMACprint[17];
    int destinationMAC[48];
    int sourceMAC[48];
    int preamble[56];
    int sfd[8];

public:
    EthernetFrame(); // podrazumevani konstruktor
    EthernetFrame(char*, char*, int*, int*, CrcBlock&);
    EthernetFrame(EthernetFrame&);
    ~EthernetFrame();

};
