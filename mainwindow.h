#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
//#include "dispwidget.h"
class dispWidget;
class CoordLabel;
struct ExtraInfoStruct;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    CoordLabel* GetCoordLbl();

private slots:

    void on_pushClear_clicked();

    void on_pushUndo_clicked();

    void on_pushAnimate_clicked();

private:
    Ui::MainWindow *ui;

    dispWidget*& mrpDispW;
    CoordLabel*& mrpCoordLbl;
    CoordLabel*& mrpExtraInfo;

protected:

public slots:
    void UpdateCoords(int x, int y);

};

#endif // MAINWINDOW_H
