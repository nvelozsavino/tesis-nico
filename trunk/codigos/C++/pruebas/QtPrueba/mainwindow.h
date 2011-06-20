#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(VideoCapture capture,QWidget *parent = 0);
    ~MainWindow();
    void setImg(Mat img);
    void paintImage(void);
    QImage mat2qimage(const Mat& mat);
private:
    Ui::MainWindow *ui;
    QImage image;
    Mat imagen;
    VideoCapture cap;

private slots:
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
protected:
    void timerEvent(QTimerEvent*);
};

#endif // MAINWINDOW_H
