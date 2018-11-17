#ifndef CAN_H
#define CAN_H

#define TXREQ 3
#define TXERR 4
#define MLOA 5

#define CAN_SCORE_ID 		0x01
#define CAN_END_GAME_ID		0x02
#define CAN_START_GAME_ID 	0x03
#define CAN_INPUT_ID 		0x04
#define CAN_SHOOT_ID		0x05

typedef struct {
	uint8_t id;
	uint8_t length;	
	uint8_t data[8];
} packet;

void CAN_init();
void CAN_send(packet* message);
packet CAN_read();
uint8_t CAN_error();
uint8_t CAN_message_recieved();

#endif // CAN_H