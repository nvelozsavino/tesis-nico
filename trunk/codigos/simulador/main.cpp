#include <iostream>

#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>


#include "spectrum.hpp"
#include "generales.hpp"
#include "muestra.hpp"
//#include "perturbacion.h"
#include "camara.hpp"
#include "interferometro.hpp"
#include <iostream>
#define TIMESTEP 1e-3
#define MAXTIME 5
#define FREQ 100
using namespace std;
using namespace cv;


int main(){
    //clock_t begin,end;
	Mat img ;
	int c;
    Spectrum fuente;
    fuente.initSpectrum(DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,1000);
    //fuente.setPlain(0.5e-9,1000e-9,1);
	fuente.setGausian(1,546.1e-9,10e-9);
	Camara camara;
	Muestra muestra;
	//camara.initCamara(30,1/30,COLOR);

	muestra.initMuestra(50e-3,100e-3,1e3);
	muestra.setMuestraFromFile("pozo.png",7*546.1e-9,IN_DEPTH,0,0);
	muestra.setMuestraPlain(1,IN_VISIBILITY);
	camara.initCamaraFromFiles(30, 1/30,"red","green","blue");
	Interferometro interf;
	interf.initInterferometro(&muestra,&fuente,&camara,TIMESTEP,0e-9,0e-9);
    float fps=camara.fps;

    CvSize size = cvSize(muestra.width,muestra.height);
    //IplImage *img8=cvCreateImage(size,IPL_DEPTH_8U,3);
    VideoWriter writer;

    if (!writer.open("video2.avi",CV_FOURCC('D', 'I', 'V', '3'),fps,size)){
        return 1;
    }

//    int i=0;
    interf.inclinacionX=-1e-6;
    interf.inclinacionY=1e-6;
    float f=FREQ;
    float tcamara=0;
    float op;
//    int sum=0;
    //Mat cuadro(interf.valores);
    //cuadro.setTo(Scalar::all(0));
    for (float t=0;t<MAXTIME;t+=TIMESTEP){
        tcamara+=TIMESTEP;
        //sum++;
        //float ran=;
        int u1,u2;
        if (t>1){
            u1=1;
        } else {
            u1=0;
        }
        if (t>2){
            u2=1;
        } else {
            u2=0;
        }
        op=u1*(exp(-4*(t-1)/0.4))*(600e-9*sin(2*M_PI*f*t))+u2*(exp(-4*(t-2.5)/0.4))*(900e-9*sin(2*M_PI*f*0.8*t));

        //float op2=u1*(exp(-(t-1)/0.1))+u2*(exp(-(t-2)/0.3));

        //cout <<"t: "<<t<<  " op2: "<<op2<<endl;
        interf.integra(op);
        //scaleAdd(interf.valores,TIMESTEP/camara.integrationTime,cuadro,cuadro);
        if (tcamara>=camara.integrationTime){
            //f=(FREQ*(float)((rand()%1000)/(float)1000));
            //cuadro/=sum;
            //sum=0;
            interf.getInterferograma(op);
            //cvtColor(interf.valores,interf.valores,CV_XYZ2BGR);


            cout <<"t: "<<t<<endl;
            imshow( "simulador", interf.valores);
            Mat hist;
            float rangos[]={0,1};
            getHist(interf.valores,hist,interf.valores.cols,50,rangos);
            interf.valores.convertTo(img,CV_8UC3,255);

            //hist2.convertTo(hist,CV_8UC3);
            imshow( "histograma", hist);
            Mat tempA;
            tempA.create(img.rows+hist.rows,img.cols,hist.type());
            tempA.setTo(Scalar::all(0));
            Mat roiA(tempA, Rect(0,0,img.cols,img.rows));
            Mat roiB(tempA, Rect(0,img.rows, hist.cols, hist.rows));
            img.copyTo(roiA);
            hist.copyTo(roiB);





        imshow( "simhist", tempA);
            writer<<tempA;//interf.getInterferograma((100e-9*sin(2*M_PI*i/20)));
            //cuadro.setTo(Scalar::all(0));
            tcamara=0;
        }
        //cout<< "width: "<<img.rows<< " height: " << img.cols<< "channels: "<< img.channels()<<endl;
		//printf("tiempo = %.2f\n", (float)(i/fps));
		c = cvWaitKey(2);
        if( (char) c == 27 )
            break;
	}
    //cvDestroyWindow("simulador");
    //cvReleaseVideoWriter(&writer);
	return 0;



}
