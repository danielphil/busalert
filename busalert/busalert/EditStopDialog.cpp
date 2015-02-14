#include "EditStopDialog.h"
#include "ui_EditStopDialog.h"
#include "buslib/DataDownloader.h"
#include "busalert/StopCodeValidator.h"
#include <QCompleter>
#include <QPushButton>
#include <QMessageBox>

EditStopDialog::EditStopDialog(
    Buslib::DataDownloader* data_downloader, QWidget *parent
) :
    QDialog(parent),
    ui(new Ui::EditStopDialog),
    m_data_downloader(data_downloader)
{
    ui->setupUi(this);
    const Buslib::BusStops stops = m_data_downloader->GetStopsData();
    StopCodeValidator* validator = new StopCodeValidator(
        stops, ui->stop_code_edit
    );
    ui->stop_code_edit->setValidator(validator);

    connect(ui->okButton, &QPushButton::clicked, this, &EditStopDialog::OkClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &EditStopDialog::reject);
    connect(ui->stop_code_edit, &QLineEdit::textChanged, this, &EditStopDialog::GetStopDetails);

    GetStopDetails();
}

EditStopDialog::~EditStopDialog()
{
    delete ui;
}

QString EditStopDialog::GetStopId() const {
    return ui->stop_code_edit->text();
}

QString EditStopDialog::GetStopName() const {
    return ui->stop_name_edit->text();
}

void EditStopDialog::GetStopDetails() {
    QString entered_stop_code = ui->stop_code_edit->text();
    Buslib::BusStops available_stops = m_data_downloader->GetStopsData();

    if (available_stops.IsValidStopId(entered_stop_code)) {
        const auto& stop = available_stops.GetStop(entered_stop_code);
        ui->stop_name_edit->setText(stop.Name());
        ui->stop_name_edit->setEnabled(true);
    } else {
        ui->stop_name_edit->setText("");
        ui->stop_name_edit->setEnabled(false);
    }
}

void EditStopDialog::OkClicked() {
    QString entered_stop_code = ui->stop_code_edit->text();
    Buslib::BusStops available_stops = m_data_downloader->GetStopsData();

    if (available_stops.IsValidStopId(entered_stop_code)) {
        done(Accepted);
    } else {
        QMessageBox alert(this);
        alert.setText("Please enter a valid stop code.");
        alert.setIcon(QMessageBox::Warning);
        alert.exec();
    }
}
