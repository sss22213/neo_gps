#include "uart.h"

void delay_ms(int ms)
{
    usleep(ms * 1e+3);
}

uart_structure* new_uart_device(char* port_name,speed_t bundrate,int parity,int stop_bits,int data_length)
{
    uart_structure* new_uart_device = (uart_structure*)calloc(sizeof(uart_structure),1);
    int char_idx = 0;
    while( *port_name != '\0' )
    {
        new_uart_device->port_name[char_idx] = *port_name;
        char_idx++;
        port_name++;
    }
    //
    new_uart_device->bundrate = bundrate;
    new_uart_device->parity = parity;
    new_uart_device->stop_bits = stop_bits;
    new_uart_device->data_length = data_length;
    return new_uart_device;
}


int uart_open(uart_structure* uart_device)
{
    uart_device->fd = open(uart_device->port_name, O_RDWR | O_NOCTTY);
    if(uart_device->fd == -1)return -1;
    struct termios SerialPortSettings;
    tcgetattr(uart_device->fd, &SerialPortSettings);
    cfsetispeed(&SerialPortSettings,uart_device->bundrate);
    cfsetospeed(&SerialPortSettings,uart_device->bundrate);
    SerialPortSettings.c_cflag &= ~PARENB;
    // stop bits
    if(uart_device->stop_bits == STOP_BITS_ONE)SerialPortSettings.c_cflag &= ~CSTOPB;
    else SerialPortSettings.c_cflag = CSTOPB;
    SerialPortSettings.c_cflag &= ~CSIZE;
    // data length
    switch (uart_device->data_length)
    {
        case DATA_LENGTH_EIGHT:
            SerialPortSettings.c_cflag |=  CS8;
            break;
        case DATA_LENGTH_SEVEN:
            SerialPortSettings.c_cflag |=  CS7;
            break;
        default:
            SerialPortSettings.c_cflag |=  CS8;
            break;
    }
    SerialPortSettings.c_cflag &= ~CRTSCTS;
    SerialPortSettings.c_cflag |= CREAD | CLOCAL;
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // timeout 
    SerialPortSettings.c_cc[VMIN] = 10;
	SerialPortSettings.c_cc[VTIME] = 0;
    if((tcsetattr(uart_device->fd,TCSANOW,&SerialPortSettings)) != 0)return -2;
    return 0;
}
void uart_close(uart_structure* uart_device)
{
    close(uart_device->fd);
}
int uart_read(uart_structure* uart_device, uint8_t* data)
{
    // flush buffer
    tcflush(uart_device->fd, TCIFLUSH);
    int bytes_read = read(uart_device->fd,data,1);
    return bytes_read;
}

int uart_readnbytes(uart_structure* uart_device, uint8_t* data, uint8_t data_length)
{
    // flush buffer
    tcflush(uart_device->fd, TCIFLUSH);
    int bytes_read = read(uart_device->fd,data,data_length);
    return bytes_read;
}

int uart_write(uart_structure* uart_device,uint8_t data)
{
    int bytes_written = write(uart_device->fd, &data,1);
    return bytes_written;
}

int uart_writenbyte(uart_structure* uart_device, uint8_t* data, uint8_t data_length)
{
    int bytes_written = write(uart_device->fd, &data, data_length);
    return bytes_written;
}

/*
int main()
{
    uart_structure* uart_device = new_uart_device("/dev/ttyACM0",B9600,PARITY_NONE,STOP_BITS_ONE,DATA_LENGTH_EIGHT);
    uart_open(uart_device);
    uint8_t data[50];
    while(1)
    {
        uart_readnbytes(uart_device, data, 50);
        for(int idx = 0; idx < 50; idx++)
        {
            printf("%c",data[idx]);
        }
        printf("\n");
        delay_ms(1000);
    }
    return 0;
}
*/