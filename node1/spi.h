#ifndef SPI_H
#define SPI_H

void SPI_init(void);		//SPI initialization (as a Master)
void SPI_write(char cData);	//Send a message to slave through SPI comm
char SPI_read(void);		//Read a message from slave through SPI comm
void SPI_select(void);		//Select CAN-controller (~CS=0)
void SPI_deselect(void);    //Deselect CAN-controller (~CS=1)

#endif // SPI_H