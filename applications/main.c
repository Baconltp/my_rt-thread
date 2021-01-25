#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtdbg.h>
#include <sts30.h>
#include <led.h>
#include <oled.h>
#define DBG_TAG "main"
#define DBG_LVL DBG_LOG

static void thread1_entry(void *parameter)
{
    while (1)
    {
        disp_temperature_page();
        rt_thread_mdelay(100);
    }
}
static void thread2_entry(void *parameter)
{
    while (1)
    {
        led_blink(500,"PC15");
        rt_thread_mdelay(100);

    }
}
int main(void)
{
    rt_thread_t tid1,tid2 = RT_NULL;
    led_init();
    sts30_init(STS30_I2C_BUS_NAME);
    oled_init();

    tid1 = rt_thread_create("thread1",
                                thread1_entry, RT_NULL,
                                2048,
                                25, 5);
    if (tid1 != RT_NULL)
        rt_thread_startup(tid1);

    tid2 = rt_thread_create("thread2",
                                thread2_entry, RT_NULL,
                                512,
                                20, 10);
    if (tid2 != RT_NULL)
        rt_thread_startup(tid2);

        /*
            led_init();
            oled_init();
            sts30_init(STS30_I2C_BUS_NAME);
            while(1)
            {
                disp_temperature_page();
                rt_thread_mdelay(100);
            }
            return RT_EOK;
        */
}

