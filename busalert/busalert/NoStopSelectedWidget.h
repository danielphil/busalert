#ifndef NOSTOPSELECTEDWIDGET_H
#define NOSTOPSELECTEDWIDGET_H

#include <QWidget>

namespace Ui {
class NoStopSelectedWidget;
}

class NoStopSelectedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit NoStopSelectedWidget(QWidget *parent = 0);
    ~NoStopSelectedWidget();

private:
    Ui::NoStopSelectedWidget *ui;
};

#endif // NOSTOPSELECTEDWIDGET_H
