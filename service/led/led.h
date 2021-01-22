#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtdbg.h>

#define led0_PIN GET_PIN(C, 15)

void led_init(void);

void led_on();

void led_off();

void led_blink(rt_uint16_t time);