# Functionality
This code works by running an LED at 10 HZ. The user can then press an button down and the time the button was pressed is now the new time the button will be on when it toggles. This works by setting up the timer to up-mode, with the SMCLK/8. The CCR0 register was initialized to 12500 for 10HZ. The timer then blinks continuously. When the button is pressed it goes into an ISR for the port. There are two sections to the Port ISR. One when the button is pressed, and one for when the button is released. The edge detect is initially set to falling edge to detect when the button is pressed. Therefore the "button oressed" section of the ISR runs first. The edge detect is toggled to catch the rising edge or button release. The timer is cleared and set to conitnuous mode, and the flag is cleared. Then when the button is realeased it will go back into the service routine and service the "Button released section. In this part it will flip the edge detect back to falling edge. The timer is set back to up mode for correct LED toggling. The value of the timer is set to be the new CCR0 to set the new LED timing. And the flag is cleared. The button will then blink at the new rate given by the button until the button is pressed again.

# Difficulties
The difficult parts of this project proved to be figuring out that the timer should be in continuous mode when trying the capture the button press timing. If it isn't, the timing can never be greater than the set value for CCR0, because if it the timer will have already rolled over. Putting the timer into continuous mode allows the new timing to be up to 0xffff, the full timer value.

# Known errors
The only known "error" is that this project could be done with the capture functionality of the timer. However this lab was completed before that functionality was known.

# Differences between boards
The only differences between boards were port names and timer names. Other than that the code was simply copied and pasted.
