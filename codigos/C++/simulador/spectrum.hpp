#ifndef _spectrum_h_included_
#define _spectrum_h_included_

#include "generales.hpp"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <opencv2/opencv.hpp>
//#include "highgui.h"
#define DEFAULT_SPECTRUM_SIZE 1000
#define DEFAULT_START_LAMDA 100e-9
#define DEFAULT_END_LAMDA 1001e-9
#define RAIZ_2PI 2.506628274631000502415765284811
#define ALPHA 50
#define LIGHT_SPEED	2.99792458e8

#define PLANCK_H    6.62606957e-34
#define BOLTZMAN_K  1.3806488e-23

using namespace std;
using namespace cv;



class Spectrum {

    float f2val(float freq);
	public:
    float resolucion;
    float startLamda;
    float endLamda;
    Mat valores;
    Mat valoresFreq;
    unsigned int size;

    void initSpectrum(float lamdaStart, float lamdaEnd,unsigned int arraySize);



    int initSpectrumFromFile(string archivo,float resX, float scale,float lamdaStart, float lamdaEnd,unsigned int arraySize);


    void initGausian (float amplitud, float mean, float sigma, unsigned int arraySize);
    void lamda2freq(void);
	//constructor
	Spectrum(){
	    size=0;
    };

    //destructor
    ~Spectrum();

    //Funciones Set
    void setGausian(float amplitud, float mean, float sigma, float add=0);
    //void setGausian(float amplitud, float mean, float sigma);
    void setPlain(float lamdastart, float lamdaend,float amplitud);
    void setDelta(float amplitud, float lamda_central, float add=0);
    void setBlackbody(float T,float amp=1, float add=0);

    //Funciones Get
//    float getResolucion(void);
    float i2lamda(unsigned int i);
    int lamda2i(float l);
    float lamda2f(float l);
    float integrarEspectro(void);
    //unsigned int getSize();

    //operadores
    //Spectrum operator*(Spectrum espectro);
    //void mult(Spectrum src,Spectrum* dst);
   // int Clone(Spectrum *espectro);
   void Borrar();
   // void multEspectros(Espectro espectro1, Espectro espectro2, Espectro* resultado);





};

void mult(Spectrum& src1,Spectrum& src2,Spectrum& dst,int spd=0);
void multFreq(Mat src1, float endFreq1, Mat src2, float endFreq2, Mat *dst, float *endFreqDst);
#endif
