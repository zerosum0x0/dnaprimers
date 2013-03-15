#include "dnadocument.h"
#include "ui_dnadocument.h"

DNADocument::DNADocument(QString file, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DNADocument)
{

    ui->setupUi(this);

    this->setWindowTitle("[*]"); // placeholder

    loadFile(file);
}

DNADocument::~DNADocument()
{
    delete ui;
}

void DNADocument::loadFile(const QString &f)
{
    this->_file = f;
    if (f == "")
        return;

    if (!QFile::exists(f))
        return;

    QFile file(f);

    if (!file.open(QFile::ReadOnly))
        return;


    QByteArray data = file.readAll();


    this->ui->plainTextEdit->blockSignals(true);
    this->ui->plainTextEdit->setPlainText(data);
    this->ui->plainTextEdit->blockSignals(false);
}

void DNADocument::on_plainTextEdit_textChanged()
{
    if (!isWindowModified()) // so we dont do it 9000x when typing
    {
        this->setWindowModified(true);
        emit this->documentChanged(true);
    }
}

QString DNADocument::rawText()
{
    return this->ui->plainTextEdit->toPlainText();
}

void DNADocument::onSaved()
{
    this->setWindowModified(false);
}

void DNADocument::emitAllSignals()
{
    emit this->documentChanged(this->isWindowModified());
}
