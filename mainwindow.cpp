#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setActiveTitle("");

    this->connect(this->ui->actionSave_As, SIGNAL(triggered()), SLOT(fileSaveAs()));
    this->connect(this->ui->action_Save, SIGNAL(triggered()), SLOT(fileSave()));

   // multiplexer.connect(this->ui->action_FindPrimers, SIGNAL(triggered()), SLOT(on_action_FindPrimers_triggered()));
    multiplexer.connect(SIGNAL(documentChanged(bool)), this, SLOT(onDocumentChanged(bool)));
    multiplexer.connect(SIGNAL(documentChanged(bool)), this->ui->action_Save, SLOT(setEnabled(bool)));
    //multiplexer.connect(this, SIGNAL(fileSaved(QString)), SLOT(onSaved(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFindProfile(uint lMin, uint lMax, long double tMin, long double tMax,
                               long double cMin, long double cMax, bool s, PrimerProfile *p)
{
    p->disconnect();
    p->deleteLater();

    DNADocument *d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());

    Primer pr(lMin, lMax, static_cast<unsigned int>(tMin), static_cast<unsigned int>(tMax), cMin / 100.0, cMax / 100.0, s);
    std::string p1 = "", p2 = "";
    uintmax_t n1 = 0, n2 = 0;

    std::string dna = d->rawText().toStdString();


    DNASearch search(pr, dna);
    if (!search.findPrimers(0, p1, n1, p2, n2))
    {
        QMessageBox::warning(this, tr("No primer found"),
                             tr("No primer sequence was located in the DNA sequence."), QMessageBox::Ok);
        return;
    }

    primerfound *pf = new primerfound(p1, n1, p2, n2); // lazy memleak fix like PrimerProfile
    pf->show();
}

void MainWindow::on_action_FindPrimers_triggered()
{
    DNADocument *d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());

    PrimerProfile *p = new PrimerProfile();
    this->connect(p, SIGNAL(findProfile(uint,uint,long double,long double,long double,long double,bool,PrimerProfile*)),
                  SLOT(onFindProfile(uint,uint,long double,long double,long double,long double,bool,PrimerProfile*)));

    std::cout << "too soon " << std::endl;
    p->show();
    //d->text();
    /*
        std::string dna = "ACTATCTATCCACTACTTTTTTTTTTACTACTATCATCACGACGGCAGCGAGAGCGGAATTTACGGAGCTTGCGCGCGCGCGCGCGCGATATATATATATATATATATATATATCGCGCGAGGCT";
        Primer p(17, 30, 55, 65, 0.5, 0.6, true);
        DNASearch s(p, dna);
        std::string p1 = "", p2 ="";
        uintmax_t n1 = 0, n2 = 0;
        s.findPrimers(0, p1, n1, p2, n2);

        std::cout << p1 << std::endl;

        std::cout << n1 << std::endl;

        std::cout << p2 << std::endl;

        std::cout << n2 << std::endl;
        */

}

void MainWindow::setActiveTitle(const QString &f, bool modified)
{

    QString title = "";

    if (this->ui->tabWidget->count() > 0)
    {
        title = (f == "") ? tr("untitled") : QFileInfo(f).fileName();

        if (modified)
            title += "*";

        this->ui->tabWidget->setTabText(this->ui->tabWidget->currentIndex(), title);

        title += " - ";
        this->setActiveActions(true);

    } else
    {
        this->setActiveActions(false);
    }

    title += QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion();
    this->setWindowTitle(title);
}

void MainWindow::addNewTab(const QString &f)
{
    QString title = (f == "") ? tr("untitled") : QFileInfo(f).fileName();

    this->ui->tabWidget->addTab(new DNADocument(f, this), "");
    this->ui->tabWidget->setCurrentIndex(this->ui->tabWidget->count()-1);

    this->setActiveTitle(f);
}

void MainWindow::on_action_New_triggered()
{
    this->addNewTab("");
}

void MainWindow::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                     "",
                                     tr("FASTA Files (*.fa *.fasta);;Text File (*.txt);;All Files (*.*)"));

    if (fileName.isNull())
        return;

    this->addNewTab(fileName);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    DNADocument* d = static_cast<DNADocument*>(this->ui->tabWidget->widget(index));

    if (d->isWindowModified())
        maybeSave();

    this->ui->tabWidget->removeTab(index);
    delete d;
}

void MainWindow::setActiveActions(bool b)
{
    this->ui->actionSave_As->setEnabled(b);
    this->ui->action_FindPrimers->setEnabled(b);
    this->ui->action_FindText->setEnabled(b);
    this->ui->action_Replace->setEnabled(b);
    this->ui->action_Copy->setEnabled(b);
    this->ui->actionCut->setEnabled(b);
    this->ui->action_Paste->setEnabled(b);
    this->ui->actionClose->setEnabled(b);
    this->ui->actionClose_All->setEnabled(b);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (index == -1) // no tabs open
    {
        this->setActiveTitle("");
        return;
    }

    DNADocument* d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());
    this->multiplexer.setCurrentObject(d);

    this->setActiveTitle(d->file(), d->isWindowModified());
}


void MainWindow::onDocumentChanged(bool b)
{
    DNADocument* d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());
    this->setActiveTitle(d->file(), b);
}

bool MainWindow::maybeSave()
{
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, QCoreApplication::applicationName(),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

bool MainWindow::fileSave()
{
    DNADocument* d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());
    if (d->file().isEmpty())
        return fileSaveAs();

    QFile file(d->file());
    bool success = file.open(QIODevice::WriteOnly);
    if (success)
    {
        // FIXME: here we always use UTF-8 encoding
        QString content = d->rawText();
        QByteArray data = content.toUtf8();
        qint64 c = file.write(data);
        success = (c >= data.length());

        d->onSaved();

        this->setActiveTitle(d->file());
    }

    return success;
}

bool MainWindow::fileSaveAs()
{
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
                 QString(), tr("FASTA Files (*.fa *.fasta);;Text File (*.txt);;All Files (*.*)"));

    if (fn.isEmpty())
        return false;

    DNADocument* d = static_cast<DNADocument*>(this->ui->tabWidget->currentWidget());
    d->setFile(fn);
    return fileSave();
}
