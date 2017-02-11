#include "mainwindow.h"
#include <QApplication>
#include "loghandler.h"
#include <QTextCodec>
#include <QFile>
#include <QDebug>
#include <QTextStream>

void messageHandler(QtMsgType type, const QMessageLogContext &context,
                         const QString &msg)
{
    Q_UNUSED(context)
    QByteArray localMsg = msg.toLocal8Bit();

       switch (type) {
       case QtDebugMsg:
           localMsg = "[DEBUG] " + localMsg;
           break;
       case QtInfoMsg:
           localMsg = "[INFO]" + localMsg;
           break;
       case QtWarningMsg:
           localMsg = "[WARN]" + localMsg;
           break;
       case QtCriticalMsg:
           localMsg = "[CRITCAL]" + localMsg;
           break;
       case QtFatalMsg:
           localMsg = "[FETAL]" + localMsg;
           abort();
       }
       //重定向消息输出到日志文件中
       QMetaObject::invokeMethod(LogHandler::instance(), "logMessage",
                                 Qt::QueuedConnection,
                                 Q_ARG(QByteArray, localMsg));
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFile file(":/skins/simpleqss.txt");
    QString stylesheetString;
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Open qss file failed!";
        qDebug() << file.errorString();
    } else {
        stylesheetString = file.readAll();
        app.setStyleSheet(stylesheetString); //设置应用皮肤
    }
    file.close();

    MainWindow w;
    w.show();

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    qInstallMessageHandler(messageHandler);

    return app.exec();
}
