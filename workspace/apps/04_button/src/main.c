#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include "button.h"

// Settings
static const int32_t sleep_ms = 100;
static const struct device *button1 = DEVICE_DT_GET(DT_ALIAS(push_button1));
static const struct device *button2 = DEVICE_DT_GET(DT_ALIAS(push_button2));
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(yellow_led), gpios);

int main(void) {
    uint8_t ret, state1, state2;
    
    if(!device_is_ready(button1) || !device_is_ready(button2)) {
        printk("ERROR: Button device not ready\r\n");
        return -1;
    }

    if(!gpio_is_ready_dt(&led)) {
        printk("ERROR: LED device not ready\r\n");
        return -1;
    }

    // Get the API from one of the buttons
    const struct button_api *btn_api1 = (const struct button_api *)button1->api;
    const struct button_api *btn_api2 = (const struct button_api *)button2->api;

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if(ret < 0) {
        printk("ERROR: Failed to configure led\r\n");
        return ret;
    }
    
    while (1) {
        ret = btn_api1->get(button1, &state1);
        ret |= btn_api2->get(button2, &state2);

        if(ret < 0) {
            printk("ERROR: Failed to read button state\r\n");
            continue;
        }

        gpio_pin_set_dt(&led, state1 || state2);
        k_msleep(sleep_ms);
    }
    return 0; 
}