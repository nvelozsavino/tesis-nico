#ifndef _RUIDO_HPP_
#define _RUIDO_HPP_

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include "generales.hpp"
#define USE_MATH_DEFINES
//extern void fft(int N, double **x, double **X);
//extern void fft_rec(int N, int offset, int delta,double **x, double **X, double **XX);
//extern void ifft(int N, double **x, double **X);

#define N_DEFAULT   (1<<10)
#define TWO_PI (6.2831853071795864769252867665590057683943L)
void fft(int N, double **x, double **X);
void fft_rec(int N, int offset, int delta,double **x, double **X, double **XX);
void ifft(int N, double **x, double **X);

class Ruido {
    double **freqArray;
    double **timeArray;
    double *outArray;
    double deltaT;
    double deltaF;
    double rangoF;
    double rangoT;
    double noiseRel;
    double tset;
    int Nset;
    int N;
    int checkN();
    int iPointer;
    int iTp;
    public:
    Ruido();
    ~Ruido();
    int initRuido(double df,int n=N_DEFAULT);
    void addDC(double amp);
    void setDC(double amp);
    void addGaus(double amp, double fo, double sigma);
    void setNoise(double amp);
    void addNoise(double amp);
    void addHarmonics(double amp, double fi, double sigma, int nHarm, double decay);
    void addGausTime(double amp, double to, double sigma);
    int setTimeArray(double t);
    int getNset();
    int setTp(double t);
    double getTp();
    double getV();
    void copyTimeArray();
    void copyFreqArray();
    double getTset();



    void iFFT();
    void clear();
    int setPointer(double t);
    double getPointer();
    int getN();
    double getDeltaT();
    double getDeltaF();
    double getTmax();
    double getFmax();
    double getRuido();


};


#endif
