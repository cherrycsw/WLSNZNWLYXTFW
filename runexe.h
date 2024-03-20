#ifndef RUNEXE_H
#define RUNEXE_H

#include <QObject>
#include<QProcess>

class RunExe : public QObject
{
    Q_OBJECT
public:
    explicit RunExe(QObject *parent = nullptr);

    void worker(QString path);//运行程序的槽函数

    //void processFinished(int exitCode, QProcess::ExitStatus exitStatus);


signals:
    void processClosed(QString path);

};

#endif // RUNEXE_H
