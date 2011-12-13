#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "clase_ag.hpp"
#include "extra_ag.hpp"

#define MIN_VAL -10
#define MAX_VAL 10
#define ORDEN 5
#define nBytes 2*ORDEN //longitud maxima del string (cromosoma) en bytes

#define MAXIMO 5
#define STEP 0.1

CLASECromosoma a,b,c,d;
CLASEAGenetico ag;

float eval(unsigned char *);
FILE *arch, *out;

float coef_solucion[8]={0,-2.4,3.6,-1.3,2,0.1,0,0}; //son los coeficientes del polinomio deseado (esta es la solucion que deberia obtenerse)
float coeficientes[nBytes]; //coeficientes resultantes de decodificar el cromosoma actual a evaluar

float polinomio (float *coeficientes, int orden, float t); //funcion que evalua un polinomio entre 0 y 1, de orden dado
float funcion_target(float t); //funcion que genera la forma de onda deseada

void mostrar(unsigned char *, unsigned long);
void mostrarf(unsigned char *, unsigned long);

int main()
{
    float best_fit=0;
    srand ( time(NULL) );
	ag.PoblacionAleatoria(250,nBytes); //creo una poblacion de 200 individuos, de longitud 'nBytes' cada string
	ag.FuncionEvaluacion(eval); //defino cual es la funcion que evalua cada cromosoma y devuelve el fitnes entre 0 y 1 (Es llamada automaticamante por al AG
    ag.dTasaMutacion = 0.05; //tasa de mutacion de 0 a 1
    CLASECromosoma *ap,alfa,beta;
    float f;

   arch = fopen ("ag_poly.xls","w+");
   out = fopen ("solucion.xls","w+");
//	randomize();
   for (int i=0;i<ORDEN;i++)
        fprintf (arch,"c[%d]\t",i); //encabezado
   fprintf (arch,"\n");

    //grabo el target (coeficientes deseados)
    for (register float t=0; t<MAXIMO; t+=STEP)
    {
//        f = polinomio(coef_solucion,ORDEN,t); //calculo el valor para cada 't'
        f = funcion_target(t);
        fprintf (out, "%.3f\t",f);
    }
    fprintf (out, "\n");
   do
   {
 		ag.Generacion(); //creo una nueva generacion de individuos
    	ap = ag.SeleccionarMejor();
        for (int i=0;i<ORDEN;i++)
            fprintf (arch,"%f\t",crDecodificar16((ap->Cromosoma)+2*i,MIN_VAL,MAX_VAL)); //encabezado
        fprintf (arch,"\n");
//        fprintf (arch,"%.3f\t%.3f\n",ap->Fitness(),ag.Fitness());
        if (!(ag.Edad()%10)) //cada 500 iteraciones muestre la mejor solucion
        {
            printf ("\n[%d] ",ag.Edad());
            //decodifico el string en los coeficientes y grafico la forma de onda
            if (fabs(ap->Fitness() - best_fit)>0.005) //si el nuevo fitness del mejor cambio perceptiblemente con el anterior mejor, actualizo
            {
                printf ("Best: %.3f\tPob:%.3f",ap->Fitness(),ag.Fitness());
                best_fit = ap->Fitness(); //nuevo mejor fitness, actualizado (si no hay elitismo no tiene porque siempre aumentar, podria algunas veces disminuir)
                for (int i=0; i<nBytes; i++)
                    coeficientes[i]=crDecodificar16(ap->Cromosoma+2*i,MIN_VAL,MAX_VAL); //decodifico entre MIN_VAL y MAX_VAL en dato dado por el byte 'i'
                for (register float t=0; t<MAXIMO; t+=STEP)
                {
                    f = polinomio(coeficientes,ORDEN,t); //calculo el valor para cada 'f'
                    fprintf (out, "%.3f\t",f); //escribo en el archivo
                }
                fprintf (out, "\n"); //
            }
        }
   }
   while (ap->Fitness()<0.9 && (ag.Edad()<10000)); //condicion de parada el fitness de la mejor solucion
   printf ("\n\tGen: %d",ag.Edad()); //imprimo la edad de la poblacion: numero de iteraciones totales ejecutadas (generaciones)
   fclose(arch);
}


float eval(unsigned char *string)
{
	float error = 0, acum = 0;
//	float coeficientes[nBytes]; //coeficientes resultantes de decodificar el cromosoma actual a evaluar
	//para evaluar los coeficientes del polinomio dados por el string, procedo a decodificar cada parametro (byte)
    for (int i=0; i<nBytes; i++)
    {
        coeficientes[i]=crDecodificar16(string+2*i,MIN_VAL,MAX_VAL); //decodifico entre MIN_VAL y MAX_VAL en dato dado por el byte 'i'
    }
    int nPuntos=0;
    //una vez tengo los coeficientes, procedo a calcular el error comparado con la ecuacion target (error promedio)
    for (register float t=0; t<MAXIMO; t+=STEP)
    {
        error = fabs(polinomio(coeficientes,ORDEN,t)- funcion_target(t));
        acum += error*error; //calculo el error acumulado para la solucion actual
        nPuntos++;
    }
    acum /= nPuntos; //promedio el error, aunque esto no tiene mayor impacto al final, si afecta los transitorios
	return (1/(1+sqrt(acum))); //ajusto fitness entre 0 y 1 segun el error
}

void mostrar(unsigned char *str, unsigned long largo)
{
	for (int i=0; i<largo ;largo++)
        printf ("%X ",*(str+i));
}

void mostrarf(unsigned char *str, unsigned long largo)
{
	for (int i=0; i<largo ;i++)
        printf ("%f ",crDecodificar16(str+2*i,MIN_VAL,MAX_VAL));
}

float polinomio (float *coeficientes, int orden, float t)
{
    //y = a0 + a1*t + a2*t˄2 + a3*t˄3+ ... + an*t˄n
    float y=0;
    for (int i=0; i<orden;i++)
    {
        y += coeficientes[i]*pow(t,(float)i); //calculo del aporte del coeficiente i-esimo al polinomio
    }
    return y;
}

float funcion_target(float t)
{
        return 3*sin(1.5*t)/(t+1)+t;
}
