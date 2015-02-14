#ifndef AVAILABLESTOPSDIALOG_H
#define AVAILABLESTOPSDIALOG_H

#include <QDialog>

namespace Ui {
class AvailableStopsDialog;
}

class AvailableStopsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AvailableStopsDialog(QWidget *parent = 0);
    ~AvailableStopsDialog();

private slots:
    void on_addButton_clicked();

private:
    Ui::AvailableStopsDialog *ui;
};

#endif // AVAILABLESTOPSDIALOG_H
