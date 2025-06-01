#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

// Settings
static const int32_t sleep_ms = 100;
static const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(DT_ALIAS(push_button1), gpios);
static const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(DT_ALIAS(push_button2), gpios);
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(yellow_led), gpios);

int main(void) {
    int ret, state1, state2;
    
    if(!gpio_is_ready_dt(&button1) || !gpio_is_ready_dt(&button2)) {
        printk("ERROR: Button device not ready\r\n");
        return -1;
    }

    if(!gpio_is_ready_dt(&led)) {
        printk("ERROR: LED device not ready\r\n");
        return -1;
    }

    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
    ret |= gpio_pin_configure_dt(&button2, GPIO_INPUT);
    ret |= gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);

    if(ret < 0) {
        printk("ERROR: Failed to configure GPIO pins\r\n");
        return ret;
    }

    printk("GPIO pins configured successfully\r\n");

    while(1) {
        state1 = gpio_pin_get_dt(&button1);
        state2 = gpio_pin_get_dt(&button2);

        if(state1 < 0 || state2 < 0) {
            printk("ERROR: Failed to read button state\r\n");
            return state1 | state2;
        } else {
            gpio_pin_set_dt(&led, state1 || state2);
        }
        k_msleep(sleep_ms);
    }
    return 0; 
}