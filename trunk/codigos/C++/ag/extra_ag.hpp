#ifndef _EXTRA_AG_H_
#define _EXTRA_AG_H_

//extra_ag.cpp
/*
 Coleccion de funciones extras utiles en la implementacion de algoritmos geneticos con 'clase_ag'
 - Codificar y Decodificar 8/16 bits Binario <-> float
 - Codificar y Decodificar Gray <-> Binario
*/

#include<stdio.h>
#include<stdlib.h>

//funcion que convierte de binario a gray (1 byte)
unsigned char exBinarioGray(unsigned char);
//funcion que convierte de gray a binario (1 byte)
unsigned char exGrayBinario(unsigned char);

//funcion que recibe dos bytes (16 bits) y lo decodifica a float (binario-lineal)
float crDecodificar16(unsigned char *ap, float min, float max);
//funcion que recibe un byte (8 bits) y lo decodifica a float (binario-lineal)
float crDecodificar8(unsigned char *ap, float min, float max);

//************************************************
//funcion que convierte de binario a gray (1 byte)
unsigned char exBinarioGray(unsigned char bin);


//************************************************
//funcion que convierte de gray a binario (1 byte)
unsigned char exGrayBinario(unsigned char gray);


//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar16(unsigned char *ap, float min, float max);

//****************************************************************
//devuelve el valor asociado a un segmento de cromosoma de 16 bits
float crDecodificar8(unsigned char *ap, float min, float max);

#endif

