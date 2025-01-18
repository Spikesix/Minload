#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "convertwindow.h"  // Συμπερίληψη της κλάσης ConvertWindow
#include <QTabWidget>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;  // Προσθήκη αυτής της γραμμής

private slots:
    void openDialog();

private:
    void initializeArchiveFolder();  // Προσθήκη δήλωσης της συνάρτησης
    QString archiveFolderPath;       // Μεταβλητή για την αποθήκευση της διαδρομής
    QString selectedFolder;          // Μεταβλητή για την επιλεγμένη διαδρομή
    };

#endif // MAINWINDOW_H
