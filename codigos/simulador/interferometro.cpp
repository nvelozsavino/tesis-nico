#include "interferometro.hpp"
using namespace cv;

void Interferometro::initInterferometro (Muestra *myMuestra, Spectrum *myFuente, Camara *myCamara, float timestep, float inclX=0, float inclY=0){
	muestra=myMuestra;
	camara=myCamara;
	fuente=myFuente;
	Scalar io;
    double normMax;
    double normMin;
    double norm=0;
    float Iomax=0;
	float endFreqFuente,endFreqSensor;
	endFreqFuente=LIGHT_SPEED/fuente->startLamda;
	Mat multip;
	Mat spdFuente;
	float endFreqMultip;
//	interferometro->perturbacion=perturbacion;
	inclinacionX=inclX;
	inclinacionY=inclY;
    scale=timestep/camara->integrationTime;
	width=muestra->width;
	height=muestra->height;
	int dim;
	if (camara->tipo==COLOR){
	    dim=3;
	    valores.create(width, height, CV_32FC3);
	} else {
	    valores.create(width, height, CV_32FC1);
	    dim=1;
	}
	    //Mat multip[3];
    Xmax=new float[dim];
    Xmin=new float[dim];
    interferograma=new Mat[dim];
    interf=new Mat[dim];
    Io=new float[dim];






    for (int i=0;i<dim;i++){
        //fuente->lamda2freq();
        endFreqSensor=LIGHT_SPEED/camara->sensor[i].startLamda;
        multFreq(fuente->valoresFreq,endFreqFuente,camara->sensor[i].valoresFreq,endFreqSensor,&multip,&endFreqMultip);
        multiply(multip,multip,multip);

        float maxLamda;
        if (fuente->endLamda>camara->sensor[i].endLamda){
            maxLamda=fuente->endLamda;
        } else {
            maxLamda=camara->sensor[i].endLamda;
        }
        //mult(*fuente,camara->sensor[i],multip[i],1);

        Xmin[i]=2*(LIGHT_SPEED/endFreqMultip);
        idft(multip,interferograma[i]);
        Xmax[i]=ALPHA*maxLamda/2;
        io=sum(multip);
        Io[i]=io[0];
        minMaxLoc(interferograma[i],&normMin,&normMax);
        if (Io[i]>Iomax){
            Iomax=Io[i];
        }

        if (fabs(normMin)>fabs(normMax)){
         //   Io[i]=fabs(normMin);
            if (norm<fabs(normMin)){
                norm=fabs(normMin);
            }
        } else {
           // Io[i]=fabs(normMax);
            if (norm<fabs(normMax)){
                norm=fabs(normMax);
            }
        }
       // interf[i]+=normMin;




    }
    for (int i=0;i<dim;i++){
        interferograma[i]/=norm;
        Io[i]/=Iomax;
        Io[i]*=0.5;
        //Io[i]=1;
        ajustaFFT(interferograma[i],interferograma[i]);
        interferograma[i].copyTo(interf[i]);
        interf[i]*=scale;
        //cout<<"interferograma=" <<interferograma[i].rows<<"  interf="<<interf[i].rows<<endl;

    }

    //integra(Xmax[0]/3,1);
    Mat imagen;
    imagen.create(500,1800,CV_32FC3);
    imagen.setTo(Scalar::all(0));
    for (int i=0;i<dim;i++){
        for (int x=0;x<imagen.cols;x++){
            int j=x*interferograma[i].rows/imagen.cols;
            int y=50+100*(i)+50*(get1D32F(interferograma[i],j));

            //cout<<"x: " << j*2*Xmax[i]/(interf[i].rows-1) << " y: "<<y-250 <<endl;
            set2D32FC(imagen,y,x,i,1);
            set2D32FC(imagen,100*i,x,i,1);
            set2D32FC(imagen,50+100*i,x,i,1);
            set2D32FC(imagen,100+100*i,x,i,1);
        }
        for (int y=0;y<50;y++){
            set2D32FC(imagen,50+100*i+y-25,(int)(imagen.cols/2),i,1);
        }

    }
    imshow( "cosas", imagen);
    /*for (;;){
        int c = cvWaitKey(1000);
        if( (char) c == 27)
        break;
    }
*/

}

Interferometro::~Interferometro(){
    delete[] Xmax;
    delete[] Xmin;
    delete[] interferograma;
    delete[] interf;
    delete[] Io;
}


void Interferometro::integra(float opticalPath){
    Mat temp;
    int desp;
    int dim;
    if (camara->tipo==COLOR){
		dim=3;
	} else {
		dim=1;
	}


	for (int d=0;d<dim;d++){
	    float v=opticalPath*interferograma[d].rows/Xmax[d];//2*fabs(depth)+Xmax[i])/(2*Xmax[i])
	    desp=(int)v;
        desplaza(interferograma[d],temp,desp);
        interf[d]+=temp*scale;
        //scaleAdd(temp,scale,interf[d],interf[d]);
	}
}



void Interferometro::getInterferograma(float opticalPath){
	int dim;
//	float coseno;
//	float lamda;
//	float valor;

//    uchar i,j,k;
 //   uchar channels=img.channels();
	unsigned int width,height;
	unsigned int x,y;
	width=muestra->width;
	height=muestra->height;
	if (camara->tipo==COLOR){
		dim=3;
		valores.create(muestra->width,muestra->height,CV_32FC3);
	} else {
		dim=1;
		valores.create(muestra->width,muestra->height,CV_32FC1);
	}
    float v,yvd,yvd1,valor,val;
    //int vd;
    float depth,inclinacion;
    float vis;
	    //cout << "Xmax="<<Xmax[i]<<" Xmin="<<Xmin[i]<<" OpticalPath="<<opticalPath<<endl;
    //int c = cvWaitKey(500);
    for (x=0;x<width;x++){
        for (y=0;y<height;y++){
            //depth=
            inclinacion=x*inclinacionX/width + y*inclinacionY/height;
            depth=get2D32F(muestra->depth,x,y)+opticalPath+inclinacion;
            //depth*=2;
            vis=get2D32F(muestra->visibilidad,x,y)/2;
            //cout <<"depth = "<<depth<<endl;
            //int c = cvWaitKey(25);

            for (int i=0;i<dim;i++){
                if (fabs(depth)<=Xmax[i]/2){
                    v=(interf[i].rows-1)*(2*depth+Xmax[i])/(2*Xmax[i]);
                    //vd=(int)v;
                    yvd=get1D32F(interf[i],(int)v);
                    yvd1=get1D32F(interf[i],(int)v+1);
                    val=((yvd1-yvd)*(v-(int)v)+yvd);
                    valor=Io[i]*(0.5+vis+(2*sqrt(0.5*vis)*val));
                    //cout <<"valor = "<<valor<<endl;

                    set2D32FC(valores,x,y,i,valor);


                    /*if(valor>=1){
                        valor=1;
                    }
                    if (valor<=0){
                        valor=0;
                    }
                    */

                }
            }
        }
    }
    for (int i=0;i<dim;i++){
        interferograma[i].copyTo(interf[i]);
        interf[i]*=scale;
    }
}




