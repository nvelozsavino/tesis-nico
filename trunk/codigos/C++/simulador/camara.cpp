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


ParametrosCamara::ParametrosCamara(){

}
ParametrosCamara::~ParametrosCamara(){

}
int ParametrosCamara::operator== (ParametrosCamara src){
    int et,f,tt,st,w,h,r,tc,tf,ac,rf,gf,bf,wf,ff;
    int sp;
    et=(_exposureTime==src._exposureTime);
    f =(_fps==src._fps);
    tt=(_transportTime==src._transportTime);
    st=(_shutterTime==src._shutterTime);
    w =(_width==src._width);
    h =(_height==src._height);
    r =(_roi==src._roi);
    tc=(_tipo==src._tipo);
    tf=(_frameType=src._frameType);
    ac=(_autoConfig==src._autoConfig);
    ff=(_fromFiles==src._fromFiles);

    rf=(_redFile==src._redFile);
    gf=(_greenFile==src._greenFile);
    bf=(_blueFile==src._blueFile);
    wf=(_whiteFile==src._whiteFile);
    if (ff && _fromFiles && tc){
        if (_tipo==COLOR){
            sp=(rf && gf && bf);
        } else {
            sp=wf;
        }
    } else {
        sp=1;
    }
    return (et && f && tt && st && w && h && r && tc && tf && ac && ff && sp );

}
int ParametrosCamara::operator!= (ParametrosCamara src){
    return !operator==(src);
}

//Constructor
Camara::Camara(){
    _sensor=NULL;
    param._redFile="";
    param._greenFile="";
    param._blueFile="";
    param._whiteFile="";
    //init(DEFAULT_WIDTH,DEFAULT_HEIGHT,DEFAULT_FPS,DEFAULT_EXPOSURE_TIME,DEFAULT_TIPO,DEFAULT_FRAME_TYPE,DEFAULT_TRANSPORT_TIME,DEFAULT_SHUTTER_TIME);
//    setSpectrumsDefaults();

}

int Camara::init(unsigned int Width, unsigned int Height,float Fps, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType, float TransportTime,float ShutterTime){

    param._width=Width;
    param._height=Height;
    param._fps=Fps;
    param._exposureTime=ExposureTime;
    param._tipo=Tipo;
    param._frameType=FrameType;
    param._transportTime=TransportTime;
    param._shutterTime=ShutterTime;
    param._autoConfig=FIXED_FPS_FIXED_EXPOSE;
    param._roi.top=0;
    param._roi.left=0;
    param._roi.width=param._width;
    param._roi.height=param._height;
    return calcTimes();
}

int Camara::initFPS(unsigned int Width, unsigned int Height,float Fps, tipoCamara Tipo, tipoFrame FrameType, float TransportTime,float ShutterTime){
    param._width=Width;
    param._height=Height;
    param._fps=Fps;
    param._exposureTime=DEFAULT_EXPOSURE_TIME;
    param._tipo=Tipo;
    param._frameType=FrameType;
    param._transportTime=TransportTime;
    param._shutterTime=ShutterTime;
    param._autoConfig=FIXED_FPS_AUTO_EXPOSE;
    param._roi.top=0;
    param._roi.left=0;
    param._roi.width=param._width;
    param._roi.height=param._height;
    return calcTimes();

}

int Camara::initExposureTime(unsigned int Width, unsigned int Height, float ExposureTime, tipoCamara Tipo, tipoFrame FrameType, float TransportTime,float ShutterTime){
    param._width=Width;
    param._height=Height;
    param._fps=DEFAULT_FPS;
    param._exposureTime=ExposureTime;
    param._tipo=Tipo;
    param._frameType=FrameType;
    param._transportTime=TransportTime;
    param._shutterTime=ShutterTime;
    param._autoConfig=AUTO_FPS_FIXED_EXPOSE;
    param._roi.top=0;
    param._roi.left=0;
    param._roi.width=param._width;
    param._roi.height=param._height;
    return calcTimes();


}

//Destructor
Camara::~Camara(){
    if (_sensor!=NULL){
        delete[] _sensor;
    }
}

//Operadores
int Camara::operator== (Camara src){
/*
    int w =(param._width==src.width());
    int h =(param._height==src.height());
    int r =(param._roi==src.roi());
    int f =(param._fps==src.fps());
    int et=(param._exposureTime==src.exposureTime());
    int t =(param._tipo==src.tipo());
    int ft=(param._frameType==src.frameType());
    int tt=(param._transportTime==src.transportTime());
    int st=(param._shutterTime==src.shutterTime());
    int ff=(param._fromFiles==src.fromFiles());
    int fr=(param._redFile==src.redFile());
    int fg=(param._greenFile==src.greenFile());
    int fb=(param._blueFile==src.blueFile());
    int fw=(param._whiteFile==src.whiteFile());
    return (w && h && r && f && et && t && ft && tt && st && ff && fr && fg && fb && fw);
*/
    return (param==src.getParametros());
}
int Camara::operator!= (Camara src){
    return !operator==(src);
}

//Funciones GET
unsigned int Camara::width(){
    return param._width;
}
unsigned int Camara::height(){
    return param._height;
}
ROI Camara::roi (){
    return param._roi;
}
float Camara::fps(){
    return param._fps;
}
float Camara::exposureTime() {
    return param._exposureTime;
}
tipoCamara Camara::tipo(){
    return param._tipo;
}
tipoFrame Camara::frameType() {
    return param._frameType;
}
float Camara::transportTime(){
    return param._transportTime;
}
float Camara::shutterTime(){
    return param._shutterTime;
}
int Camara::fromFiles(){
    return param._fromFiles;
}
string Camara::redFile() {
    return param._redFile;
}
string Camara::greenFile(){
    return param._greenFile;
}
string Camara::blueFile(){
    return param._blueFile;
}
string Camara::whiteFile(){
    return param._whiteFile;
}
Spectrum Camara::sensor (int index){
    return _sensor[index];
}
autoSettings Camara::autoConfig(){
    return param._autoConfig;
}
ParametrosCamara Camara::getParametros(){
    return param;
}
float Camara::getNotIntegrationTime(){
    return ((1/param._fps)-param._exposureTime);
}
//Funciones SET
int Camara::setSize(unsigned int width, unsigned int height) {
    param._width=width;
    param._height=height;
    param._roi.left=0;
    param._roi.top=0;
    param._roi.width=param._width;
    param._roi.height=param._height;

    return calcTimes();
}
int Camara::roi (unsigned int width, unsigned int height,unsigned int top, unsigned int left){
    param._roi.width=width;
    param._roi.height=height;
    param._roi.left=left;
    param._roi.top=top;
    return calcTimes();

}
int Camara::roi (ROI Roi){
    param._roi.width=Roi.width;
    param._roi.height=Roi.height;
    param._roi.left=Roi.left;
    param._roi.top=Roi.top;
    return calcTimes();

}
int Camara::fps(float Fps){
    param._fps=Fps;
    param._autoConfig=FIXED_FPS_AUTO_EXPOSE;
    return calcTimes();
}
int Camara::exposureTime(float ExposureTime){
    param._exposureTime=ExposureTime;
    param._autoConfig=AUTO_FPS_FIXED_EXPOSE;
    return calcTimes();
}
int Camara::fpsExposureTime(float Fps,float ExposureTime){
    param._exposureTime=ExposureTime;
    param._fps=Fps;
    param._autoConfig=FIXED_FPS_FIXED_EXPOSE;
    return calcTimes();
}
int Camara::tipo(tipoCamara Tipo){
    param._tipo=Tipo;
    return calcTimes();
}
int Camara::frameType(tipoFrame FrameType) {
    param._frameType=FrameType;
    return calcTimes();
}
int Camara::transportTime(float TransportTime){
    param._transportTime=TransportTime;
    return calcTimes();
}
int Camara::shutterTime(float ShutterTime){
    param._shutterTime=ShutterTime;
    return calcTimes();
}
int Camara::setSpectrumsFiles(string RedFile, string GreenFile, string BlueFile){
    param._fromFiles=true;
    param._tipo=COLOR;
    param._redFile=RedFile;
    param._greenFile=GreenFile;
    param._blueFile=BlueFile;
    if (_sensor!=NULL){
        delete[] _sensor;
    }
    _sensor=new Spectrum[3];//(200e-9,1000e-9,SPECTRUM_SIZE);
    int r,g,b;
    r=_sensor[2].initSpectrumFromFile(param._redFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    g=_sensor[1].initSpectrumFromFile(param._greenFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    b=_sensor[0].initSpectrumFromFile(param._blueFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    return (calcTimes() || (r||g||b));
}
int Camara::setSpectrumsFiles(string WhiteFile){
    param._fromFiles=true;
    param._tipo=BW;
    param._whiteFile=WhiteFile;
    if (_sensor!=NULL){
        delete[] _sensor;
    }
    _sensor=new Spectrum[1];//(200e-9,1000e-9,SPECTRUM_SIZE);
    int w;
    w=_sensor[0].initSpectrumFromFile(param._whiteFile,1e-9,1,DEFAULT_START_LAMDA,DEFAULT_END_LAMDA,DEFAULT_SPECTRUM_SIZE);
    return (calcTimes() || w);
}
int Camara::setSpectrumsDefaults(){
    param._fromFiles=false;
    if (_sensor!=NULL){
        delete[] _sensor;
    }
	if (param._tipo==COLOR){
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
	return 0;
}
int Camara::autoConfig(autoSettings AutoConfig){
    param._autoConfig=AutoConfig;
    return calcTimes();
}


//Funciones Privadas
int Camara::calcTimes(){
    float exposureTimeMin;
    float fpsMax,fpsMax_ExposeMin;
    int transportVoid,transportExpose;
    float timeShutter;
    int error;
    switch (param._frameType){
        case FULL_FRAME:
            transportVoid=(param._height-param._roi.top-param._roi.width)+((1+param._width-param._roi.left)*param._roi.height);
            transportExpose=0;
            timeShutter=2*param._shutterTime;
            break;
        case FRAME_TRANSFERE:
            transportVoid=2*param._height-param._roi.top-param._roi.height;
            transportExpose=param._roi.height*(1+param._width-param._roi.left);
            timeShutter=0;
            break;
        case INTERLINE:
            transportVoid=1;
            transportExpose=(param._height-param._roi.top-param._roi.height)+(param._roi.height*(1+(param._width-param._roi.left)));
            timeShutter=0;
            break;
        default:
            return -1;
            break;
    }

    exposureTimeMin=transportExpose*param._transportTime;
    fpsMax=1/((transportVoid*param._transportTime) + timeShutter +param._exposureTime);
    fpsMax_ExposeMin=1/((transportVoid*param._transportTime) + timeShutter + exposureTimeMin);
    error=0;
    switch (param._autoConfig){
        case FIXED_FPS_FIXED_EXPOSE: //FPS fijo y exposicion fijo
            if (param._exposureTime<exposureTimeMin){
                param._exposureTime=exposureTimeMin;
                error=error+2; //Error en exposuretime
                if(param._fps>fpsMax_ExposeMin){
                    param._fps=fpsMax_ExposeMin;
                    error=error+1;
                }
            } else if (param._fps>fpsMax) {
                param._fps=fpsMax;
                error=error+1; //    Error en FPS
            }
            break;
        case FIXED_FPS_AUTO_EXPOSE: //FPS fijo, exposicion automatico
            error=0;
            if (param._fps>fpsMax_ExposeMin){
                param._exposureTime=exposureTimeMin;
                param._fps=fpsMax_ExposeMin;
                error=error+1;
            } else {
                param._exposureTime=(1/param._fps)-((param._transportTime*transportVoid)+timeShutter);
            }
            break;
        case AUTO_FPS_FIXED_EXPOSE: //FPS automatico, exposicion fijo
            if (param._exposureTime<exposureTimeMin){
                param._exposureTime=exposureTimeMin;
                param._fps=fpsMax_ExposeMin;
                error=error+2;  //Error en exposuretime
            } else {
                param._fps=fpsMax;
            }

            break;
        default:
            error=-1;
            break;
    }
    return error;

}

