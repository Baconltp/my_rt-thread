#include <led.h>
#include <string.h>
void led_init(void)
{
    rt_pin_mode(led0_PIN,PIN_MODE_OUTPUT);
    rt_pin_mode(ledk1_PIN,PIN_MODE_OUTPUT);
    rt_pin_mode(ledk2_PIN,PIN_MODE_OUTPUT);
    rt_pin_write(led0_PIN, PIN_HIGH);
    rt_pin_write(ledk1_PIN, PIN_LOW);
    rt_pin_write(ledk2_PIN, PIN_LOW);
}

void led_on()
{
    rt_pin_write(led0_PIN, PIN_LOW);
}

void led_off()
{
    rt_pin_write(led0_PIN, PIN_HIGH);
}

void led_blink(rt_uint16_t time,char *led_id)
{
    if(strcmp("PC15",led_id)==0){
        rt_pin_write(led0_PIN, PIN_HIGH);
        rt_thread_mdelay(time);
        rt_pin_write(led0_PIN, PIN_LOW);
        rt_thread_mdelay(time);
    }
    else if(strcmp("K1",led_id)==0){
        rt_pin_write(ledk1_PIN, PIN_HIGH);
        rt_thread_mdelay(time);
        rt_pin_write(ledk1_PIN, PIN_LOW);
        rt_thread_mdelay(time);
    }
    else if(strcmp("K2",led_id)==0){
        rt_pin_write(ledk2_PIN, PIN_HIGH);
        rt_thread_mdelay(time);
        rt_pin_write(ledk2_PIN, PIN_LOW);
        rt_thread_mdelay(time);
    }
    else{
        rt_kprintf("Error:LED_ID not define");
    }
}
