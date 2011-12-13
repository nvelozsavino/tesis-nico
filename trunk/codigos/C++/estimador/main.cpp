#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "clase_ag.hpp"
#include "extra_ag.hpp"

#include <opencv2/opencv.hpp>

#define STEP 0.1

#define ORDEN 5
#define nBytes 2*ORDEN //longitud maxima del string (cromosoma) en bytes

CLASECromosoma a,b,c,d;
CLASEAGenetico ag;

using namespace cv;

float eval(unsigned char *);

int getFrame(Mat &frame,VideoCapture &video){

    return 0;

}

int main()
{

    Mat frame;
    VideoCapture video("/home/nico/Documents/tesis/video.avi");
    if(!video.isOpened()) { // check if we succeeded
        return -1;
    }
    char c;
    if (!video.grab()){
        return -2;
    }
    video>>frame;

    while (c!=13){
        imshow("video",frame);
        //imshow("video",frame);
        c = cvWaitKey(2);
        if (c!=-1){
            printf("hola %d\n",c);
        }

        if (c==27){
            break;
        } else if (c==83){
            if (!video.grab()){
                return -2;
            }
            video>>frame;
        }

    }
    return 0;
    int frameCount;
    frameCount=video.get(CV_CAP_PROP_FRAME_COUNT);
    return frameCount;
    for (int i=0;i<frameCount;i++){
        video>>frame;
        imshow("video",frame);
        if(waitKey(30) >= 0) {
            break;
        }
    }
    return 0;

//    float best_fit=0;
    srand ( time(NULL) );
	ag.PoblacionAleatoria(250,nBytes); //creo una poblacion de 200 individuos, de longitud 'nBytes' cada string
	ag.FuncionEvaluacion(eval); //defino cual es la funcion que evalua cada cromosoma y devuelve el fitnes entre 0 y 1 (Es llamada automaticamante por al AG
    ag.dTasaMutacion = 0.05; //tasa de mutacion de 0 a 1
    CLASECromosoma *ap,alfa,beta;
//    float f;


    //grabo el target (coeficientes deseados)
   do
   {
 		ag.Generacion(); //creo una nueva generacion de individuos
    	ap = ag.SeleccionarMejor();
   }
   while (ap->Fitness()<0.9 && (ag.Edad()<10000)); //condicion de parada el fitness de la mejor solucion
}


float eval(unsigned char *string)
{

	return (1/(1+sqrt(0))); //ajusto fitness entre 0 y 1 segun el error
}

