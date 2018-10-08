#ifndef SPI_H
#define SPI_H

void SPI_init(void);		//SPI initialization
void SPI_write(char cData);	//Send a message to slave through SPI comm
char SPI_read(void);		//Read a message from slave through SPI comm

#endif // SPI_H