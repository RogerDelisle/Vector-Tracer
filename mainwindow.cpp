#include <QStringBuilder>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mrpDispW(ui->displayW), mrpCoordLbl(ui->labelCoords),
    mrpExtraInfo(ui->extraInfo)
{
    ui->setupUi(this);
    mrpDispW->SetOwner(this);
    mrpDispW->ConnectCoordLbl(mrpCoordLbl);
    mrpDispW->ConnectExtraInfo(mrpExtraInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

CoordLabel* MainWindow::GetCoordLbl()
{
    return mrpCoordLbl;
}

void MainWindow::UpdateCoords(int x, int y)
{
    mrpCoordLbl->setText(QString("X:%1 Y:%2").arg(x).arg(y));
}

void MainWindow::on_pushClear_clicked()
{
    mrpDispW->clear();
}

void MainWindow::on_pushUndo_clicked()
{
    mrpDispW->Undo();
}

void MainWindow::on_pushAnimate_clicked()
{
    mrpDispW->Animate();
}
