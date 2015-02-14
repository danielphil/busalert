#include "AvailableStopsDialog.h"
#include "ui_AvailableStopsDialog.h"
#include "busalert/EditStopDialog.h"
#include "busalert/ApiKey.h"
#include "buslib/DataDownloader.h"

AvailableStopsDialog::AvailableStopsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AvailableStopsDialog)
{
    ui->setupUi(this);
}

AvailableStopsDialog::~AvailableStopsDialog()
{
    delete ui;
}

void AvailableStopsDialog::on_addButton_clicked()
{
    Buslib::DataDownloader downloader(ApiKey::MyBusTrackerKey);
    EditStopDialog dialog(&downloader, this);
    dialog.setWindowFlags(Qt::Sheet);
    dialog.exec();
}
