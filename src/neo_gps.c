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


void split_comm(char* data, char** output)
{
    char *ptr_s = data;
    char **ptr_output = output;
    char *end;
    int i = 0;
    while(*ptr_s != '\0')
    {
        end = ptr_s + strcspn(ptr_s, ",");
        *end = '\0';
        // bzero(*ptr_output,100);
        if(!strlen(ptr_s))memcpy(*ptr_output,"Z",2);
        else memcpy(*ptr_output,ptr_s,strlen(ptr_s));
        printf("STX %s %s ETX\n",ptr_s,*ptr_output);
        ptr_output++;
        ptr_s = end + 1;
    }
}


void gps_package_analysis(neo_gps* gps_device, char* gps_data)
{
    char *ptr_GPGGA = strstr(gps_data,"$GPGGA,");
    char *ptr_GPRMC = strstr(gps_data,"$GPRMC,");
    if(ptr_GPGGA)
    {
       1 == 1; 
    }
    // printf("%s\n",ptr_GPGGA);
    if(ptr_GPRMC)printf("%s\n",ptr_GPRMC);
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
        // int byte_read = uart_readline(gps_device->device, data_buffer, 70);
        int byte_read = uart_readline(gps_device->device, data_buffer, 70);
        char *ptr_GPGGA = strstr(data_buffer,"$GPGGA");
        if(ptr_GPGGA)
        {
            char **analysis_result = (char**)calloc(sizeof(char),100);
            for(int idx = 0; idx < 100; idx++)
            {
                *(analysis_result + idx) = (char*)calloc(sizeof(char),100);
            }
            split_comm(ptr_GPGGA, analysis_result);
            free(analysis_result);
        }
    }
    printf("\n");
}