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

# Begin library implementation
Based on an available specification and various code found on GitHub, begin the implementation of the library.
* Manchester code using radio state coding (H, L) (step3)