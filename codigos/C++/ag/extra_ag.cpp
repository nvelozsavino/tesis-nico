//extra_ag.cpp
/*
 Coleccion de funciones extras utiles en la implementacion de algoritmos geneticos con 'clase_ag'
 - Codificar y Decodificar 8/16 bits Binario <-> float
 - Codificar y Decodificar Gray <-> Binario
*/

#include "extra_ag.hpp"

//************************************************
//funcion que convierte de binario a gray (1 byte)
unsigned char exBinarioGray(unsigned char bin)
{
        return bin^(bin>>1); //BIN XOR (BIN>>1)
}

//************************************************
//funcion que convierte de gray a binario (1 byte)
unsigned char exGrayBinario(unsigned char gray)
{
    unsigned char bin=gray^(gray>>1);
    for(register int k=2;k<8;k++) bin=bin^(gray>>k);
    return bin;
}

//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar16(unsigned char *ap, float min, float max)
{
	float a;
   unsigned short int b;
   b = *(unsigned short int*) ap;
   a = (b*(max-min)/65536)+min;
   return a;
}

//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar8(unsigned char *ap, float min, float max)
{
	float a, b;
   b = (float)*ap;
   a = (b*(max-min)/256)+min;
   return a;
}
