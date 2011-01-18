#ifndef _interferometro_h_included_
#define _interferometro_h_included_
#include "generales.hpp"
#include "camara.hpp"
#include "spectrum.hpp"
#include "muestra.hpp"
#include "cv.h"
#include "highgui.h"
//#include "perturbacion.hpp"
using namespace cv;
#define LIGHT_SPEED		3e8

class Interferometro {
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


	//Constructor
	Interferometro(){};
	void initInterferometro(Muestra *muestra, Spectrum *fuente, Camara *camara,float timestep, float inclX, float inclY);
    void integra(float opticalPath);
	//Destructor
	~Interferometro();

	//Funciones Set


	//Funciones Get
	void getInterferograma(float opticalPath);

};

#endif


