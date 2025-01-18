#include "mainwindow.h"
#include "convertwindow.h"  // Συμπερίληψη της κλάσης ConvertWindow
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialog>
#include <QSlider>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QTextEdit>
#include <QProgressBar>
#include <QDebug>
#include <QSettings>
#include <QCoreApplication>
#include <QApplication>
#include <QEvent>
#include <QFontDatabase>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    QIcon appIcon(":/icon.ico");  // Φόρτωση του .ico αρχείου από το .qrc

    QPixmap pixmap = appIcon.pixmap(256, 256);  // Επιλέγει την εικόνα 64x64 pixels
    this->setWindowIcon(pixmap);


    // Ορισμός του μεγέθους του παραθύρου
    this->resize(650, 350);

    // Ορισμός τίτλου παραθύρου
    this->setWindowTitle("Minload");

    // Δημιουργία του QTabWidget
    QTabWidget *tabWidget = new QTabWidget(this);

    // Καρτέλα "Main"
    QWidget *mainTab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(mainTab);



    // Δημιουργία του QLabel με τις οδηγίες
    QLabel *instructionLabel = new QLabel("Do you want to Download or Convert?", mainTab);
    instructionLabel->setAlignment(Qt::AlignCenter);
    // Ορισμός του μεγέθους της γραμματοσειράς

    // Φόρτωση της γραμματοσειράς από τους πόρους
    int fontId = QFontDatabase::addApplicationFont(":/Montserrat-VariableFont_wght.ttf");
    if (fontId != -1) {
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            QFont Font(fontFamilies.at(0), 15, QFont::Bold); // Δημιουργία QFont
            instructionLabel->setFont(Font); // Ορισμός της γραμματοσειράς στο QLabel
        }
    }


    // Δημιουργία των κουμπιών
    QPushButton *button1 = new QPushButton("Download", mainTab);
    QPushButton *button2 = new QPushButton("Convert", mainTab);

    // Δημιουργία οριζόντιας διάταξης για τα κουμπιά
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(button1);
    buttonLayout->addWidget(button2);

    // Δημιουργία ενός container widget για τα κουμπιά
    QWidget *buttonContainer = new QWidget(mainTab);
    buttonContainer->setLayout(buttonLayout);

    // Δημιουργία ενός κεντρικού layout για να κεντράρουμε τα κουμπιά
    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addWidget(buttonContainer);  // Προσθήκη των κουμπιών




    // Δημιουργία κύριας διάταξης και προσθήκη των στοιχείων
    mainLayout->addStretch();  // Προσθήκη stretch για να μετακινήσει τα κουμπιά προς το κέντρο

    mainLayout->addWidget(instructionLabel);
    mainLayout->addStretch();  // Προσθήκη stretch για να μετακινήσει τα κουμπιά προς το κέντρο

    mainLayout->addLayout(centerLayout);  // Προσθήκη του κεντρικού layout
    mainLayout->addStretch();  // Προσθήκη stretch για να μετακινήσει τα κουμπιά προς το κέντρο


    // Σύνδεση του κουμπιού "Λήψη" με τη δημιουργία του νέου παραθύρου
    connect(button1, &QPushButton::clicked, this, &MainWindow::openDialog);

    // Σύνδεση του κουμπιού "Convert" με τη δημιουργία του ConvertWindow
    connect(button2, &QPushButton::clicked, this, [this]() {
        ConvertWindow *convertWindow = new ConvertWindow(this);  // Δημιουργία νέου παραθύρου
        convertWindow->show();  // Εμφάνιση του νέου παραθύρου
    });

    // Προσθήκη της καρτέλας "Main" στο QTabWidget
    tabWidget->addTab(mainTab, "Main");

    // Καρτέλα "Βοήθεια"
    QWidget *helpTab = new QWidget();
    QVBoxLayout *helpLayout = new QVBoxLayout(helpTab);

    QTextEdit *helpText = new QTextEdit(helpTab);
    helpText->setReadOnly(true);
    helpText->setPlainText(
        "This program is called Minload and is used in combination with YT-DLP and FFmpeg for downloading and converting audio and video files.\n"
        "Some feautures are under construction so they are not available in this version.\n"
        "You can choose from the slider the quality you want and if this feature is disabled then the quality is the best that the source can provide.\n"
        "Decide your file format, Select a folder, choose if you want an Archive, paste your URL and press ok.\n"
        "Archive is a .txt file that has all the Urls you have download so you dont download the same again.\n\n"
        "Thank you for your support. Hope you enjoy our work!\n"
        "Minload Studio 25.0.1 - beta."
        );

    helpLayout->addWidget(helpText);

    // Προσθήκη της καρτέλας "Βοήθεια" στο QTabWidget
    tabWidget->addTab(helpTab, "HELP");

    // Καρτέλα "Ρυθμίσεις"
    QWidget *settingsTab = new QWidget();
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsTab);

    QLabel *settingsLabel = new QLabel("This Tab is under construction in beta version.", settingsTab);
    settingsLabel->setAlignment(Qt::AlignCenter);

    settingsLayout->addWidget(settingsLabel);

    // Προσθήκη της καρτέλας "Ρυθμίσεις" στο QTabWidget
    tabWidget->addTab(settingsTab, "Settings");

    // Ορισμός του QTabWidget ως κεντρικού widget
    setCentralWidget(tabWidget);

    QString tabStyle =
        "QTabWidget::pane { "
        "   border: 1px solid #cccccc; "  // Απλό περίγραμμα γύρω από τα tabs
        "   background-color: #ffffff; "  // Λευκό φόντο για το περιεχόμενο
        "   margin-top: -1px; "           // Για να ευθυγραμμιστεί σωστά με τα tabs
        "}"
        "QTabBar::tab { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f5f5f5, stop:1 #e0e0e0); "  // Διαβαθμίση για τα tabs
        "   color: #333333; "             // Σκούρο γκρι κείμενο
        "   padding: 2px 12px; "          // Μικρότερο padding (2px πάνω-κάτω, 12px αριστερά-δεξιά)
        "   border: 1px solid #cccccc; "  // Απλό περίγραμμα γύρω από τα tabs
        "   border-bottom: none; "        // Χωρίς περίγραμμα στο κάτω μέρος
        "   font-size: 12px; "            // Μικρότερο μέγεθος γραμματοσειράς
        "   font-weight: 500; "           // Medium font weight
        "   margin-right: 2px; "          // Μικρότερη απόσταση μεταξύ των tabs (από 4px σε 2px)
        "   min-width: 100px; "           // Το πλάτος παραμένει το ίδιο
        "   min-height: 20px; "           // Ελάχιστο ύψος για πιο κοντά tabs
        "   border-top-left-radius: 4px; "  // Ελαφρώς στρογγυλεμένες γωνίες
        "   border-top-right-radius: 4px; "
        "}"
        "QTabBar::tab:selected { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffffff, stop:1 #f0f0f0); "  // Διαβαθμίση για επιλεγμένο tab
        "   color: #000000; "             // Μαύρο κείμενο για το επιλεγμένο tab
        "   border-bottom: 2px solid #333333; "  // Λευκή γραμμή κάτω από το επιλεγμένο tab
        "}"
        "QTabBar::tab:hover { "
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e0e0e0, stop:1 #d0d0d0); "  // Διαβαθμίση όταν το ποντίκι πλησιάζει
        "   color: #000000; "             // Μαύρο κείμενο όταν το ποντίκι πλησιάζει
        "}"
        "QTabBar::tab:!selected { "
        "   margin-top: 2px; "            // Μικρή απόσταση από τα μη επιλεγμένα tabs
        "}"
        "QTabBar { "
        "   background: transparent; "    // Διαφανές φόντο για την γραμμή των tabs
        "   border: none; "               // Χωρίς περίγραμμα
        "}";

    tabWidget->setStyleSheet(tabStyle);

    // Ορισμός των IDs (objectName)
    button1->setObjectName("button1");  // ID για το κουμπί "Λήψη"
    button2->setObjectName("button2");  // ID για το κουμπί "Μετατροπή"


    // Εφαρμογή στυλ για όλα τα κουμπιά (εκτός από τα παράθυρα μηνυμάτων)
    QString buttonStyle =
        "QMainWindow { background-color: #f0f0f0; }"
        "QPushButton { "
        "   color: white; "
        "   border: none; "
        "   padding: 15px 20px; "  // Βασικό padding
        "   font-size: 25px; "
        "   font-weight: bold; "
        "   border-radius: 10px; "
        "   background-color: #4CAF50; "  // Βασικό χρώμα για τα κουμπιά
        "}"
        "QPushButton:hover { "
        "   background-color: #43A047; "  // Πιο έντονο χρώμα όταν το ποντίκι πλησιάζει (hover)
        "   border: 2px solid #388E3C; "  // Πιο έντονο border στο hover
        "   padding: 8px 18px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        "QPushButton:pressed { "
        "   background-color: #388E3C; "  // Πιο έντονο χρώμα όταν το κουμπί πατιέται (pressed)
        "   border: 2px solid #2E7D32; "  // Πιο έντονο border στο pressed
        "   padding: 8px 18px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        "QPushButton#button1 { background-color: #4CAF50; }"  // Πράσινο για το κουμπί "Λήψη"
        "QPushButton#button2 { background-color: #2196F3; }"  // Μπλε για το κουμπί "Μετατροπή"
        "QPushButton#button1:hover { background-color: #43A047; border: 2px solid #388E3C; padding: 8px 18px; }"  // Hover για το κουμπί "Λήψη"
        "QPushButton#button2:hover { background-color: #1E88E5; border: 2px solid #1976D2; padding: 8px 18px; }"  // Hover για το κουμπί "Μετατροπή"
        "QPushButton#button1:pressed { background-color: #388E3C; border: 2px solid #2E7D32; padding: 8px 18px; }"  // Pressed για το κουμπί "Λήψη"
        "QPushButton#button2:pressed { background-color: #1976D2; border: 2px solid #1565C0; padding: 8px 18px; }";  // Pressed για το κουμπί "Μετατροπή"
    // Εφαρμογή του στυλ στο κύριο παράθυρο
    this->setStyleSheet(buttonStyle);

}



void MainWindow::openDialog() {
    // Δήλωση του downloadLabel ως τοπική μεταβλητή
    QLabel *downloadLabel = nullptr;
    QDialog *dialog = new QDialog(this);  // Ensure dialog is a child of MainWindow
    dialog->setWindowTitle("Download");
    dialog->resize(600, 600);

    // Set window flags for secondary window
    dialog->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    // Προσθήκη event filter για να ανιχνεύουμε αλλαγές στην κατάσταση του παραθύρου
    dialog->installEventFilter(this);

    // Δημιουργία του QTabWidget
    QTabWidget *tabWidget = new QTabWidget(dialog);

    // Καρτέλα "Ήχος"
    QWidget *audioTab = new QWidget();  // Δημιουργία της πρώτης καρτέλας
    QVBoxLayout *audioLayout = new QVBoxLayout(audioTab);  // Layout για την καρτέλα "Ήχος"

    // Δημιουργία του slider
    QSlider *slider = new QSlider(Qt::Horizontal, audioTab);
    slider->setRange(0, 9);  // Ορίζουμε το εύρος τιμών από 0 έως 9

    // Δημιουργία ενός QLabel που περιέχει την ετικέτα "Ποιότητα ήχου:" και τον αριθμό
    QLabel *qualityLabel = new QLabel("Sound quality: 0", audioTab);  // Αρχικοποίηση με τιμή 0
    qualityLabel->setStyleSheet("font-size: 14px; color: #333; font-weight: bold;");

    // Δημιουργία ενός QLabel για την σημείωση
    QLabel *noteLabel = new QLabel("(Best quality 0 - Worst quality 9)", audioTab);
    noteLabel->setStyleSheet("font-size: 10px; color: #555; font-style: italic;");

    // Σύνδεση του valueChanged signal του slider με την ενημέρωση του QLabel
    connect(slider, &QSlider::valueChanged, [qualityLabel](int value) {
        qualityLabel->setText("Sound quality: " + QString::number(value));  // Ενημέρωση του κειμένου
    });

    // Δημιουργία ενός QHBoxLayout για την ετικέτα και την σημείωση
    QHBoxLayout *qualityLayout = new QHBoxLayout();
    qualityLayout->addWidget(qualityLabel);  // Προσθήκη της ετικέτας "Ποιότητα ήχου: X"
    qualityLayout->addWidget(noteLabel);     // Προσθήκη της σημείωσης
    qualityLayout->setSpacing(300);            // Μικρή απόσταση μεταξύ των στοιχείων
    qualityLayout->setContentsMargins(0, 0, 0, 0);  // Χωρίς περιθώρια

    // Δημιουργία ενός QHBoxLayout για τους αριθμούς 0 έως 9
    QHBoxLayout *numbersLayout = new QHBoxLayout();
    numbersLayout->setSpacing(0);  // Χωρίς απόσταση μεταξύ των αριθμών
    numbersLayout->setContentsMargins(0, 0, 0, 0);  // Χωρίς περιθώρια

    for (int i = 0; i <= 9; ++i) {
        QLabel *numberLabel = new QLabel(QString::number(i), audioTab);
        numberLabel->setAlignment(Qt::AlignCenter);  // Κεντράρισμα των αριθμών
        numberLabel->setStyleSheet("font-size: 10px; color: #777;");  // Λίγο μεγαλύτερο και γκρι font
        numbersLayout->addWidget(numberLabel);
    }

    // Προσθήκη του slider και των αριθμών σε ένα κοινό layout
    QVBoxLayout *sliderLayout = new QVBoxLayout();
    sliderLayout->addLayout(qualityLayout);  // Προσθήκη της ετικέτας, του αριθμού και της σημείωσης
    sliderLayout->addWidget(slider);
    sliderLayout->addLayout(numbersLayout);
    sliderLayout->setSpacing(2);  // Πολύ μικρή απόσταση μεταξύ slider και labels
    sliderLayout->setContentsMargins(0, 0, 0, 0);  // Χωρίς περιθώρια

    // Δημιουργία του QComboBox για την επιλογή μορφής αρχείου
    QComboBox *comboBox = new QComboBox(audioTab);
    comboBox->addItems({"mp3", "wav", "flac", "m4a", "webm"});
    comboBox->setFixedWidth(170);  // Ορίζουμε σταθερό πλάτος για το QComboBox

    // Δημιουργία του QCheckBox για την ενεργοποίηση του αρχείου καταγραφής
    QCheckBox *logCheckBox = new QCheckBox("Use Archive File", audioTab);

    // Δημιουργία ενός QHBoxLayout για να τοποθετήσουμε το QLabel, το QComboBox και το QCheckBox
    QHBoxLayout *formatLogLayout = new QHBoxLayout();
    formatLogLayout->setContentsMargins(0, 0, 0, 0);  // Χωρίς περιθώρια γύρω από το layout

    // Προσθήκη της ετικέτας "Μορφή αρχείου:"
    QLabel *formatLabel = new QLabel("File Format:", audioTab);
    formatLogLayout->addWidget(formatLabel);


    // Προσθήκη του QComboBox
    formatLogLayout->addWidget(comboBox);

    // Προσθήκη ενός QSpacerItem για απόσταση 10px μεταξύ του QComboBox και του QCheckBox
    formatLogLayout->addSpacing(150);

    // Προσθήκη του QCheckBox
    formatLogLayout->addWidget(logCheckBox);
    formatLogLayout->addSpacing(20);


    QLineEdit *urlLineEdit = new QLineEdit(audioTab);
    QLabel *folderLabel = new QLabel("Selected Folder: ", audioTab);
    QPushButton *folderButton = new QPushButton("Select Folder", audioTab);
    QPushButton *okButton = new QPushButton("OK", audioTab);

    // Ορισμός των διαστάσεων των κουμπιών
    okButton->setFixedSize(600, 30);        // Επαναφορά στις αρχικές διαστάσεις
    folderButton->setFixedSize(150, 30);    // Πιο μικρό και συμπαγές κουμπί επιλογής φακέλου

    // QTextEdit για εμφάνιση της εντολής και της εξόδου
    QTextEdit *outputTextEdit = new QTextEdit(audioTab);
    outputTextEdit->setReadOnly(true);

    // QProgressBar για την εμφάνιση της προόδου
    QProgressBar *progressBar = new QProgressBar(audioTab);
    progressBar->setRange(0, 100);
    progressBar->setTextVisible(false);  // Εμφάνιση του ποσοστού πάνω στην μπάρα

    // Διαχείριση της επιλογής φακέλου
    connect(folderButton, &QPushButton::clicked, [&]() {
        selectedFolder = QFileDialog::getExistingDirectory(dialog, "Select Folder");
        if (!selectedFolder.isEmpty()) {
            folderLabel->setText("Selected Folder: " + selectedFolder);
            folderLabel->setStyleSheet("font-size: 12px; color: gray;");  // Εφαρμογή γκρι χρώματος και μικρότερου μεγέθους γραμματοσειράς
        } else {
            folderLabel->setText("Selected Folder: ");
            folderLabel->setStyleSheet("font-size: 14px; color: #333;");  // Επαναφορά στο αρχικό στυλ αν δεν έχει επιλεγεί φάκελος
        }
        qDebug() << "Επιλεγμένος φάκελος (μέσα στο κουμπί):" << selectedFolder;
    });

    // Διαχείριση της ενεργοποίησης/απενεργοποίησης του slider
    connect(comboBox, &QComboBox::currentTextChanged, [=](const QString &text) {
        if (text == "m4a" || text == "webm") {
            slider->setEnabled(false);  // Απενεργοποίηση του slider
            slider->setStyleSheet(
                "QSlider::groove:horizontal { background: #cdcdcd; height: 4px; border-radius: 2px; }"
                "QSlider::sub-page:horizontal { background: #cdcdcd; height: 4px; border-radius: 2px; }"
                "QSlider::handle:horizontal { background: #cdcdcd; width: 12px; height: 12px; margin: -4px 0; border-radius: 6px; border: 1px solid #999999; }"
                );
        } else {
            slider->setEnabled(true);  // Ενεργοποίηση του slider
            slider->setStyleSheet(
                "QSlider { border: none; }"
                "QSlider::groove:horizontal { background: #e0e0e0; height: 4px; border-radius: 2px; }"
                "QSlider::sub-page:horizontal { background: #415D70; height: 4px; border-radius: 2px; }"
                "QSlider::handle:horizontal { background: #1B4F72; width: 12px; height: 12px; margin: -4px 0; border-radius: 6px; border: 1px solid #ccc; }"
                "QSlider::handle:horizontal:hover { background: #5994B9; }"
                "QSlider::handle:horizontal:pressed { background: #5F89A6; }"
                );
        }
    });

    // Διαχείριση του κουμπιού OK
    connect(okButton, &QPushButton::clicked, [=]() {
        okButton->setEnabled(false);  // Απενεργοποίηση του κουμπιού μετά το πάτημα

        // Έλεγχος διαδρομών
        if (selectedFolder.isEmpty()) {
            QMessageBox::critical(dialog, "Error", "You have to choose a folder.");
            okButton->setEnabled(true);  // Επαναφορά της ενεργοποίησης αν υπάρξει σφάλμα
            return;
        }

        if (!QDir(selectedFolder).exists()) {
            QMessageBox::critical(dialog, "Error", "This Folder does not exist.");
            okButton->setEnabled(true);  // Επαναφορά της ενεργοποίησης αν υπάρξει σφάλμα
            return;
        }

        // Δημιουργία της εντολής
        QStringList commandParts;
        commandParts << "-f" << "bestaudio";  // Προσθήκη του -f bestaudio
        commandParts << "--extract-audio" << "--audio-format" << comboBox->currentText();

        if (slider->isEnabled()) {
            commandParts << "--audio-quality" << QString::number(slider->value());
        }

        if (logCheckBox->isChecked() && !selectedFolder.isEmpty()) {
            QString folderPath = QDir::toNativeSeparators(selectedFolder + "/archive.txt");
            commandParts << "--download-archive" << folderPath ;
        }

        if (!selectedFolder.isEmpty()) {
            QString folderPath = QDir::toNativeSeparators(selectedFolder);
            commandParts << "-o" << folderPath + "\\%(title)s.%(ext)s";
            qDebug() << "Επιλεγμένος φάκελος (στη δημιουργία της εντολής):" << folderPath;
        }

        if (!urlLineEdit->text().isEmpty()) {
            QString url = urlLineEdit->text();
            url.replace("\\", "/");
            commandParts << url;
        }

        // Αρχικοποίηση της μπάρας προόδου
        progressBar->setValue(0);

        // Δημιουργία του QLabel για την εμφάνιση του ποσοστού
        QLabel *progressLabel = new QLabel("0%", audioTab);
        progressLabel->setStyleSheet("font-size: 14px; color: #333; font-weight: bold;");

        // Προσθήκη της QProgressBar και του QLabel στο layout
        QHBoxLayout *progressLayout = new QHBoxLayout();
        progressLayout->addWidget(progressBar);
        progressLayout->addWidget(progressLabel);
        audioLayout->addLayout(progressLayout);



        // Εμφάνιση της εντολής στο QTextEdit
        QString command = "yt-dlp " + commandParts.join(" ");
        outputTextEdit->append("Final Command:\n" + command + "\n");

        // Ενημέρωση της μπάρας προόδου στο 2%
        progressBar->setValue(2);
        progressLabel->setText("2%");

        // Εμφάνιση της εντολής στο Application Output
        qDebug() << "Final Command:" << command;

        // Ενημέρωση της μπάρας προόδου στο 4%
        progressBar->setValue(4);
        progressLabel->setText("4%");

        // Εκτέλεση της εντολής
        QProcess *process = new QProcess(dialog);
        process->setProcessChannelMode(QProcess::MergedChannels);

        // Ενημέρωση της μπάρας προόδου στο 5%
        progressBar->setValue(5);
        progressLabel->setText("5%");

        // Σύνδεση για ανάγνωση της εξόδου γραμμή προς γραμμή
        QObject::connect(process, &QProcess::readyReadStandardOutput, [=]() mutable {
        QString output = process->readAllStandardOutput();
        outputTextEdit->append(output);



        // Έλεγχος για το μήνυμα "[youtube:tab] Extracting URL:"
        if (output.contains("[youtube:tab] Extracting URL:")) {
            // Δημιουργία του QLabel μόνο αν δεν υπάρχει ήδη
            if (!downloadLabel) {
                downloadLabel = new QLabel("", audioTab);
                downloadLabel->setStyleSheet("font-size: 12px; color: #333; font-weight: bold;");


                audioLayout->addWidget(downloadLabel);



            }
        }

        // Ενημέρωση της μπάρας προόδου στο 6%
        progressBar->setValue(6);
        progressLabel->setText("6%");

        // Εντοπισμός του μηνύματος "[download] Downloading item X of Y"
        QRegularExpression regexDownloadItem(R"(\[download\] Downloading item (\d+) of (\d+))");
        QRegularExpressionMatch matchDownloadItem = regexDownloadItem.match(output);
        if (matchDownloadItem.hasMatch()) {
            int currentItem = matchDownloadItem.captured(1).toInt();
            int totalItems = matchDownloadItem.captured(2).toInt();
            if (downloadLabel) {
                downloadLabel->setText(QString("Downloading item %1 of %2").arg(currentItem).arg(totalItems));
            }
        }



        if (output.contains("[youtube] Extracting URL")) {
        progressBar->setValue(7);  // 7% για το πρώτο στάδιο
        progressLabel->setText("7%");
        }
        if (output.contains("[youtube] Downloading webpage")) {
        progressBar->setValue(10);  // 10% για το δεύτερο στάδιο
        progressLabel->setText("10%");
        }
        if (output.contains("[youtube] Downloading ios player API JSON")) {
        progressBar->setValue(12);  // 12% για το τρίτο στάδιο
        progressLabel->setText("12%");
        }
        if (output.contains("Downloading mweb player API JSON")) {
        progressBar->setValue(15);  // 15% για το τέταρτο στάδιο
        progressLabel->setText("15%");
        }
        if (output.contains("Downloading m3u8 information")) {
        progressBar->setValue(17);  // 17% για το πέμπτο στάδιο
        progressLabel->setText("17%");
        }
        if (output.contains("Downloading 1 format(s)")) {
        progressBar->setValue(20);  // 20% για το έκτο στάδιο
        progressLabel->setText("20%");
        }
        if (output.contains("[download] Destination")) {
        progressBar->setValue(23);  // 23% για την έναρξη της λήψης
        progressLabel->setText("23%");
        }

        // Ενημέρωση του QLabel με βάση το ποσοστό λήψης
        QRegularExpression regex(R"(\[download\]\s+(\d+\.?\d*)% of)");
        QRegularExpressionMatch match = regex.match(output);
        if (match.hasMatch()) {
        double progress = match.captured(1).toDouble();
        int scaledProgress = 23 + static_cast<int>(progress * 0.72);  // Κλιμάκωση στο εύρος 70-90%
        progressBar->setValue(scaledProgress);
        progressLabel->setText("" + QString::number(scaledProgress) + "%");
        }

        if (output.contains("[ExtractAudio] Destination")) {
        progressBar->setValue(99);
        progressLabel->setText("99%");
        }

        if (output.contains("Deleting original file")) {
        progressBar->setValue(100);
        progressLabel->setText("100%");
        }
        });

        // Σύνδεση για ανάγνωση του standard error
        QObject::connect(process, &QProcess::readyReadStandardError, [=]() {
            QString errorOutput = process->readAllStandardError();
            outputTextEdit->append("Error: " + errorOutput);
        });

        // Σύνδεση για την ολοκλήρωση της διαδικασίας
        QObject::connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), [=](int exitCode, QProcess::ExitStatus exitStatus) {
            okButton->setEnabled(true);  // Επαναφορά της ενεργοποίησης του κουμπιού μετά την ολοκλήρωση
            if (exitStatus == QProcess::NormalExit && exitCode == 0) {
                progressBar->setValue(100);
                progressLabel->setText("100%");

                // Δημιουργία QMessageBox
                QMessageBox successBox;
                successBox.setWindowTitle("Completed");
                successBox.setText("The command was executed successfully!");
                successBox.exec();

                // Διαγραφή του QLabel ποσοστού
                progressLabel->deleteLater();
                qDebug() << "Το QLabel ποσοστού διαγράφηκε.";
                qDebug() << "#######################################################" << "\n";

            } else {
                QString error = process->readAllStandardError();
                outputTextEdit->append("Error: " + error);
                QMessageBox::critical(dialog, "Error", "The Command Failed.");

                // Διαγραφή του QLabel ποσοστού
                progressLabel->deleteLater();
                progressBar->setValue(0);
                qDebug() << "Το QLabel ποσοστού διαγράφηκε.";
                qDebug() << "#######################################################" << "\n";
            }
            process->deleteLater();
        });

        // Εκτέλεση της εντολής
        process->start("yt-dlp", commandParts);

        if (!process->waitForStarted()) {
            QMessageBox::critical(dialog, "Error", "The Command Failed.");
            outputTextEdit->append("Error: The command could not start.");
            process->deleteLater();
            return;
        }
    });

    // Διάταξη των στοιχείων στην καρτέλα "Ήχος"
    audioLayout->addLayout(sliderLayout);  // Προσθήκη του sliderLayout
    audioLayout->addSpacing(20);  // Προσθήκη κενού 20 pixels μεταξύ slider και μορφής αρχείου
    audioLayout->addLayout(formatLogLayout);  // Προσθήκη του formatLogLayout (QComboBox και QCheckBox)
    audioLayout->addSpacing(20);  // Προσθήκη κενού 20 pixels μεταξύ μορφής αρχείου και URL
    audioLayout->addWidget(urlLineEdit);

    // Δημιουργία οριζόντιας διάταξης για το label και το κουμπί επιλογής φακέλου
    QHBoxLayout *folderLayout = new QHBoxLayout();
    folderLayout->addWidget(folderButton);  // Πρώτα το κουμπί
    folderLayout->addWidget(folderLabel);   // Μετά το label
    audioLayout->addLayout(folderLayout);

    audioLayout->addSpacing(20);  // Προσθήκη κενού 20 pixels μεταξύ επιλογής φακέλου και URL
    audioLayout->addWidget(new QLabel("URL:", audioTab));
    audioLayout->addWidget(urlLineEdit);

    audioLayout->addSpacing(20);  // Προσθήκη κενού 20 pixels μεταξύ επιλογής φακέλου και κουμπιού OK
    audioLayout->addWidget(okButton);
    audioLayout->addWidget(new QLabel("Command output:", audioTab));
    audioLayout->addWidget(outputTextEdit);
    audioLayout->addWidget(progressBar);

    // Καρτέλα "Βίντεο" (άδεια προς το παρόν)
    QWidget *videoTab = new QWidget();  // Δημιουργία της δεύτερης καρτέλας
    QVBoxLayout *videoLayout = new QVBoxLayout(videoTab);  // Layout για την καρτέλα "Βίντεο"
    videoLayout->addWidget(new QLabel("This Tab is empty.", videoTab));

    // Προσθήκη των καρτελών στο QTabWidget
    tabWidget->addTab(audioTab, "Audio");
    tabWidget->addTab(videoTab, "Video");

    // Ορισμός του QTabWidget ως κεντρικού layout του παραθύρου
    QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
    dialogLayout->addWidget(tabWidget);

    dialog->setStyleSheet(
        "QDialog { background-color: #f5f5f5; }"
        "QLabel { font-size: 14px; color: #333; font-weight: bold; }"
        "QLabel#valueLabel { font-size: 14px; color: #333; font-weight: bold; }"
        "QPushButton { "
        "   color: white; "
        "   border: none; "
        "   padding: 5px 10px; "
        "   font-size: 12px; "
        "   border-radius: 5px; "
        "   background-color: #607D8B; "
        "}"
        "QPushButton:hover { "
        "   background-color: #546E7A; "
        "   border: 2px solid #455A64; "
        "   padding: 3px 8px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        "QPushButton:pressed { "
        "   background-color: #455A64; "
        "   border: 2px solid #37474F; "
        "   padding: 3px 8px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        "QPushButton#okButton { background-color: #4CAF50; }"
        "QPushButton#folderButton { background-color: #607D8B; }"
        "QPushButton#folderButton:hover { background-color: #546E7A; border: 2px solid #455A64; padding: 3px 8px; }"
        "QPushButton#folderButton:pressed { background-color: #455A64; border: 2px solid #37474F; padding: 3px 8px; }"
        "QLineEdit, QComboBox, QSlider, QCheckBox { padding: 5px; border-radius: 4px; border: 1px solid #ccc; }"
        "QTextEdit { background-color: white; border-radius: 4px; border: 1px solid #ccc; padding: 5px; }"
        "QProgressBar { border-radius: 4px; border: 1px solid #ccc; background-color: white; }"
        "QProgressBar::chunk { background-color: #4CAF50; border-radius: 4px; }"
        "QSlider { border: none; }"
        "QSlider::groove:horizontal { background: #e0e0e0; height: 4px; border-radius: 2px; }"
        "QSlider::sub-page:horizontal { background: #415D70; height: 4px; border-radius: 2px; }"
        "QSlider::handle:horizontal { background: #1B4F72; width: 12px; height: 12px; margin: -4px 0; border-radius: 6px; border: 1px solid #ccc; }"
        "QSlider::handle:horizontal:hover { background: #5994B9; }"
        "QSlider::handle:horizontal:pressed { background: #5F89A6; }"
        "QMessageBox QPushButton { "  // Εφαρμογή στυλ για τα κουμπιά του QMessageBox
        "   color: white; "
        "   border: none; "
        "   padding: 4px 25px; "
        "   font-size: 12px; "
        "   border-radius: 5px; "
        "   background-color: #4CAF50; "  // Χρώμα για το κουμπί "OK"
        "}"
        "QMessageBox QPushButton:hover { "
        "   background-color: #43A047; "  // Χρώμα hover για το κουμπί "OK"
        "   border: 2px solid #388E3C; "
        "   padding: 3px 8px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        "QMessageBox QPushButton:pressed { "
        "   background-color: #388E3C; "  // Χρώμα pressed για το κουμπί "OK"
        "   border: 2px solid #2E7D32; "
        "   padding: 3px 8px; "  // Μειώστε το padding κατά 2px για να αντισταθμίσετε το border
        "}"
        );

    // Ορισμός IDs για τα κουμπιά
    okButton->setObjectName("okButton");
    folderButton->setObjectName("folderButton");

    dialog->setLayout(dialogLayout);
    dialog->exec();
}

// Υλοποίηση του event filter
bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::WindowStateChange) {
        QDialog *dialog = qobject_cast<QDialog*>(obj);
        if (dialog) {
            // Αν το παράθυρο ελαχιστοποιήθηκε
            if (dialog->windowState() & Qt::WindowMinimized) {
                // Ελαχιστοποίηση του κύριου παραθύρου
                this->showMinimized();
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
