#pragma once
#ifndef FSSERIAL_H
#define FSSERIAL_H

#include <Arduino.h>
// #include <M5Unified.h>

class BrySerial
{
public:
    BrySerial()
    {
    }
    ~BrySerial()
    {
    }
    bool CreateHeader(byte *head, String header, uint32_t size);
    void SendText(String str);
    void SendBin(String key, uint8_t *data, uint32_t size);
    bool compHeader(char *head, char *header);
};

#endif // FSSERIAL_H
