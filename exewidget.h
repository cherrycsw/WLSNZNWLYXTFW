#ifndef EXEWIDGET_H
#define EXEWIDGET_H

#include <QWidget>
#include<QString>
#include<QIcon>
#include<QLabel>
#include<infowidget.h>

namespace Ui {
class ExeWidget;
}

class ExeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExeWidget(int x,int y,QString name,QString path,QWidget *parent = nullptr);
    //ExeWidget(int x,int y,QString name,QString path);
    ~ExeWidget();

    QLabel *statusLabel;
    InfoWidget *infoWidget;

    int PosX;//在主界面ExeWidget矩阵中的横坐标
    int PosY;//在主界面ExeWidget矩阵中的纵坐标

    QString exeName;//exe文件的名称
    QString exePath;//exe文件的的路径

    void zomm(QString direction);//上下跳越函数

    void updateStatus(int status);//更新状态槽函数

    virtual void enterEvent(QEvent *event);//鼠标进入窗口事件

    virtual void leaveEvent(QEvent *event);//鼠标离开窗口事件

    virtual void mouseDoubleClickEvent(QMouseEvent *event);//鼠标双击事件进入exe程序

signals:
    void startExe(QString path);
    void startInfo();
    void changeStatus(int status);

private:
    Ui::ExeWidget *ui;
};

#endif // EXEWIDGET_H
