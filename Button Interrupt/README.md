# Functionality
This code works by using a Port interrupt to toggle an LED. The port which was attached to the button was configured with pullup resistors. Then the port interrupts were enabled. An infinite loop was created and the ISR was created to toggle the LED. 

# Resources used
The resource explorer was used to figure out how to configure Port interrupts, and how to create service routines. 

# Difficulties
Figuring out how to configure the Port for interrupts proved to be difficult. Additionally, discovering that interrupt flags needed to be cleared took time.

# Differences between boards
The only differences that appeared between boards was which port was attached to the button on the launchpad. 


