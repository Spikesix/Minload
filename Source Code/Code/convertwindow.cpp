#include "convertwindow.h"

ConvertWindow::ConvertWindow(QWidget *parent) : QMainWindow(parent) {
    // Ορισμός τίτλου παραθύρου
    this->setWindowTitle("Convert Window");

    // Ορισμός μεγέθους παραθύρου
    this->resize(500, 150);

    // Δημιουργία ετικέτας με κείμενο
    label = new QLabel("This window is under construction in beta version!", this);
    label->setAlignment(Qt::AlignCenter);

    // Δημιουργία διάταξης και προσθήκη της ετικέτας
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);

    // Ορισμός του κεντρικού widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
}
