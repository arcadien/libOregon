
#if !defined(AVR)
#include <unity.h>
#include <string.h>
#include <oregon.h>
#include <sharedConstants.h>
#include <NativeHal.h>

NativeHal testHal;

Oregon oregon(testHal);

void setUp(void)
{
  testHal.reset();
}

void tearDown(void)
{
}

void expect_msb_to_be_sent_first()
{
  static const unsigned char *EXPECTED_ORDERS[][CHAR_COUNT_FOR_A_BIT] = {
      EXPECTED_ORDERS_FOR_ONE,
      EXPECTED_ORDERS_FOR_ONE,
      EXPECTED_ORDERS_FOR_ONE,
      EXPECTED_ORDERS_FOR_ZERO,
      EXPECTED_ORDERS_FOR_ONE,
      EXPECTED_ORDERS_FOR_ZERO,
      EXPECTED_ORDERS_FOR_ZERO,
      EXPECTED_ORDERS_FOR_ZERO};

  const unsigned char data[] = {0b01110001};
  oregon.sendData(data, 1);
  TEST_ASSERT_EQUAL_CHAR_ARRAY(EXPECTED_ORDERS, testHal.radioOutput, 8 * CHAR_COUNT_FOR_A_BIT);
}

int runtestByteMsbFirstTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(expect_msb_to_be_sent_first);
  return UNITY_END();
}

int main(void)
{
  return runtestByteMsbFirstTests();
}
#endif