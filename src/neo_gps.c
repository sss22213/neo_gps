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

void string_copy_until(char* data_buffer,char* result_buffer, char terminer_chr)
{
    char* ptr_data_buffer = data_buffer;
    char* ptr_result_buffer = result_buffer;
    while(*ptr_data_buffer != terminer_chr)
    {
        *ptr_result_buffer = *ptr_data_buffer;
        ptr_data_buffer++;
        ptr_result_buffer++;
    }
}

void gps_read(neo_gps* gps_device)
{
    // get 100 byte
    char data_buffer[70];
    //
    int gpgga_exist = 0;
    int gprmc_exist = 0;
    while( !gpgga_exist && !gprmc_exist )
    {
        int byte_read = uart_readline(gps_device->device, data_buffer, 70);
        printf("%s\n",data_buffer);
        /*
        int byte_read = uart_readnbytes(gps_device->device, data_buffer, 70);
        for(int idx = 0; idx < byte_read; idx++)
        {
            printf("%c",data_buffer[idx]);
        }
        printf("\n");
        */
        /*
        // GPGGA
        char *ptr_GPGGA = strstr(data_buffer,"$GPGGA,");
        char *ptr_GPRMC = strstr(data_buffer,"$GPRMC,");
        char buffer[70];
        if(ptr_GPGGA)
        {
            string_copy_until(data_buffer + strlen("$GPGGA"), buffer, '\n');
            // printf("%s\n",buffer);
        }
        if(ptr_GPRMC)
        {


        }
        */
        
        /*
        if(ptr_GPGGA)
        {
            char * pch;
            pch = strtok(ptr_GPGGA," ,");
            while (pch != NULL)
            {
                printf ("%s||",pch);
                pch = strtok (NULL, " ,");
            }
        }
        */
        // printf("||||%s||||\n",ptr_GPGGA + sizeof("$GPGGA,"));
    }
    

    printf("\n");
}