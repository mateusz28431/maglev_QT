#ifndef PLOTSDIALOG_H
#define PLOTSDIALOG_H

#include <QDialog>
#include "measures.h"
namespace Ui {
class PlotsDialog;
}

class PlotsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotsDialog( QWidget *parent = 0 );
    ~PlotsDialog( );
    void InitializePlots( );
    void SetRange( int range );
    void ClearPlots( );

private:
    Ui::PlotsDialog *ui;

private slots:
    void AddData2Plots( double current, double displacement, ADC_measures a, int no_sample );
};

#endif // PLOTSDIALOG_H
