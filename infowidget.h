#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include<QMap>
#include<QString>

namespace Ui {
class InfoWidget;
}

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QString name);
    ~InfoWidget();

    QString name;

    QMap<QString,QString> map;//存储每个系统对应的信息

private:
    Ui::InfoWidget *ui;
};

#endif // INFOWIDGET_H
