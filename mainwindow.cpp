#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QProcess>
#include<QDebug>
#include<searchwidget.h>
#include<QWidgetAction>
#include<exewidget.h>
#include<mypushbutton2.h>
#include<QThread>
#include<runexe.h>
#include<QLabel>
#include<infowidget.h>
#include<QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(1100,500);

    //设置菜单栏样式
    this->setStyleSheet("QMenu{background-color:rgb(240,240,240);border-radius:5px;padding:5px;margin:6px;}"
                        "QMenu::item:text{padding-left:10px;padding-right:10px;}"
                        "QMenu::item:selected{color:rgb(106,90,205);background-color:rgb(240,240,240);border-radius:3px;}"
                        "QMenuBar{background-color:rgb(0,100,200);color:white;}"
                        "QMenuBar::item:selected{color:black;background-color:rgb(0,100,200)}"
                        "QMenuBar::item{padding-top:30px;padding-bottom:30px;padding-left:10px;}");
    setWindowTitle("物流枢纽智能物联云协同服务平台");
    setWindowIcon(QIcon(":/img/manager.png"));

    //创建SearchWidget对象
    //SearchWidget *search=new SearchWidget(this);
    //search->move(620,ui->menubar->height()*0.5-search->height()*0.5);

    //设置title
    QLabel *title=new QLabel("物流枢纽智能物联云协同服务平台",this);
    title->setStyleSheet("QLabel{color:white;font-family:'楷体';font-size:30px;}");
    title->setAlignment(Qt::AlignCenter);//居中
    title->adjustSize();//label动态调整为文本大小
    title->move(ui->menubar->width()*0.5-title->width()*0.5,ui->menubar->height()*0.5-title->height()*0.5);

    connect(ui->actionquit,&QAction::triggered,this,&MainWindow::close);//菜单栏点击退出

    //初始化map
    map.insert(1,"跨境电商大数据分析系统");
    map.insert(2,"跨境货物通关轨迹追溯查询系统");
    map.insert(3,"区港联动业务协同服务平台");
    map.insert(4,"数字口岸综合服务平台");
    map.insert(5,"通关大数据分析平台");
    map.insert(6,"物流枢纽智能物联协同服务平台");

    //创建运行程序的线程
    QThread *thread=new QThread();
    RunExe *work=new RunExe();
    work->moveToThread(thread);
    thread->start();
    //创建ExeWidget对象
    for(int i=0;i<map.size();i++){
        //qDebug()<<map.size();
        QString path=QApplication::applicationDirPath();//获取主exe路径
        QString str="/res/%1/app.exe";
        path+=str.arg(i+1);
        qDebug()<<i%3<<i/3<<map[i+1]<<path;
        ExeWidget *exe=new ExeWidget(i%3,i/3,map[i+1],path,this);
        exe->move(2+exe->width()*(i%3),120+exe->height()*(i/3));
        exeVector.push_back(exe);
        //监听程序启动信号
        connect(exe,&ExeWidget::startExe,work,&RunExe::worker);
        connect(exe,&ExeWidget::changeStatus,exe,&ExeWidget::updateStatus);
    }

    //监听运行程序的工作线程发回的关闭程序信号
    connect(work,&RunExe::processClosed,this,[=](QString path){
        for(int i=0;i<exeVector.size();i++){
            if(exeVector[i]->exePath==path){
                exeVector[i]->updateStatus(0);
            }
        }
    });

    connect(this,&MainWindow::destroyed,this,[=](){
        //资源释放
        thread->quit();
        thread->wait();
        work->deleteLater();
        thread->deleteLater();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
