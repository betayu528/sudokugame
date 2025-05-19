/**
* Author: by cdhmuer333@126.com
*/

#include "itemwidget.h"
#include "optiondialog.h"
#include <QLineEdit>
#include <QRegularExpression>
#include <QDebug>
#include <QRegularExpressionValidator>
#include <QLineEdit>

ItemWidget::ItemWidget(qint8 number)
    :_is_editable(true)
{
    setMaximumSize(40, 40);
    setAlignment(Qt::AlignCenter); // 居中
    setStyleSheet(
                    "QLineEdit {"
                    "   border: 1px solid;"
                    "   font-size: 40px;"
                    "}"
                    "QLineEdit:focus {"
                    "   background-color: lightblue;"
                    "}"
                 );

    setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]?"), this));

    setValue(number, false);

    QFont font = this->font();
    font.setBold(true);
    setFont(font);
    adjustSize();
}

ItemWidget::~ItemWidget()
{
    qDebug() << this->objectName() << " Object destructed !";
}


/**
 * @brief ItemWidget::setValue
 * 接受0~9范围的数字，其余数字一律当做0来处理
 * @param number
 * @param reset 是否游戏重置； false：游戏初始化；true：游戏重置
 */
void ItemWidget::setValue(qint8 number, bool reset)
{
     if (number == 0) {
         setText("");
         setEditable(true);
     } else {
         setText(QString::number(number));
         if (!reset)
            setEditable(false);
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
