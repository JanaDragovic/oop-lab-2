#include "Config.h"


Config::Config() {

	const char destinationMACprint[17] = { '0', '0', ':', '0', '0', ':', '5', 'e', ':', '0', '0', ':', '5', '3', ':', 'a', 'f' };
	const int destinationMAC[48] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1 };

	const char sourceMACprint[17] = { '0', '0', ':', '0', '0', ':', '5', 'e', ':', '0', '0', ':', '5', '3', ':', 'f', 'f' };
	const int sourceMAC[48] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	for (int i = 0; i < 17; i++) {
		this->destinationMACprint[i] = destinationMACprint[i];
		this->sourceMACprint[i] = sourceMACprint[i];
	}

	for (int i = 0; i < 48; i++) {
		this->destinationMAC[i] = destinationMAC[i];
		this->sourceMAC[i] = sourceMAC[i];
	}

	const int degree = 32;
	const int coefficients[33] = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1 };
	this->crc = CrcBlock(Polynomial(degree, coefficients));
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

   
