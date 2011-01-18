#include "spectrum.hpp"

void Spectrum::initSpectrum(float lamdaStart, float lamdaEnd,unsigned int arraySize){
	size=arraySize;
	startLamda=lamdaStart;
	endLamda=lamdaEnd;
	valores.create(size,1,CV_32FC1);
	valores.setTo(Scalar::all(0));
    //lamda = new float[size];//(double*) calloc (size,sizeof(double));
	//valores = new float[size];
	resolucion=(endLamda-startLamda)/(size-1);
/*	for (i=0;i<size;i++){
		lamda[i]=startLamda+i*resolucion;
		valores[i]=0;
	}
	*/
}



void Spectrum::initGausian(float amplitud, float mean, float sigma, unsigned int arraySize){
//	float li=mean-3*sigma;
	float lf=mean+3*sigma;
	initSpectrum(DEFAULT_START_LAMDA,lf,arraySize);
	setGausian(amplitud,mean,sigma,0);
}


Spectrum::~Spectrum(){
//void freeEspectro(Espectro *espectro){

}


void Spectrum::setGausian(float amplitud, float mean, float sigma, float add){
	float l;
	float amp;
	float sum;
	amp=1;// /(RAIZ_2PI*sigma);
	for (unsigned int i=0;i<size;i++){
		l=i2lamda(i);
		sum=add*get1D32F(valores,i);
		set1D32F(valores,i,sum+amp*amplitud*exp(-(l-mean)*(l-mean)/(2*sigma*sigma)));
		//valores[i]=amp*amplitud*exp(-(l-mean)*(l-mean)/(2*sigma*sigma));
	}
	lamda2freq();
}


void Spectrum::setPlain(float lamdastart, float lamdaend,float amplitud=1){
	int is,ie,i;
	is=lamda2i(lamdastart);
	ie=lamda2i(lamdaend);
	if (is<0){
	    is=0;
	} else if (is>(int)(size-1) ){
		is=size-1;
	}
	if (ie<0){
	    ie=0;
	} else if (ie>(int)(size-1) ){
		ie=size-1;
	}
	for (i=is;i<ie+1;i++){
		set1D32F(valores,i,abs(amplitud));
	}
	lamda2freq();
}

void Spectrum::setDelta(float amplitud, float lamda_central, float add){
    setGausian(amplitud, lamda_central, resolucion*0.25, add);
}

int Spectrum::lamda2i(float l){
	return (int)((l-startLamda)*(size-1)/(endLamda-startLamda));
}
float Spectrum::lamda2f(float l){
	return ((l-startLamda)*(size-1)/(endLamda-startLamda));
}


float Spectrum::i2lamda(unsigned int i){
    return (startLamda+i*(endLamda-startLamda)/(size-1));
}

float Spectrum::integrarEspectro(void){
	float deltaX;
	float result;
	result=0;
	float ff=LIGHT_SPEED/startLamda;
	deltaX=ff/(valoresFreq.cols-1);
	Scalar Io=sum(valoresFreq);
	result=Io[0]-(get1D32F(valoresFreq,0) + get1D32F(valoresFreq,valoresFreq.cols-1))/2;
/*	for (unsigned int i=0; i<size-1; i++){
	    result+=0.5*deltaX*get1D32F(valores,i);
	    result+=0.5*deltaX*get1D32F(valores,i+1);
    }
    */
	return (result*deltaX);
}

void Spectrum::Borrar(){
    size=0;
    valores.release();
    valoresFreq.release();
}
/*
 int Spectrum::Clone(Spectrum *copia){
    if (!size) {
         return -1;
    }
    if (size!=copia->size){
         copia->Borrar();
         //espectro->size=size;
         copia->createEspectro(lamda[0],lamda[size-1],size);
    }
    memcpy(copia->lamda, lamda , size);
    memcpy(copia->valores, valores, size);
    copia->size=size;
    return size;

 }
*/

void mult(Spectrum& src1,Spectrum& src2,Spectrum& dst,int spd){

	unsigned int size_temp;
	float li_temp;
	float lf_temp;
	float l;
	unsigned int i;
	float mults, multp;

    Mat valores;

    if (spd){
        multiply(src1.valores,src1.valores,valores);
    } else {
        valores=src1.valores;
    }
	//Mat rowRange(int startrow, int endrow) const;

	//freeEspectro(resultado);
/*	lamda_end1=lamda[size -1];
	lamda_end2=espectro2->lamda[espectro2->size -1];
	lamda_start1=lamda[0];
	lamda_start2=espectro2->lamda[0];

	res1=(lamda_end1-lamda_start1)/size;
	res2=(lamda_end2-lamda_start2)/espectro2->size;
*/
	//establezco cual es el inicio menor
	if (src1.startLamda<src2.startLamda){
		li_temp=src1.startLamda;
	} else {
		li_temp=src2.startLamda;
	}

	//establezco cual es el fin mayor
	if (src1.endLamda>src2.endLamda){
		lf_temp=src1.endLamda;
	} else {
		lf_temp=src2.endLamda;
	}

	//establezco cual tiene mas resolucion y determino el mayor tamaño
	if (src1.resolucion<src2.resolucion){
		size_temp=myRound((lf_temp-li_temp)/src1.resolucion,ROUND_UP);
		//resolucion;
	} else {
		size_temp=myRound((lf_temp-li_temp)/src2.resolucion,ROUND_UP);
		//myRound((lf_temp-li_temp)/res2,ROUND_DOWN);
	}
    if (dst.size==0){
        dst.Borrar();
    }
	//creo el espectro
	//temp=new Spectrum;
	dst.initSpectrum(li_temp,lf_temp,size_temp);
   // printf("size_temp %d\n",size_temp);
	//lleno el espectro
	float m,b,isf,ipf;
	int isd,isu;
	for (i=0;i<size_temp;i++){
		l=dst.i2lamda(i);
		isf=src1.lamda2f(l);
		ipf=src2.lamda2f(l);
		if (isf<0 || ipf<0 || ipf>src2.size-1 || isf>src1.size-1){
		    //set1D32FC1(dst->valores,i,0);
		} else {
            isd=myRound(isf,ROUND_DOWN);
            isu=myRound(isf,ROUND_UP);
            if (isu!=isd){
                m=(get1D32F(valores,isu)-get1D32F(valores,isd))/(isu-isd);
                b=get1D32F(valores,isd);
                mults=m*(isf-isd)+b;
            } else {
                mults=get1D32F(valores,isu);
            }

            isd=myRound(ipf,ROUND_DOWN);
            isu=myRound(ipf,ROUND_UP);
            if (isu!=isd){

                m=(get1D32F(src2.valores,isu)-get1D32F(src2.valores,isd))/(isu-isd);
                b=get1D32F(src2.valores,isd);
                multp=m*(ipf-isd)+b;
            } else {
                multp=get1D32F(src2.valores,isu);
            }

            set1D32F(dst.valores,i,mults*multp);
        }
	}
	dst.lamda2freq();

}



void multFreq(Mat src1, float endFreq1, Mat src2, float endFreq2, Mat *dst, float *endFreqDst){

	unsigned int size_temp;
//	float resTemp;
	float res1,res2;

	float mult1, mult2;

    float f;
    float is1,is2;
    float yu1,yd1,yu2,yd2;
    int i1,i2;

	if (endFreq1>endFreq2){
		*endFreqDst=endFreq1;
	} else {
		*endFreqDst=endFreq2;
	}

    res1=(src1.rows)/endFreq1;
    res2=(src2.rows)/endFreq2;

    if (res1>res2){
        size_temp=src1.rows;
    } else {
        size_temp=src2.rows;
    }
    dst->create(size_temp,1,CV_32FC1);


	for (unsigned int i=0;i<size_temp;i++){

		f=i*(*endFreqDst)/(size_temp-1);
		is1=f*(src1.rows-1)/endFreq1;
        is2=f*(src2.rows-1)/endFreq2;

        if (is1>(src1.rows-1)){
            mult1=0;
        } else {
            i1=(int)is1;
            if (i1!=src1.rows-1){
                yd1=get1D32F(src1,i1);
                yu1=get1D32F(src1,i1+1);
                mult1=(yu1-yd1)*(is1-i1)+yd1;
            } else {
                mult1=get1D32F(src1,i1);
            }
        }

        if (is2>(src2.rows-1)){
            mult2=0;
        } else {
            i2=(int)is2;
            if (i2!=src2.rows-1){
                yd2=get1D32F(src2,i2);
                yu2=get1D32F(src2,i2+1);
                mult2=(yu2-yd2)*(is2-i2)+yd2;
            } else {
                mult2=get1D32F(src2,i2);
            }
        }
        set1D32F((*dst),i,mult1*mult2);
	}
}


int Spectrum::initSpectrumFromFile(string archivo,float resX, float scale,float lamdaStart, float lamdaEnd,unsigned int arraySize){

    //ifstream RdFile(archivo); //open file
   // string line;
    //char buffer[256];
   // string campo;
    //stringstream iss;
    int puntos;
    float *lamd;
    float *vals;
//    float l,v;
    int m;
    float l,v;
    initSpectrum(lamdaStart,lamdaEnd,arraySize);
    //Detector *detectors; //a pointer to the array detectors;
    //int nDet,nSamp;     //nDet=number of detectors, nSamp=number of samples
    FILE *file;
    file=fopen(archivo.c_str(),"r");
    if (file == NULL) {
        cout<< "Error opening file"<<endl;
        return -1;
    } else {
        if (fscanf(file,"%d\n",&puntos)!=1){
            cout <<"Error leyendo archivo"<<endl;
            return -1;
        }
        lamd=new float[puntos];
        vals=new float[puntos];

        for (m=0;m<puntos;m++){
            if (fscanf(file,"%f\t%f\n",&l,&v)!=2){
                cout <<"Error leyendo archivo"<<endl;
                return -1;
            }
            lamd[m]=l*resX;
            vals[m]=v*scale;
        }
        fclose(file);

    }

    for (int m=0;m<(int)size;m++){
        float indice;
        float l;
        float v;
        l=startLamda+m*(endLamda-startLamda)/(size-1);
        indice=(l-lamd[0])*(puntos-1)/(lamd[puntos-1]-lamd[0]);
        if (indice>puntos-1 || indice<0){
            v=0;
        } else {
            int iu=(int)indice;
            if (iu!=(int)(puntos-1)){
                float yd1=vals[iu];
                float yu1=vals[iu+1];
                v=(yu1-yd1)*(indice-iu)+yd1;
            } else {
                v=vals[iu];
            }
        }
        set1D32F(valores,m,v);
    }
    lamda2freq();
    return 0;
}
/*


    if(RdFile){
        //we read the first line, to obtain the number of detectors
        //initialization of the size of the detector's array
        getline(RdFile, line);
        puntos=atoi(line.c_str());

        for(int m=0;m<puntos;m++){
            if(!getline(RdFile,line)){
                cout << "The file contains less samples than it says "<< archivo <<endl;
                return -1;
            }
            iss<<line;
            for(int d=0;d<2;d++){
                getline(iss,campo,'\t');
                switch (d){
                    case 0:
                    lamd[m]=resX*atof(campo.c_str());
                    break;
                    case 1:
                    vals[m]=scale*atof(campo.c_str());
                    break;
                }

            }
            iss.clear();

        }
        for (unsigned int m=0;m<size;m++){
            float i;
            float l;
            float v;
            l=startLamda+m*(endLamda-startLamda)/(size-1);
            i=(puntos-1)*(l-lamd[0])/(lamd[puntos-1]-lamd[0]);
            if (i>puntos-1 || i<0){
                v=0;
            } else {
                int iu=(int)i;
                if (iu!=(int)(puntos-1)){
                    float yd1=vals[iu];
                    float yu1=vals[iu+1];
                    v=(yu1-yd1)*(i-iu)+yd1;
                } else {
                    v=vals[iu];
                }
            }
            set1D32F(valores,m,v);
        }
        //delete lamd;
        //delete vals;
    } else {
        cout << "Error while opening the file "<< archivo <<endl;
        return -1;
    }

    RdFile.close();
    return 0;

}
*/



void Spectrum::lamda2freq(void){
    int N=1+(ALPHA*endLamda/startLamda);
    float ff=LIGHT_SPEED/startLamda;
    valoresFreq.create(N,1,CV_32FC1);
    valoresFreq.setTo(Scalar::all(0));
    for (int y=1;y<valoresFreq.rows;y++){
        float f=y*(ff/(valoresFreq.rows-1));
        set1D32F(valoresFreq,y,f2val(f));
    }

}


float Spectrum::f2val(float freq){
    if (freq<=0){
        return 0;
    }
    float lamda=LIGHT_SPEED/freq;
    float i=(lamda-startLamda)*(valores.rows-1)/(endLamda-startLamda);
    int id=(int)i;
    if (id>=valores.rows){
        return 0;
    }
    if (id!=valores.rows-1){
        float yid=get1D32F(valores,id);
        float yid1=get1D32F(valores,id+1);
        return ((yid1-yid)*(i-id)+yid);
    }else {
        return get1D32F(valores,id);
    }
}



