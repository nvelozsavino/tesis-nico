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

/*
    int t,l,w,h;
    t=(top != src.top);
    l=(left != src.left);
    w=(width != src.width);
    h=(height != src.height);
*/
    return !operator==(src);
}


//Constructor
Camara::Camara(){
    _sensor=NULL;
    _redFile="";
    _greenFile="";
    _blueFile="";
    _whiteFile="";
    _fromFiles=false;
    init(DEFAULT_WIDTH,DEFAULT_HEIGHT,DEFAULT_FPS,DEFAULT_EXPOSURE_TIME,DEFAULT_TIPO,DEFAULT_FRAME_TYPE,DEFAULT_TRANSPORT_TIME,DEFAULT_SHUTTER_TIME);

}

int Camara::init(unsigned int Width, unsigned int Height,float Fps, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME){

    _width=Width;
    _height=Height;
    _fps=Fps;
    _exposureTime=ExposureTime;
    _tipo=Tipo;
    _frameType=FrameType;
    _transportTime=TransportTime;
    _shutterTime=ShutterTime;
    _autoConfig=FIXED_FPS_FIXED_EXPOSE;
    _roi.top=0;
    _roi.left=0;
    _roi.width=_width;
    _roi.height=_height;
    if (_fromFiles){
        fileSpectrums();
    } else {
        defaultSpectrums();
    }
    return calcTimes();
}

void Camara::initFPS(unsigned int Width, unsigned int Height,float Fps, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME){
    _width=Width;
    _height=Height;
    _fps=Fps;
    _exposureTime=DEFAULT_EXPOSURE_TIME;
    _tipo=Tipo;
    _frameType=FrameType;
    _transportTime=TransportTime;
    _shutterTime=ShutterTime;
    _autoConfig=FIXED_FPS_AUTO_EXPOSE;
    _roi.top=0;
    _roi.left=0;
    _roi.width=_width;
    _roi.height=_height;
    if (_fromFiles){
        fileSpectrums();
    } else {
        defaultSpectrums();
    }
    return calcTimes();

}

void Camara::initExposureTime(unsigned int Width, unsigned int Height, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType=DEFAULT_FRAME_TYPE, float TransportTime=DEFAULT_TRANSPORT_TIME,float ShutterTime=DEFAULT_SHUTTER_TIME){
    _width=Width;
    _height=Height;
    _fps=DEFAULT_FPS;
    _exposureTime=ExposureTime;
    _tipo=Tipo;
    _frameType=FrameType;
    _transportTime=TransportTime;
    _shutterTime=ShutterTime;
    _autoConfig=AUTO_FPS_FIXED_EXPOSE;
    _roi.top=0;
    _roi.left=0;
    _roi.width=_width;
    _roi.height=_height;
    if (_fromFiles){
        fileSpectrums();
    } else {
        defaultSpectrums();
    }
    return calcTimes();


}

//Destructor
Camara::~Camara(){
    if (_sensor!=NULL){
        delete[] _sensor;
    }
}

void Camara::defaultSpectrums(){
    _fromFiles=false;
    if (_sensor!=NULL){
        delete[] _sensor;
    }
	if (_tipo==COLOR){
		_sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
        _sensor[2].initGausian(RED_AMP,RED_MIU,RED_SIGMA,SPECTRUM_SIZE);
        _sensor[1].initGausian(GREEN_AMP,GREEN_MIU,GREEN_SIGMA,SPECTRUM_SIZE);
        _sensor[0].initGausian(BLUE_AMP,BLUE_MIU,BLUE_SIGMA,SPECTRUM_SIZE);
//		cout<<"A: " << a<<endl;
		//cout << "Sized = " <<sensoŕ[2].getSize() <<endl;
	} else {
	    _sensor=new Spectrum[1];//(200e-9,1000e-9,SPECTRUM_SIZE);
	    _sensor[0].initGausian(GRAY_AMP,GRAY_MIU,GRAY_SIGMA,SPECTRUM_SIZE);
	}
}

void Camara::fileSpectrums(){
    _fromFiles=true;
    if (_sensor!=NULL){
        delete[] _sensor;
    }
    if (_tipo==COLOR){
        _sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
        _sensor[2].initSpectrumFromFile(redFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
        _sensor[1].initSpectrumFromFile(greenFile,1e-9,1.5,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
        _sensor[0].initSpectrumFromFile(blueFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    } else {
	    _sensor=new Spectrum[1];
        _sensor[0].initSpectrumFromFile(whiteFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    }
}

int Camara::operator== (Camara src){
    int w =(_width==src.width());
    int h =(_height==src.height());
    int r =(_roi==src.roi());
    int f =(_fps==src.fps());
    int et=(_exposureTime==src.exposureTime());
    int t =(_tipo==src.tipo());
    int ft=(_frameType==src.frameType());
    int tt=(_transportTime==src.transportTime());
    int st=(_shutterTime==src.shutterTime());
    int ff=(_fromFiles==src.fromFiles());
    int fr=(_redFile==src.redFile());
    int fg=(_greenFile==src.greenFile());
    int fb=(_blueFile==src.blueFile());
    int fw=(_whiteFile==src.whiteFile());
    return (w && h && r && f && et && t && ft && tt && st && ff && fr && fg && fb && fw);

}
int Camara::operator!= (Camara src){
    return !operator==(src);
}
unsigned int Camara::width();
unsigned int Camara::height();
ROI Camara::roi ();
float Camara::fps();
float Camara::exposureTime();
tipoCamara Camara::tipo();
tipoFrame Camara::frameType();
float Camara::transportTime();
float Camara::shutterTime();
int Camara::fromFiles();
string Camara::redFile();
string Camara::greenFile();
string Camara::blueFile();
string Camara::whiteFile();



int Camara::exposureTime(float ExposureTime);


int Camara::fps(float Fps);

//bool Camara::hasROI ();


int Camara::roi (unsigned int width, unsigned int height,unsigned int top, unsigned int left);

Spectrum Camara::sensor (int index);

int Camara::setSize(unsigned int width, unsigned int height);


//int width (unsigned int Width);


//int height (unsigned int Height);

int Camara::tipo (tipoCamara Tipo);


autoSettings Camara::autoConfig();
int Camara::autoConfig(autoSettings AutoConfig);



int Camara::setSpectrums(string RedFile,string GreenFile, string BlueFile);
int Camara::setSpectrums(string WhiteFile);
//int createCamara(Camara *camara, )

int Camara::calcTimes(){
    float exposureTimeMin;
    float fpsMax,fpsMax_ExposeMin;
    float transportVoid,transportExpose,timeShutter;
    int error;
    switch (_frameType){
        case FULL_FRAME:
            transportVoid=(_height-roi.top-roi.width)+((1+_width-roi.left)*roi.height);
            transportExpose=0;
            timeShutter=2*_shutterTime;
            break;
        case FRAME_TRANSFERE:
            transportVoid=2*_height-roi.top-roi.height;
            transportExpose=roi.height*(1+_width-roi.left);
            timeShutter=0;
            break;
        case INTERLINE:
            transportVoid=1;
            transportExpose=(_height-roi.top-roi.height)+(roi.height*(1+(_width-roi.left)));
            timeShutter=0;
            break;
        default:
            return -1;
            break;
    }

    exposureTimeMin=transportExpose*_transportTime;
    fpsMax=1/((transportVoid*_transportTime) + timeShutter +_exposureTime);
    fpsMax_ExposeMin=1/((transportVoid*_transportTime) + timeShutter + exposureTimeMin);
    error=0;
    switch (autoFPSexposure){
        case 0: //FPS fijo y exposicion fijo
            if (_exposureTime<exposureTimeMin){
                _exposureTime=exposureTimeMin;
                error=error+2; //Error en exposuretime
                if(_fps>fpsMax_ExposeMin){
                    _fps=fpsMax_ExposeMin;
                    error=error+1;
                }
            } else if (_fps>fpsMax) {
                _fps=fpsMax;
                error=error+1; //    Error en FPS
            }
            break;
        case 1: //FPS fijo, exposicion automatico
            error=0;
            if (_fps>fpsMax_ExposeMin){
                _exposureTime=exposureTimeMin;
                _fps=fpsMax_ExposeMin;
                error=error+1;
            } else {
                _exposureTime=(1/_fps)-((_transportTime*transportVoid)+timeShutter);
            }
            break;
        case 2: //FPS automatico, exposicion fijo
            if (_exposureTime<exposureTimeMin){
                _exposureTime=exposureTimeMin;
                _fps=fpsMax_ExposeMin;
                error=error+2;  //Error en exposuretime
            } else {
                _fps=fpsMax;
            }

            break;
        default:
            error=-1;
            break;
    }
    return error;

}




























void Camara::initCamara(unsigned int f, float it, tipoCamara type=COLOR){
    _tipo=type;
    _hasROI=false;
    _roi.top=0;
    _roi.left=0;
    _roi.width=0;
    _roi.height=0;
    //Spectrum *se;
	if (_tipo==COLOR){
		_sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
        _sensor[2].initGausian(RED_AMP,RED_MIU,RED_SIGMA,SPECTRUM_SIZE);
        _sensor[1].initGausian(GREEN_AMP,GREEN_MIU,GREEN_SIGMA,SPECTRUM_SIZE);
        _sensor[0].initGausian(BLUE_AMP,BLUE_MIU,BLUE_SIGMA,SPECTRUM_SIZE);
//		cout<<"A: " << a<<endl;
		//cout << "Sized = " <<sensoŕ[2].getSize() <<endl;
	} else {
	    _sensor=new Spectrum[1];//(200e-9,1000e-9,SPECTRUM_SIZE);
	    _sensor[0].initGausian(GRAY_AMP,GRAY_MIU,GRAY_SIGMA,SPECTRUM_SIZE);
	}

	_fps=f;
	_exposureTime=it;
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



float Camara::exposureTime () {
    return _exposureTime;
}
int Camara::exposureTime(float ExposureTime){
    _exposureTime=ExposureTime;
    return calcTimes();
}
float Camara::fps {
    return _fps;
}

int Camara::fps(float Fps){
    _fps=Fps;
    return calcTimes();
}

ROI Camara::roi () {
    return _roi;
}
int Camara::roi (unsigned int width, unsigned int height,unsigned int top, unsigned int left){
    _roi.width=width;
    _roi.height=height;
    _roi.left=left;
    _roi.top=top;
    return calcTimes();

}

Spectrum Camara::sensor (int index){
    return _sensor[index];
}

int Camara::setSize(unsigned int width, unsigned int height) {
    _width=width;
    _height=height;
    return calcTimes();
}

unsigned int Camara::width() {
    return _width;
}

/*
int Camara::width (unsigned int Width) {
    _width=Width;
    return calcTimes();
}
*/

unsigned int Camara::height() {
    return _height;
}
/*
int Camara::height (unsigned int Height) {
    _height=Height;
    return calcTimes();
}
*/
tipoCamara Camara::tipo(){
    return _tipo;
}

int Camara::tipo (tipoCamara Tipo){
    init
}

