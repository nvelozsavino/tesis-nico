#ifndef _RUIDO_HPP_
#define _RUIDO_HPP_

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <iostream>


#define N_DEFAULT   (1<<8)
#define TWO_PI (6.2831853071795864769252867665590057683943L)
using namespace std;

typedef struct {
    float value;
    float freq;
} PuntoEspectro;

class Ruido {
    private:
    //Variables Privadas
        PuntoEspectro *_espectro;
        string _fileSpectrum;
        unsigned int _maxSize;
        unsigned int _realSize;
    //Funciones Privadas

    public:
    //Variables Publicas
    //Constructores
        Ruido();
        int initRuido(string FileSpectrum, unsigned int MaxPoints=N_DEFAULT);

        //Destructores
        ~Ruido();

        //Funciones Get
        float getRuido(float time);
        string fileSpectrum();
        unsigned int maxSize();
        unsigned int realSize();

        //Funciones Set
        int fileSpectrum(string FileSpectrum, unsigned int MaxPoints=N_DEFAULT);


};


#endif
