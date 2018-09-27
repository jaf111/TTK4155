#ifndef BUTTONS_H
#define BUTTONS_H

#define JOY_LR 0x04
#define JOY_DU 0x05
#define SLIDER_R 0x06
#define SLIDER_L 0x07


typedef struct {
	int16_t XX;
	int16_t YY;
} position;


void button_init(void);

int16_t JoyCoord_init(int16_t XY);

position getJoyCoord(int16_t X_coord, int16_t Y_coord, int16_t JoyX_init, int16_t JoyY_init);

void getJoyDirection(int16_t X_coord, int16_t Y_coord);

void sliders();



#endif // BUTTON_H