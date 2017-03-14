#ifndef RTDACDIALOG_H
#define RTDACDIALOG_H

#include <QDialog>
#include "rtdacinterface.h"
#define CURRENT_CHANNEL 2
#define DISPLACEMENT_CHANNEL 4
#define PWM_CHANNEL 0 // to check
namespace Ui {
class RTDACDialog;
}

class RTDACDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RTDACDialog( QWidget *parent = 0 );
    ~RTDACDialog( );

private:
    Ui::RTDACDialog *ui;
    RTDACInterface *rtdac;
    bool connected;
    double current_value;
    double displacement_value;
    uint pwm_value;
    bool brake;


private slots:
    void connect2RTDAC( );
    void measureCurrent( );
    void measureDisplacement( );
    void dacSliderChanged( int val );
    void PWMSet( );
    void Brake( );

};

#endif // RTDACDIALOG_H
