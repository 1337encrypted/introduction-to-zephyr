#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>

// Settings
static const int32_t sleep_time_ms = 100;

// Get Devicetree configurations
#define MY_ADC_CH DT_ALIAS(my_adc_channel)
static const struct device *adc = DEVICE_DT_GET(DT_ALIAS(my_adc));
static const struct adc_channel_cfg adc_ch = ADC_CHANNEL_CFG_DT(MY_ADC_CH);

int main(void)
{
    int ret;
    uint16_t buf;
    uint16_t val_mv;
    int32_t vref_mv;

    // Get Vref (mV) from Devicetree property
    vref_mv = DT_PROP(MY_ADC_CH, zephyr_vref_mv);

    // Buffer and options for ADC (defined in adc.h)
    struct adc_sequence seq = {
        .channels = BIT(adc_ch.channel_id),
        .buffer = &buf,
        .buffer_size = sizeof(buf),
        .resolution = DT_PROP(MY_ADC_CH, zephyr_resolution)
    };

    // Make sure that the ADC was initialized
    if (!device_is_ready(adc)) {
        printk("ADC peripheral is not ready\r\n");
        return 0;
    }

    // Configure ADC channel
    ret = adc_channel_setup(adc, &adc_ch);
    if (ret < 0) {
        printk("Could not set up ADC\r\n");
        return 0;
    }

    // Do forever
    while (1) {

        // Sample ADC
        ret = adc_read(adc, &seq);
        if (ret < 0) {
            printk("Could not read ADC: %d\r\n", ret);
            continue;
        }

        // Calculate ADC value (mV)
        val_mv = buf * vref_mv / (1 << seq.resolution);

        // Print ADC value
        printk("Raw: %u, mV: %u\r\n", buf, val_mv);

        // Sleep
        k_msleep(sleep_time_ms);
    }
}