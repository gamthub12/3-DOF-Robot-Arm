#include "Robot.h"

RobotArm::RobotArm(QObject *parent)
    : QObject{parent},
    Demthoigian(new QTimer(this)),
    Ketnoi_arduino(nullptr)

{
    QObject::connect(Demthoigian, &QTimer::timeout, this, &RobotArm::Dichuyen_Auto);
    QObject::connect(timer_diem_next, &QTimer::timeout, this, &RobotArm::DiemtoDiem);
    QObject::connect(timer_vitri_Home, &QTimer::timeout, this, &RobotArm::Home);
}

bool RobotArm::Ket_noi(QString portName)
{
    Ketnoi_arduino = new QSerialPort(this);
    Ketnoi_arduino->setPortName(portName);
    Ketnoi_arduino->setBaudRate(QSerialPort::Baud9600);
    Ketnoi_arduino->setDataBits(QSerialPort::Data8);
    Ketnoi_arduino->setParity(QSerialPort::NoParity);
    Ketnoi_arduino->setStopBits(QSerialPort::OneStop);
    if(Ketnoi_arduino->open(QIODevice::ReadWrite)){
        QObject::connect(Ketnoi_arduino, &QSerialPort::readyRead, this, &RobotArm::dataReady);
    }
    return Ketnoi_arduino->isOpen();
}

void RobotArm::Ngat_Ket_noi()
{
    if(Ketnoi_arduino!=nullptr&&Ketnoi_arduino->isOpen()){
        Ketnoi_arduino->close();
        if (Ketnoi_arduino->error() != QSerialPort::NoError) {
            qDebug() << Ketnoi_arduino->errorString();
        }
    }

}

void RobotArm::write(QByteArray data)
{
    data.append(' ');
    Ketnoi_arduino->write(data);
}
RobotArm::~RobotArm()
{
    if(Ketnoi_arduino != nullptr){
        Ketnoi_arduino->close();
        delete Ketnoi_arduino;
    }
}

void RobotArm::dataReady()
{
    if(Ketnoi_arduino->isOpen()){
        emit Nhan_Dulieu( Ketnoi_arduino->readAll());
    }
}


void RobotArm::Dichuyen_Auto()
{
    if (Diem_hien_tai < Toa_do.size() && !timer_diem_next->isActive()) {
        Tach_goc = Toa_do[Diem_hien_tai].mid(1).split(':');
        timer_diem_next->start(25);
        Diem_hien_tai++;
        if (Diem_hien_tai == Toa_do.size()) {
            Diem_hien_tai = 0;
        }
    }
}

void RobotArm::DiemtoDiem()
{
    static  int Nextj1, Nextj2, Nextj3, Nextgap;
    Nextj1 = Tach_goc[0].toInt();
    Nextj2 = Tach_goc[1].toInt();
    Nextj3 = Tach_goc[2].toInt();
    Nextgap = Tach_goc[3].toInt();
    if (j1 != Nextj1)
    {
        if (j1 < Nextj1) {
            j1 += 1;
            if (j1 >Nextj1) {
                j1 = Nextj1;
            }
        } else {
            j1 -= 1;
            if (j1 < Nextj1) {
                j1=Nextj1;
            }
        }
    }
    if(j2!=Nextj2)
    {
        if (j2 <Nextj2) {
            j2 += 1;
            if (j2 >Nextj2) {
                j2 =Nextj2;
            }
        } else {
            j2 -= 1;
            if (j2 <Nextj2) {
                j2 = Nextj2;
            }
        }
    }
    if(j3!=Nextj3)
    {
        if (j3 <Nextj3) {
            j3 += 1;
            if (j3 > Nextj3) {
                j3 = Nextj3;
            }
        } else {
            j3 -= 1;
            if (j3 < Nextj3) {
                j3 = Nextj3;
            }
        }
    }
    if(gap!=Nextgap)
    {
        gap= Nextgap;
    }
    QString coordinate = QString(">%1:%2:%3:%4").arg(j1).arg(j2).arg(j3).arg(gap);
    write(coordinate.toUtf8());
    if (j1 == Nextj1 && j2 == Nextj2 && j3 == Nextj3 && gap==Nextgap)
    {
        Donghoc_thuan();
        emit Capnhat_ManHinh();
        timer_diem_next->stop();
    }
}

void RobotArm::dichuyenkhop(int cases)
{
    QString str;
    switch (cases) {
    case 1:
        if(j1>=0&&j1<110){
        j1+=1;
        }
        break;
    case 2:
        if(j1>0&&j1<=110){
        j1-=1;
        }
        break;
    case 3:
        if(j2>=-6&&j2<53){
        j2+=1;
    }
        break;
    case 4:
        if(j2>-6&&j2<=53){
        j2-=1;
        }
        break;
    case 5:
        if(j3>= -120&&j3<-49){
        j3+=1;
        }
        break;
    case 6:
        if(j3>-120&&j3<=-49){
        j3-=1;
        }
        break;
    case 7:
        if(gap==0)
            gap =1;
        else gap =0;
        break;
     default:
          break;
    }
     str = QString(">%1:%2:%3:%4").arg(j1).arg(j2).arg(j3).arg(gap);
     write(str.toUtf8());
     Donghoc_thuan();
     emit Capnhat_ManHinh();
}



void RobotArm::Them_diem(QString now_point)
{
    Toa_do.append( now_point);
}



QString RobotArm::ThongTin_khop()
{
    return QString(">%1:%2:%3:%4").arg(j1).arg(j2).arg(j3).arg(gap);
}


void RobotArm::Bat_dau_auto() {
    Demthoigian->start(1);
}

void RobotArm::Ketthuc_auto() {
    Demthoigian->stop();
}


void RobotArm::Xoa_diemAuto()
{
    Diem_hien_tai=0;
    Toa_do.clear();
}


void RobotArm::Donghoc_thuan()
{
    x = d2*cos((M_PI*j1)/180)*cos((M_PI*j2)/180)  +  d3*cos((M_PI*j1)/180)*cos((M_PI*j2)/180)*cos((M_PI*j3)/180)  -  d3*cos((M_PI*j1)/180)*sin((M_PI*j2)/180)*sin((M_PI*j3)/180);
    y = d2*cos((M_PI*j2)/180)*sin((M_PI*j1)/180)  +  d3*cos((M_PI*j2)/180)*cos((M_PI*j3)/180)*sin((M_PI*j1)/180)  -  d3*sin((M_PI*j1)/180)*sin((M_PI*j2)/180)*sin((M_PI*j3)/180);
    z =  d1 + d2*sin((M_PI*j2)/180)  +  d3*cos((M_PI*j2)/180)*sin((M_PI*j3)/180)  +  d3*cos((M_PI*j3)/180)*sin((M_PI*j2)/180);

}

void RobotArm::Home()
{
    if (j1 != 0)
    {
        if (j1 <0) {
            j1 += 1;
            if (j1 >0) {
                j1 = 0;
            }
        } else {
            j1 -= 1;
            if (j1 < 0) {
                j1=0;
            }
        }
    }
    if(j2!=53)
    {
        if (j2 <53) {
            j2 += 1;
            if (j2 >53) {
                j2 =53;
            }
        } else {
            j2 -= 1;
            if (j2 <53) {
                j2 = 53;
            }
        }
    }
    if(j3!=-120)
    {
        if (j3 <-120) {
            j3 += 1;
            if (j3 > -120) {
                j3 = -120;
            }
        } else {
            j3 -= 1;
            if (j3 < -120)
            {
                j3 = -120;
            }
        }
    }
    QString Toado = QString(">%1:%2:%3:%4").arg(j1).arg(j2).arg(j3).arg(gap);
    write(Toado.toUtf8());
    if (j1 == 0 && j2 == 53 && j3 == -120)
    {
        Donghoc_thuan();
        emit Capnhat_ManHinh();
        timer_vitri_Home->stop();
    }
}
