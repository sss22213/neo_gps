#include "neo_gps.h"

neo_gps *new_neo_gps(char* port)
{
    neo_gps *new_gps_device = (neo_gps*)calloc(sizeof(neo_gps),1);
    // initial uart
    new_gps_device->device = new_uart_device(port,B9600,PARITY_NONE,STOP_BITS_ONE,DATA_LENGTH_EIGHT);
    // alloc
    new_gps_device->gps_loc.latitude_direction = (char*)calloc(sizeof(char),5);
    new_gps_device->gps_loc.longitude_direction = (char*)calloc(sizeof(char),5);
    return new_gps_device;

}

int gps_open(neo_gps* gps_device)
{
    return uart_open(gps_device->device);
}

void split_comm(char* data, c_string* output)
{
    char *ptr_s = data;
    c_string *ptr_output = output;
    char *end;
    int i = 0;
    while(*ptr_s != '\0')
    {
        end = ptr_s + strcspn(ptr_s, ",");
        *end = '\0';
        if(!strlen(ptr_s))memcpy(ptr_output->string,"Z",2);
        else memcpy(ptr_output->string,ptr_s,strlen(ptr_s));
        ptr_output++;
        ptr_s = end + 1;
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
        // int byte_read = uart_readline(gps_device->device, data_buffer, 70);
        int byte_read = uart_readline(gps_device->device, data_buffer, 70);
        char *ptr_GPGGA = strstr(data_buffer,"$GPGGA");
        char *ptr_GPRMC = strstr(data_buffer,"$GPRMC");
        if(ptr_GPGGA)
        {
            c_string string_array[100];
            split_comm(ptr_GPGGA, string_array);
            memcpy(gps_device->gps_loc.latitude_direction, string_array[2].string, sizeof(string_array[2].string));
            gps_device->gps_loc.latitude = atof(string_array[3].string);
            memcpy(gps_device->gps_loc.longitude_direction, string_array[4].string, sizeof(string_array[5].string));
            gps_device->gps_loc.longitude = atof(string_array[5].string);
        }
        else if(ptr_GPRMC)
        {
            // printf("%s\n",ptr_GPRMC);
            c_string string_array_GPRMC[100];
            split_comm(ptr_GPRMC, string_array_GPRMC);
            if(string_array_GPRMC[2].string[0] != 'V')gps_device->gps_status = 1;
            else gps_device->gps_status = 0;
        }
    }
}
