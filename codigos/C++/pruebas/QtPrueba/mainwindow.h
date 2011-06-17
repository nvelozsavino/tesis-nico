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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setImg(Mat img);
    void paintImage(void);
    QPixmap mat2qimage(const Mat& mat);
private:
    Ui::MainWindow *ui;
    QImage image;
    QPixmap pixmap;


private slots:
    void on_pushButton_cancel_clicked();
    void on_pushButton_ok_clicked();
};

#endif // MAINWINDOW_H
