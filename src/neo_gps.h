#ifndef __neo__gps__h__
#define __neo__gps__h__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"

typedef struct neo_gps neo_gps;
typedef struct location location;

typedef struct location
{
    int latitude_direction;
    int latitude;
    int longitude_direction;
    int longitude;
}location;

typedef struct neo_gps
{
    long utc_time;
    int gps_status;
    location gps_loc;
    uart_structure *device;
}neo_gps;

neo_gps *new_neo_gps(char*);
int gps_open(neo_gps*);
void gps_read(neo_gps*);

#endif