#include "ddolauncher.h"
#include <QApplication>
#include <QFile>


int main(int argc, char *argv[])
{
 //Q_INIT_RESOURCE(ddons);
    QApplication a(argc, argv);

// set font
    int id = QFontDatabase::addApplicationFont(":/resources/Resource/styles/VL-PGothic-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont vlfont(family);
a.setFont(vlfont);



//// set font
//    QFont font;
//    font.setFamily("VL PGothic");
//    a.setFont(font);

// set style sheet
    QFile file(":/resources/styles/darkgold.qss");
    if(file.open(QFile::ReadOnly)== true){
        QString StyleSheet(file.readAll());
        a.setStyleSheet(StyleSheet);
    }
    else{
        printf("failed to open style sheet");
    }
a.setApplicationName("Dragon's Dogma Online Launcher");
a.setApplicationDisplayName("Dragon's Dogma Online Launcher");

    QString serverSettingsPath = QCoreApplication::applicationDirPath().append("/DDO_Launcher.ini");
    DDOLauncher m(serverSettingsPath);
    m.show();


    return a.exec();
}
