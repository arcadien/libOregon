#include <Arduino.h>
#include <unity.h>

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

void setup()
{
  delay(1000);
  runUnityTests();
}
void loop() {}