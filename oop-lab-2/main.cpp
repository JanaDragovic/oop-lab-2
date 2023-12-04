#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Config.h"
#include "EthernetFrame.h"

int* generateRandomBinaryArray(int length) {
    int* array = new int[length];
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 2;  // generiši 0 ili 1
    }
    return array;
}

int main() {

    //  slučajan binarni niz manji od 120 Kbita

    int length = rand() % (120 * 1024);  // 120 Kbita = 120 * 1024 bita
    int* randomBinaryArray = generateRandomBinaryArray(length);

    // Kreiraj objekat Config
    Config config;

    // Kreiraj objekat EthernetFrame koristeći objekat Config
    EthernetFrame frame1(config.getDestinationMACprint(), config.getSourceMACprint(), config.getDestinationMAC(), config.getSourceMAC(), config.getCRC());

    EthernetFrame frame2(frame1);
    // Učitaj binarni niz u EthernetFrame i formiraj Ethernet okvir
    frame2.setPayload(length, randomBinaryArray);
    frame2.addPadding();
    frame2.addCRC(frame2.getPayloadLength(), frame2.getPayload());
    frame2.printEthernetInfo(config);

    // Oslobodi memoriju alociranu za binarni niz
    delete[] randomBinaryArray;

    return 0;
}