#include "neo_gps.h"

neo_gps *new_neo_gps(char* port)
{
    neo_gps *new_gps_device = (neo_gps*)calloc(sizeof(neo_gps),1);
    // initial uart
    new_gps_device->device = new_uart_device(port,B9600,PARITY_NONE,STOP_BITS_ONE,DATA_LENGTH_EIGHT);
    return new_gps_device;

}

int gps_open(neo_gps* gps_device)
{
    return uart_open(gps_device->device);
}

void gps_read(neo_gps* gps_device)
{
    // get 100 byte
    char data_buffer[100];
    uart_readnbytes(new_gps_device->device, data_buffer, 100);

}