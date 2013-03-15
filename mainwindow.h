#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <sstream>

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "primerprofile.h"
#include "primerfound.h"
#include "dnadocument.h"
#include "signalmultiplexer.h"
#include "dnasearch.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_action_Open_triggered();

    void on_action_FindPrimers_triggered();

    void on_action_New_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

signals:
    //void fileSaved(QString s);

public slots:
    void onFindProfile(uint,uint,long double,long double,long double,long double,bool,PrimerProfile*);
    void onDocumentChanged(bool b);
    bool maybeSave();
    bool fileSave();
    bool fileSaveAs();

    void addNewTab(const QString &f);
    void setActiveTitle(const QString &f, bool modified = false);
    void setActiveActions(bool b);

private:
    Ui::MainWindow *ui;
    SignalMultiplexer multiplexer;
};

#endif // MAINWINDOW_H
