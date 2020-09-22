import serial

class gps_device:
    def __init__(self, gps_device):
        self.serial_dev = serial.Serial(gps_device, 9600)
        # self.gps_status = None
        self.initial()


    def initial(self):
        self.gps_loc = {
            "utc_time":None,
            "gps_status":None,
            "latitude_direction":None,
            "latitude":None,
            "longitude_direction":None,
            "longitude":None,
            }

    def analysis(self):
        self.initial()
        gps_status,gps_fix_data = self.read_loc()
        gps_status_list = gps_status.split(',')
        gps_fix_data_list = gps_fix_data.split(',')
        if 'A' in gps_status_list[2]:
            self.gps_loc["gps_status"] = True
            self.gps_loc["latitude_direction"] = gps_fix_data_list[3]
            self.gps_loc["latitude"] = gps_fix_data_list[2]
            self.gps_loc["longitude_direction"] = gps_fix_data_list[5]
            self.gps_loc["longitude"] = gps_fix_data_list[4]
        else:
            self.gps_loc["gps_status"] = False
        self.gps_loc["utc_time"] = gps_status_list[1]
        '''
        gps_list_data = gps_fix_data.split(',')
        self.utc_time = gps_list_data[1]
        self.gps_loc["latitude"] = gps_list_data[2]
        print(gps_list_data[2])
        '''
        return self.gps_loc
    

    def read_loc(self):
        gps_fix_data = '1'
        gps_status = '1'
        while('$GPGGA' not in gps_fix_data):
            gps_fix_data = self.serial_dev.readline().decode("utf-8")
        while('$GPRMC' not in gps_status):
            gps_status = self.serial_dev.readline().decode("utf-8")
        return gps_status,gps_fix_data

    def test(self):
        while True:
            print(self.serial_dev.readline().decode("utf-8"))

if __name__ == "__main__":
    gps_dev = gps_device('/dev/ttyACM0')
    while True:
        print(gps_dev.analysis())
    # gps_dev.test()
    # print(gps_dev.analysis())