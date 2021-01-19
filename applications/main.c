/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-19     RT-Thread    first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <u8g2.h>
#include "u8g2_port.h"
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>
#define LED0_PIN GET_PIN(C, 15)
#define OLED_PIN GET_PIN(B,5)

int main(void)
{
    u8g2_t u8g2;
    rt_pin_mode(OLED_PIN,PIN_MODE_OUTPUT);
    rt_pin_write(OLED_PIN,PIN_LOW);

    u8g2_Setup_ssd1306_i2c_128x32_univision_f(&u8g2, U8G2_R0, u8x8_byte_rt_hw_i2c, u8x8_rt_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g_font_7x14);
    u8g2_DrawStr(&u8g2, 1, 22, "U8g2 on RT-Thread");
    u8g2_SendBuffer(&u8g2);

    while (1)
    {
        rt_pin_write(LED0_PIN, PIN_HIGH);
        rt_thread_mdelay(500);
        rt_pin_write(LED0_PIN, PIN_LOW);
        rt_thread_mdelay(500);
    }

}
