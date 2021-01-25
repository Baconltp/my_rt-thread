#include <sts30.h>

static struct rt_i2c_bus_device *i2c_bus = RT_NULL; 
static rt_bool_t initialized = RT_FALSE;               

static rt_err_t write_reg(struct rt_i2c_bus_device *bus, rt_uint8_t *data)
{
    rt_uint8_t buf[2];
    struct rt_i2c_msg msgs;

    buf[0] = data[0];
    buf[1] = data[1];

    msgs.addr = STS30_ADDR;
    msgs.flags = RT_I2C_WR;
    msgs.buf = buf;
    msgs.len = 2;

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &msgs, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        rt_kprintf("write error\ntemp[0]:0x%02x\ntemp[1]:0x%02x\ntemp[2]:0x%02x\n",buf[0],buf[1],buf[2]);
        return -RT_ERROR;
    }
}

static rt_err_t read_regs(struct rt_i2c_bus_device *bus, rt_uint8_t len, rt_uint8_t *buf)
{
    struct rt_i2c_msg msgs[2];
    struct rt_i2c_msg rev;
	rt_uint8_t reg[2] = {CLOCK_STRETCHING,DATA_ACQUISITION_MODE};

    msgs[0].addr = STS30_ADDR;
    msgs[0].flags = RT_I2C_WR;
    msgs[0].buf = reg;
    msgs[0].len = 2;

    msgs[1].addr = STS30_ADDR;
    msgs[1].flags = RT_I2C_RD;
    msgs[1].buf = 0;
    msgs[1].len = 0;

    rev.addr = STS30_ADDR;
    rev.flags = RT_I2C_RD;
    rev.buf = buf;
    rev.len = len;

    rt_i2c_transfer(bus, msgs, 2);
    rt_thread_mdelay(20);

    /* 调用I2C设备接口传输数据 */
    if (rt_i2c_transfer(bus, &rev, 1) == 1)
    {
        return RT_EOK;
    }
    else
    {
        return -RT_ERROR;
    }
}


float read_temp()
{
    float cur_temp = 0;
    rt_uint8_t temp[3];
    if(read_regs(i2c_bus, 3, temp)!=-1)
    {
        /* 温度数据转换 */
        cur_temp = ( ( (temp[0]<<8) | temp[1]))*175.0 / 65535 - 45;
    }       
    else
    {
        rt_kprintf("Read Temperature Error\n");
        rt_kprintf("temp[0]:0x%02x\ntemp[1]:0x%02x\ntemp[2]:0x%02x\n",temp[0],temp[1],temp[2]);
    }   
    return cur_temp; 
}

void sts30_init(const char *name)
{
    rt_uint8_t temp[2] = {0, 0};

    /* 查找I2C总线设备，获取I2C总线设备句柄 */
    i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(name);

    if (i2c_bus == RT_NULL)
    {
        rt_kprintf("can't find %s device!\n", name);
    }
    else
    {
        temp[0]=CLOCK_STRETCHING;
        temp[1]=DATA_ACQUISITION_MODE;
        write_reg(i2c_bus, temp);
        rt_thread_mdelay(2);

        initialized = RT_TRUE;
    }
}


void i2c_sts30_sample(int argc, char *argv[])
{
    float temperature;
    char name[RT_NAME_MAX];

    temperature = 0.0;

    if (argc == 2)
    {
        rt_strncpy(name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(name, STS30_I2C_BUS_NAME, RT_NAME_MAX);
    }

    if (!initialized)
    {
        /* 传感器初始化 */
        sts30_init(name);
    }
    if (initialized)
    {
        /* 读取温湿度数据 */
        temperature = read_temp();

        if( temperature >= 0 )
        {
            rt_kprintf("read sts30 sensor temperature: %d.%d°C\n", (int)temperature, (int)(temperature * 10) % 10);
        }
        else
        {
            rt_kprintf("read sts30 sensor temperature: %d.%d°C\n", (int)temperature, (int)(-temperature * 10) % 10);
        }
    }
    else
    {
        rt_kprintf("initialize sensor failed!\n");
    }
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(i2c_sts30_sample, i2c sts30 sample);
