#include <unity.h>

#if defined(AVR)
#include <Arduino.h>
#endif

void setUp(void)
{
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