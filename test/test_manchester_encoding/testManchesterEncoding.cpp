#include <unity.h>
#include <string.h>
#if defined(AVR)
#include <Arduino.h>
#endif

#include <oregon.h>

class TestHal : public Hal
{
public:
  TestHal() : Hal()
  {
    reset();
  }

  void reset()
  {
    radioOutputIndex = 0;
    memset(&radioOutput[0], 0, (128 / sizeof(int)));
  }

  void rfHigh()
  {
    radioOutput[radioOutputIndex] = 'H';
    radioOutputIndex++;
  }
  void rfLow()
  {
    radioOutput[radioOutputIndex] = 'L';
    radioOutputIndex++;
  }

  void shortWait()
  {
    radioOutput[radioOutputIndex] = 'S';
    radioOutputIndex++;
  }

  void longWait()
  {
    radioOutput[radioOutputIndex] = 'W';
    radioOutputIndex++;
  }

  char radioOutput[128];

private:
  uint8_t radioOutputIndex;
};

TestHal testHal;

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
  TEST_FAIL_MESSAGE("not implemented");
}
void expect_encoding_one()
{
  TEST_FAIL_MESSAGE("not implemented");
}
int runManchesterEncodingTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(expect_encoding_zero);
  RUN_TEST(expect_encoding_one);
  return UNITY_END();
}

#if defined(AVR)
/**
 * For Arduino framework
 */
void setup()
{
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runManchesterEncodingTests();
}
void loop() {}

#else
int main(void)
{
  return runManchesterEncodingTests();
}
#endif