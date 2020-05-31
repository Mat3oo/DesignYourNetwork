#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>

#include "IPstructs.h"

using namespace core;

namespace Ui {
class HostDialog;
}

class HostDialog : public QDialog
{
    Q_OBJECT

public:

    explicit HostDialog(QWidget *parent = nullptr);
    ~HostDialog();

    void InjectData(Subnet::Host);

    void SetData();

private slots:

    void on_hostName_textEdited(const QString &arg1);

private:

    Ui::HostDialog *ui;

    Subnet::Host host;
};

#endif // HOSTDIALOG_H
