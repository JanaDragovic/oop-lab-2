#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Config.h"
#include "EthernetFrame.h"

int* generateRandomBinaryArray(int length) {
    int* array = new int[length];
    for (int i = 0; i < length; ++i) {
        array[i] = rand() % 2;  // generiši 0 ili 1
    }
    return array;
}

int main() {
    // Postavite seed za generisanje slučajnih brojeva
    srand(static_cast<unsigned int>(time(0)));

    // Kreiraj slučajan binarni niz manji od 120 Kbita
    int length = rand() % (120 * 1024);  // 120 Kbita = 120 * 1024 bita
    int* randomBinaryArray = generateRandomBinaryArray(length);

    // Kreiraj objekat Config
    Config config;
    config.printConfig();  // Možete dodati ovu liniju da proverite da li su podaci u config-u ispravno postavljeni

    // Kreiraj objekat EthernetFrame koristeći objekat Config
    EthernetFrame frame1(config.getDestinationMACprint(), config.getSourceMACprint(), config.getDestinationMAC(), config.getSourceMAC(), config.getCRC());

    // Učitaj binarni niz u EthernetFrame i formiraj Ethernet okvir
    frame1.setPayload(length, randomBinaryArray);
    frame1.addPadding();
    frame1.addCRC(frame1.getPayloadLength(), frame1.getPayload());
    frame1.printEthernetInfo();

    // Oslobodi memoriju alociranu za binarni niz
    delete[] randomBinaryArray;

    return 0;
}
