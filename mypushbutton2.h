#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton2 : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton2(QWidget *parent = nullptr);

    //点击开始按钮 向上下跳跃函数
    void zomm(QString direction);

    //重写鼠标按下和释放事件
    //virtual void mousePressEvent(QMouseEvent *e) override;
    //virtual void mouseReleaseEvent(QMouseEvent *e) override;

signals:

};

#endif // MYPUSHBUTTON_H
