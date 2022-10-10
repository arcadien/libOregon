
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

int main(void)
{
  return runManchesterEncodingTests();
}
#endif