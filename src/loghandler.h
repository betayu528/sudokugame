#ifndef LOGHANDLER
#define LOGHANDLER

#include <QObject>

class LogHandler : public QObject
{
    Q_OBJECT
public:
    static LogHandler* instance();
public slots:
    void logMessage(const QByteArray& msg);

private:
    LogHandler();

    static LogHandler _handler;
};

#endif // LOGHANDLER

