#include "Math.h"
#include "HardwareSerial.h"
#include "EasyGPS.h"

/* ToDo: [fix] ピン設定をスケッチから指定できるようにする。 */
HardwareSerial gpsSerial = HardwareSerial(PA10, PA9);
EasyGPS::EasyGPS(){
    /* hoge */
}

void EasyGPS::setup(){
    gpsSerial.begin(9600);
}

float NMEA2DD(float val) {
  int d = val / 100;
  int m = (((val / 100.0) - d) * 100.0) / 60;
  float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
  return float (d + m + s);
}

void EasyGPS::update(){
    String line = gpsSerial.readStringUntil('\n');
    if(line != ""){
        int i, index = 0, len = line.length();
        String str = "";
        // StringListの生成(簡易)
        String list[30];
        for (i = 0; i < 30; i++) {
            list[i] = "";
        }
        // 「,」を区切り文字として文字列を配列にする
        for (i = 0; i < len; i++) {
            if (line[i] == ',') {
                list[index++] = str;
                //index++;
                str = "";
                continue;
            }
            str += line[i];
        }
        // $GPGGAセンテンスのみ読み込む
        if (list[0] == "$GPGGA") {
            ido = NMEA2DD(list[2].toFloat());
            keido = NMEA2DD(list[4].toFloat());
        }
    }
}

float EasyGPS::getIdo(){
    return ido;
}

float EasyGPS::getKeido(){
    return keido;
}

const float R = 6378137;

float EasyGPS::getDistance(float targetIdo, float targetKeido){
    float delta_x = targetIdo - ido;
    float delta_y = targetKeido - keido;
    float distance = R * sqrt(delta_x * delta_x + delta_y * delta_y);
    return distance;
}

float rad2deg(float radian) {
  return radian * 180.00 / M_PI;
}

float EasyGPS::getRawAzimuth(float targetIdo, float targetKeido){
    float delta_x = targetIdo - ido;
    float delta_y = targetKeido - keido;
    float phi = rad2deg(atan2(R * delta_y, R * delta_x));
    return phi;
}

float EasyGPS::getAzimuth(float targetIdo, float targetKeido){
    float phi = getRawAzimuth(targetIdo, targetKeido);
    if(-90 <= phi && phi <= 180) phi = phi - 90;
    if(-180 <= phi && phi < -90) phi = phi + 270;
    return phi;
}