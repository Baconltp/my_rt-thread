#include <oled.h>

u8g2_t _u8g2; // 显示屏句柄

void oled_power_on()
{
    rt_pin_write(OLED_PIN,PIN_LOW);
}

void oled_power_off()
{
    rt_pin_write(OLED_PIN,PIN_HIGH);
}

void oled_init(void)
{
    u8g2_t * dispHandle = get_disp_handel();    
    rt_pin_mode(OLED_PIN,PIN_MODE_OUTPUT);    
    oled_power_on();
    u8g2_Setup_ssd1306_i2c_128x32_univision_f(dispHandle, U8G2_R0, u8x8_byte_rt_hw_i2c, u8x8_rt_gpio_and_delay);
    u8g2_InitDisplay(dispHandle);
    u8g2_SetPowerSave(dispHandle, 0);
    u8g2_ClearBuffer(dispHandle);   
}

/*获取显示屏句柄, 给u8g2用的*/
u8g2_t * get_disp_handel(void)
{
    return &_u8g2;
}

void disp_log_page()
{
    u8g2_t * dispHandle = get_disp_handel();
    u8g2_ClearBuffer(dispHandle);

    u8g2_SetFont(dispHandle, u8g_font_7x14);
    u8g2_DrawStr(dispHandle, 1, 22, "U8g2 on RT-Thread");

    u8g2_SendBuffer(dispHandle);
    return;
}
MSH_CMD_EXPORT(disp_log_page, disp log page); 

void disp_temperature_page()
{
    float temperature = 0;
    char string[6]={0};
    temperature = read_temp();
    u8g2_t * dispHandle = get_disp_handel();
    float2char(temperature,string,6);
    u8g2_ClearBuffer(dispHandle);

    if((temperature <= 65) && (temperature >= 0))
    {
        u8g2_SetFont(dispHandle, u8g_font_6x13);
        u8g2_DrawStr(dispHandle, 1, 22, "Temperature:");
        u8g2_DrawStr(dispHandle, 78, 22, string);
    }
    else
    {
        rt_kprintf("temperature is out of range!\n");
    }
    
    

    u8g2_SendBuffer(dispHandle);
    return;
}
MSH_CMD_EXPORT(disp_temperature_page, disp temperature page); 

void float2char(float slope,char*buffer,int n)  //浮点型数，存储的字符数组，字符数组的长度
{
    int temp,i,j;
    if(slope>=0)//判断是否大于0
        buffer[0] = '+';
    else
    {
        buffer[0] = '-';
        slope = -slope;
    }
    temp = (int)slope;//取整数部分
    for(i=0;temp!=0;i++)//计算整数部分的位数
        temp /=10;
    temp =(int)slope;
    for(j=i;j>0;j--)//将整数部分转换成字符串型
    {
        buffer[j] = temp%10+'0';
        temp /=10;
    }
    buffer[i+1] = '.';
    slope -=(int)slope;
    for(i=i+2;i<n-1;i++)//将小数部分转换成字符串型
    {
        slope*=10;
        buffer[i]=(int)slope+'0';
        slope-=(int)slope;
    }
    buffer[n-1] = '\0';
}
