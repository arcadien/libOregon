#include <arduino.h>
#include <unity.h>
#include <string.h>

#include <oregon.h>

class ArduinoHal : public Hal
{
public:
  ArduinoHal(volatile unsigned char *dataDirectionPort, volatile unsigned char *radioPort, uint8_t radioPin) : Hal(),
                                                                                                               _dataDirectionPort(dataDirectionPort),
                                                                                                               _radioPort(radioPort),
                                                                                                               _radioPin(radioPin)
  {
    *_dataDirectionPort |= (1 << _radioPin);
  }

  inline void reset()
  {
  }

  inline void rfHigh()
  {
    *_radioPort |= (1 << _radioPin);
  }

  inline void rfLow()
  {
    *_radioPort &= ~(1 << _radioPin);
  }

  inline void shortWait()
  {
    _delay_us(512);
  }

  inline void longWait()
  {
    _delay_us(1024);
  }

private:
  volatile unsigned char *_dataDirectionPort;
  volatile unsigned char *_radioPort;
  unsigned char _radioPin;
};

ArduinoHal testHal(&DDRH, &PORTH, 5);

Oregon oregon(testHal);
void setUp(void)
{
  testHal.reset();
}

void tearDown(void)
{
}

void expect_encoding_zero()
{
  TEST_MESSAGE("expect_encoding_zero()");
  oregon.sendZero();
}

void expect_encoding_one()
{
  TEST_MESSAGE("expect_encoding_one()");
  oregon.sendOne();
}

static bool BitRead(uint8_t value, uint8_t bit)
{
  return (((value) >> (bit)) & 0x01);
}

void SendMSB(const uint8_t data)
{
  (BitRead(data, 4)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 5)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 6)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 7)) ? oregon.sendOne() : oregon.sendZero();
}

void SendLSB(const uint8_t data)
{
  (BitRead(data, 0)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 1)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 2)) ? oregon.sendOne() : oregon.sendZero();
  (BitRead(data, 3)) ? oregon.sendOne() : oregon.sendZero();
}
void SendData(const char *data, uint8_t size)
{
  for (uint8_t i = 0; i < size; ++i)
  {
    SendLSB(data[i]);
    SendMSB(data[i]);
  }
}

void expect_sample_to_be_decoded()
{
  TEST_MESSAGE("expect_sample_to_be_decoded()");
  const char *sample = "FA2814A93022304443BE";
  SendData(sample, 20);

  // THGR228N, Id:72 ,Channel:1 ,temp:20.50 ,hum:78 ,bat:90
  SendData("1A2D1072512080E73F2C", 20);
}

int runManchesterEncodingTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(expect_encoding_zero);
  RUN_TEST(expect_encoding_one);
  RUN_TEST(expect_sample_to_be_decoded);

  return UNITY_END();
}

void setup()
{
  delay(2000);
  runManchesterEncodingTests();
}
void loop() {}