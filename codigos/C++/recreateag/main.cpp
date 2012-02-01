#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "clase_ag.hpp"
#include "extra_ag.hpp"

#define MIN_VAL -10
#define MAX_VAL 10
#define ORDEN 6
#define nBytes 2*ORDEN //longitud maxima del string (cromosoma) en bytes

#define MAXIMO 5
#define STEP 0.1


#include <iostream>

#include <opencv2/opencv.hpp>
//#include "highgui.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>



#include "simulador.hpp"
//#define TIMESTEP 1e-3
#define MAXTIME 10
//#define FREQ 100
#define LAMDA_0 546.1e-9
#define M_DEFAULT 1

#define GET_TIME 10
#define PORCENTAJEMAS   0.1
#define PORCENTAJE_STOP 0.5
#define PORCENTAJE_JUEGO 0.95

#define VECES_SUPERIOR  3


#define TO_DIV      50
#define AMP_DIV     50
#define S_DIV       50


#define MAXTIME_CONTROL (GET_TIME+60)
#define MAXTIME_TOTAL   (MAXTIME_CONTROL+10)

//#define RUIDO 1
#define ARCHIVO_VIDEO "../archivos/resultados/video222.avi"
#define ARCHIVO_DATA "../archivos/resultados/dataplana2222.xls"
#define EXPOSURE_STEP   20
using namespace std;
using namespace cv;
/*
int main(){

    //clock_t begin,end;
	Mat img ;
	int c;

    fuente.initSpectrum(DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,1000);
	fuente.setGausian(1,LAMDA_0,10e-9);
	muestra.initMuestra(163e-6,163e-6,7.030674847e6);
	muestra.setMuestraPlain(1,IN_VISIBILITY);

	if (camara.setSpectrumsFiles("../archivos/r1.dat","../archivos/g1.dat","../archivos/b1.dat")){
        return -1;
	};
	interf.initInterferometro(&muestra,&fuente,&camara,camara.exposureTime());
	muestra.setMuestraFromFile("../archivos/pozo.png",7*LAMDA_0,IN_DEPTH,0,0);

    camara.
    float copt=0;
    interf.inclinacionX=0e-6;
    interf.inclinacionY=0e-6;

    interf.getInterferograma(copt);
    while(1){
        imshow( "simulador", interf.valores);
        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    }
    return 0;
}

*/

Mat getImg(unsigned char *string);


Spectrum fuente;
Camara camara;
Muestra muestra;
Interferometro interf;
Mat target;


CLASECromosoma a,b,c,d;
CLASEAGenetico ag;

float eval(unsigned char *);

int main()
{
    int c;
    target=imread("../archivos/pozo_real_big.png",CV_32FC3);
    target.convertTo(target,CV_32FC3,1.0/255);

    fuente.initSpectrum(DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,1000);
	fuente.setGausian(1,LAMDA_0,10e-9);
	muestra.initMuestra(163e-6,163e-6,7.030674847e6);
	muestra.setMuestraPlain(1,IN_VISIBILITY);
    muestra.setMuestraFromFile("../archivos/pozo.png",1,IN_DEPTH,0,0);
	if (camara.setSpectrumsFiles("../archivos/r1.dat","../archivos/g1.dat","../archivos/b1.dat")){
        return -1;
	};
    camara.initFPS(1146,1146,30,COLOR);
	interf.initInterferometro(&muestra,&fuente,&camara,camara.exposureTime());




    srand ( time(NULL) );
	ag.PoblacionAleatoria(10,nBytes); //creo una poblacion de 200 individuos, de longitud 'nBytes' cada string
	ag.FuncionEvaluacion(eval); //defino cual es la funcion que evalua cada cromosoma y devuelve el fitnes entre 0 y 1 (Es llamada automaticamante por al AG
    ag.dTasaMutacion = 0.05; //tasa de mutacion de 0 a 1
    CLASECromosoma *ap,alfa,beta;

    while(1) {
         imshow("target",target);
        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    }
    printf("comienza\n");
    do {
 		ag.Generacion(); //creo una nueva generacion de individuos
    	ap = ag.SeleccionarMejor();
        if (!(ag.Edad()%1)) {//cada 500 iteraciones muestre la mejor solucion
            printf ("\n[%d] ",(int)ag.Edad());
            printf ("Best: %.3f\tPob:%.3f",ap->Fitness(),ag.Fitness());
            imshow("eval",getImg(ap->Cromosoma));
        }
        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    } while (ap->Fitness()<0.9 && (ag.Edad()<10000)); //condicion de parada el fitness de la mejor solucion
    printf ("\n\tGen: %d",(int)ag.Edad()); //imprimo la edad de la poblacion: numero de iteraciones totales ejecutadas (generaciones)
    for (;;) {
        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    }
    return 0;
}


Mat getImg(unsigned char *string){
	float gains[4];
	float copt;

    muestra.resDepth=LAMDA_0*crDecodificar16(string+2*0,0,10);
	muestra.resVisibility=1;//crDecodificar16(string+2*1,0,1);
    gains[0]=crDecodificar16(string+2*2,0,3);
    gains[1]=crDecodificar16(string+2*3,0,3);
    gains[2]=crDecodificar16(string+2*4,0,3);
    gains[3]=crDecodificar16(string+2*5,0,3);

    camara.gain=gains[0];
    camara.setChannelGain(gains[1],gains[2],gains[3]);
    interf.inclinacionX=crDecodificar16(string+2*6,-5e-6,5e-6);
    interf.inclinacionY=crDecodificar16(string+2*7,-5e-6,5e-6);
    copt=0;//;crDecodificar16(string+2*8,-10e-6,10e-6);
    interf.getInterferograma(copt);
    return interf.valores;

}

float eval(unsigned char *string)
{
    int c;
	float error = 0;
	Scalar suma;
    Mat img, errorImg;
    img=getImg(string);

    errorImg=img-target;
    /*
    while(1) {
         imshow("img",img);
        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    }
    */
    multiply(errorImg,errorImg,errorImg);
    suma=sum(errorImg);
    error=suma[0];// /(errorImg.cols*errorImg.rows);
	return (1/(1+error)); //ajusto fitness entre 0 y 1 segun el error
}
