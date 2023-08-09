/**
* Author: by cdhmuer333@126.com
*/

#include "itemwidget.h"
#include "optiondialog.h"
#include <QDebug>


ItemWidget::ItemWidget(qint8 number)
    :_is_editable(true)
{
    setMaximumSize(40, 40);
    if (number > 9 || number < 0)
        number = 0;
    if (number == 0) {
        setEditable(true);
        setText("");
    } else {
        setText(QString::number(number));
        setEditable(false);
    }
    QFont font = this->font();
    font.setBold(true);
    setFont(font);
    adjustSize();
}

ItemWidget::~ItemWidget()
{
    qDebug() << this->objectName() << " Object destructed !";
}

void ItemWidget::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)

    if (!_is_editable) {
        return;
    }
    OptionDialog w(this);
    w.setModal(false);
    if (w.exec() == QDialog::Accepted) {
        qint8 value = w.selectValue();
        setValue(value);
    }
}


/**
 * @brief ItemWidget::setValue
 * 接受0~9范围的数字，其余数字一律当做0来处理
 * @param number
 * @param reset 是否游戏重置； false：游戏初始化；true：游戏重置
 */
void ItemWidget::setValue(qint8 number, bool reset)
{
    if (number > 9 || number < 0) {
        number = 0;
    }

    if (number == 0) {
        setText("");
        setEditable(true);
    } else {
        setText(QString::number(number));
        setEditable(!reset);
    }
}

void ItemWidget::setEditable(bool editable)
{
    this->_is_editable = editable;
    QPalette p = this->palette();
    if (editable) {
        setStyleSheet("color: blue");
    } else {
        setStyleSheet("color: rgb(253, 128, 53)");
    }

    setPalette(p);
}

bool ItemWidget::isEditable() const
{
    return _is_editable;
}
