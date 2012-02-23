#include <iostream>

#include <opencv2/opencv.hpp>
//#include "highgui.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>



#include "simulador.hpp"
#include "ruido.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
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

double getRuido(double tiempo, double Amp, double Freq){
    return Amp*cos(2*M_PI*(tiempo)*Freq);
}

int main(){

    //clock_t begin,end;
	Mat img ;
	int c;
    Spectrum fuente;
    fuente.initSpectrum(1e-9,1001e-9,1001);
    //fuente.initSpectrum(DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,10000);
    //fuente.setPlain(0.5e-9,1000e-9,2);        //Fuente plana todo el espectro
    double lamda=546e-9;
	fuente.setGausian(20,lamda,1e-9);       //Fuente Lab con Filtro Expectral
	//fuente.setDelta(200,lamda,0);       //Fuente Lab con Filtro Expectral
	//fuente.setDelta(10,632.8e-9,0);           //Laser He-Ne
	//fuente.setBlackbody(3000,1.18);


	Camara camara;
	Muestra muestra;
	//camara.initCamara(30,1/30,COLOR);

	//Pozo
/*
	muestra.initMuestra(163e-6,163e-6,7.030674847e6);
	muestra.setMuestraFromFile("../archivos/pozo.png",2.75e-6,IN_DEPTH,0,0);
	muestra.setMuestraPlain(1,IN_VISIBILITY);

*/
//Plano
	muestra.initMuestra(5e-3,5.e-3,100e3);
	muestra.setMuestraPlain(0,IN_DEPTH);
	muestra.setMuestraPlain(1,IN_VISIBILITY);


//	camara.initFPS(1146,1146,30,COLOR); //Pozo
	camara.initFPS(300,300,60,COLOR); //Plano
	if (camara.setSpectrumsFiles("../archivos/r1.dat","../archivos/g1.dat","../archivos/b1.dat")){
        return -1;
	};
    //camara.gain=2;
    camara.setChannelGain(1.5,1,1.392);


/*----------------------INICIO SOLO IMAGEN------------------------------*/
    //float fps=camara.fps();
    float exposureTime=camara.exposureTime();
	float timeStep=exposureTime/EXPOSURE_STEP;
    float notExposureTime=camara.getNotIntegrationTime();


	Interferometro interf;
	interf.initInterferometro(&muestra,&fuente,&camara,timeStep);
    interf.inclinacionX=1e-6;
    interf.inclinacionY=0e-6;
    float step=(lamda/2);
    float copt=0;
    namedWindow("simulador",CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO |CV_GUI_EXPANDED);
    bool dibuja=true;
    //interf.getInterferograma(copt);
    //imshow( "simulador", interf.valores);
    Mat imgw;
    string filename;
    Ruido ruido;


    float rAmp=(00.0*M_PI/180.0)*(lamda/2.0)/(M_PI*2.0);
    //ruido.initRuido("../archivos/ruido2.txt",rAmp,1);
//    float rFreq=1;
    Mat im[5];
    Mat num,den,cosa;
    int imagen=0;
    float alpha;
    float fase;
    bool toma=false;
    int pasos=36;
    int veces=2;
    int p,v;
    float pi,dp;
    dp=10;
    pi=10;
    p=0;
    v=0;
    bool corre=false;
    bool video=false;
    char filename2[50];

    double tstep=interf.timeStep();
    double t=tstep;
    double tiempo=tstep;
    double ta=0;
    double r;
    int j=0;
   // bool exporta=false;
    while(1){

        c = cvWaitKey(2);
        if (c!=-1){

            cout << "c = "<<(int)((char)c)<<endl;
            switch ((char)c){
                case 81: //Izquierda
                    interf.inclinacionX-=step;
                    dibuja=true;
                  //  cout <<"incl(X,Y) = ("<<interf.inclinacionX << " , "<< interf.inclinacionY <<")"<<endl;
                    break;
                case 82: //Arriba
                    interf.inclinacionY+=step;
                    dibuja=true;
                    //cout <<"incl(X,Y) = ("<<interf.inclinacionX << " , "<< interf.inclinacionY <<")"<<endl;
                    break;
                case 83: //derecha
                    interf.inclinacionX+=step;
                    dibuja=true;
                    //cout <<"incl(X,Y) = ("<<interf.inclinacionX << " , "<< interf.inclinacionY <<")"<<endl;
                    break;
                case 84: //abajo
                    interf.inclinacionY-=step;
                    dibuja=true;
                    //cout <<"incl(X,Y) = ("<<interf.inclinacionX << " , "<< interf.inclinacionY <<")"<<endl;
                    break;
                case -85: //+
                    step+=1e-9;
                    cout<<"Step = "<<step<<endl;
                    break;
                case -83: //-
                    step-=1e-9;
                    cout<<"Step = "<<step<<endl;
                    break;
                case 114:   //R
                    step=10e-9;
                    dibuja=true;
                    interf.inclinacionX=6.1e-7;
                    interf.inclinacionY=-1.775e-6;
                    muestra.resDepth=3.375e-6;
                    camara.gain=4;
                    camara.offset=-0.1;
                    copt=-2.75e-7;
                    rAmp=9e-8;
                    //cout<<"Step = "<<step<<endl;
                    break;
        //Depth
                case 103:   //G
                    muestra.resDepth+=step;
                    dibuja=true;
                    break;
                case 98:    //B
                    muestra.resDepth-=step;
                    dibuja=true;
                    break;
        //Ganancia
                case 102:   //F
                    camara.gain+=0.1;
                    dibuja=true;
                    break;
                case 118:    //V
                    camara.gain-=0.1;
                    dibuja=true;
                    break;

        //Camino Optico
                case 97:   //A
                    copt+=step;
                    dibuja=true;
                    break;
                case 122:    //Z
                    copt-=step;
                    dibuja=true;
                    break;

        //Amp Ruido
                case 109:   //M
                    rAmp+=step;
                    dibuja=true;
                    break;
                case 110:    //N
                    rAmp-=step;
                    dibuja=true;
                    break;
        //Camara Offset
                case 46: //.
                    camara.offset+=0.05;
                    dibuja=true;
                    break;
                case 44: //,
                    camara.offset-=0.05;
                    dibuja=true;
                    break;

                case 115:

                    cout<<endl<<"Ingrese el nombre del archivo"<<endl;
                    cin>>filename;
                    interf.valores.convertTo(imgw,CV_16UC3,65535);

                    if(imwrite(filename,imgw)){
                        cout <<"Guardado satisfactorio"<<endl;
                    } else {
                        cout <<"Ha ocurrido un error al guardar"<<endl;
                    }
                    break;
                case 32: //espacio
                    corre=true;
                    cout<<endl<<"Ingrese el nombre del archivo de texto"<<endl;
                    cin>>filename;
                    break;

                case 10: //ENTER
                    video=!video;
                    break;
                default:
                    break;
            }
            if ((char)c==27 || (char)c==113){
                break;
            }

        }
        if (corre){
            if (v<veces){

                alpha=p*dp+pi;
                fase=(alpha*M_PI/180)*(lamda/2)/(M_PI*2);
                copt=(imagen-2)*fase;
                toma=true;
                dibuja=true;
                sprintf(filename2,"%s%.2f-%d-%d.txt",filename.c_str(),alpha,v,0);
            } else {
                p++;
                v=0;
            }
            if (p>=pasos){
                corre=false;
            }






        }

        if (dibuja || video){
            dibuja=false;



            while (1){
                r=ruido.getUnif(rAmp);
                if (t<exposureTime){
                    //r=ruido.getRuido(tiempo);//,rAmp,rFreq);

                    interf.integra(r,(t-ta)/tstep);
                    ta=t;
                    tiempo+=tstep;
                    t+=tstep;
                } else if(t>=exposureTime) {
                    //r=ruido.getRuido(tiempo-(t-exposureTime));//,rAmp,rFreq);
                    interf.integra(r,(exposureTime-ta)/tstep);
                    interf.getInterferograma(copt);
                    imshow( "simulador", interf.valores);

                    if (t>=(exposureTime+notExposureTime)){
                        tiempo=tiempo;
                        t=t-(exposureTime+notExposureTime);
                        ta=0;

                    } else {
                        float tnof=notExposureTime-(t-exposureTime);
                        int skipsteps=1+(int)(tnof/tstep);
                        tiempo+=tstep*skipsteps;
                        t=tstep*skipsteps-tnof;
                        ta=0;
                    }

                    j++;


                    if (toma){
                        if (imagen>=5){
                            num=im[4]-im[0];
                            den=2*(im[3]-im[1]);
                            cosa=num/den;
                            imagen=0;
                            FILE * pFile;
                            pFile = fopen (filename2,"w");
                            if (pFile!=NULL) {
                                float val[3];
                                for (int w=0;w<num.cols;w++){
                                    for (int h=0;h<num.rows;h++){
                                        val[0]=get2D32F(num,w,h,1);
                                        val[1]=get2D32F(den,w,h,1);
                                        val[2]=get2D32F(cosa,w,h,1);
                                        fprintf(pFile,"%.3f\t%.3f\t%.3f\n",val[0],val[1],val[2]);
                                    }
                                }
                                fclose (pFile);

                            } else {
                                cout << "Unable to open file";
                            }
                            v++;

                        } else {
                            interf.valores.copyTo(im[imagen]);
                            //interf.valores.convertTo(im[imagen],CV_8UC3,255);
                            imagen++;
                        }
                        toma=false;
                    }
                    break;

                }


            }
            cout<<"j = "<< j <<endl;
           // interf.getInterferograma(copt);
           // imshow( "simulador", interf.valores);
            cout<<endl<<"Listo"<<endl;
            cout<<"Gain: "<<camara.gain<<endl;
            cout<<"Offset: "<<camara.offset<<endl;
            cout<<"Incl X: "<<interf.inclinacionX<<endl;
            cout<<"Incl Y: "<<interf.inclinacionY<<endl;
            cout<<"Res Depth: "<<muestra.resDepth<<endl;
            cout<<"Camino Óptico: "<<copt<<endl;
            cout<<"Amplitud Ruido: "<<r<<endl;
            cout<<endl;
        }

    }
    return 0;
}

/*----------------------FIN SOLO IMAGEN------------------------------*/

/*----------------------INICIO VIDEO RUIDO SIN CONTROL------------------------------*/
/*
    srand(time(NULL));
    Ruido ruido;
    ruido.initRuido("../archivos/ruido2.txt",10e-9,30);

    float fps=camara.fps();
    float exposureTime=camara.exposureTime();
    float notExposureTime=camara.getNotIntegrationTime();
	float timeStep=(exposureTime/(EXPOSURE_STEP));

	Interferometro interf;
	interf.initInterferometro(&muestra,&fuente,&camara,timeStep);

    float tstep=interf.timeStep();

    CvSize size = cvSize(camara.roi().width,camara.roi().height);
    //IplImage *img8=cvCreateImage(size,IPL_DEPTH_8U,3);

    VideoWriter writer;

    if (!writer.open(ARCHIVO_VIDEO,CV_FOURCC('M','J','P','G'),fps,size)){
        return -1;
    }


    interf.inclinacionX=0e-6;
    interf.inclinacionY=0e-6;

    float tiempo=notExposureTime;
    float t=0;
    int i=0;
    //float copt=0e-6;
    while(1){
        if (t>=exposureTime) {
            interf.getInterferograma(ruido.getRuido(tiempo));
            //interf.getInterferograma(copt);
            imshow( "simulador", interf.valores);
            interf.valores.convertTo(img,CV_8UC3,255);
            writer<<img;

            t=t-exposureTime;
            if(t<notExposureTime){
                t=0;
            } else {
                t=t-notExposureTime;
            }
            i++;
            tiempo=i/fps;
            cout<<"tiempo = "<< tiempo <<endl;
        } else {
            //cout<<"integra, i="<<i<<endl;
            interf.integra(ruido.getRuido(tiempo));
            //interf.integra(copt);
            t+=tstep;
            tiempo+=tstep;
        }

        c = cvWaitKey(2);
        if ((char)c==27){
            break;
        }
    }
    return 0;
}

*/
/*----------------------FIN VIDEO RUIDO SIN CONTROL------------------------------*/

/*----------------------INICIO VIDEO RUIDO CON CONTROL------------------------------*/
/*


    //FILE * pFile;
    //pFile = fopen ("archivos/si_rnn.xls","w");

    double contraste;
    double heta;
    double time;
    int status=0;
    double baseContrast=0;
    double bestContrast=0;
    double bestContrastInRound=0;
    double sumContrast=0;
//    int nt=(int)(ti/ruido.getDeltaT());
    //for (int t=0;t<(int)(MAXTIME/ti);t++){
    int vs=0;
    double *prueba;
    double *control;
    int N=ruido.getNset();
    prueba=new double [N];
    control=new double [N];
    for (int i=0;i<N;i++){
        prueba[i]=0;
        control[i]=0;
    }
    float dt=ruido.getDeltaT();

    float maxAmp=0;

    //variables de las se~nales de control
    //char *cromosoma;
    //int sizeCromosoma=BYTES_AMP+BYTES_SIGMA+BYTES_TO;
    //cromosoma=new char[sizeCromosoma];

    double amp=0;
    double s=0;
    double to=0;
    double bestAmp=0;
    double ampSwim=0;
    double bestS=0;
    double sSwim=0;
    double bestTo=0;
    int inbest=0;

    FILE *fp;
    fp=fopen(ARCHIVO_DATA,"w+");
    if (fp==NULL){
        return 1;
    }

    int superior=0;
    time=0;
    while (1){
        time+=tstep;
        ruido.setNoise(5e-9);
        ruido.iFFT();
        ruido.copyTimeArray();
        int nt=ruido.getNset();
        float ruidovalue;
        if (time<nit){
            //no hace nada
        } else
        for (int i=0;i<nt-1;i++){
            ruidovalue=ruido.getV()-(control[i]+prueba[i]);
            interf.integra(ruidovalue);
        }
        interf.getInterferograma(ruido.getV()-(control[nt-1]+prueba[nt-1]));
        imshow( "simulador", interf.valores);
        interf.valores.convertTo(img,CV_8UC3,255);
        writer<<img;

        Mat blackwhite;
        cvtColor(interf.valores, blackwhite, CV_RGB2GRAY);

        double min,max;
        minMaxLoc(blackwhite, &min, &max);
        contraste=max-min;

        fprintf(fp,"%f\t%f\t",time,contraste);
        printf("t=%.3f\tc=%.3f\t%.2f\t",time,contraste,100*contraste/bestContrastInRound);
        printf("A=%.4f\t s=%.4f\tto=%.4f\n",amp*1e9,s,to);
        switch (status){
            case 0:
                inbest=0;
                if (time<GET_TIME){
                    vs++;
                    baseContrast+=contraste;
                } else {
                    baseContrast/=vs;
                    vs=0;
                    status=1;
                    heta=(LAMDA_0/(4*M_PI))*ti*(1-((2*baseContrast)/(M_DEFAULT*(max+min))));
                    heta*=heta;
                    maxAmp=N*sqrt(heta/ti);
                    bestContrast=baseContrast;
                    fprintf(fp,"Mejor contraste calculado: %f.  Comienza busqueda aleatoria\t",bestContrast);
                    printf("\n\n\tMejor contraste calculado: %.4f\n\n",bestContrast);
                }
                break;
            case 1:
                inbest=0;
                amp=2*maxAmp*(double)(rand()%1000/1000.f)-maxAmp;
                s=(ti/2)*(double)(rand()%1000/1000.f)+(ti/100);
                to=0;
                gauss(prueba,dt,N,amp,to,s);
                status=2;
                fprintf(fp,"Generando nueva Gausiana: Amp=%.4fnm  s=%.5fs\t",amp*1e9,s);
                printf("\n\tGenerando nueva Gausiana: Amp=%.3f\t s=%.3f\n",amp*1e9,s);
                superior=0;
                bestContrastInRound=bestContrast;
                sumContrast=0;
                break;
            case 2:
                if (contraste>(bestContrastInRound*PORCENTAJE_JUEGO)||superior>=VECES_SUPERIOR){
                    if(superior>=VECES_SUPERIOR){
                        sumContrast/=VECES_SUPERIOR;
                        if (sumContrast>bestContrastInRound){
                            bestContrastInRound=sumContrast;
                            bestTo=to;
                            bestAmp=amp;
                            bestS=s;
                            fprintf(fp,"Mejor to encontrado: to=%fs\t",bestTo);
                            printf("\n\tEncontro mejor to=%.4f\n",bestTo);
                            inbest=1;
                        }
                        sumContrast=0;
                        superior=0;
                        to+=(N/TO_DIV)*dt;
                        gauss(prueba,dt,N,amp,to,s);
                    } else {
                        sumContrast+=contraste;
                        superior++;
                    }
                } else {
                    superior=0;
                    sumContrast=0;
                    to+=(N/TO_DIV)*dt;
                    gauss(prueba,dt,N,amp,to,s);
                }
                if (to>ti){
                    if (bestContrastInRound<=bestContrast){
                        status=1;
                        inbest=0;
                    } else {
                        status=3;
                        bestContrast=bestContrastInRound;
                        ampSwim=2*amp;
                        //bestAmp=amp;
                        amp=(ampSwim/AMP_DIV);
                        to=bestTo;

                        gauss(prueba,dt,N,amp,bestTo,bestS);
                        fprintf(fp,"Comienza barrido de Amplitud\t");
                        printf("\n\tComienza barrido de Amplitud\n");
                    }
                }
                break;
            case 3:
                if (contraste>(bestContrastInRound*PORCENTAJE_JUEGO)||superior>=VECES_SUPERIOR){
                    if (superior>=VECES_SUPERIOR){
                        sumContrast/=VECES_SUPERIOR;
                        if (sumContrast>bestContrastInRound){
                            bestContrastInRound=sumContrast;
                            bestTo=to;
                            bestAmp=amp;
                            bestS=s;
                            inbest=1;
                            fprintf(fp,"Mejor Amplitud encotnrada: amp=%.4fnm\t",bestAmp*1e9);
                            printf("\n\tEncontro mejor amp=%.4f\n",bestAmp);
                        }
                        sumContrast=0;

                        superior=0;
                        if (ampSwim>0){
                            amp+=(ampSwim/AMP_DIV);
                        } else {
                            amp-=(ampSwim/AMP_DIV);
                        }
                        gauss(prueba,dt,N,amp,bestTo,bestS);
                    } else {
                        sumContrast+=contraste;
                        superior++;
                    }
                } else {
                    superior=0;
                    sumContrast=0;

                    if (ampSwim>0){
                        amp+=(ampSwim/AMP_DIV);
                    } else {
                        amp-=(ampSwim/AMP_DIV);
                    }
                    gauss(prueba,dt,N,amp,bestTo,bestS);
                }
                if (fabs(amp)>fabs(ampSwim)){
                        status=4;
                        bestContrast=bestContrastInRound;
                        sSwim=2*s;
                        //bestS=s;

                        amp=bestAmp;

                        s=(sSwim/AMP_DIV);
                        gauss(prueba,dt,N,bestAmp,bestTo,s);
                        fprintf(fp,"Comienza barrido de Sigma\t");
                        printf("\n\tComienza barrido de Sigma\n");
                }
                break;
            case 4:
                if (contraste>(bestContrastInRound*PORCENTAJE_JUEGO)||superior>=VECES_SUPERIOR){
                    if (superior>=VECES_SUPERIOR){
                        sumContrast/=VECES_SUPERIOR;
                        if (sumContrast>bestContrastInRound){
                            bestContrastInRound=sumContrast;
                            bestTo=to;
                            bestAmp=amp;
                            bestS=s;
                            inbest=1;
                            fprintf(fp,"Mejor sigma encontrada: s=%fs\t",bestS);
                            printf("\n\tEncontro mejor s=%.4f\n",bestS);
                        }
                        sumContrast=0;
                        superior=0;
                        s+=(sSwim/S_DIV);
                        gauss(prueba,dt,N,amp,bestTo,bestS);

                    } else {
                        sumContrast+=contraste;
                        superior++;
                    }
                } else {
                    superior=0;
                    sumContrast=0;

                    s+=(sSwim/S_DIV);
                    gauss(prueba,dt,N,amp,bestTo,bestS);
                }
                if (s>sSwim){
                        gauss(prueba,dt,N,bestAmp,bestTo,bestS);
                        add(prueba,control,N);
                        bestContrast=bestContrastInRound;
                        fprintf(fp,"Se agrega la gaussiana al control: Amp=%.4fnm s=%fs to=%fs\t",bestAmp*1e9,bestS,bestTo);
                        printf("\n\n\tSe agrega la gaussiana al control: Amp=%.4fnm s=%fs to=%fs\n",bestAmp*1e9,bestS,bestTo);
                        if (bestContrast>baseContrast*(1+PORCENTAJE_STOP)){
                            status=10;
                            inbest=0;
                            fprintf(fp,"Mas del 50 del contraste obtenido\t");
                            printf("\n\n\t\tMas del 50 del contraste obtenido\n\n");
                        } else {
                            status=1;
                            inbest=0;
                        }
                }
                break;
            case 10:
                if (inbest==1){
                    gauss(prueba,dt,N,bestAmp,bestTo,bestS);
                    add(prueba,control,N);
                    bestContrast=bestContrastInRound;
                    fprintf(fp,"Se agrega la gaussiana al control: Amp=%.4fnm s=%fs to=%fs\t",bestAmp*1e9,bestS,bestTo);
                    printf("\n\n\tSe agrega la gaussiana al control: Amp=%.4fnm s=%fs to=%fs\n",bestAmp*1e9,bestS,bestTo);
                } else {
                    clear(prueba,N);
                }
                status=11;
                fprintf(fp,"Se deja de buscar aleatoriamente3\t");
                printf("\n\n\tSe deja de buscar aleatoriamente3\n");
                camara.setROI(10,300,100,100);
                break;
            default:
                break;
        }


        fprintf(fp,"\n");
		c = cvWaitKey(2);
        if ((char)c==27){
            if (status<10){
                status=10;
            } else {
                break;
            }
        } else if ((char)c==13){
            status=2;

        }
        if (time>=MAXTIME_CONTROL&& status<10 &&inbest==0){
            status=10;
        }
        if (time>=MAXTIME_TOTAL&& status>=10 ){
            break;
        }


    }
    delete[] control;
    delete[] prueba;
    fclose(fp);
//    delete[] dst;
	return 0;
}
*/
/*----------------------FIN VIDEO RUIDO CON CONTROL------------------------------*/
