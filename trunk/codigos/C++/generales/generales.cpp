#include "generales.hpp"

int myRound(float valor, roundType tipo=ROUND_APROX){
	switch (tipo){
		case ROUND_DOWN: // por debajo
			return ((int)valor);
			break;
		case ROUND_UP:	//por encima
			if ((int)valor==valor){
				return ((int)valor);
			} else {
				return (((int)valor)+1);
			}
			break;
		case ROUND_APROX:
			if (abs( ((int)valor)-valor )>=0.5){
				return (((int)valor)+1);
			} else {
				return (((int)valor));
			}
			break;
		default:
			return (0);
			break;
	}
}

bool setPoint(float *arreglo, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float valor){
	if ((y*w+x)>=(w*h) || (y*w+x)<0 || x>=w || x<0 || y>=h || y<0 ){
		return false;
	}
	arreglo[y*w+x]=valor;
	return true;
}

bool getPoint(float *arreglo, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float *valor){
	if ((y*w+x)>=(w*h) || (y*w+x)<0 || x>=w || x<0 || y>=h || y<0 ){
		return false;
	}
	*valor=arreglo[y*w+x];
	return true;
}


void ajustaFFT(const Mat& src, Mat &dst){

    Mat tempA;
    Mat tempB;
    //rows=N
    //cols=1
    tempA.create(src.rows,2*src.cols,src.type());
    tempA.setTo(Scalar::all(0));

    Mat roiA(tempA, Rect(src.cols,0,src.cols,src.rows));
    src.copyTo(roiA);
    Mat roiB(tempA,Rect(0,0,src.cols,src.rows));
    src.copyTo(roiB);
    tempA(Rect(src.cols/2,0, src.cols, src.rows)).copyTo(dst);

}

void copyPart(const Mat& src, Mat &dst, unsigned int Width,unsigned int Height, unsigned int Left,unsigned int Top){
    unsigned int realWidth,realHeight;
    unsigned int dstWidth,dstHeight;
    //int tipo;
    dst.create(Height,Width,src.type());
    dst.setTo(Scalar::all(0));
    //tipo=dst.type();
        if (Left>(unsigned int)src.cols || Top>(unsigned int)src.rows) {
            return;
        }
        realWidth=src.cols-Left;
        realHeight=src.rows-Top;
        if (realWidth>Width) {
            dstWidth=Width;
        } else {
            dstWidth=realWidth;
        }
        if (realHeight>Height) {
            dstHeight=Height;
        } else {
            dstHeight=realHeight;
        }
        Mat roi(dst,Rect(0,0,dstWidth,dstHeight));
        src(Rect(Left,Top,dstWidth,dstHeight)).copyTo(roi);
        //tipo=dst.type();
        return;
}

void desplaza(const Mat& src, Mat &dst, int desp){
    Mat tempA;
    //Mat tempB;
    int d;

    if (desp>0){
        d=desp;
        tempA.create(src.rows,src.cols+2*d,src.type());
        tempA.setTo(Scalar::all(0));
        Mat roiA(tempA, Rect(2*d,0,src.cols,src.rows));
        src.copyTo(roiA);
        tempA(Rect(d, 0, src.cols, src.rows)).copyTo(dst);
    } else {
        d=-desp;
        tempA.create(src.rows,src.cols+2*d,src.type());
        tempA.setTo(Scalar::all(0));
        Mat roiA(tempA, Rect(0,0,src.cols,src.rows));
        src.copyTo(roiA);
        tempA(Rect(d, 0, src.cols, src.rows)).copyTo(dst);
    }
    //cout<<"src=" <<src.rows<<"  dst="<<dst.rows<<endl;
}

double diffclock(clock_t clock1,clock_t clock2){
    double diffticks=clock1-clock2;
    double diffms=(diffticks*1000000)/CLOCKS_PER_SEC;
    return diffms;
}


double getContraste(const Mat& src)
{
    Mat gray;
    cvtColor(src, gray, CV_BGR2HLS);
    Scalar mean;
    Scalar stddev;
    meanStdDev(src, mean, stddev);
    return stddev[1];
}

void getHist(const Mat& src, Mat &dst, int width, int height, float rangos[]){

    Mat gray;
    cvtColor(src, gray, CV_BGR2HLS);

    // let's quantize the hue to 30 levels
    // and the saturation to 32 levels
    int bins = width;
    int hsize[] = {bins};
    // hue varies from 0 to 179, see cvtColor
   // float xranges[] = rangos;//{ 0, 256 };
    // saturation varies from 0 (black-gray-white) to
    // 255 (pure spectrum color)
    const float* ranges[] = { rangos };
    MatND hist;
    // we compute the histogram from the 0-th and 1-st channels
    int channels[] = {1};

    calcHist( &gray, 1, channels, Mat(), hist, 1, hsize, ranges, true, false );
    double maxVal=0;
    minMaxLoc(hist, 0, &maxVal, 0, 0);

    Mat histImg = Mat::zeros(height,bins, CV_8UC3);
    rectangle(histImg, Point(0,0), Point(bins,height), CV_RGB(255,255,255),-1);

    for( int h = 0; h < bins; h++ ){
            float binVal = hist.at<float>(h);
            int intensity = round(binVal*height/maxVal);
            line(histImg,Point(h,height), Point(h,height-intensity), CV_RGB(0,0,0));

            //rectangle( histImg, Point(h*scale, s*scale),Point( (h+1)*scale - 1, (s+1)*scale - 1),Scalar::all(intensity),CV_FILLED );
        }
        histImg.copyTo(dst);
}

void dibujaPatron(Mat *interferograma, int dim,int width, int height, string nombre){
    Mat imagen;
    imagen.create(height,width,CV_32FC3);
    imagen.setTo(Scalar::all(0));
    for (int i=0;i<dim;i++){
        for (int x=0;x<imagen.cols;x++){
            int j=x*interferograma[i].cols/imagen.cols;
            int y=50+100*(i)+50*(get2D32F(interferograma[i],j,0,0));

            //cout<<"x: " << j*2*Xmax[i]/(interf[i].rows-1) << " y: "<<y-250 <<endl;
            set2D32F(imagen,x,y,i,1);
            set2D32F(imagen,x,100*i,i,1);
            set2D32F(imagen,x,50+100*i,i,1);
            set2D32F(imagen,x,100+100*i,i,1);
        }
        for (int y=0;y<50;y++){
            set2D32F(imagen,(int)(imagen.cols/2),50+100*i+y-25,i,1);
        }

    }
    imshow( nombre, imagen);
}
/*
// FFT
void fft(int N, double **x, double **X){
// Declare a pointer to scratch space.
  double **XX=new double*[N];
  for(int i=0;i<N;i++){
      XX[i]=new double[2];
  }

  //double (*XX)[2] = (double*) malloc(2 * N * sizeof(double));

  // Calculate FFT by a recursion.
  fft_rec(N, 0, 1, x, X, XX);

  // Free memory.
  for (int i=0;i<N;i++){
      delete[] XX[i];
  }
  delete[]XX;
}
*/

/*// FFT recursion
void fft_rec(int N, int offset, int delta, double **x, double **X, double **XX) {
  int N2 = N/2;            // half the number of points in FFT
  int k;                   // generic index
  double cs, sn;           // cosine and sine
  int k00, k01, k10, k11;  // indices for butterflies
  double tmp0, tmp1;       // temporary storage

  if(N != 2)  // Perform recursive step.
    {
      // Calculate two (N/2)-point DFT's.
      fft_rec(N2, offset, 2*delta, x, XX, X);
      fft_rec(N2, offset+delta, 2*delta, x, XX, X);

      // Combine the two (N/2)-point DFT's into one N-point DFT.
      for(k=0; k<N2; k++)
        {
          k00 = offset + k*delta;    k01 = k00 + N2*delta;
          k10 = offset + 2*k*delta;  k11 = k10 + delta;
          cs = cos(TWO_PI*k/(double)N); sn = sin(TWO_PI*k/(double)N);
          tmp0 = cs * XX[k11][0] + sn * XX[k11][1];
          tmp1 = cs * XX[k11][1] - sn * XX[k11][0];
          X[k01][0] = XX[k10][0] - tmp0;
          X[k01][1] = XX[k10][1] - tmp1;
          X[k00][0] = XX[k10][0] + tmp0;
          X[k00][1] = XX[k10][1] + tmp1;
        }
    }
  else  // Perform 2-point DFT.
    {
      k00 = offset; k01 = k00 + delta;
      X[k01][0] = x[k00][0] - x[k01][0];
      X[k01][1] = x[k00][1] - x[k01][1];
      X[k00][0] = x[k00][0] + x[k01][0];
      X[k00][1] = x[k00][1] + x[k01][1];
    }
}
*/
/*
// IFFT
void ifft(int N, double **x, double **X){
  int N2 = N/2;       // half the number of points in IFFT
  int i;              // generic index
  double tmp0, tmp1;  // temporary storage

  // Calculate IFFT via reciprocity property of DFT.
  fft(N, X, x);
  x[0][0] = x[0][0]/N;    x[0][1] = x[0][1]/N;
  x[N2][0] = x[N2][0]/N;  x[N2][1] = x[N2][1]/N;
  for(i=1; i<N2; i++)
    {
      tmp0 = x[i][0]/N;       tmp1 = x[i][1]/N;
      x[i][0] = x[N-i][0]/N;  x[i][1] = x[N-i][1]/N;
      x[N-i][0] = tmp0;       x[N-i][1] = tmp1;
    }
}
*/
/*
float funcion(float f, float fharm, int sizeHarm){
    float valor=0;
    float fo=fharm;
    float s=2;
    int j;
    for (j=0;j<sizeHarm;j++){
        valor+=1*exp(-3*j/sizeHarm)*exp(-(f-j*fo)*(f-j*fo)/(2*s*s));
    }
    //valor=2*(1*1+(1+2*exp(-(f-fo)*(f-fo)/(2*s*s))+2*exp(-(f-2*fo)*(f-2*fo)/(2*s*s))+1.5*exp(-(f-3*fo)*(f-3*fo)/(2*s*s))+2.0*exp(-(f-4*fo)*(f-4*fo)/(2*s*s))));
    //valor=(1+2*exp(-(f-fo)*(f-fo)/(2*s*s))+2*exp(-(f-2*fo)*(f-2*fo)/(2*s*s))+1.5*exp(-(f-3*fo)*(f-3*fo)/(2*s*s))+2.0*exp(-(f-4*fo)*(f-4*fo)/(2*s*s)));
    if (valor>=0){
        return valor;
    } else {
        return 0;
    }
}
*/

/*
void getRuido(int N, double* dst, float ti,float amp,float ampRuido, float fharm, int sizeHarm){
    srand(time(NULL));
    int i;
    double **src;
    double **fdst;
    float fmax=N/(ti);
    float deltaf=fmax/N;
    src=new double*[N];
    fdst=new double*[N];
    float f;
    for (i=0;i<N;i++){
        src[i]=new double[2];
        fdst[i]=new double[2];
    }
    src[0][0]=src[0][1]=N*amp*funcion(0,fharm,sizeHarm);
    for (i=1;i<(N>>1);i++){
        f=i*deltaf;
        float fase=N*ampRuido*(double)(rand()%1000)/1000;
        src[i][1]=fase;
        src[N-i][1]=-fase;
        src[i][0]=src[N-i][0]=N*amp*funcion(f,fharm,sizeHarm);
    }
    f=(N>>1)*deltaf;
    src[(N>>1)][0]=N*funcion(f,fharm,sizeHarm);
    src[(N>>1)][1]=N*ampRuido*(double)(rand()%1000)/1000;

    ifft(N,fdst,src);
    //fdst[0][0]=fdst[1][0];
    //double max;
    //max=(fdst[0][0]);
    for (i=0;i<N>>1;i++){

        dst[i]=fdst[i+(N>>1)][0];
        dst[i+(N>>1)]=fdst[i][0];

    }
    for (i=0;i<N;i++){
        //dst[i]*=amp/max;
        delete[] src[i];
        delete[] fdst[i];
    }
    delete[] src;
    delete[] fdst;
}
*/
