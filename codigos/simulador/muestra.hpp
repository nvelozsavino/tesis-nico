#ifndef _muestra_h_included_
#define _muestra_h_included_

#include "generales.hpp"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
//#include "highgui.h"
#include <iostream>
#include <string>

using namespace std;
using namespace cv;
#define SAMPLE_DEPTH_RESOLUTION	10e-9

typedef enum {IN_DEPTH=1, IN_VISIBILITY=0} lugarMuestra;

class Muestra {

    public:
    Mat depth;
    Mat visibilidad;
    //float *visibilidad;
	//float *depth;
	float realWidth;
	float realHeight;

    unsigned int width;
    unsigned int height;
    float resolucion;
	//Constructores
	Muestra(){};
	void initMuestra(float realWidth,float realHeight, float resolucion);

	//Destructores
	~Muestra();

	//Funciones Set
	void setMuestraFromFile(string filename,  float resolucion, lugarMuestra lugar, int top, int left);
    void setMuestraFull(lugarMuestra lugar);
    void setMuestraPlain(float amplitud,lugarMuestra lugar);
    bool setPMuestra(unsigned int x, unsigned int y, lugarMuestra lugar, float valor);

    //Funciones Get

    bool getPMuestra(unsigned int x, unsigned int y, lugarMuestra lugar, float *valor);

};






#endif
