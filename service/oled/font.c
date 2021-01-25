#include <font.h>

/*摄氏度℃符号*/
const unsigned char picture_degree[] = {
0x00,0x02,0x05,0x05,0x02,0x18,0x24,0x04,0x04,0x04,0x24,0x18,0x00/* (6 X 13 )*/
};
GUI_BITMAP bmp_degree = {
    .x = 105,
    .y = 10,
    .w = 6,
    .h = 13,
    .pictureData = (unsigned char *)picture_degree,
};

void show_bmp(u8g2_t * dispHandle, GUI_BITMAP* bmp)
{
    u8g2_DrawXBMP(dispHandle, bmp->x, bmp->y, bmp->w, bmp->h, bmp->pictureData);

    return;
}
