#include "Arduino.h"
#include "Math.h"
#include "HardwareSerial.h"
#include "EasyGPS.h"

EasyGPS::EasyGPS(){
    /* hoge */
}

void EasyGPS::setup(){
    gpsSerial = HardwareSerial(PA10, PA9);
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

float NMEA2DD(float val) {
  int d = val / 100;
  int m = (((val / 100.0) - d) * 100.0) / 60;
  float s = (((((val / 100.0) - d) * 100.0) - m) * 60) / (60 * 60);
  return float (d + m + s);
}