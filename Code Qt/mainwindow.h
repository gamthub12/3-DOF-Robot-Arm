#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QtWidgets>
#include <QMessageBox>
#include "Robot.h"
#include <QTimer>
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();  
    int Tocdo;
public slots:
    void Hienthi_goc();
    void Hienthi_xyz();
private slots:
    void on_btn_connect_clicked();

    void on_j1cong_clicked();
    void on_j1tru_clicked();
    void on_j2cong_clicked();
    void on_j2tru_clicked();
    void on_j3cong_clicked();
    void on_j3tru_clicked();
    void on_daugap_clicked();

    void on_Them_diem_clicked();
    void on_Bat_dau_clicked();
    void on_Xoa_diem_clicked();

    void on_j1cong_released();
    void on_j1cong_pressed();
    void on_j1tru_pressed();
    void on_j1tru_released();
    void on_j2cong_pressed();
    void on_j2cong_released();
    void on_j2tru_pressed();
    void on_j2tru_released();
    void on_j3cong_pressed();
    void on_j3cong_released();
    void on_j3tru_pressed();
    void on_j3tru_released();

    void on_Toc_do_valueChanged(int value);
    void on_Home_clicked();

private:
    Ui::MainWindow *ui;
    RobotArm  Robot;
    void Nhan_cong();
    bool Trangthai_ketnoi;
    bool Trangthai_batdau;
    bool Trangthai_auto;
    QTimer *timer_j1cong =new QTimer(this);
    void start_j1cong();
    void stop_j1cong();
    QTimer *timer_j1tru =new QTimer(this);
    void start_j1tru();
    void stop_j1tru();
    QTimer *timer_j2cong =new QTimer(this);
    void start_j2cong();
    void stop_j2cong();
    QTimer *timer_j2neg =new QTimer(this);
    void start_j2tru();
    void stop_j2tru();
    QTimer *timer_j3pos =new QTimer(this);
    void start_j3cong();
    void stop_j3cong();
    QTimer *timer_j3tru =new QTimer(this);
    void start_j3tru();
    void stop_j3tru();

};
#endif // MAINWINDOW_H
