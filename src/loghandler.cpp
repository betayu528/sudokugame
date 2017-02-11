#include "loghandler.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <QMessageBox>


LogHandler LogHandler::_handler;

LogHandler::LogHandler()
{
}

LogHandler* LogHandler::instance()
{
    return &_handler;
}

void LogHandler::logMessage(const QByteArray& localMsg)
{
    QFile file("sudokulog.log");
    if (!file.open(QIODevice::Append)) {
       printf("Error ,cannot open file");
       return ;
    }

    QTextStream s(&file);
    s << localMsg << "\n";
    file.close();
    //QMessageBox::information(0, "helloloo", localMsg, QMessageBox::Ok); //Debug box
}

