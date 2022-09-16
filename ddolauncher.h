#ifndef DDOLAUNCHER_H
#define DDOLAUNCHER_H

#include <QWidget>
#include <QAction>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTabWidget>
#include <QToolBar>
#include <QToolTip>
#include <QVBoxLayout>
#include <QtCore/QVariant>

#include <QList>

#include <QGroupBox>

#include <QPushButton>
#include <QLineEdit>

#include <QFileDialog>
#include <QMessageBox>

//image stuff
#include <QColor>

#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QDockWidget>
#include <QFontDatabase>
#include <QFont>
#include <QSettings>
#include <QDesktopWidget>

//network shit
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QProcess>
//#include <QSslSocket>

class DDOLauncher : public QMainWindow
{
    Q_OBJECT
public:
    static const unsigned int MaxWidth;
    static const unsigned int MaxHeight;
    static const QString SizeStr;
    static const QString PtStr;


    explicit DDOLauncher(QMainWindow *parent = 0);
    ~DDOLauncher();


protected:


private:

    QSettings    m_settings;

    QStatusBar * mStatusbar;
    QProgressBar * mProgressbar;
    QMenu *viewMenu;

    QNetworkAccessManager manager;

    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
        QVBoxLayout *outerLayout;
            QVBoxLayout *insideboxLayout;

    QLabel *label_2;
    QLineEdit *spinBoxMax;
    QLineEdit *spinBox;
    QLabel *label;
    QLabel *label_3;
    QLabel *difflabel;
    QLabel *speclabel;
    QLabel *normlabel;
    QLabel *litelabel;


    QLineEdit *spinboxIdle;


    QLabel *label_meshcount;
    QLineEdit *meshcount;
    QLabel *label_materialcount;
    QLineEdit *materialcount;
    QLabel *label_vertexcount;
    QLineEdit *vertexcount;



    QLabel *label_facecount;
    QLineEdit *facecount;
    QLabel *label_vertexids;
    QLineEdit *vertexids;
    QLabel *label_vertexbuffersize;
    QLineEdit *vertexbuffersize;


    QLabel *label_scondbuffersize;
    QLineEdit *scondbuffersize;
    QLabel *label_groupcount;
    QLineEdit *groupcount;
    QLabel *label_bonesoffset;
    QLineEdit *bonesoffset;


    QLabel *label_groupoffset;
    QLineEdit *groupoffset;
    QLabel *label_textureoffset;
    QLineEdit *textureoffset;
    QLabel *label_meshoffset;
    QLineEdit *meshoffset;




    QLabel *label_vertexoffset;
    QLineEdit *vertexoffset;
    QLabel *label_facesoffset;
    QLineEdit *facesoffset;
    QLabel *label_unkoffset;
    QLineEdit *unkoffset;

    QLabel* label_bounding_sphere ;
     QLineEdit* bounding_spherex ;
      QLineEdit* bounding_spherey ;
       QLineEdit* bounding_spherez ;
        QLineEdit* bounding_spherew ;

    QHBoxLayout* boundingspherehLayout ;

    QLabel* label_bounding_boxmin;
     QLineEdit* bounding_boxminx ;
      QLineEdit* bounding_boxminy ;
       QLineEdit* bounding_boxminz ;
        QLineEdit* bounding_boxminw ;

      QHBoxLayout* boundingboxminhLayout;

                QLabel* label_bounding_boxmax  ;
                 QLineEdit* bounding_boxmaxx  ;
                  QLineEdit* bounding_boxmaxy ;
                   QLineEdit* bounding_boxmaxz ;
                    QLineEdit* bounding_boxmaxw ;

                QHBoxLayout* boundingboxmaxhLayout ;


                QLabel* label_h_unkn02  ;
                 QLineEdit* h_unkn02  ;

                 QLabel* label_h_unkn03 ;
                  QLineEdit* h_unkn03  ;

                  QLabel* label_h_unkn04  ;
                   QLineEdit* h_unkn04  ;

                   QLabel* label_h_unkn05  ;
                    QLineEdit* h_unkn05  ;

                    QLabel* label_h_unkn06  ;
                     QLineEdit* h_unkn06  ;


    QLabel *label_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_0;
    QHBoxLayout *horizontalLayout_1;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *btnLogin;
    QPushButton *btnRegister;

    QTabWidget * bonetabs ;


    QLabel *labelrememberme;
    QCheckBox *rememberme;

    QLabel * loginacc;
    QLabel * loginpass;
        QLineEdit *acclogintext;
            QLineEdit *passlogintext;
QHBoxLayout *loginacclayouth;
QHBoxLayout *loginpasslayouth;

    QTabWidget *Groupstabs;

    QTabWidget *Materialstabs;

    QTabWidget *MeshPartstabs;

    QTabWidget *Texturestabs;

    QTabWidget *MeshDatatabs;

    QTabWidget *Weightstabs;


signals:


public slots:

private slots:
    void about();
    void on_login_req();
    void on_reg_req();
    void onManagerFinished(QNetworkReply *reply);
};

#endif // DDOLAUNCHER_H
