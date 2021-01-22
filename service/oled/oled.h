#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtdbg.h>
#include <u8g2.h>
#include "u8g2_port.h"
#include <sts30.h>

#define OLED_PIN GET_PIN(B,5)

void oled_init(void);

void oled_power_on();

void oled_power_off();

u8g2_t * get_disp_handel(void);

void disp_log_page();

void disp_temperature_page();

void float2char(float slope,char*buffer,int n);  //浮点型数，存储的字符数组，字符数组的长度