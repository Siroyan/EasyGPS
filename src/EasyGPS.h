#ifndef EasyGPS_h
#define EasyGPS_h

class EasyGPS{
    public:
        EasyGPS(void);
        void setup();
        void update();
        float getIdo();
        float getKeido();
        float getDistance(float targetIdo, float targetKeido);
        float getRawAzimuth(float targetIdo, float targetKeido);
        float getAzimuth(float targetIdo, float targetKeido);
    private:
        float ido;
        float keido;
};
#endif