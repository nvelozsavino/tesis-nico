#include "camara.hpp"
#include <iostream>


ROI::ROI(){
    top=0;
    left=0;
    width=0;
    height=0;
}
ROI::ROI(unsigned int w, unsigned int h, unsigned int t, unsigned int l){
        top=t;
        left=l;
        width=w;
        height=h;
    }

int ROI::operator == (ROI src){
    int t,l,w,h;
    t=(top == src.top);
    l=(left == src.left);
    w=(width == src.width);
    h=(height == src.height);

    return (t && l && w && h );
}

int ROI::operator != (ROI src){
    int t,l,w,h;
    t=(top != src.top);
    l=(left != src.left);
    w=(width != src.width);
    h=(height != src.height);

    return (t || l || w || h );
}

void Camara::initCamara(unsigned int f, float it, tipoCamara type=COLOR){
    tipo=type;
    hasROI=false;
    roi.top=0;
    roi.left=0;
    roi.width=0;
    roi.height=0;
    //Spectrum *se;
	if (tipo==COLOR){
		sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
        sensor[2].initGausian(RED_AMP,RED_MIU,RED_SIGMA,SPECTRUM_SIZE);
        sensor[1].initGausian(GREEN_AMP,GREEN_MIU,GREEN_SIGMA,SPECTRUM_SIZE);
        sensor[0].initGausian(BLUE_AMP,BLUE_MIU,BLUE_SIGMA,SPECTRUM_SIZE);

//		cout<<"A: " << a<<endl;
		//cout << "Sized = " <<sensoŕ[2].getSize() <<endl;
	} else {
	    sensor=new Spectrum[1];//(200e-9,1000e-9,SPECTRUM_SIZE);
	    sensor[0].initGausian(GRAY_AMP,GRAY_MIU,GRAY_SIGMA,SPECTRUM_SIZE);
	}

	fps=f;
	integrationTime=it;
}

void Camara::initCamaraFromFiles(unsigned int f, float it,string red,string green, string blue){
    tipo=COLOR;
    //Spectrum *se;
    sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
    sensor[2].initSpectrumFromFile(red,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    sensor[1].initSpectrumFromFile(green,1e-9,1.5,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    sensor[0].initSpectrumFromFile(blue,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);

	fps=f;
	integrationTime=1/(float)fps;
}
Camara::~Camara(){
    if (sensor!=NULL){

        //sensor=new Spectrum[0];
//        if (tipo==COLOR){
  //          delete[] sensor[2];
    //        delete[] sensor[1];
      //  }
        //delete[] sensor[0];
        delete[] sensor;
    }
}

Camara::Camara(){
    hasROI=false;
}

unsigned int Camara::getFPS(void){
    return fps;
}

float Camara::getIntegrationTime(void) {
    return integrationTime;
}

tipoCamara Camara::getType(void){
    return (tipo);
}


void Camara::setFPS(unsigned int f){
    fps=f;
}
void Camara::setIntegrationTime(float it){
    integrationTime=it;
}

void Camara::setROI (unsigned int width, unsigned int height,unsigned int top=0, unsigned int left=0){
    hasROI=true;
    roi.top=top;
    roi.left=left;
    roi.width=width;
    roi.height=height;
}
