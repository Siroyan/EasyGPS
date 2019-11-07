#include "EasyGPS.h"

EasyGPS gps;

void setup(){
    Serial.begin(115200);
    gps.setup();
}

void loop(){
    gps.update();
    Serial.print("緯度=");Serial.println(gps.getIdo(), 6);
    Serial.print("経度=");Serial.println(gps.getKeido(), 6);
}