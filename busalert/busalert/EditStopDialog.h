#ifndef EDITSTOPDIALOG_H
#define EDITSTOPDIALOG_H

#include <QDialog>

namespace Buslib { class DataDownloader; }

namespace Ui {
class EditStopDialog;
}

class EditStopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditStopDialog(Buslib::DataDownloader* data_downloader, QWidget *parent = 0);
    ~EditStopDialog();

    QString GetStopId() const;
    QString GetStopName() const;

private:
    Ui::EditStopDialog *ui;
    Buslib::DataDownloader* m_data_downloader;

    void GetStopDetails();
    void OkClicked();
};

#endif // EDITSTOPDIALOG_H
