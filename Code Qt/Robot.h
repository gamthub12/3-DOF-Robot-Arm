#ifndef ROBOT_H
#define ROBOT_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QVector>
#include <QMessageBox>
#include <QDebug>
#include <QStringList>
#include <cmath>


class RobotArm : public QObject
{
    Q_OBJECT
public:
    explicit RobotArm(QObject *parent = nullptr);
    ~RobotArm();
    bool Ket_noi(QString portName);
    void Ngat_Ket_noi();

    int j1=0, j2=53, j3=-120, gap = 0;

    double x, y, z;

    void write(QByteArray data);


    void dichuyenkhop(int cases);
    void Bat_dau_auto();
    void Ketthuc_auto();

    QTimer *Demthoigian =new QTimer(this);
    void Them_diem(QString now_point);
    QString ThongTin_khop();

    QVector<QString> Toa_do;
    int Diem_hien_tai=0;

    QTimer *timer_diem_next =new QTimer(this);
    QTimer *timer_vitri_Home =new QTimer(this);

    QStringList Tach_goc;
    void Xoa_diemAuto();
    QSerialPort *Ketnoi_arduino;

    void Donghoc_thuan();
    void Home();

signals:
      void Nhan_Dulieu(QByteArray(b));
      void Capnhat_ManHinh();


private slots:
      void dataReady();
public slots:

    void Dichuyen_Auto();
    void DiemtoDiem();

private:
    int d1 = 35, d2 = 70, d3 = 75;
};

#endif // ROBOT_H
