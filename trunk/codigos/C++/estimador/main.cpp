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

#define ORDEN 3
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
    Mat imagen;
    Mat result;

    VideoCapture video("/home/nico/Documents/tesis/video.avi");
    if(!video.isOpened()) { // check if we succeeded
        return -1;
    }
    char c;
    if (!video.grab()){
        return -2;
    }
    video>>imagen;

    width=frame.cols;
    height=frame.rows;

    cvtColor(imagen,frame,CV_RGB2GRAY);
    //frame.convertTo(frame,CV_16SC1);





//    float best_fit=0;
    srand ( time(NULL) );
	ag.PoblacionAleatoria(10,nBytes); //creo una poblacion de 200 individuos, de longitud 'nBytes' cada string
	ag.FuncionEvaluacion(eval); //defino cual es la funcion que evalua cada cromosoma y devuelve el fitnes entre 0 y 1 (Es llamada automaticamante por al AG
    ag.dTasaMutacion = 0.1; //tasa de mutacion de 0 a 1
    ag.usarElitismo=true;
    ag.usarHarem=true;
    CLASECromosoma *ap,alfa,beta;
//    float f;


    //grabo el target (coeficientes deseados)
   do
   {
 		ag.Generacion(); //creo una nueva generacion de individuos
    	ap = ag.SeleccionarMejor();
    	if (!(ag.Edad()%10)){
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
            getResult(&result,ap->Cromosoma);
            float alpha=crDecodificar16(ap->Cromosoma+2*0,0,180)/M_PI;
    float franjas=crDecodificar16(ap->Cromosoma+2*1,0,10);
    float gris=crDecodificar16(ap->Cromosoma+2*2,0,1);
    printf("alpha=%f\tfranjas=%f\tgris=%f\n",alpha,franjas,gris);
   for(;;){

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
    float alpha=crDecodificar16(string+2*0,0,180)/M_PI;
    float franjas=crDecodificar16(string+2*1,0,10);
    float gris=crDecodificar16(string+2*2,0,1);

    float f=franjas/(float)frame.cols;
    float value;
    Mat prueba(frame.size(),CV_8UC1);
    for (unsigned int x=0;x<frame.cols;x++){
        for (unsigned int y=0;y<frame.rows;y++){
            value=255*(gris*0.5*(1+sin(2*M_PI*f*(x*cos(alpha)+y*sin(alpha)))));
            set2D8U(prueba,x,y,0,(unsigned int)value);
        }

    }

    prueba.copyTo(*dst);
    return 0;
}

float eval(unsigned char *string)
{
    Scalar suma;
    Mat original,result,error;

    getResult(&result, string);
    result.convertTo(result,CV_32FC1);
    result/=255;
    frame.convertTo(original,CV_32FC1);
    original/=255;
    error=result-original;
    error=error.mul(error);
     //       imshow("result",result);
     //       imshow("error",error);

       //cvWaitKey(30);
    suma=sum(error);
    float e=0;
    for (int i=0; i< result.channels();i++){
        e+=suma[i];
    }
	return (1/(1+sqrt(e))); //ajusto fitness entre 0 y 1 segun el error
}

