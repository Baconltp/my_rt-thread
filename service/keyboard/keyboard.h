#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtdbg.h>

#define ROW1 GET_PIN(B, 6)
#define ROW2 GET_PIN(B, 7)
#define COLUMN1 GET_PIN(B, 0)
#define COLUMN2 GET_PIN(B, 1)
#define COLUMN3 GET_PIN(A, 8)

typedef enum{
    B1 = 0,
    B2,
    B3,
    B4,
    B5,
    B6,
    NONE
}button_id_t;

void keyboard_init(void);

button_id_t ket_sacn(void);
