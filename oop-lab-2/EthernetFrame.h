#include "CrcBlock.h"
#include "Config.h"

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
    EthernetFrame(); 
    EthernetFrame(char*, char*, int*, int*, CrcBlock&); 
    EthernetFrame(EthernetFrame&); 
    ~EthernetFrame(); 

    void setPayload(int, int*);
    int* getFrame();
    int* addCRC(int, int*);
    void addPadding();
    int checkCRC(int, int*);
    void printEthernetInfo(Config&);

    int getPayloadLength();
    int* getPayload();
    int getFrameLength();

};
