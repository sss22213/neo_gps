#ifndef __uart__h__
#define __uart__h__
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h> 
#include <termios.h> 
#include <unistd.h>
#include <errno.h>

#define PARITY_NONE 0
#define PARITY_ODD 1
#define PARITY_EVEN 2

#define STOP_BITS_ONE 0
#define STOP_BITS_TWO 1

#define DATA_LENGTH_EIGHT 0
#define DATA_LENGTH_SEVEN 1

typedef struct uart_structure uart_structure;

typedef struct uart_structure
{
    int fd;
    char port_name[20];
    speed_t bundrate;
    int parity;
    int stop_bits;
    int data_length;
}uart_structure;

uart_structure* new_uart_device(char*,speed_t,int,int,int);
int uart_open(uart_structure*);
void uart_close(uart_structure*);
int uart_read(uart_structure*,uint8_t*);
int uart_readnbytes(uart_structure*, uint8_t*, uint8_t);
int uart_write(uart_structure*,uint8_t);
int uart_writenbyte(uart_structure*,uint8_t*,uint8_t);
#endif