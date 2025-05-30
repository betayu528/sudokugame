﻿#ifndef ITEMWIDGET
#define ITEMWIDGET

#include <QLineEdit>
class ItemWidget : public QLineEdit
{
    Q_OBJECT
public:
    ItemWidget(qint8 number);
    ~ItemWidget();

    void setValue(qint8 number, bool reset = false);
    bool isEditable() const;
    void setEditable(bool editable);

protected:
    //void mousePressEvent(QMouseEvent *ev);

private slots:
    //void draw();

private:
    bool _is_editable;
};

#endif // ITEMWIDGET

