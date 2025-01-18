#include <QApplication>
#include <QSplashScreen>  // Προσθήκη της κλάσης QSplashScreen
#include <QTimer>         // Προσθήκη της κλάσης QTimer
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    // Δημιουργία του Splash Screen
    QPixmap splashImage(":/MLopening.png");  // Φόρτωση της εικόνας από το .qrc
    QSplashScreen splash(splashImage);          // Δημιουργία του Splash Screen
    splash.show();                              // Εμφάνιση του Splash Screen

    // Προσομοίωση καθυστέρησης (π.χ. για φόρτωση δεδομένων)
    QTimer::singleShot(5000, &splash, &QSplashScreen::close);  // Κλείσιμο του Splash Screen μετά από 3 δευτερόλεπτα

    // Δημιουργία του κύριου παραθύρου
    MainWindow mainWindow;

    // Εμφάνιση του κύριου παραθύρου μετά το κλείσιμο του Splash Screen
    QTimer::singleShot(5000, &mainWindow, &QMainWindow::show);


    return app.exec();
}
