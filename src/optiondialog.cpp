#include "optiondialog.h"
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QDebug>


OptionDialog::OptionDialog(QWidget *parent)
    :QDialog(parent),
      _select_value(1),
      _temport_value(1)
{
    setWindowTitle(QString("选择数字"));
    setup();
}

void OptionDialog::setup()
{
    resize(100, 100);

    QGridLayout * glayout = new QGridLayout;

    for (int i = 0; i < 9; ++i){
        QPushButton * button = new QPushButton(QString::number(i + 1));
        _buttons.append(button);
        connect(button, SIGNAL(clicked()), this, SLOT(chooseValue()));
        glayout->addWidget(button, i / 3, i % 3);
    }

    setLayout(glayout);
}

void OptionDialog::accept()
{
     _select_value = _temport_value;
     return QDialog::accept();
}

qint8 OptionDialog::selectValue() const
{
    return _select_value;
}

void OptionDialog::chooseValue()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (!button) {
        _select_value = 0;
        return;
    }
    _select_value = button->text().toInt();
    QDialog::accept();
}
