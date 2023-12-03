#include "Config.h"

/*

U zasebnom fajlu kreirati konfiguracionu strukturu Config koja sadrži polja odredišne i
izvorišne MAC adrese u formi string podatka i u formi binarnog niza, kao i polinom CRC koda
zapisan preko binarnih koeficijenata. Za potrebe testiranja moguće je koristiti sledeće vrednosti:

odredišna MAC adresa: (string) 00:00:5e:00:53:af (binarno 0000 0000 0000 0000 0101 1110 0000 0000 0101 0011 1010 1111)
izvorišna MAC adresa: (string) 00:00:5e:00:53:ff (binarno 0000 0000 0000 0000 0101 1110 0000 0000 0101 0011 1111 1111)
polinom CRC koda: x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 (binarno 100000100110000010001110110110111).

*/

Config::Config()
{
    const char destinationMACprint[17] = { '0', '0', ':', '0', '0', ':', '5', 'e', ':', '0', '0', ':', '5', '3', ':', 'a', 'f' };
    const char sourceMACprint[17] = { '0', '0', ':', '0', '0', ':', '5', 'e', ':', '0', '0', ':', '5', '3', ':', 'f', 'f' };
    for (int i = 0; i < 17; i++)
    {
        this->destinationMACprint[i] = destinationMACprint[i];
        this->sourceMACprint[i] = sourceMACprint[i];
    }
    const int destinationMAC[48] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 0, 1, 1, 1, 1, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 1, 0, 1, 0, 0, 1, 1,
                                    1, 0, 1, 0, 1, 1, 1, 1 };
    const int sourceMAC[48] = { 0, 0, 0, 0, 0, 0, 0, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 1, 0, 1, 1, 1, 1, 0,
                               0, 0, 0, 0, 0, 0, 0, 0,
                               0, 1, 0, 1, 0, 0, 1, 1,
                               1, 1, 1, 1, 1, 1, 1, 1 };
    for (int i = 0; i < 48; i++)
    {
        this->destinationMAC[i] = destinationMAC[i];
        this->sourceMAC[i] = sourceMAC[i];
    }
    const int degree = 32;
    const int coeffs[33] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1,
                            0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
                            1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 };
    this->crc = CrcBlock(Polynomial(degree, coeffs));
}

char* Config::getDestinationMACprint() const
{
    return (char*)this->destinationMACprint;
}

char* Config::getSourceMACprint() const
{
    return (char*)this->sourceMACprint;
}

int* Config::getDestinationMAC() const
{
    return (int*)this->destinationMAC;
}

int* Config::getSourceMAC() const
{
    return (int*)this->sourceMAC;
}

CrcBlock& Config::getCRC() const
{
    return (CrcBlock&)this->crc;
}

void Config::printConfig() const
{
    cout << "Destination MAC address: ";
    for (int i = 0; i < 17; i++)
    {
        cout << this->destinationMACprint[i];
    }
    cout << endl;
    cout << "Destination MAC address (binary): ";
    for (int i = 0; i < 48; i++)
    {
        cout << this->destinationMAC[i];
    }
    cout << endl;
    cout << "Source MAC address: ";
    for (int i = 0; i < 17; i++)
    {
        cout << this->sourceMACprint[i];
    }
    cout << endl;
    cout << "Source MAC address (binary): ";
    for (int i = 0; i < 48; i++)
    {
        cout << this->sourceMAC[i];
    }
    cout << endl;
    cout << "CRC polynomial: ";
    this->crc.printCrcBlock();
    cout << endl;
}


