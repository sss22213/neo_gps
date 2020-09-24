#include "neo_gps.h"

int main()
{
    neo_gps *gps_device = new_neo_gps("/dev/ttyACM0");
    gps_open(gps_device);
    gps_read(gps_device);
    return 0;
}