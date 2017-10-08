# Functionality
This project was completed by getting the button to blink using timer interrupts. The clock for the timer was set, and the capture compare register was set and the interrupt was enabled. Because the timer is in up-mode, every time the timer reaches the value of the capture compare register, the LED toggles.

# Resources used
The resource explorer was used for the first couple projects to discover how to create the interrupts.

# Differences between boards
There were almost no differences between these boards. All timers worked nearly exactly the same in terms of the functionality required here. For most of the boards the code is exactly the same. The only exception is that the MSP430FR2311 only has a Timer B and needed to be named accordingly.

