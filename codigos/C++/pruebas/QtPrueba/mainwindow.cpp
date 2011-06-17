#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QImage dummy(300,100,QImage::Format_RGB32);
    image = dummy;
    for (int x = 0; x < 100; x ++) {
        for (int y =0; y < 100; y++) {
            image.setPixel(x,y,qRgb(x, y, y));
        }
    }
    ui->imagelabel->setPixmap(QPixmap::fromImage(image));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ok_clicked()
{
    //ui->label->setText("Ok");
    paintImage();
}

void MainWindow::on_pushButton_cancel_clicked()
{
    //quit();
    //ui->label->setText("Cancel");
}

void MainWindow::setImg(Mat img) {
    int x,y;
    x=img.cols;
    y=img.rows;
    QImage dummy(y,x,QImage::Format_RGB32);
    ui->imagelabel->setPixmap(QPixmap::fromImage(dummy));
    ui->label_x->setText(QString::number(x));
    ui->label_y->setText(QString::number(y));
    pixmap=mat2qimage(img);



}

void MainWindow::paintImage(){
    ui->imagelabel->setPixmap(pixmap);
}


QPixmap MainWindow::mat2qimage(const Mat& mat) {
    QPixmap p;
    Mat rgb,img;
    //img=mat;
    //cvtColor(img, img, CV_BGR2RGB);
    //ui->label_x->setText(QString::number(img.channels()));
    //ui->label_y->setText(QString::number(CV_8UC3));

    mat.convertTo(img,CV_8UC3,(double)(1/255));
    cvtColor(img, rgb, CV_BGR2RGB);
    p.loadFromData((uchar *)rgb.data,rgb.cols,rgb.rows)
            loadFromData((uchar *)rgb.data, rgb.cols, rgb.rows);
    return p;
};
