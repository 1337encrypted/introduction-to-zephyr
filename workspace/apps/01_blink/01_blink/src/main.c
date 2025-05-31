#include "blink.h"

int main(void)
{

	init_gpio();

	// Do forever
	while (1) {
		blink_led(1, 500); // Blink the LED once with a 500 ms delay
		say_hello();       // Print "Hello" to the console
	}

	return 0;
}
