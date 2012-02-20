#include "ruido.hpp"

//Constructores
Ruido::Ruido(){
    _fileSpectrum="";
    _maxSize=0;
    _realSize=0;
    _espectro=NULL;
}
int Ruido::initRuido(string FileSpectrum,double Amplitud, unsigned int MaxPoints){
    return fileSpectrum(FileSpectrum,Amplitud,MaxPoints);
}

//Destructores
Ruido::~Ruido(){
    if (_espectro!=NULL){
        delete[] _espectro;
    }
}
//Funciones Get
double Ruido::getRuido(double time){
    float ruido=0;
    for (unsigned int i=0;i<_realSize;i++){
        ruido+=_espectro[i].value*cos(TWO_PI*_espectro[i].freq*time);
    }
    return ruido;
}
string Ruido::fileSpectrum(){
    return _fileSpectrum;
}
unsigned int Ruido::maxSize(){
    return _maxSize;
}
unsigned int Ruido::realSize(){
    return _realSize;
}
//Funciones Set
int Ruido::fileSpectrum(string FileSpectrum,double Amplitud, unsigned int MaxPoints){
    FILE *file;
    unsigned int i=0;
    int response;
    file=fopen(FileSpectrum.c_str(),"r");
    if (file == NULL) {
        cout<< "Error opening file"<<endl;
        return -1;
    } else {
        _fileSpectrum=FileSpectrum;
        _maxSize=MaxPoints;
        if (_espectro!=NULL){
            delete[] _espectro;
        }
        _espectro= new PuntoEspectro[_maxSize];
        do {
            response=fscanf(file,"%lf\t%lf\n",&(_espectro[i].freq),&(_espectro[i].value));
            _espectro[i].value*=Amplitud;
            i++;
        } while ((response==2 || response!=EOF) && i<_maxSize);
        _realSize=i;
        for (;i<_maxSize;i++){
            _espectro[i].value=0;
            _espectro[i].freq=0;
        }
        fclose(file);
    }
    return 0;
}














