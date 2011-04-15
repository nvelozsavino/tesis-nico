#ifndef _interferometro_h_included_
#define _interferometro_h_included_
#include "generales.hpp"
#include "camara.hpp"
#include "spectrum.hpp"
#include "muestra.hpp"
#include <opencv2/opencv.hpp>
//#include "highgui.h"
//#include "perturbacion.hpp"
using namespace cv;
#define LIGHT_SPEED		3e8

class Interferometro {
    private:
        float _timeStep;
        int setMats(void);
    public:
    //Spectrum *multip;
        float *Xmax;
        float *Xmin;
        Mat *interferograma;
        Mat *interf;
        float *Io;
        public:
        float scale;
        Spectrum *fuente;
        Camara *camara;
        Muestra *muestra;
        float inclinacionX;
        float inclinacionY;
        Mat valores;
        //float **valores;
        unsigned int width;
        unsigned int height;
        Mat roiDepth;
        Mat roiVisibility;
        ROI camaraROI;
        ParametrosCamara camaraParam;

        //Constructor
        Interferometro(){};
        void initInterferometro(Muestra *muestra, Spectrum *fuente, Camara *camara,float timestep, float inclX, float inclY);
        void integra(float opticalPath);
        //Destructor
        ~Interferometro();

        //Funciones Set
        int timeStep(float TimeStep);

        //Funciones Get
        void getInterferograma(float opticalPath);
        float timeStep();


};

#endif


