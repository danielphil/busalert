#include "NoStopSelectedWidget.h"
#include "ui_NoStopSelectedWidget.h"

NoStopSelectedWidget::NoStopSelectedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoStopSelectedWidget)
{
    ui->setupUi(this);
}

NoStopSelectedWidget::~NoStopSelectedWidget()
{
    delete ui;
}
