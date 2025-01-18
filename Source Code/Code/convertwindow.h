#ifndef CONVERTWINDOW_H
#define CONVERTWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class ConvertWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ConvertWindow(QWidget *parent = nullptr);  // Κατασκευαστής

private:
    QLabel *label;  // Ετικέτα για να εμφανίζει κείμενο στο νέο παράθυρο
};

#endif // CONVERTWINDOW_H
