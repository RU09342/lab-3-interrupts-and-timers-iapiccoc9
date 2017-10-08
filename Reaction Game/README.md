# Functionality
Two buttons were configured with pullup resistors. Then, the red LED blinks 12 times. It then stops blinking for a short period of time. When the button turns back on, the next person to press then button wins. In each button press ISR there are two scenarios. If the button is pressed before the button turns back on, and the "test" register is set, then the opposite player wins, because the button was pressed too early. This is symbolized by the LED closer to the other players button blinking continuously. The second scenario is when the button is pressed after the LED blinks and the test register is set. The button closer to the button that was pressed blinks continuously. These scanrios account for the button being pressed before and after the LED turns on to prevent cheating.

# Diffiulties

The main difficulty for this project was figuring out how to prevent players from cheating. This was eventually achieved by setting a register at the point when the button should be pressed and checking this register in the ISR. 

# Known Errors

This game cannot be played more than one time without using the Hard Reset button located on the launchpad. 

# Resources used

There were no outside resources used for this project and only from previous knowledge.