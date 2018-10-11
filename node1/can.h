#ifndef CAN_H
#define CAN_H

#define TXREQ 3
#define TXERR 4

typedef struct {
	uint8_t id;
	uint8_t length;	
	uint8_t data[8];
} packet;

void CAN_init();
void CAN_send(packet* message);
packet CAN_read();

#endif // CAN_H