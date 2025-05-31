#include <zephyr/random/random.h>

#ifdef CONFIG_SAY_HELLO
    #include "say_hello.h"
#endif

static int32_t sleep_ms = 1000; // Sleep duration in milliseconds

int main(void)
{
    uint32_t random_value; 
    double random_float;
    while (1)
    {
        random_value =  sys_rand32_get();
        random_float = (double)random_value / (UINT32_MAX + 1.0); // Convert to float in range [0, 1)
        printk("Random value: %.3f\r\n", random_float);

#ifdef CONFIG_SAY_HELLO
        say_hello();
#endif
        k_msleep(sleep_ms); 
    }
    return 0;
}