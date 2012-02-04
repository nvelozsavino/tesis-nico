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
//#define LIGHT_SPEED		3e8
#define DEFAULT_REFLEXION_RM 1
#define DEFAULT_REFLEXION_BS 0.5
#define DEFAULT_TRANSMITION_BS (1-DEFAULT_REFLEXION_BS)

#define DEFAULT_TIPO_INTERF MICHELSON

typedef enum {MICHELSON, MIRAU} TipoInterferometro;


class BeamSplitter {
    private:
        float tBS;  //coeficiente de transmisión del Beam Spliter
        float rBS;  //coeficiente de reflexión del Beam Spliter
    public:
        void initBeamSplitterR(float r);
        void initBeamSplitterT(float t);

        float getR();
        float getT();

        BeamSplitter();
        ~BeamSplitter(){};
};

class Interferometro {
    private:
        float _timeStep;
        int setMats(void);
        float rRM;  //coeficiente de reflexion del Espejo de Referencia (Reference Mirror)
        TipoInterferometro tipo;
        float iRc, iSc;
    public:
        BeamSplitter beamSplitter;
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

        void initInterferometro(Muestra *muestra, Spectrum *fuente, Camara *camara,float timestep, float inclX=0, float inclY=0, TipoInterferometro t=DEFAULT_TIPO_INTERF, float RRM=DEFAULT_REFLEXION_RM, BeamSplitter bs=BeamSplitter());

        void integra(float opticalPath);

        //Destructor
        ~Interferometro();

        //Funciones Set
        int timeStep(float TimeStep);

        //Funciones Get
        void getInterferograma(float opticalPath);
        float timeStep();


        //void setTipo(TipoInterferometro t);
        TipoInterferometro getTipo();
        //float setMirrorRefferenceR(float r);
        float getMirrorRefferenceR();


};

#endif


