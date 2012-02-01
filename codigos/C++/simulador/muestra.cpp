#include "muestra.hpp"


void Muestra::initMuestra(float rWidth,float rHeight, float resolucion){
//int createMuestra(Muestra *muestra, double realWidth,double realHeight, double resolucion){
    realWidth=rWidth;
	realHeight=rHeight;
	width=myRound(realWidth*resolucion,ROUND_UP);
	height=myRound(realHeight*resolucion,ROUND_UP);
	resolucion=width/realWidth;
	depth.create(height,width,CV_32FC1);
	visibilidad.create(height,width,CV_32FC1);
	resDepth=1;
	resVisibility=1;
//	int tipo;
//	tipo=depth.type();
	//depth=new float[width*height];
	//visibilidad= new float[width*height];

	//depth = (double*) calloc (muestra->width*muestra->height,sizeof(double));
	//muestra->visibilidad = (double*) calloc (muestra->width*muestra->height,sizeof(double));

	//muestra->resolucion=resolucion;
//	tipo=0;

}

Muestra::~Muestra(){
/*    if (depth!=NULL){
        delete[] depth;
    }
    if (visibilidad!=NULL){
        delete[] visibilidad;
    }
    */
}


/*int Muestra::setPMuestra(unsigned int x,unsigned int y,lugarMuestra lugar, float valor){
	if ((y*width+x)>=(width*height) || (y*width+x)<0 || x>=width || x<0 || y>=height || y<0 ){
		return -1;
	}
	set2D32FC(x,y,lugar,valor);
	return 0;
}
*/
/*
bool Muestra::getPMuestra(unsigned int x, unsigned int y, lugarMuestra lugar, float *valor){
	float *temp;
	if (lugar==IN_DEPTH){
		temp=depth;
	} else {
		temp=visibilidad;
	}
	if ((y*width+x)>=(width*height) || (y*width+x)<0 || x>=width || x<0 || y>=height || y<0 ){
		return false;
	}
	*valor=temp[y*width+x];
	return true;
}
*/
void Muestra::setMuestraFromFile(string filename, float resolucion, lugarMuestra lugar, int top = 0, int left=0){
    //int right, buttom;
    //int imgW,imgH, arrayW,arrayH;
    Mat imagen;
    Mat *array;

    int startX,endX,startY,endY;
    int x0,y0;
    if (lugar==IN_DEPTH){
        array=&depth;
        resDepth=resolucion;
    } else {
        array=&visibilidad;
        resVisibility=resolucion;
    }
    imagen=imread(filename,CV_16UC1);
    if (imagen.data==NULL){
        cout <<"error al cargar el archivo"<<endl;
        exit(EXIT_FAILURE);
    }
    imagen.convertTo(imagen,CV_32FC1);
    imagen/=65535;
    if (top<0){
        startY=0;
        y0=top;
    } else {
        startY=top;
        y0=0;
    }

    if (left<0){
        startX=0;
        x0=left;
    } else {
        startX=left;
        x0=0;
    }

    if (imagen.cols>(*array).cols){
        endX=(*array).cols;
    } else {
        endX=imagen.cols;
    }
    if (imagen.rows>(*array).rows){
        endY=(*array).rows;
    } else {
        endY=imagen.rows;
    }
    for(int x=startX;x<endX;x++){
        for(int y=startY;y<endY;y++){
            float valor;
            valor=get2D32F(imagen,x,y,0);
            set2D32F((*array),x+x0,y+y0,0,valor);
        }
    }
    //imshow("muestra",imagen);
    //imagen/=normMax;
    //(*array)*=resolucion;

}


void Muestra::setMuestraFull(lugarMuestra lugar){
    setMuestraPlain(1,lugar);
}

void Muestra::setMuestraPlain(float amplitud,lugarMuestra lugar){
    Mat *array;
    if (lugar==IN_DEPTH){
        array=&depth;
    } else {
        array=&visibilidad;
    }
	for (unsigned int i=0; i<width;i++){
		for (unsigned int j=0;j<height;j++){
			set2D32F((*array),i,j,0,amplitud);
		}
	}
}
