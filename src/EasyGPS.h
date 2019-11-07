#ifndef EasyGPS_h
#define EasyGPS_h

class EasyGPS{
    public:
        EasyGPS(void);
        void setup();
        void update();
        float getIdo();
        float getKeido();
    private:
        float ido;
        float keido;
};
#endif