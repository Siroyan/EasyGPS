#ifndef EasyGPS_h
#define EasyGPS_h

#include "Arduino.h"
#include "HardwareSerial"

class EasyGPS{
    public:
        EasyGPS();
        void setup();
        void update();
        float getIdo();
        float getKeido();
    private:
        float ido;
        float keido;
        float NMEA2DD(float val);
        HardwareSerial gpsSerial;
}

#endif