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
#include <rtdbg.h>
#include <sts30.h>
#include <led.h>
#include <oled.h>

#define DBG_TAG "main"
#define DBG_LVL DBG_LOG

int main(void)
{
    led_init();
    oled_init();
    sts30_init("i2c1");
    while (1)
    {
        led_blink(500);//500ms
        disp_temperature_page();
    }

}

