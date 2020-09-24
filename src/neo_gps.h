#ifndef __neo__gps__h__
#define __neo__gps__h__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"

typedef struct neo_gps neo_gps;
typedef struct location location;
typedef struct c_string c_string;

typedef struct location
{
    char *latitude_direction;
    float latitude;
    char *longitude_direction;
    float longitude;
}location;

typedef struct neo_gps
{
    char utc_time[100];
    int gps_status;
    location gps_loc;
    uart_structure *device;
}neo_gps;

typedef struct c_string
{
    char string[100];
}c_string;

neo_gps *new_neo_gps(char*);
int gps_open(neo_gps*);
void gps_read(neo_gps*);

#endif