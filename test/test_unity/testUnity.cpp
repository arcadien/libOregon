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

void expect_unity_to_run()
{
  TEST_MESSAGE("Unity is working");
}

int runUnityTests(void)
{
  UNITY_BEGIN();
  RUN_TEST(expect_unity_to_run);
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

  runUnityTests();
}
void loop() {}
#else
int main(void)
{
  return runUnityTests();
}
#endif