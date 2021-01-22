#include <rtthread.h>
#include <rtdevice.h>
#include <drv_soft_i2c.h>
#include <stdint.h>
#include <stddef.h>
#define STS30_I2C_BUS_NAME          "i2c1"            /* 传感器连接的I2C总线设备名称 */
#define STS30_ADDR                   0x4A             /* 从机地址 */
#define CLOCK_STRETCHING             0X24             /*命令1*/
#define DATA_ACQUISITION_MODE        0X0b             /*命令2*/


void sts30_init(const char *name);

void i2c_sts30_sample(int argc, char *argv[]);

float read_temp(); 
