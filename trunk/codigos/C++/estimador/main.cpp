#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "clase_ag.hpp"
#include "extra_ag.hpp"

#include "simulador.hpp"
#include <opencv2/opencv.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#define STEP 0.1

#define ORDEN 5
#define nBytes 2*ORDEN //longitud maxima del string (cromosoma) en bytes


#define LAMDA_0 546.1e-9
#define LAMDA_MIN 500e-9
#define LAMDA_MAX 600e-9
#define SIGMA_MIN 1e-9
#define SIGMA_MAX 100e-9
#define INCLINACION_MIN 0
#define INCLINACION_MAX 10e-6



CLASECromosoma a,b,c,d;
CLASEAGenetico ag;

using namespace cv;

float eval(unsigned char *);
int getResult(Mat *dst, unsigned char *string);

int width,height;
Mat frame;
int main()
{

    Mat result;

    VideoCapture video("/home/nico/Documents/tesis/video.avi");
    if(!video.isOpened()) { // check if we succeeded
        return -1;
    }
    char c;
    if (!video.grab()){
        return -2;
    }
    video>>frame;

    width=frame.cols;
    height=frame.rows;








//    float best_fit=0;
    srand ( time(NULL) );
	ag.PoblacionAleatoria(10,nBytes); //creo una poblacion de 200 individuos, de longitud 'nBytes' cada string
	ag.FuncionEvaluacion(eval); //defino cual es la funcion que evalua cada cromosoma y devuelve el fitnes entre 0 y 1 (Es llamada automaticamante por al AG
    ag.dTasaMutacion = 0.05; //tasa de mutacion de 0 a 1
    CLASECromosoma *ap,alfa,beta;
//    float f;


    //grabo el target (coeficientes deseados)
   do
   {
 		ag.Generacion(); //creo una nueva generacion de individuos
    	ap = ag.SeleccionarMejor();
    	if (!(ag.Edad()%1)){
            getResult(&result,ap->Cromosoma);
            imshow("result",result);
            imshow("frame",frame);
            c=cvWaitKey(20);
           if (c!=-1){
                break;
           }
            printf("Fitness=%f\tEdad=%d\n",ap->Fitness(),ag.Edad());
    	}
   }
   while (ap->Fitness()<0.9 && (ag.Edad()<10000)); //condicion de parada el fitness de la mejor solucion
    printf("Fitness=%f\tEdad=%d\n",ap->Fitness(),ag.Edad());
   for(;;){
            getResult(&result,ap->Cromosoma);
            imshow("result",result);
            imshow("frame",frame);

       c=cvWaitKey(30);
       if (c!=-1){
            break;
       }
   }
   return 43;
}

int getResult(Mat *dst, unsigned char *string){
    float lamda=crDecodificar16(string+2*0,LAMDA_MIN,LAMDA_MAX);
    float sigma=crDecodificar16(string+2*1,SIGMA_MIN,SIGMA_MAX);
    float incX=crDecodificar16(string+2*2,INCLINACION_MIN,INCLINACION_MAX);
    float incY=crDecodificar16(string+2*3,INCLINACION_MIN,INCLINACION_MAX);
    float visibilidad=crDecodificar16(string+2*4,0,1);



    Spectrum fuente;
    fuente.initSpectrum(DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,1000);
    //fuente.setPlain(0.5e-9,1000e-9,1);
	fuente.setGausian(1,lamda,sigma);
	Camara camara;
	Muestra muestra;
	//camara.initCamara(30,1/30,COLOR);

	muestra.initMuestra(1000e-3,1000e-3,1e3);
	//muestra.setMuestraFromFile("../archivos/pozo.png",7*LAMDA_0,IN_DEPTH,0,0);
	muestra.setMuestraPlain(0,IN_DEPTH);
	muestra.setMuestraPlain(visibilidad,IN_VISIBILITY);
	camara.initFPS(width,height,30,COLOR);
	if (camara.setSpectrumsFiles("../archivos/red","../archivos/green","../archivos/blue")){
        return -1;
	};

    float exposureTime=camara.exposureTime();

	Interferometro interf;
	interf.initInterferometro(&muestra,&fuente,&camara,exposureTime);

    interf.inclinacionX=incX;
    interf.inclinacionY=incY;
    interf.getInterferograma(0);
    interf.valores.copyTo(*dst);
    return 0;
}

float eval(unsigned char *string)
{
    Scalar suma;
    Mat result,error;
    Mat f;
    getResult(&result, string);
    frame.convertTo(f,result.type());
    f/=255;

    error=result-f;
    error=error.mul(error);

    suma=sum(error);
    float e=0;
    for (int i=0; i< result.channels();i++){
        e+=suma[i];
    }
	return (1/(1+sqrt(e))); //ajusto fitness entre 0 y 1 segun el error
}

