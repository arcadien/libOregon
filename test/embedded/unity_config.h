#pragma once

#define UNITY_OUTPUT_CHAR(a)    Serial.print(a)
#define UNITY_OUTPUT_START()    Serial.begin(115200)
#define UNITY_OUTPUT_FLUSH()    RS232_flush()
#define UNITY_OUTPUT_COMPLETE()