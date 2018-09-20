#ifndef BUTTONS_H
#define BUTTONS_H


void button_init(void);

int16_t JoyCoord_init(int16_t X_coord, int16_t Y_coord);

void getJoyCoord(int16_t X_coord, int16_t Y_coord);

void getJoyCoord2(int16_t X_coord, int16_t Y_coord);

void getJoyDirection(int16_t X_coord, int16_t Y_coord);



#endif // BUTTON_H