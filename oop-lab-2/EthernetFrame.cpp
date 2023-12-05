#include "EthernetFrame.h"


// podrazumevani konstruktor 
EthernetFrame::EthernetFrame() {

    // izvorisna i odredisna adresa inicijalizovane nulama 
    for (int i = 0; i < 48; i++) {
        destinationMAC[i] = 0;
        sourceMAC[i] = 0;
    }

    for (int i = 0; i < 17; i++) {
        destinationMACprint[i] = '0';
        sourceMACprint[i] = '0';
    }

    // crc inicijalizovan nula polinomom
    this->crc = CrcBlock(); 

    // prazno payload polje
    this->payloadLength = 0;
    this->payload = new int [0];
    this->frameLength = 0;


    // polje Preamble je fiksno za sve okvire i iznosi
    // 10101010 10101010 10101010 10101010 10101010 10101010 10101010
    for (int i = 0; i < 56; i++) {
        this->preamble[i] = i % 2 == 0 ? 1 : 0;
    }

    // polje SFD je fiksno i iznosi 10101011
    for (int i = 0; i < 8; i++) {
        this->sfd[i] = i % 2 == 0 ? 1 : 0;
    }
    sfd[7] = 1;
}

EthernetFrame::EthernetFrame(char* sourceMACprint, char* destinationMACprint, int* sourceMAC, int* destinationMAC, CrcBlock& crc) {

    // inicijalizacija odredisne i izvorisne MAC adrese prosledjenim objektom
    for (int i = 0; i < 48; i++) {
        this->destinationMAC[i] = destinationMAC[i];
        this->sourceMAC[i] = sourceMAC[i];
    }

    for (int i = 0; i < 17; i++) {
        this->destinationMACprint[i] = destinationMACprint[i];
        this->sourceMACprint[i] = sourceMACprint[i];
    }

    // inicijalizacija CRC polinoma prosledjenim objektom
    this->crc = CrcBlock(crc);

    // prazno payload polje
    this->payloadLength = 0;
    this->payload = new int[0];
    this->frameLength = 0;

    // fiksno preamble polje
    for (int i = 0; i < 56; i++) {
        this->preamble[i] = i % 2 == 0 ? 1 : 0;
    }
    
    // fiksno SFD polje
    for (int i = 0; i < 8; i++) {
        this->sfd[i] = i % 2 == 0 ? 1 : 0;
    }
    sfd[7] = 1;
}

// copy konstruktor
EthernetFrame::EthernetFrame(EthernetFrame& frame){

    // inicijalizja odredišne i izvorišne MAC adrese na osnovu drugog objekta
    for (int i = 0; i < 48; i++) {
        this->destinationMAC[i] = frame.destinationMAC[i];
        this->sourceMAC[i] = frame.sourceMAC[i];
    }

    for (int i = 0; i < 17; i++) {
        this->destinationMACprint[i] = frame.destinationMACprint[i];
        this->sourceMACprint[i] = frame.sourceMACprint[i];
    }

    // inicijalizacija CRC polinoma na osnovu drugog objekta
    this->crc = CrcBlock(frame.crc);

    // prazno payload polje
    this->payloadLength = 0;
    this->payload = new int[0];
    this->frameLength = 0;

    // fiksno preamble polje
    for (int i = 0; i < 56; i++) {
        this->preamble[i] = i % 2 == 0 ? 1 : 0;
    }

    // fiksno SFD polje
    for (int i = 0; i < 8; i++) {
        this->sfd[i] = i % 2 == 0 ? 1 : 0;
    }
    sfd[7] = 1;
}

// destruktor
EthernetFrame::~EthernetFrame()
{
    delete[] payload;
}


void EthernetFrame::setPayload(int payloadlength, int* payload) {

    if (this->payloadLength != 0) {
        delete[] payload;
    }
    else {

        this->payloadLength = payloadLength;
        this->payload = new int[payloadLength];

        for (int i = 0; i < payloadLength; i++) {
            this->payload[i] = payload[i];
        }

        frameLength = 8*26 + payloadLength;

    }
}

int* EthernetFrame::getFrame() {

    int* frame = new int[frameLength];
    int counter = 0;

    // dodavanje polja preamble
    for (int i = 0; i < 56; i++) {
        frame[counter] = preamble[i];
        counter++;
    }

    // dodavanje polja SFD
    for (int i = 0; i < 8; i++) {
        frame[counter] = sfd[i];
        counter++;
    }
    // dodavanje destinacione MAC adrese
    for (int i = 0; i < 48; i++) {
        frame[counter] = destinationMAC[i];
        counter++;
    }

    // dodavanje izvorisne MAC adrese
    for (int i = 0; i < 48; i++) {
        frame[counter] = sourceMAC[i];
        counter++;
    }

    // dodavanje polja length
    for (int i = 0; i < 16; i++) {
        frame[counter] = this->payloadLength / (int)pow(2, 15 - i);
        counter++;
    }

    // dodavanje polja payload
    for (int i = 0; i < payloadLength; i++) {
        frame[counter] = payload[i];
        counter++;
    }

    // dodavanje CRC-a
    int* crc = addCRC(payloadLength, payload);
    for (int i = 0; i < payloadLength; i++) {
        frame[counter] = crc[i];
        counter++;
    }

    return frame;
}
// funkcija koja racuna CRC dodatak
int* EthernetFrame::addCRC(int payloadLength, int* payload)
{
    return crc.encodeWord(payloadLength, payload);
}

void EthernetFrame::addPadding() {
    if (payloadLength < 46) {
        int* broadPayload = new int[46];
        for (int i = 0; i < payloadLength; i++) {
            broadPayload[i] = payload[i];
        } 

        for (int i = payloadLength; i < 46; i++) {
            broadPayload[i] = 0;
        }

        delete[] payload;
        payload = broadPayload;
        payloadLength = 46;
    
    }
    else {
        payloadLength = payloadLength;
    }
}

// funkcija koja proverava da li je CRC ispravno primljen
int EthernetFrame::checkCRC(int frameLength, int* frame)
{
    return crc.checkSum(frameLength, frame);
}

int EthernetFrame::getPayloadLength() {
    return this->payloadLength;
}

int* EthernetFrame::getPayload() {
    int* payloadtmp = new int[payloadLength];
    for (int i = 0; i < payloadLength; ++i) {
        payloadtmp[i] = payload[i];
    }
    return payloadtmp;
}

int EthernetFrame::getFrameLength() {
    return frameLength;
}

void EthernetFrame::printEthernetInfo(Config& config)  {
    std::cout << "Destination MAC address: " << config.getDestinationMACprint() << std::endl;
    std::cout << "Source MAC address: " << config.getSourceMACprint() << std::endl;
    std::cout << "Payload Length: " << payloadLength << " bytes" << std::endl;
    
}
