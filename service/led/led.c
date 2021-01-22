#include <led.h>

void led_init(void)
{
    rt_pin_mode(led0_PIN,PIN_MODE_OUTPUT);
}

void led_on()
{
    rt_pin_write(led0_PIN, PIN_HIGH);
}

void led_off()
{
    rt_pin_write(led0_PIN, PIN_HIGH);
}

void led_blink(rt_uint16_t time)
{
    rt_pin_write(led0_PIN, PIN_HIGH);
    rt_thread_mdelay(time);
    rt_pin_write(led0_PIN, PIN_LOW);
    rt_thread_mdelay(time);
}