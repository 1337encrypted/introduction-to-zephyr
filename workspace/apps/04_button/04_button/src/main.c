#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

// Settings
static const int32_t sleep_ms = 100;
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(push_button), gpios);

int main(void) {
    int ret, state;
    
    if(!gpio_is_ready_dt(&button)) {
        printk("ERROR: Button device not ready\r\n");
        return -1;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if(ret < 0) {
        printk("ERROR: Failed to configure button pin %d\r\n", button.pin);
        return ret;
    }

    printk("Button spec flags: 0x%x\r\n", button.dt_flags);

    while(1) {
        state = gpio_pin_get_dt(&button);
        if(state < 0) {
            printk("ERROR: Failed to read button state\r\n");
            return state;
        } else {
            printk("Button state: %d\r\n", state);
        }
        k_msleep(sleep_ms);
    }
    return 0; 
}