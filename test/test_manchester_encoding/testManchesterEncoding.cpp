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

static const uint8_t CHAR_COUNT_FOR_A_BIT = 6;

static const unsigned char
    EXPECTED_ORDERS_FOR_ZERO[CHAR_COUNT_FOR_A_BIT] = {'H', 'S', 'L', 'W', 'H', 'S'};

static const unsigned char
    EXPECTED_ORDERS_FOR_ONE[CHAR_COUNT_FOR_A_BIT] = {'L', 'S', 'H', 'W', 'L', 'S'};

void expect_encoding_zero()
{
  oregon.sendZero();
  TEST_ASSERT_EQUAL_CHAR_ARRAY(EXPECTED_ORDERS_FOR_ZERO, testHal.radioOutput, CHAR_COUNT_FOR_A_BIT);
}
void expect_encoding_one()
{
  oregon.sendOne();
  TEST_ASSERT_EQUAL_CHAR_ARRAY(EXPECTED_ORDERS_FOR_ONE, testHal.radioOutput, CHAR_COUNT_FOR_A_BIT);
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