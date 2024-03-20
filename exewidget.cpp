#include "exewidget.h"
#include "ui_exewidget.h"
#include<QGraphicsDropShadowEffect>
#include<mypushbutton2.h>
#include<QFileInfo>
#include<QFileIconProvider>
#include<QPixmap>
#include<QDateTime>
#include<QDebug>
#include<QPoint>
#include<QMouseEvent>
#include<QPropertyAnimation>
#include<QMenu>
#include<QIcon>
#include<infowidget.h>


ExeWidget::ExeWidget(int x,int y,QString name,QString path,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExeWidget)
{
    ui->setupUi(this);
    //setStyleSheet("widget{background-color:transparent}");//设置Widget背景为透明
    this->PosX=x;
    this->PosY=y;
    this->exeName=name;
    this->exePath=path;

    ui->nameLabel->adjustSize();
    ui->dateLabel->adjustSize();
    ui->statusLabel->adjustSize();//自动调整大小

    //创建阴影
    QGraphicsDropShadowEffect *effect=new QGraphicsDropShadowEffect(this);
    effect->setOffset(3);//设置偏移
    effect->setBlurRadius(20);//设置模糊
    effect->setColor(QColor("#444440"));
    //ui->frame->setStyleSheet("frame{background-color:rgb(25,255,255)}");//设置frame背景为白色
    ui->frame->setGraphicsEffect(effect);

    //创建三点按钮
    MyPushButton2 *btn=new MyPushButton2(this);
    btn->move(this->width()-btn->width()-5,10);

    //新建Menu
    QMenu *cmenu = new QMenu(this);
    cmenu->setStyleSheet("QMenu{background-color:rgb(240,240,240);border-radius:5px;padding:5px;margin:6px;}QMenu::item:text{padding-left:10px;padding-right:10px;}QMenu::item:selected{color:rgb(106,90,205);background-color:rgb(240,240,240);border-radius:3px;}");
    //新建两个右键菜单,分别为Menu1,Menu2
    QAction *action1 = cmenu->addAction("运行");
    action1->setIcon(QIcon(":/img/run.png"));
    cmenu->addSeparator();//添加分隔符
    QAction *action2 = cmenu->addAction("详情");
    action2->setIcon(QIcon(":/img/info.png"));
    //连接这三个菜单项触发动作和对应的槽函数
    connect(action1, &QAction::triggered, this, [=](){
        emit startExe(this->exePath); //发出开始运行信号
        emit changeStatus(1);
    });


    //创建InfoWidget对象
    infoWidget=new InfoWidget(this->exeName);
    connect(action2, &QAction::triggered, this, [=](){
        //emit startInfo(); //发出显示详情信号
        infoWidget->show();//显示InfoWidget对象
    });

    //监听三点按钮点击信号
    connect(btn,&QPushButton::clicked,[=](){
        btn->zomm("down");
        btn->zomm("up");
        cmenu->exec(QCursor::pos());//呼出菜单
    });

    //图标文字设置
    //设置exeWidget程序名
    ui->nameLabel->setText(exeName);
    QFileInfo info(this->exePath);//获取该exe程序的信息
    //设置exeWidget程序图标
    QFileIconProvider iconProvider;
    QIcon icon=iconProvider.icon(info);//获取当前exe程序的图标
    QPixmap pix=icon.pixmap(QSize(32,32));
    ui->iconLabel->setPixmap(pix);
    //设置exeWidget程序上次访问时间
    QString dateInfo="系统上次访问时间："+info.lastRead().toString("yyyy/MM/dd hh:mm:ss");
    ui->dateLabel->setText(dateInfo);
    //设置exeWidget程序运行状态
    //QString sizeInfo="程序大小："+QString::number(info.size()/1000000)+"MB";
    QString statusInfo="系统运行状态：未启动";
    ui->statusLabel->setText(statusInfo);

    //创建状态图标
    statusLabel=new QLabel(this);
    QPixmap statusPix;
    statusPix.load(":/img/statusFalse.png");
    statusLabel->setPixmap(statusPix);
    statusLabel->setScaledContents(true);
    statusLabel->resize(15,15);
    statusLabel->move(335,97);


}


ExeWidget::~ExeWidget()
{
    delete ui;
    delete statusLabel;
    if(infoWidget!=NULL){
        delete infoWidget;
        infoWidget=NULL;
    }

}

//向上下跳跃函数实现
void ExeWidget::zomm(QString direction)
{
    //创建动画对象
    QPropertyAnimation *animation1=new QPropertyAnimation(this,"geometry");

    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //向下跳
    if(direction=="down"){
        //创建起始位置
        animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

        //创建结束位置
        animation1->setEndValue(QRect(this->x(),this->y()+3,this->width(),this->height()));
    }else if(direction=="up"){//向下跳
        //创建起始位置
        animation1->setStartValue(QRect(this->x(),this->y()+3,this->width(),this->height()));

        //创建结束位置
        animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    }else{
        qDebug()<<"输入的弹跳方式有误！";
        return;
    }

    //设置缓和曲线 QEasingCurve::OutBounce为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();
}

void ExeWidget::updateStatus(int status)
{
    if(status==1){
        ui->statusLabel->setText("系统运行状态：运行中...");
        //创建新状态图标
        statusLabel->setPixmap(QPixmap(":/img/statusTrue.png"));
    }else{
        ui->statusLabel->setText("系统运行状态：已关闭");
        statusLabel->setPixmap(QPixmap(":/img/statusFalse.png"));
    }
}

//鼠标移动至窗口事件
void ExeWidget::enterEvent(QEvent *event)
{
    qDebug()<<"触发鼠标进入事件";
    ui->frame->setStyleSheet("QFrame{background-color:rgb(230,230,230);border-radius:10px;}");//设置frame背景设置为灰色
    return QWidget::enterEvent(event);
}

void ExeWidget::leaveEvent(QEvent *event)
{
    qDebug()<<"触发鼠标离开事件";
    ui->frame->setStyleSheet("QFrame{background-color:white;border-radius:10px;}");//设置frame背景设置为白色
    return QWidget::leaveEvent(event);
}

void ExeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug()<<"触发鼠标双击事件";
    zomm("down");
    zomm("up");
    emit startExe(this->exePath);//发送运行程序的信号
    emit changeStatus(1);
    return QWidget::mouseDoubleClickEvent(event);
}



