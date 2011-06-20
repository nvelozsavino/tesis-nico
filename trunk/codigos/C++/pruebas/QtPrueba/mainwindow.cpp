#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(VideoCapture capture, QWidget *parent) :
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
    cap=capture;
    startTimer(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ok_clicked()
{
    cap >> imagen;
    setImg(imagen);
    //ui->label->setText("Ok");
    paintImage();
}

void MainWindow::on_pushButton_cancel_clicked()
{
    //quit();
    //ui->label->setText("Cancel");
    ui->label_x->setText(QString::number(cap.get(CV_CAP_PROP_FOURCC )));
}

void MainWindow::setImg(Mat img) {
    int x,y;
    x=img.cols;
    y=img.rows;   
    QImage dummy(y,x,QImage::Format_RGB32);
    ui->imagelabel->setPixmap(QPixmap::fromImage(dummy));
    //ui->label_x->setText(QString::number(x));
    //ui->label_y->setText(QString::number(y));
    image=mat2qimage(img);



}

void MainWindow::paintImage(){
    ui->imagelabel->setPixmap(QPixmap::fromImage(image));
}


QImage MainWindow::mat2qimage(const Mat& mat) {
    //cvtColor(mat,mat,CV_BGR2RGB);
    QImage img(mat.data, mat.size().width, mat.size().height, mat.step,QImage::Format_RGB888);

    return img.rgbSwapped();;
};

void MainWindow::timerEvent(QTimerEvent*) {
    cap >> imagen;
    setImg(imagen);
    //ui->label->setText("Ok");
    paintImage();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_y->setText(QString::number(value));
    //cap.set(CV_CAP_PROP_HUE,(double)value);
    ui->label_x->setText(QString::number(cap.get(value)));
}
