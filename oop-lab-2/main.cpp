#include <iostream>
#include <cstdlib>
#include "Config.h"
#include "EthernetFrame.h"

// funkcija za generisanje random binarnog niza
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

    // kreiranje objekta Config
    Config config;

    // kreiranje objekta klase EthernetFrame koristeći objekat Config
    EthernetFrame frame1(config.getDestinationMACprint(), config.getSourceMACprint(), config.getDestinationMAC(), config.getSourceMAC(), config.getCRC());

    EthernetFrame frame2(frame1);

    // ucitavanje binarnog niza u EthernetFrame i formiranje okvira
    frame2.setPayload(length, randomBinaryArray);
    frame2.addPadding();
    frame2.addCRC(frame2.getPayloadLength(), frame2.getPayload());

    int error = frame2.checkCRC(frame2.getPayloadLength(), frame2.getPayload());

    if (error == 0) {

        cout << "Error: " << error << endl;
        frame2.printEthernetInfo(config);
    }
    else {

        cout << "There is an error in given Ethernet Frame.";
    }

    // oslobadjanje memorije alociranu za binarni niz
    delete[] randomBinaryArray;

    return 0;
}