#ifndef PRIMERPROFILE_H
#define PRIMERPROFILE_H

#include <QWidget>

namespace Ui {
class PrimerProfile;
}

class PrimerProfile : public QWidget
{
    Q_OBJECT
    
public:
    explicit PrimerProfile(QWidget *parent = 0);
    ~PrimerProfile();


signals:
    void findProfile(unsigned int l, unsigned int, long double t, long double,
                       long double c, long double, bool s, PrimerProfile* p);
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::PrimerProfile *ui;
};

#endif // PRIMERPROFILE_H
