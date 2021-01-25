#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <u8g2_port.h>

typedef struct
{
    int x; // 起始坐标
    int y;
    int w; // 宽
    int h; // 高
    unsigned char * pictureData; // Pointer to picture data
}GUI_BITMAP;

extern GUI_BITMAP bmp_degree; //摄氏度℃符号

void show_bmp(u8g2_t * dispHandle, GUI_BITMAP* bmp); // 显示图片
