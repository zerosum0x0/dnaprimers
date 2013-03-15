#ifndef PRIMERFOUND_H
#define PRIMERFOUND_H

#include <QWidget>

namespace Ui {
class primerfound;
}

class primerfound : public QWidget
{
    Q_OBJECT
    
public:
    explicit primerfound(std::string p1, uint n1, std::string p2, uint n2, QWidget *parent = 0);
    ~primerfound();
    
private:
    Ui::primerfound *ui;
};

#endif // PRIMERFOUND_H
