#ifndef _camara_h_included_
#define _camara_h_included_


#include "spectrum.hpp"
#include <cstdlib>
#include <iostream>

typedef enum {BW,COLOR} tipoCamara;
typedef enum {FULL_FRAME,FRAME_TRANSFERE,INTERLINE} tipoFrame;
typedef enum {FIXED_FPS_FIXED_EXPOSE,FIXED_FPS_AUTO_EXPOSE,AUTO_FPS_FIXED_EXPOSE} autoSettings;

#define RAIZ_2PI 2.506628274631000502415765284811


#define GREEN_MIU		540e-9
#define GREEN_SIGMA		90e-9
//62e-9
#define GREEN_AMP		(RAIZ_2PI*GREEN_SIGMA)/(LIGHT_SPEED*LIGHT_SPEED)


#define GRAY_MIU		540e-9
#define GRAY_SIGMA		235e-9
#define GRAY_AMP		(RAIZ_2PI*GRAY_SIGMA)/(LIGHT_SPEED*LIGHT_SPEED)



#define RED_MIU			650e-9
//650e-9
#define RED_SIGMA		96e-9
#define RED_AMP			(RAIZ_2PI*RED_SIGMA)/(LIGHT_SPEED*LIGHT_SPEED)



#define BLUE_MIU		462e-9
#define BLUE_SIGMA		93e-9
#define BLUE_AMP		(RAIZ_2PI*BLUE_SIGMA)/(LIGHT_SPEED*LIGHT_SPEED)

#define SPECTRUM_SIZE	1000
#define SPECTRUM_RESOLUTION

#define DEFAULT_TIPO    COLOR
#define DEFAULT_TRANSPORT_TIME  0.5e-8
#define DEFAULT_SHUTTER_TIME    0
#define DEFAULT_WIDTH   800
#define DEFAULT_HEIGHT  600
#define DEFAULT_FPS     60
#define DEFAULT_EXPOSURE_TIME  1/DEFAULT_FPS
#define DEFAULT_FRAME_TYPE  INTERLINE
//#define DEFAULT_RED_GAIN 1.2755
//#define DEFAULT_GREEN_GAIN 0.2358
//#define DEFAULT_BLUE_GAIN 0.3255
//#define DEFAULT_WHITE_GAIN 0.3255
#define DEFAULT_RED_GAIN 1
#define DEFAULT_GREEN_GAIN 1
#define DEFAULT_BLUE_GAIN 1
#define DEFAULT_WHITE_GAIN 1

#define DEFAULT_GAIN 1



class ROI {
    public:
        unsigned int top;
        unsigned int left;
        unsigned int width;
        unsigned int height;

    ROI();
    ROI(unsigned int w, unsigned int h, unsigned int t, unsigned int l);
    int operator== (ROI src);
    int operator!= (ROI src);
};
class ParametrosCamara {
    public:
    float _exposureTime;
    float _fps;
    float _transportTime;
//        float _adcTime;
    float _shutterTime;
    unsigned int _width;
    unsigned int _height;
    ROI _roi;
    tipoCamara _tipo;
    tipoFrame   _frameType;
    autoSettings _autoConfig;
    string _redFile;
    string _greenFile;
    string _blueFile;
    string _whiteFile;

    int _fromFiles;
    ParametrosCamara();
    ~ParametrosCamara();
    int operator== (ParametrosCamara src);
    int operator!= (ParametrosCamara src);

};

class Camara {
    private:
        //Variables Privadas
        Spectrum *_sensor;
        ParametrosCamara param;

        //Funciones Privadas
        int calcTimes();


    public:
        float *channelGain;
        float gain;
        //Constructor
        Camara();

        int init(unsigned int Width, unsigned int Height,float Fps, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME);

        int initFPS(unsigned int Width, unsigned int Height,float Fps, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME);

        int initExposureTime(unsigned int Width, unsigned int Height, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME);

        //Destructor
        ~Camara();

        //Operadores
        int operator== (Camara src);
        int operator!= (Camara src);

        //Funciones GET
        unsigned int width();
        unsigned int height();
        ROI roi ();
        float fps();
        float exposureTime();
        tipoCamara tipo();
        tipoFrame frameType();
        float transportTime();
        float shutterTime();
        int fromFiles();
        string redFile();
        string greenFile();
        string blueFile();
        string whiteFile();
        Spectrum sensor (int index);
        autoSettings autoConfig();
        ParametrosCamara getParametros();
        float getNotIntegrationTime();


        //Funciones SET
        int setSize(unsigned int width, unsigned int height);
        int roi (unsigned int width, unsigned int height,unsigned int top, unsigned int left);
        int roi (ROI Roi);
        int fps(float Fps);
        int exposureTime(float ExposureTime);
        int fpsExposureTime(float Fps,float ExposureTime);
        int tipo(tipoCamara Tipo);
        int frameType(tipoFrame FrameType);
        int transportTime(float TransportTime);
        int shutterTime(float ShutterTime);
        int setSpectrumsFiles(string RedFile, string GreenFile, string BlueFile);
        int setSpectrumsFiles(string WhiteFile);
        int setSpectrumsDefaults();
        int autoConfig(autoSettings AutoConfig);

void setChannelGain(float Ar, float Ag, float Ab);
void setChannelGain(float Aw);
void setDefaultChannelGain();

};

#endif
