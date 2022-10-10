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
   
    void sendData(const unsigned char* data, uint8_t size)
    {
        
    }

private:
    Hal *_hal;
};