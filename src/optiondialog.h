#ifndef OPTIONDIALOG
#define OPTIONDIALOG

#include <QDialog>

class QPushButton;
class OptionDialog: public QDialog
{
    Q_OBJECT
public:
    typedef QVector<QPushButton*> Buttons;
    OptionDialog(QWidget* parent = 0);

    void accept();

    qint8 selectValue() const;

private slots:
    void chooseValue();

private:
    void setup();

    int _select_value;
    int _temport_value;
    Buttons _buttons;
};

#endif // OPTIONDIALOG

