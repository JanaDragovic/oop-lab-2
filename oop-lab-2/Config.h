#ifndef CONFIG_H
#define CONFIG_H

#include "CrcBlock.h"

class Config {
private: 

    char destinationMACprint[17];
    char sourceMACprint[17];
    int destinationMAC[48];
    int sourceMAC[48];
    CrcBlock crc;

    

public: 
	Config();
    char* getDestinationMACprint() const;
    char* getSourceMACprint() const;
    int* getDestinationMAC() const;
    int* getSourceMAC() const;
    CrcBlock& getCRC() const;

};












#endif 
