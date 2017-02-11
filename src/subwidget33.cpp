#include "subwidget33.h"
#include "itemwidget.h"

#include <QLayout>
#include <QPainter>
#include <QEvent>

Data33::Data33(int array[9])
{
    init();
    if (!array) {
        for (int i = 0; i < 9; ++i)
            _data[i/3][i%3] = i + 1;
    } else {
        for (int i = 0; i < 9; ++i)
            _data[i/3][i%3] = array[i];
    }
}

Data33::Data33()
{
    init();
    for (int i = 0; i < 9; ++i)
        _data[i/3][i%3] = i + 1;
}

void Data33::init()
{
    _data = new int*[3];
    for (int i = 0; i < 3; ++i) {
        _data[i] = new int[3];
    }
}

Data33::~Data33()
{
    if (_data) {
        for (int i = 0; i < 3; ++i) {
            delete [] _data[i];
        }
        delete [] _data;
        _data = NULL;
    }
}

bool Data33::valid() const
{
    int bucket[9] = {0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j){
            bucket[_data[i][j]]++;
        }
    }
    for (int i = 0; i < 9; ++i) {
        if (bucket[i] == 0 || bucket[i] > 1)
            return false;
    }
    return true;
}


/**inplement of Widget33
 */
Widget33::Widget33(QWidget *parent)
    :QFrame(parent)
{
    _d_data = new Data33();
    setup();
}

Widget33::Widget33(Data33 *array)
{
    _d_data = array;
    setup();
}

Widget33::~Widget33()
{
//    if (_d_data) {
//        delete _d_data;
//        _d_data = NULL;
//    }
}

void Widget33::setup()
{
    resize(400, 400);
    setStyleSheet("background:rgb(0,0,0);border:10px");
    QGridLayout *layout = new QGridLayout;
    layout->setMargin(0);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(0);
    for (int i = 0; i < 9; ++i) {
        ItemWidget *w = new ItemWidget(i + 1);
        layout->addWidget(w, i / 3, i % 3, Qt::AlignCenter);
    }

    setLayout(layout);
}

void Widget33::paintEvent(QPaintEvent *e)
{
    //QEvent *event = static_cast<QEvent*>(e);
    QPainter painter(this);
    QColor color(240, 248, 255);
    painter.save();
    painter.setBackground(color);
    //painter.drawLine(0, this->width(), 90, 90);
    painter.restore();
}
