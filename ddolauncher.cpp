#include "ddolauncher.h"


const unsigned int DDOLauncher::MaxWidth=780;
const unsigned int DDOLauncher::MaxHeight=280;
const QString DDOLauncher::SizeStr("size");
const QString DDOLauncher::PtStr("point");

DDOLauncher::DDOLauncher(QString serverSettingsPath, QMainWindow *parent)
    : QMainWindow(parent),
      m_settings("DDO_Launcher","DDO_Launcher"),
      server_settings(serverSettingsPath, QSettings::IniFormat)
{
    qDebug() << "Loading server settings from file: " << serverSettingsPath;

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Model Editor"));

    connect(&manager, &QNetworkAccessManager::finished, this, &DDOLauncher::onManagerFinished);
    /*
    qDebug() << QSslSocket::sslLibraryBuildVersionString();

    qDebug() << QSslSocket::supportsSsl();

    qDebug() << QSslSocket::sslLibraryVersionString();
*/
    // make the window a nice size and make sure it is on the screen
      QSize deskSize(QApplication::desktop()->size());

      unsigned int width=MaxWidth<(unsigned int)deskSize.width()?MaxWidth:deskSize.width()-100;
      unsigned int height=MaxHeight<(unsigned int)deskSize.height()?MaxHeight:deskSize.height()-100;

      int locX=(deskSize.width()-width)/2;
      int locY=(deskSize.height()-height)/2;

    this->resize(m_settings.value(SizeStr, QSize(width, height)).toSize());
    this->move(m_settings.value(PtStr, QPoint(locX, locY)).toPoint());

      // first messsage warning
      if(m_settings.value(tr("firsttime"), 1).toInt()){
          QMessageBox msgBox;
          msgBox.setText("WARNING! \n Currently the server does NOT use SSL \n your account info will be transmitted in plain text.");
          msgBox.exec();
      }

    //setup menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
/*        QToolBar *fileToolBar = addToolBar(tr("File"));

        const QIcon newIcon = QIcon::fromTheme("document-open", QIcon(":/resources/Resource/icon_lot.png"));
        QAction *newOpenMod = new QAction(newIcon, tr("&Open"), this);
        newOpenMod->setShortcuts(QKeySequence::Open);
        newOpenMod->setStatusTip(tr("Open a .mod File.."));
       // connect(newLetterAct, &QAction::triggered, this, &MainWindow::newLetter);


        connect(newOpenMod,SIGNAL(triggered(bool)),this,SLOT(on_Open_clicked()));


        fileMenu->addAction(newOpenMod);
        fileToolBar->addAction(newOpenMod);

        const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/resources/Resource/icon_stone.png"));
        QAction *saveAct = new QAction(saveIcon, tr("&Save..."), this);
        saveAct->setShortcuts(QKeySequence::Save);
        saveAct->setStatusTip(tr("Save the current Model"));
       // connect(saveAct, &QAction::triggered, this, &MainWindow::save);
          connect(saveAct,SIGNAL(triggered(bool)),this,SLOT(on_Save_clicked()));
        fileMenu->addAction(saveAct);
        fileToolBar->addAction(saveAct);


        fileMenu->addSeparator();
*/
        QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, SLOT(close()));
        quitAct->setShortcuts(QKeySequence::Quit);
        quitAct->setStatusTip(tr("Quit the Model Editor"));
    /*
        QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
        QToolBar *editToolBar = addToolBar(tr("Edit"));
        const QIcon undoIcon = QIcon::fromTheme("edit-undo", QIcon(":/images/undo.png"));
        QAction *undoAct = new QAction(undoIcon, tr("&Undo"), this);
        undoAct->setShortcuts(QKeySequence::Undo);
        undoAct->setStatusTip(tr("Undo the last editing action"));
        connect(undoAct, &QAction::triggered, this, &MainWindow::undo);
        editMenu->addAction(undoAct);
        editToolBar->addAction(undoAct);
    */
        viewMenu = menuBar()->addMenu(tr("&View"));

        menuBar()->addSeparator();

        QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

        QAction *aboutAct = helpMenu->addAction(tr("&About"), this, SLOT(about()));
        aboutAct->setStatusTip(tr("what do you want? go away"));



    //setup menu




    outerLayout = new QVBoxLayout;

    insideboxLayout = new QVBoxLayout;

    groupBox = new QGroupBox(this);

    groupBox->setLayout(insideboxLayout);

    groupBox->setObjectName(QStringLiteral("groupBox"));


    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QStringLiteral("label_2"));
    spinBoxMax = new QLineEdit(groupBox);
    spinBoxMax->setObjectName(QStringLiteral("spinBoxMax"));
    spinBox = new QLineEdit(groupBox);
    spinBox->setObjectName(QStringLiteral("spinBox"));

    label = new QLabel(groupBox);
    label->setObjectName(QStringLiteral("label"));




    meshcount = new QLineEdit(groupBox);
    label_meshcount = new QLabel(groupBox);
    materialcount = new QLineEdit(groupBox);
    label_materialcount = new QLabel(groupBox);


// dl server and port
    horizontalLayout_3 = new QHBoxLayout;
    horizontalLayout_3->addWidget(label_meshcount);
    horizontalLayout_3->addWidget(meshcount);
    meshcount->setToolTip("DL argument (just include the host name or ip, this is the http server)");
    QString dlIp=server_settings.value(tr("DLIP"), "localhost").toString();
    meshcount->setText(dlIp);
    horizontalLayout_3->addWidget(label_materialcount);
    horizontalLayout_3->addWidget(materialcount);
    materialcount->setToolTip("DL argument (just include the port, this is the http server)");
    int dlport=server_settings.value(tr("DLPort"), 52099).toInt();
    materialcount->setText(QString::number(dlport));



// server ip
    horizontalLayout_1 = new QHBoxLayout;
    horizontalLayout_1->addWidget(label);
    horizontalLayout_1->addWidget(spinBox);
    spinBox->setToolTip("Addr argument (this would be the lobby server's ip)");
    QString LIp=server_settings.value(tr("LobbyIP"), "localhost").toString();
    spinBox->setText(LIp);
// server port
    horizontalLayout_1->addWidget(label_2);
    horizontalLayout_1->addWidget(spinBoxMax);
    spinBoxMax->setToolTip("Port argument (this would be the lobby server's port)");
    int lport=server_settings.value(tr("LPort"), 52100).toInt();
    spinBoxMax->setText(QString::number(lport));







//new lazy stuff

    insideboxLayout->addLayout(horizontalLayout_1);
    insideboxLayout->addLayout(horizontalLayout_3);


        difflabel = new QLabel;



    this->setWindowTitle(QApplication::translate("DDOLauncher", "", 0));
   label_2->setText(QApplication::translate("DDOLauncher", "Server Port:", 0));
    label->setText(QApplication::translate("DDOLauncher", "Server IP:", 0));


    label_meshcount->setText(QApplication::translate("DDOLauncher", "DL IP: ", 0));
    label_materialcount->setText(QApplication::translate("DDOLauncher", "DL Port: ", 0));



    const QPixmap pixmap(":/resources/Resource/cici2.png");
    difflabel->setPixmap(pixmap);
    //
    //difflabel->show();
    //Texturestabs->addTab(difflabel,"Diffuse");
    const QImage image = pixmap.toImage();
    qDebug() << (image.isNull() ? "QImage error" : "QImage ok");



    /* buttons
    connect(btnListen,SIGNAL(clicked(bool)),this,SLOT(on_btnListen_clicked()));
    connect(btnClose,SIGNAL(clicked(bool)),this,SLOT(on_btnClose_clicked()));
    connect(cmbAddress,SIGNAL(activated(QString)),this,SLOT(on_addr_changed(QString)));
    */
 //  this->setLayout(outerLayout);
QDockWidget *dock = new QDockWidget(tr("Server Info"),this);
dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
dock->setWidget(groupBox);
//dock->setFloating(true);
addDockWidget(Qt::LeftDockWidgetArea,dock);
viewMenu->addAction(dock->toggleViewAction());


this->setCentralWidget(difflabel);


// actions
dock = new QDockWidget(tr("Actions"),this);
QGroupBox * Texturesbox = new QGroupBox(dock);
Texturesbox->setObjectName(QStringLiteral("Actions"));
Texturestabs = new QTabWidget(Texturesbox);
 QVBoxLayout * Texturesboxlayout = new QVBoxLayout;
Texturesbox->setLayout(Texturesboxlayout);
Texturesboxlayout->addWidget(Texturestabs);
dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
dock->setWidget(Texturesbox);

addDockWidget(Qt::LeftDockWidgetArea,dock);
viewMenu->addAction(dock->toggleViewAction());

// add register and login

//login

 int remember = this->m_settings.value(tr("RememberMe"),0).toInt();


QGroupBox * login =  new QGroupBox(this);
     loginacc = new QLabel(login);
      acclogintext = new QLineEdit(login);
      acclogintext->setToolTip("Account ID");


     loginacclayouth = new QHBoxLayout;
    loginacclayouth->addWidget(loginacc);
    loginacclayouth->addWidget(acclogintext);


                 loginpass = new QLabel(login);
                  passlogintext = new QLineEdit(login);
                  passlogintext->setEchoMode(QLineEdit::Password);
                  passlogintext->setToolTip("Account Password");


                 loginpasslayouth = new QHBoxLayout;
                loginpasslayouth->addWidget(loginpass);
                loginpasslayouth->addWidget(passlogintext);




 btnLogin = new QPushButton;
 btnLogin->setText(QString("Login"));
 btnLogin->setStyleSheet("QPushButton{font-size: 30px;}");
 QVBoxLayout * loginlayoutv = new QVBoxLayout;
  QHBoxLayout* savedetails = new QHBoxLayout;
  rememberme = new QCheckBox(login);
  rememberme->setCheckable(true);

  if(remember){
    int feltId = this->m_settings.value(tr("Felt_Color"),0).toInt();
    QString acc=m_settings.value(tr("Account"), "").toString();
    QString pss=m_settings.value(tr("Password"), "").toString();
    acclogintext->setText(acc);
    passlogintext->setText(pss);
    rememberme->setChecked(1);
  }

  labelrememberme = new QLabel(login);
  savedetails->addWidget(labelrememberme);
  savedetails->addWidget(rememberme);
 login->setLayout(loginlayoutv);
 loginlayoutv->addLayout(loginacclayouth);
 loginlayoutv->addLayout(loginpasslayouth);
 loginlayoutv->addLayout(savedetails);

   loginlayoutv->addWidget(btnLogin);
login->setMinimumWidth(800);

            labelrememberme->setText(QApplication::translate("DDOLauncher", "Remember Me? ", 0));
            loginacc->setText(QApplication::translate("DDOLauncher", "Account: ", 0));
            loginpass->setText(QApplication::translate("DDOLauncher", "Password: ", 0));

Texturestabs->addTab(login,"Login");

connect(btnLogin,SIGNAL(clicked(bool)),this,SLOT(on_login_req()));

// register
QGroupBox * reg =  new QGroupBox(this);
     label_bounding_boxmin = new QLabel(reg);
      bounding_boxminx = new QLineEdit(reg);
      bounding_boxminx->setToolTip("Account ID");


     boundingboxminhLayout = new QHBoxLayout;
    boundingboxminhLayout->addWidget(label_bounding_boxmin);
    boundingboxminhLayout->addWidget(bounding_boxminx);


                 label_bounding_boxmax = new QLabel(reg);
                  bounding_boxmaxx = new QLineEdit(reg);
                  bounding_boxmaxx->setEchoMode(QLineEdit::Password);
                  bounding_boxmaxx->setToolTip("Account Password");


                 boundingboxmaxhLayout = new QHBoxLayout;
                boundingboxmaxhLayout->addWidget(label_bounding_boxmax);
                boundingboxmaxhLayout->addWidget(bounding_boxmaxx);


                             label_bounding_sphere = new QLabel(reg);
                              bounding_spherex = new QLineEdit(reg);
                              bounding_spherex->setToolTip("E-mail (not required but needed if you lose your password)");


                             boundingspherehLayout = new QHBoxLayout;
                            boundingspherehLayout->addWidget(label_bounding_sphere);
                            boundingspherehLayout->addWidget(bounding_spherex);

 btnRegister = new QPushButton;
 btnRegister->setText(QString("Register"));
 btnRegister->setStyleSheet("QPushButton{font-size: 30px;}");
 QVBoxLayout * reglayoutv = new QVBoxLayout;

 reg->setLayout(reglayoutv);
 reglayoutv->addLayout(boundingboxminhLayout);
 reglayoutv->addLayout(boundingboxmaxhLayout);
  reglayoutv->addLayout(boundingspherehLayout);
   reglayoutv->addWidget(btnRegister);
reg->setMinimumWidth(800);
                            label_bounding_sphere->setText(QApplication::translate("DDOLauncher", "E-mail: ", 0));
                            label_bounding_boxmin->setText(QApplication::translate("DDOLauncher", "Account ID: ", 0));
                            label_bounding_boxmax->setText(QApplication::translate("DDOLauncher", "Password: ", 0));

Texturestabs->addTab(reg,"Register");

connect(btnRegister,SIGNAL(clicked(bool)),this,SLOT(on_reg_req()));


// progress bar (for loading or saving)
mProgressbar = new QProgressBar(this);
mProgressbar->setMaximum(100);
mProgressbar->setMinimum(0);
mProgressbar->setTextVisible(true);
mProgressbar->setValue(0);

mProgressbar->setVisible(false);

// status bar
mStatusbar = new QStatusBar(this);
mStatusbar->addPermanentWidget(mProgressbar);

mStatusbar->showMessage(tr("Ready."));
this->setStatusBar(mStatusbar);


// file change shit connections
    //connect(cmbAddress,SIGNAL(activated(QString)),this,SLOT(on_File_changed(QString)));


    QIcon icon = QIcon(":/resources/Resource/icon.png");
    this->setWindowIcon(icon);



}

DDOLauncher::~DDOLauncher()
{
    // cleanup

    // save the position of the window
    this->m_settings.setValue(SizeStr,this->size());
    this->m_settings.setValue(PtStr,this->pos());

    // save dl server info
    this->server_settings.setValue(tr("DLIP"),meshcount->text());
    this->server_settings.setValue(tr("DLPort"),materialcount->text().toInt());
    // save lobby server info
    this->server_settings.setValue(tr("LobbyIP"),spinBox->text());
    this->server_settings.setValue(tr("LPort"),spinBoxMax->text().toInt());

    if(rememberme->isChecked()){
      this->m_settings.setValue(tr("Account"),acclogintext->text());
      this->m_settings.setValue(tr("Password"),passlogintext->text());
      this->m_settings.setValue(tr("RememberMe"),1);
    }
    this->m_settings.setValue(tr("firsttime"),0);
}





void DDOLauncher::about()
{

       QMessageBox::about(this, tr("About Dragon's Dogma Online Launcher"),
                tr("The <b>Dragon's Dogma Online Launcher</b> blah blah "
                   "use it to communicate with server api, "
                   "yada yada yada, "
                   "use at your own risk."
                   "Please visit White Dragon Temple <a href='https://discord.gg/CVNjF4ztP4'>Discord</a> for support"
                   ));

}

void DDOLauncher::on_login_req()
{
btnLogin->setDisabled(true);
    QNetworkRequest request(QUrl(QString("http://%1:%2/api/account").arg(meshcount->text(),materialcount->text()))); // without ID

request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
//request.setRawHeader("Accept-Encoding", "gzip, deflate");

    QJsonObject logindetails;
   // QJsonDocument jdoc;

    logindetails.insert("Action","login");
    logindetails.insert("Account",acclogintext->text());
    logindetails.insert("Password",passlogintext->text());

    QJsonDocument jdoc(logindetails);
  //  jdoc.setObject(logindetails);

         QByteArray ba = jdoc.toJson();
         manager.post(request, ba);

    // qDebug() << QJsonDocument(logindetails).toJson();
     //manager.post(request, QJsonDocument(logindetails).toJson());

}

void DDOLauncher::on_reg_req()
{
    btnRegister->setDisabled(true);
    QNetworkRequest request(QUrl(QString("http://%1:%2/api/account").arg(meshcount->text(),materialcount->text()))); // without ID

    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    QJsonObject Registerdetails;
  //  QJsonDocument jdoc;

    Registerdetails.insert("Action","create");
    Registerdetails.insert("Account",bounding_boxminx->text());
    Registerdetails.insert("Password",bounding_boxmaxx->text());
    Registerdetails.insert("E-mail",bounding_spherex->text());

   // jdoc.setObject(Registerdetails);

      //   QByteArray ba = jdoc.toBinaryData();
       //  qDebug() << "go fuck yourself"; //ba.toStdString();
         manager.post(request, QJsonDocument(Registerdetails).toJson());
}

void DDOLauncher::onManagerFinished(QNetworkReply *reply)
{


    QJsonDocument jdoc;
   // QString err = reply->errorString();
  //  qDebug() << err;
//return;
    jdoc = jdoc.fromJson(reply->readAll());
    if(!jdoc.isNull()){
    QJsonObject jobj = jdoc.object();
    QJsonValue Message = jobj.value(QString("Message"));
    qDebug() << Message;

    if(Message.toString() == "Login Success"){
        // launch game
         QJsonValue Token = jobj.value(QString("Token"));
         QProcess derp;
         derp.startDetached(QString("ddo.exe addr=%1 port=%2 token=%3 DL=http://%4:%5/win/ LVer=03.04.003.20181115.0 RVer=3040008").arg(
                                spinBox->text(),
                                spinBoxMax->text(),
                                Token.toString(),
                                meshcount->text(),
                                materialcount->text()
                                ));
         qDebug() << "TOKEN: "<< Token.toString();
         QApplication::quit();
    }
    else{
        if(!Message.isNull()){
        QMessageBox msgBox;
        msgBox.setText(Message.toString());
        msgBox.exec();}
    }

    QJsonValue Error = jobj.value(QString("Error"));

    if(!Error.isNull()){
        QMessageBox msgBox;
        msgBox.setText(Error.toString());
        msgBox.exec();
    }


    }
    else{
        qDebug() << "invalid json reply";
        QMessageBox msgBox;
        msgBox.setText("Invalid Reply from Server.");
        msgBox.exec();
    }
    btnRegister->setDisabled(false);
    btnLogin->setDisabled(false);

reply->deleteLater();


}
/*
void ::on_Open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
          tr("Load Mod File"), "./",tr("MOD (*.mod)"));
    cmbAddress->insertItem(0,fileName);
    label_3->setText("File: " + fileName.section("/",-1,-1)); // just the file name
    open_file(fileName);
}
*/


