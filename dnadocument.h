#ifndef DNADOCUMENT_H
#define DNADOCUMENT_H

#include <QWidget>

#include "signalmultiplexer.h"

namespace Ui {
class DNADocument;
}

class DNADocument : public QWidget, public DocumentObject
{
    Q_OBJECT
    
public:
    explicit DNADocument(QString file, QWidget *parent = 0);
    ~DNADocument();

    inline const QString& file() { return this->_file; }
    void setFile(const QString& name) { this->_file = name; }

    QString rawText();


    void emitAllSignals();

protected:
    void loadFile(const QString &file);

signals:

    void documentChanged(bool b);
    
public slots:
    void on_plainTextEdit_textChanged();

    void onSaved();

private:
    Ui::DNADocument *ui;

    QString _file;
};

#endif // DNADOCUMENT_H
