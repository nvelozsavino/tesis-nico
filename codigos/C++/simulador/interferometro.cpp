#include "interferometro.hpp"
using namespace cv;

int Interferometro::setMats(void){
    unsigned int left,top,myWidth,myHeight;
    if (camaraParam!=camara->getParametros()) {
        left=camara->roi().left;
        myWidth=camara->roi().width;
        top=camara->roi().top;
        myHeight=camara->roi().height;
        copyPart(muestra->visibilidad,roiVisibility,myWidth,myHeight,left,top);
        copyPart(muestra->depth,roiDepth,myWidth,myHeight,left,top);
        camaraROI=camara->roi();
        width=camara->roi().width;
        height=camara->roi().height;
        scale=_timeStep/camara->exposureTime();
        return 1;
    } else {
        return 0;
    }

}

int Interferometro::timeStep(float TimeStep){
    _timeStep=TimeStep;
    return setMats();
}

float Interferometro::timeStep(){
    return _timeStep;
}

void Interferometro::initInterferometro (Muestra *myMuestra, Spectrum *myFuente, Camara *myCamara, float timestep, float inclX, float inclY, TipoInterferometro t,float RRM, BeamSplitter bs){
	tipo=t;
	if (RRM>1 || RRM<0){
        rRM=DEFAULT_REFLEXION_RM;
	} else {
        rRM=RRM;
	}
	beamSplitter=bs;
	muestra=myMuestra;
	camara=myCamara;
	fuente=myFuente;
	Scalar io,ifu;
    double normMax;
    double normMin;
    double norm=0;
    float *Iomax;
	float endFreqFuente,endFreqSensor;
	endFreqFuente=LIGHT_SPEED/fuente->startLamda;
	Mat multip;
	Mat spdFuente;
	float endFreqMultip;
//	interferometro->perturbacion=perturbacion;
	inclinacionX=inclX;
	inclinacionY=inclY;
	_timeStep=timestep;
    //scale=timestep*camara->fps();
    /*
	if (!camara->hasROI){
        camara->setROI(muestra->width,muestra->height,0,0);
	}
	*/
	setMats();
	int dim;
	if (camara->tipo()==COLOR){
	    dim=3;
	//    valores.create(width, height, CV_32FC3);
	} else {
	//    valores.create(width, height, CV_32FC1);
	    dim=1;
	}

	    //Mat multip[3];
    Xmax=new float[dim];
    Xmin=new float[dim];
    interferograma=new Mat[dim];
    interf=new Mat[dim];
    Io=new float[dim];
    Iomax=new float[dim];


        //int N;

   // ifu=sum(fuente->valoresFreq);
   // cout<<"Ifuente = "<< ifu[0]<<endl;
   // Iomax=ifu[0]*endFreqFuente/fuente->valoresFreq.cols;
   // cout<<"Iomax = "<< Iomax<<endl;
    for (int i=0;i<dim;i++){

        Mat aux,maux;
        endFreqSensor=LIGHT_SPEED/camara->sensor(i).startLamda;
        aux=camara->sensor(i).valoresFreq;//*camara->channelGain[i];
        multiply(aux,aux,maux);
        ifu=sum(maux);
        Iomax[i]=ifu[0]*endFreqSensor/(maux.cols-1);

        //fuente->lamda2freq();



        multFreq(fuente->valoresFreq,endFreqFuente,aux,endFreqSensor,&multip,&endFreqMultip);
        multiply(multip,multip,multip);

        float maxLamda;
        if (fuente->endLamda>camara->sensor(i).endLamda){
            maxLamda=fuente->endLamda;
        } else {
            maxLamda=camara->sensor(i).endLamda;
        }
        float minLamda;
        if (fuente->startLamda<camara->sensor(i).startLamda){
            minLamda=fuente->startLamda;
        } else {
            minLamda=camara->sensor(i).startLamda;
        }
        //mult(*fuente,camara->sensor[i],multip[i],1);
        //N=multip.cols;
        Xmin[i]=(multip.cols-1)*minLamda/multip.cols;   //(N-1)*minLamda/N
        //Xmin[i]=2*(LIGHT_SPEED/endFreqMultip);
        idft(multip,interferograma[i],DFT_REAL_OUTPUT );//, DFT_REAL_OUTPUT); //no se pone DFT_SCALE porque luego hay que multiplicarla por N
        Xmax[i]=(ALPHA*maxLamda)/2;
        io=sum(multip);
        Io[i]=camara->gain*camara->channelGain[i]*(io[0]*endFreqMultip/(multip.cols-1))/Iomax[i];///Iomax;
         cout<<"Io["<<i<<"] = "<< Io[i]<<endl;
        //Iomax+=Io[i];
        minMaxLoc(interferograma[i],&normMin,&normMax);

        cout<<"Interferograma Max ["<<i<<"] = "<< normMax<<endl;
        cout<<"Interferograma Min ["<<i<<"] = "<< normMin<<endl;
        //if (Io[i]>Iomax){
            //Iomax=Io[i];
        //}

        if (fabs(normMin)>fabs(normMax)){
         //   Io[i]=fabs(normMin);
            norm=fabs(normMin);
            /*
            if (norm<fabs(normMin)){
                norm=fabs(normMin);
            }
            */
        } else {
            norm=fabs(normMax);
           // Io[i]=fabs(normMax);
           /*
            if (norm<fabs(normMax)){
                norm=fabs(normMax);
            }
            */
        }
       // interf[i]+=normMin;
        interferograma[i]*=Io[i]/norm;



    }
    //Iomax=Iomax/dim;
    for (int i=0;i<dim;i++){
//       interferograma[i]/=norm;
//       interferograma[i]*=Io[i];
        minMaxLoc(interferograma[i],&normMin,&normMax);

        cout<<"Interferograma Max ["<<i<<"] = "<< normMax<<endl;
        cout<<"Interferograma Min ["<<i<<"] = "<< normMin<<endl;
        //interferograma[i]*=endFreqMultip*N/(N-1);
        //Io[i]/=Iomax;
       // Io[i]*=0.5;
        //Io[i]=1;
        ajustaFFT(interferograma[i],interferograma[i]);
        interferograma[i].copyTo(interf[i]);
        interf[i]*=scale;
        //cout<<"interferograma=" <<interferograma[i].cols<<"  interf="<<interf[i].cols<<endl;

    }
/*
    //integra(Xmax[0]/3,1);
   // dibujaPatron(interferograma, dim);
    dibujaPatron(interferograma, dim,1000,1000, "patron Inicial");
    for (;;){
        int c = cvWaitKey(1000);
        if( (char) c == 27)
        break;
    }
*/
    switch (tipo){
        case MICHELSON:
        default:
            iRc=beamSplitter.getR()*beamSplitter.getT()*rRM;
            iSc=beamSplitter.getR()*beamSplitter.getT();
            break;
        case MIRAU:
            iRc=beamSplitter.getR()*beamSplitter.getR()*rRM;
            iSc=beamSplitter.getT()*beamSplitter.getT();
            break;
    }
    cout<<"iRc = "<< iRc<<endl;
    cout<<"iSc = "<< iSc<<endl;
}

Interferometro::~Interferometro(){
    delete[] Xmax;
    delete[] Xmin;
    delete[] interferograma;
    delete[] interf;
    delete[] Io;
}

void Interferometro::integra(float opticalPath){
    int desp;
    int dim;
    if (camara->tipo()==COLOR){
		dim=3;
	} else {
		dim=1;
	}
    int w, h;//,type;
    w=interferograma[0].cols;
    h=interferograma[0].rows;
    //type=interferograma[0].type();
	for (int d=0;d<dim;d++){
	    float v=opticalPath*interferograma[d].cols/Xmax[d];//2*fabs(depth)+Xmax[i])/(2*Xmax[i])
	    desp=(int)v;
// Esto mejora en 25% la velocidad de procesamiento
	    if ((unsigned int)desp<(unsigned int)w){
            if (desp>0) {
                interf[d](Rect(desp,0,w-desp,h))+=interferograma[d](Rect(0,0,w-desp,h))*scale;
            } else {
                interf[d](Rect(0,0,w+desp,h))+=interferograma[d](Rect(-desp,0,w+desp,h))*scale;
            }
	    }

//Con respecto a esta parte
        /*
        Mat temp;
        desplaza(interferograma[d],temp,desp);
        interf[d]+=temp*scale;
        */
	}
	//cout << "integra, opticalPath="<<opticalPath <<endl;
	//dibujaPatron(interf, dim,1000,500, "patron Integra");
}

void Interferometro::getInterferograma(float opticalPath){
	int dim;
//	float coseno;
//	float lamda;
//	float valor;

//    uchar i,j,k;
 //   uchar channels=img.channels();
//	unsigned int width,height;
	unsigned int x,y;
//	width=muestra->width;
//	height=muestra->height;
    setMats();
	if (camara->tipo()==COLOR){
		dim=3;
		valores.create(height,width,CV_32FC3);
	} else {
		dim=1;
		valores.create(height,width,CV_32FC1);
	}
    float v,yvd,yvd1,valor,val;
    //int vd;
    float depth,inclinacion;
    float vis;
	    //cout << "Xmax="<<Xmax[i]<<" Xmin="<<Xmin[i]<<" OpticalPath="<<opticalPath<<endl;
    //int c = cvWaitKey(500);
    for (x=0;x<width;x++){
        for (y=0;y<height;y++){
            inclinacion=((float)x-((float)width/2))*inclinacionX/muestra->width + ((float)y-((float)height/2))*inclinacionY/muestra->height;
            depth=get2D32F(roiDepth,x,y,0)+opticalPath+inclinacion;
            //depth*=2;
            vis=get2D32F(roiVisibility,x,y,0);
            //cout <<"depth = "<<depth<<endl;


            for (int i=0;i<dim;i++){
                if (fabs(depth)<=Xmax[i]/2){
                    v=(interf[i].cols-1)*(2*depth+Xmax[i]/2)/(Xmax[i]);
                    //vd=(int)v;
                    yvd=get2D32F(interf[i],(int)v,0,0);
                    yvd1=get2D32F(interf[i],(((int)v)+1),0,0);
                    val=((yvd1-yvd)*(v-(int)v)+yvd);
                    valor=Io[i]*(iRc+(vis*iSc))+(2*sqrt(iRc*iSc*vis)*val);
/*                    cout <<"val["<<i<<"] = "<<val<<endl;
                    cout <<"valor["<<i<<"] = "<<valor<<endl;
                    cout <<"v["<<i<<"] = "<<v<<endl;
                    cout <<"yvd["<<i<<"] = "<<yvd<<endl;
                    cout <<"yvd1["<<i<<"] = "<<yvd1<<endl;
*/
                    set2D32F(valores,x,y,i,valor);


                }
            }
            //int c = cvWaitKey(25000);
        }
    }
    for (int i=0;i<dim;i++){
        interferograma[i].copyTo(interf[i]);
        interf[i]*=scale;
    }
    //dibujaPatron(interf, dim,1000,500, "patron Integra2");
}


        TipoInterferometro Interferometro::getTipo(){
            return tipo;
        }
        //float setMirrorRefferenceR(float r);
        float Interferometro::getMirrorRefferenceR(){
            return rRM;
        }



BeamSplitter::BeamSplitter(){
    tBS=DEFAULT_TRANSMITION_BS;
    rBS=1-tBS;
}

void BeamSplitter::initBeamSplitterR(float r){
    if (r>1 || r<0){
        rBS=DEFAULT_REFLEXION_BS;

	} else {
        rBS=r;
	}
	tBS=1-rBS;
}

void BeamSplitter::initBeamSplitterT(float t){
    if (t>1 || t<0){
        tBS=DEFAULT_TRANSMITION_BS;
	} else {
        tBS=t;
	}
	rBS=1-tBS;
}

float BeamSplitter::getT(){
    return tBS;
}

float BeamSplitter::getR(){
    return rBS;
}


