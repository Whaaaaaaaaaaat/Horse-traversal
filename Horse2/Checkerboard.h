#ifndef Checkerboard_H
#define Checkerboard_H
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
protected:
    void paintEvent(QPaintEvent *); //重绘事件处理函数的声明: 所有的绘制操作都要在这个函数里面完成。
private slots:
    void on_pushButton_clicked();
    void on_OK_clicked();
    void on_custom_clicked();
    void on_setHW_clicked();
};

#endif // MAINWINDOW_H
