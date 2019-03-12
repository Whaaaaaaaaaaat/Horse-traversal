#include "Checkerboard.h"
#include "ui_Checkerboard.h"
#include<function.h>
#include <QPainter>
#include<QString>
#include<QPen>
#include<QColor>
#include<QPixmap>
#include<vector>
#include<iostream>
using namespace std;
//计算棋盘数据
int WindowWidth;
int WindowHeight;
int h=HEIGHT,w=WIDTH;
int interval=10;
int square;
int LX,UY;
int RX,DY;
int ckbX,ckbY;
int step;
vector<int> indata;
bool beginDraw=false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//画马
void drawHorse(QPainter *painter)
{
    QPixmap pix;
    pix.load(":/images/紅馬.png");
 //   pix.load("C:/Users/雨/Desktop/中国象棋棋子/紅馬.png");
    double W=pix.width();
    double H=pix.height();
    double WHpro=W/H;
    painter->drawPixmap(LX+square*(ckbX-0.6),UY+square*(ckbY-0.6),WHpro*square,square,pix);
    //删除被吃掉的棋子
    int ox,oy,v;
    for(int i=3;i<indata.size();)
    {
        ox=indata[i++];
        oy=indata[i++];
        v=indata[i++];
        if(v==-1&&ox==ckbX&&oy==ckbY)
        {
            indata.erase(indata.begin()+(--i));
            indata.erase(indata.begin()+(--i));
            indata.erase(indata.begin()+(--i));
        }
    }
}
void drawSoldier(QPainter *painter,int x,int y,int v)
{
    QPixmap pix[2];
    pix[0].load(":/images/紅兵.png");
    pix[1].load(":/images/黑卒.png");
    double W=pix[v].width();
    double H=pix[v].height();
    double WHpro=W/H;
    painter->drawPixmap(LX+square*(x-0.6),UY+square*(y-0.6),WHpro*square,square,pix[v]);
}
//画标记
void drawPathOrder(QPainter *painter,int orderX,int orderY,int order,bool isBrush)
{
    //画实心圆
    if(isBrush)
        painter->setBrush(QColor(170,170,127));
    else
        painter->setBrush(QColor(255,255,255));
    painter->drawEllipse(LX+square*(orderX-0.25),UY+square*(orderY-0.25),square/2,square/2);
    //画字
    QPointF point;
    if(order<10)
         point.setX(LX+(orderX-0.10)*square);
    else
          point.setX(LX+(orderX-0.10*2)*square);
    point.setY(UY+(orderY+0.142)*square);
    painter->setFont(QFont("Arial", square/4));
    painter->setPen(QColor(255,0,0));
    painter->drawText(point, QString::number(order));
}
void drawChainCk(QPainter *painter)
{

}
void MainWindow::paintEvent(QPaintEvent *)
{
    LX=400;
    UY=50;
    WindowWidth=this->width();
    WindowHeight=this->height();
    square=(WindowHeight-2*UY-2*interval)/(h-1);
    if(LX+(w-1)*square+2*interval>WindowWidth-LX)
        square=(WindowWidth-2*LX-2*interval)/(w-1);
    RX=LX+(w-1)*square+2*interval;
    DY=UY+(h-1)*square+2*interval;
    //QPainter对象
    QPainter painter(this);
    QPen pen;
    //画棋盘外围方框
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawLine(QPointF(LX, UY), QPointF(RX, UY));
    painter.drawLine(QPointF(LX, DY), QPointF(RX,DY));
    painter.drawLine(QPointF(LX,UY), QPointF(LX,DY));
    painter.drawLine(QPointF(RX, UY), QPointF(RX,DY));
    //画棋盘
    LX+=10;
    RX-=10;
    UY+=10;
    DY-=10;
    pen.setWidth(1);
    painter.setPen(pen);
    for(int i=0;i<h;i++)
    {
        //画横线
         painter.drawLine(QPointF(LX, UY+i*square), QPointF(RX, UY+i*square));
    }
    //画中国象棋棋盘
    if(h==10&&w==9)
    {
        //画楚河汉界
      QPointF point(LX+square*1.4, UY+square*4.7);
      painter.setFont(QFont("Arial", 30));
      painter.drawText(point, "楚河                汉界");
        for(int i=0;i<w;i++)
        {
            if(i==0||i==w-1)
            {
                painter.drawLine(QPointF(LX+i*square,UY),QPointF(LX+i*square,DY));
            }
            else
            {
                painter.drawLine(QPointF(LX+i*square,UY),QPointF(LX+i*square,UY+(h-2)/2*square));
                painter.drawLine(QPointF(LX+i*square,UY+h/2*square),QPointF(LX+i*square,DY));

            }
            //画斜线
            if(i==3)
            {
               painter.drawLine(QPointF(LX+i*square,UY),QPointF(LX+(i+2)*square,UY+2*square));
               painter.drawLine(QPointF(LX+i*square,UY+2*square),QPointF(LX+(i+2)*square,UY));
               painter.drawLine(QPointF(LX+i*square,UY+(h-1)*square),QPointF(LX+(i+2)*square,UY+(h-3)*square));
               painter.drawLine(QPointF(LX+i*square,UY+(h-3)*square),QPointF(LX+(i+2)*square,UY+(h-1)*square));
            }
        }
    }
    //画普通棋盘
    else
    {
        for(int i=0;i<w;i++)
             painter.drawLine(QPointF(LX+i*square,UY),QPointF(LX+i*square,DY));
    }
    if(beginDraw)
    {
        //画棋盘中原有的棋子
        int ox,oy,v;
        for(int i=3;i<indata.size();)
        {
            ox=indata[i++];
            oy=indata[i++];
            v=indata[i++];
            drawSoldier(&painter,ox,oy,v+2);
        }
        //画标记
       for(int i=0;i<step;i+=2)
        {
            drawPathOrder(&painter,path[i],path[i+1],i/2+1,true);
        }
        if(step+1<path.size())
            drawPathOrder(&painter,path[step],path[step+1],step/2+1,false);
        //画马
        drawHorse(&painter);
    }
    painter.end();
}
void getData(QString strd)
{
    QString temp;
    for(int i=0;i<strd.length();i++)
    {
        if(strd.mid(i,1)==" "||strd.mid(i,1)=="\n")
        {
            if(temp.length()!=0)
            {
                indata.push_back(temp.toInt());
                temp.clear();
            }
        }
        else
        {
            temp+=strd.mid(i,1);
        }
    }
    if(temp.length()!=0)
    {
        indata.push_back(temp.toInt());
        temp.clear();
    }
}
void dealData()
{
    int n,ox,oy,v;
    n=indata[2];
    for(int i=3;i<indata.size();)
    {
        ox=indata[i++];
        oy=indata[i++];
        v=indata[i++];
        visited[oy][ox]=v;
        if(v==-2)
            stop--;
    }
}
void MainWindow::on_pushButton_clicked()
{

}
void MainWindow::on_OK_clicked()
{
    initialize();
    beginDraw=false;
    indata.clear();
    step=0;
    update();
    QString strd=ui->input->toPlainText();
    getData(strd);
    dealData();
    int beginx,beginy;
    beginx=indata[0];
    beginy=indata[1];
    if(beginx<0||beginx>=WIDTH||beginy<0||beginy>=HEIGHT)
        ui->output->setText("输入格式不正确\n请重写输入。");
    else
    {
         t1=clock();
         if(jump(beginx,beginy,1))
         {
             ui->output->setText(getSPath());
         }
         else
         {
             ui->output->setText("3到4秒内没有找到符合条件的路径");
         }
    }
}

void MainWindow::on_custom_clicked()
{
    if(step>=2*stop)
        return;
    beginDraw=true;
    ckbX=path[step];
    ckbY=path[step+1];
    update();
    step+=2;
}

void MainWindow::on_setHW_clicked()
{
    HEIGHT=ui->inH->value();
    WIDTH=ui->inW->value();
    h=HEIGHT;
    w=WIDTH;
    beginDraw=false;
    step=0;
    ui->output->setText("");
    update();

}
