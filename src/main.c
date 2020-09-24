#include "neo_gps.h"

int main()
{
    neo_gps *gps_device = new_neo_gps("/dev/ttyACM0");
    gps_open(gps_device);
    gps_read(gps_device);
    printf("GPS STATUS: %d, latitude_direction: %s, latitude: %e, longitude_direction: %s, longitude: %e\n",
        gps_device->gps_status, 
        gps_device->gps_loc.latitude_direction,
        gps_device->gps_loc.latitude,
        gps_device->gps_loc.longitude_direction,
        gps_device->gps_loc.longitude
    );
    return 0;
}