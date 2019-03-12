#include "Checkerboard.h"
#include"function.h"
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.showMaximized();

    return a.exec();
}
