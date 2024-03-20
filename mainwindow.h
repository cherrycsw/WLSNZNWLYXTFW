#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVector>
#include<exewidget.h>
#include<QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<ExeWidget *> exeVector;//存储ExeWidget对象
    QMap<int,QString> map;//存储路径索引对应的系统名称

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
