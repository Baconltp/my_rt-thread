#include <keyboard.h>

void keyboard_init(void)
{
    rt_pin_mode(ROW1,PIN_MODE_OUTPUT);
    rt_pin_mode(ROW2,PIN_MODE_OUTPUT);
    rt_pin_mode(COLUMN1,PIN_MODE_INPUT);
    rt_pin_mode(COLUMN2,PIN_MODE_INPUT);
    rt_pin_mode(COLUMN3,PIN_MODE_INPUT);
}

button_id_t ket_sacn(void){
    rt_pin_write(ROW1, PIN_HIGH);
    if(rt_pin_read(COLUMN1)){
        return B1;
    }
    else if(rt_pin_read(COLUMN2)){
        return B2;
    }
    else if(rt_pin_read(COLUMN3)){
        return B3;
    }
    else {
        rt_pin_write(ROW1, PIN_LOW);
        rt_pin_write(ROW2, PIN_HIGH);
    }
    if(rt_pin_read(COLUMN1)){
        return B4;
    }
    else if(rt_pin_read(COLUMN2)){
        return B5;
    }
    else if(rt_pin_read(COLUMN3)){
        return B6;
    }
    else{
        rt_pin_write(ROW2, PIN_LOW);
        return NONE;
    }
    return NONE;
}
