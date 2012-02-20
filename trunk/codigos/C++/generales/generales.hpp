#ifndef _generales_h_included_
#define _generales_h_included_
#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace cv;
using namespace std;
/*
//1D Sin Canales
    //Float
#define set1D32F(mat,x,value) (*((float*)((mat).data+((x)*(mat).step))))=(value)
#define get1D32F(mat,x) (*((float*)((mat).data+((x)*(mat).step))))

    //Integer
#define set1D8U(mat,x,value) (*((unsigned int*)((mat).data+((x)*(mat).step))))=(value)
#define get1D8U(mat,x) (*((unsigned int*)((mat).data+((x)*(mat).step))))

//1D Con Canales
    //Float
#define set1D32FC(mat,x,channel,value) (*((float*)((mat).data+((x)*(mat).step+))+(channel)))=(value)
#define get1D32FC(mat,x,channel) (*((float*)((mat).data+((x)*(mat).step+))+(channel)))

    //Integer
#define set1D8UC(mat,x,channel,value) (*((unsigned int*)((mat).data+((x)*(mat).step+))+(channel)))=(value)
#define get1D8UC(mat,x,channel) (*((unsigned int*)((mat).data+((x)*(mat).step+))+(channel)))

//2D Sin Canales
    //Float
//#define set2D32F(mat,x,y,value) (*((float*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))))=(value)
#define set2D32F(matrix,x,y,value)  (matrix.ptr<float>(x)[y])=(value)
//#define get2D32F(mat,x,y) (*((float*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))))
#define get2D32F(mat,x,y) (matrix.ptr<float>(x)[y])

    //Integer
#define set2D8U(mat,x,y,value) (*((unsigned char*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))))=(value)
#define get2D8U(mat,x,y) (*((unsigned char*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))))

//2D Con Canales
    //Float
#define set2D32FC(mat,x,y,channel,value) (*((float*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))+(channel)))=(value)
#define get2D32FC(mat,x,y,channel) (*((float*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))+(channel)))

    //Integer
#define set2D8UC(mat,x,y,channel,value) (*((unsigned int*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))+(channel)))=(value)

#define get2D8UC(mat,x,y,channel) (*((unsigned int*)((mat).data+((x)*(mat).step+(y)*(mat).elemSize()))+(channel)))
*/

#define set2D8U(mat,x,y,c,value)  ((mat).ptr<unsigned char>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D8U(mat,x,y,c) ((mat).ptr<unsigned char>((y))[(mat).channels()*(x)+(c)])

#define set2D8S(mat,x,y,c,value)  ((mat).ptr<char>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D8S(mat,x,y,c) ((mat).ptr<char>((y))[(mat).channels()*(x)+(c)])

#define set2D16U(mat,x,y,c,value)  ((mat).ptr<unsigned short int>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D16U(mat,x,y,c) ((mat).ptr<unsigned short int>((y))[(mat).channels()*(x)+(c)])

#define set2D16S(mat,x,y,c,value)  ((mat).ptr<short int>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D16S(mat,x,y,c) ((mat).ptr<short int>((y))[(mat).channels()*(x)+(c)])

#define set2D16U(mat,x,y,c,value)  ((mat).ptr<unsigned short int>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D16U(mat,x,y,c) ((mat).ptr<unsigned short int>((y))[(mat).channels()*(x)+(c)])

#define set2D32S(mat,x,y,c,value)  ((mat).ptr<int>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D32S(mat,x,y,c) ((mat).ptr<int>((y))[(mat).channels()*(x)+(c)])

#define set2D32F(mat,x,y,c,value)  ((mat).ptr<float>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D32F(mat,x,y,c) ((mat).ptr<float>((y))[(mat).channels()*(x)+(c)])

#define set2D64F(mat,x,y,c,value)  ((mat).ptr<double>((y))[(mat).channels()*(x)+(c)])=(value)
#define get2D64F(mat,x,y,c) ((mat).ptr<double>((y))[(mat).channels()*(x)+(c)])


#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

typedef enum {ROUND_UP=1, ROUND_DOWN=0, ROUND_APROX=2} roundType;
int myRound(float valor, roundType tipo);

bool setPoint(float *arreglo, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float valor);

bool getPoint(float *arreglo, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float *valor);
//void convolveDFT(const Mat& A, const Mat& B, Mat& C);
void ajustaFFT(const Mat& src, Mat& dst);


void desplaza(const Mat& src, Mat &dst, int desp);
void copyPart(const Mat& src, Mat &dst, unsigned int Width,unsigned int Height, unsigned int Left=0,unsigned int Top=0);

double diffclock(clock_t clock1,clock_t clock2);

void getHist(const Mat& src, Mat &dst, int width, int height, float rangos[]);

double getContraste(const Mat& src);
void dibujaPatron(Mat *interferograma, int dim,int width, int height, string nombre);
int roundn(double d);
/*
#define TWO_PI (6.2831853071795864769252867665590057683943L)


// function prototypes
void fft(int N, double **x, double **X);
void fft_rec(int N, int offset, int delta,
             double **x, double **X, double **XX);
void ifft(int N, double **x, double **X);
//void getRuido(int N, double*dst, float ti,float amp, float fharm, int sizeHarm);
*/

#endif
