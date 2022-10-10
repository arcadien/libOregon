# LibOregon: embedded TDD

Environments:
* Native (we always need a native GCC environment)
* Arduino Mega 2560 (large flash, easy to program)
* VSCode/PlatformIO (No CMake this time)

# Install environments (step1)
Install VSCode, PlatformIO extension and Arduino USB drivers if needed.
Plug the Arduino and store its COM/tty port.
Create environment definition and stay *native* by default.

# The first test (step2)
Create a test which ensure **Unity** and both environment are working.
Native environment simply use standard output. The Arduino Mega communicates with the host
using its _Serial_ library using RS232 to USB port. All of this is abstracted by PlatformIO.
One choice for Arduino here is clear: no pain for communication with the embedded target. 

*Note*: Later, real target hardware will not have enough flash to load Unity and/or string messages and it will become more fun to test.

# Library implementation

Based on an [available specification](../doc/OregonScientific-RF-Protocols.pdf) and various code found on GitHub, begin the implementation of the library.

## 1. Bit encoding  (step3 and step4)
Bit encoding is the smallest information to be send. To allow testing on native and cross environment, a system HAL shall be implemented. Tests and implementation will be written for native environment (step3) then embedded (step4).

## 2. Byte encoding (step 5)
Bytes are sent MSB first. It means byte `0b01110001` shall be sent as `11101000`.