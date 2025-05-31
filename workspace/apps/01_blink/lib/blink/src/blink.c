#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "blink.h"

int state = 0; // Global variable to track the LED statek
// Initialize the GPIO for the LED
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(my_led), gpios);

int init_gpio(void) {
    if (!gpio_is_ready_dt(&led)) {
        printf("LED GPIO is not ready\n");
        return 0;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret != 0) {
        printf("Failed to configure LED GPIO (err %d)\n", ret);
        return 0;
    }

    return 1;
}


void blink_led() {
    gpio_pin_set_dt(&led, state); // Turn on the LED
    state = !state;
	k_msleep(1000);   // Wait for 1 second before the next iteration
}

void say_hello(void) {
    printk("Hello\n");
}