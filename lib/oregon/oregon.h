#pragma once

class Hal
{
public:
    virtual void rfHigh() = 0;
    virtual void rfLow() = 0;
    virtual void shortWait() = 0;
    virtual void longWait() = 0;
};

class Oregon
{
public:
    Oregon(Hal &hal) : _hal(&hal) {}

    inline void sendOne()
    {
        _hal->rfLow();
        _hal->shortWait();
        _hal->rfHigh();
        _hal->longWait();
        _hal->rfLow();
        _hal->shortWait();
    }

    inline void sendZero()
    {
        _hal->rfHigh();
        _hal->shortWait();
        _hal->rfLow();
        _hal->longWait();
        _hal->rfHigh();
        _hal->shortWait();
    }

    void sendData(const uint8_t *data, uint8_t size)
    {
        for (uint8_t i = 0; i < size; i++)
        {
            sendMSB(data[i]);
            sendLSB(data[i]);
        }
    }

private:
#ifndef bitread
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif
    void sendMSB(uint8_t data)
    {
        (bitRead(data, 4)) ? sendOne() : sendZero();
        (bitRead(data, 5)) ? sendOne() : sendZero();
        (bitRead(data, 6)) ? sendOne() : sendZero();
        (bitRead(data, 7)) ? sendOne() : sendZero();
    }

    void sendLSB(uint8_t data)
    {
        (bitRead(data, 0)) ? sendOne() : sendZero();
        (bitRead(data, 1)) ? sendOne() : sendZero();
        (bitRead(data, 2)) ? sendOne() : sendZero();
        (bitRead(data, 3)) ? sendOne() : sendZero();
    }

    Hal *_hal;
};