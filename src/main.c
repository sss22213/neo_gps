#include "neo_gps.h"

int main()
{
    neo_gps *gps_device = new_neo_gps("/dev/ttyACM0");
    int open_result = gps_open(gps_device);
    
    return 0;
}