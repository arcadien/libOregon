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
    }

    inline void sendZero()
    {
    }

private:
    Hal *_hal;
};