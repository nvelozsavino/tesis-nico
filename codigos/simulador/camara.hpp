#ifndef _camara_h_included_
#define _camara_h_included_


#include "spectrum.hpp"
#include <cstdlib>
#include <iostream>

 typedef enum {MONO,COLOR} tipoCamara;
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

typedef struct {
    int top;
    int left;
    int width;
    int height;
} ROI;


class Camara {
    public:

    tipoCamara tipo;
    Spectrum *sensor;
    unsigned int fps;
    float integrationTime;
    int hasROI;
    ROI roi;


    //int createCamara(Camara *camara, )
    //Constructor
    Camara(){};
    void initCamara(unsigned int f, float it,tipoCamara type);
    void initCamaraFromFiles(unsigned int f, float it,string red,string green, string blue);
    //Destructor
    ~Camara();

    //Funciones get
    unsigned int getFPS(void);
    float getIntegrationTime(void);
    tipoCamara getType(void);

    //Funciones set
    void setFPS(unsigned int f);
    void setIntegrationTime(float it);
    int setROI (int top, int left, int width, int height);
    int clearROI (void);

};

#endif
