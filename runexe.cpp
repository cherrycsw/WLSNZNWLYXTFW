#include "runexe.h"
#include<QProcess>
#include<QDebug>
#include<QProcess>
#include<QDebug>

RunExe::RunExe(QObject *parent) : QObject(parent)
{

}

void RunExe::worker(QString path)
{

    if(path!=""){
        QProcess *process=new QProcess(this);
        //监听程序退出
        connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),[=](int exitCode, QProcess::ExitStatus exitStatus){
            emit processClosed(path);
        });
        process->start(path);

    }else{
        qDebug()<<"运行的程序路径为空！";
        return;
    }

}
