#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    Trangthai_ketnoi(false),
    Trangthai_batdau(false),
    Trangthai_auto(false)
{
    ui->setupUi(this);
    Nhan_cong();
    QObject::connect(&Robot, &RobotArm::Capnhat_ManHinh, this, &MainWindow::Hienthi_goc);
    QObject::connect(&Robot, &RobotArm::Capnhat_ManHinh, this, &MainWindow::Hienthi_xyz);
    QObject::connect(timer_j1cong, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(1);});
    QObject::connect(timer_j1tru, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(2);});
    QObject::connect(timer_j2cong, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(3);});
    QObject::connect(timer_j2neg, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(4);});
    QObject::connect(timer_j3pos, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(5);});
    QObject::connect(timer_j3tru, &QTimer::timeout, this, [this]() { MainWindow::Robot.dichuyenkhop(6);});
    QPixmap anhRobot("C:/Qt_project/Project/robot.png");
    int w = ui->anhRobot->width();
    int h = ui ->anhRobot->height();
    ui->anhRobot->setPixmap(anhRobot.scaled(w,h, Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Toc_do_valueChanged(int value)
{
    Tocdo = 251-value;
}


void MainWindow::start_j1cong()
{
    timer_j1cong->start(Tocdo);
}

void MainWindow::stop_j1cong()
{
    timer_j1cong->stop();
}

void MainWindow::start_j1tru()
{
    timer_j1tru->start(Tocdo);
}

void MainWindow::stop_j1tru()
{
    timer_j1tru->stop();
}

void MainWindow::start_j2cong()
{
     timer_j2cong->start(Tocdo);
}

void MainWindow::stop_j2cong()
{
    timer_j2cong->stop();
}

void MainWindow::start_j2tru()
{
     timer_j2neg->start(Tocdo);
}

void MainWindow::stop_j2tru()
{
    timer_j2neg->stop();
}

void MainWindow::start_j3cong()
{
     timer_j3pos->start(Tocdo);
}

void MainWindow::stop_j3cong()
{
    timer_j3pos->stop();
}

void MainWindow::start_j3tru()
{
     timer_j3tru->start(Tocdo);
}

void MainWindow::stop_j3tru()
{
    timer_j3tru->stop();
}

void MainWindow::Hienthi_goc()
{
        ui->Toado_j1->setText(QByteArray::number(Robot.j1));
        ui->Toado_j2->setText(QByteArray::number(Robot.j2));
        ui->Toado_j3->setText(QByteArray::number(Robot.j3));
}

void MainWindow::Nhan_cong(){

    foreach (auto &cong_com, QSerialPortInfo::availablePorts()){
        ui->Cong_com->addItem(cong_com.portName());
    }
}

void MainWindow::on_btn_connect_clicked()
{
    if(!Trangthai_ketnoi)
    {
    auto isConnected = Robot.Ket_noi(ui->Cong_com->currentText());
    if(!isConnected){

    }
    ui->btn_connect->setText("Ngắt Kết Nối");
    }
    else
    {
        Robot.Ngat_Ket_noi();
         ui->btn_connect->setText("Kết Nối");
    }
    Trangthai_ketnoi=!Trangthai_ketnoi;
}

void MainWindow::on_j1cong_clicked()
{
    Robot.dichuyenkhop(1);
}

void MainWindow::on_j1tru_clicked()
{
     Robot.dichuyenkhop(2);

}

void MainWindow::on_j2cong_clicked()
{
    Robot.dichuyenkhop(3);

}

void MainWindow::on_j2tru_clicked()
{
    Robot.dichuyenkhop(4);

}

void MainWindow::on_j3cong_clicked()
{
    Robot.dichuyenkhop(5);

}

void MainWindow::on_j3tru_clicked()
{
    Robot.dichuyenkhop(6);

}

void MainWindow::on_daugap_clicked()
{
    Robot.dichuyenkhop(7);

}

void MainWindow::on_Them_diem_clicked()
{
   Robot.Them_diem(Robot.ThongTin_khop());
    ui->Tong_diem->setText(QByteArray::number(Robot.Toa_do.size()));
}

void MainWindow::on_Bat_dau_clicked()
{
    if(!Trangthai_batdau)
    {  
       Robot.Bat_dau_auto();
        ui->Bat_dau->setText("Dừng lại");
    }
    else
    {
        Robot.Ketthuc_auto();
         ui->Bat_dau->setText("Bắt Đầu");
    }
    Trangthai_batdau=!Trangthai_batdau;
}

void MainWindow::on_Xoa_diem_clicked()
{
   Robot.Xoa_diemAuto();

    ui->Tong_diem->setText(QByteArray::number(Robot.Toa_do.size()));

}

void MainWindow::on_Home_clicked()
{
    Robot.timer_vitri_Home->start(20);
}

void MainWindow::on_j1cong_pressed()
{

     start_j1cong();
}

void MainWindow::on_j1cong_released()
{
    stop_j1cong();
}

void MainWindow::on_j1tru_pressed()
{

    start_j1tru();
}


void MainWindow::on_j1tru_released()
{
    stop_j1tru();
}

void MainWindow::on_j2cong_pressed()
{
   start_j2cong();
}

void MainWindow::on_j2cong_released()
{
  stop_j2cong();
}

void MainWindow::on_j2tru_pressed()
{
   start_j2tru();
}

void MainWindow::on_j2tru_released()
{
    stop_j2tru();
}

void MainWindow::on_j3cong_pressed()
{
    start_j3cong();
}

void MainWindow::on_j3cong_released()
{
    stop_j3cong();
}

void MainWindow::on_j3tru_pressed()
{
    start_j3tru();
}

void MainWindow::on_j3tru_released()
{
    stop_j3tru();
}

void MainWindow::Hienthi_xyz()
{
    ui->x->setText(QString::number(Robot.x));
    ui->y->setText(QString::number(Robot.y));
    ui->z->setText(QString::number(Robot.z));
}


