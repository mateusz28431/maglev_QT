#ifndef TERMINALDIALOG_H
#define TERMINALDIALOG_H

#include <QDialog>

namespace Ui {
class TerminalDialog;
}

class TerminalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TerminalDialog(QWidget *parent = 0);
    ~TerminalDialog();

private:
    Ui::TerminalDialog *ui;
private slots:
    void ShowData( QString );

};

#endif // TERMINALDIALOG_H
