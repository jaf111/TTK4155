#ifndef CAN_H
#define CAN_H

#define TXREQ 3
#define TXERR 4
#define MLOA 5

typedef struct {
	uint8_t id;
	uint8_t length;	
	int8_t data[8];
} packet;

void CAN_init();
void CAN_send(packet* message);
packet CAN_read();
int CAN_error();

#endif // CAN_H