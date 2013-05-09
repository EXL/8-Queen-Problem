#include "widget.h"

#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    /* Set icons for menus, etc */
    iconQuit.addFile(":/quit.png");
    iconSave.addFile(":/save.png");

    /* Set INI-file for settings */
    qSettings = new QSettings(QString("settings.ini"), QSettings::IniFormat);

    /* Install translations for App and Qt lib */
    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    /* 1 */
    createActions();

    /* 2 */
    createMenus();

    /* 3 */
    createStatusBar();

    /* 4 */
    readSettings();

    /* 5 */
    createGLWidget();

    /* 6 */
    createLay();

    /* 7 */
    settingsWidget();

    /* 8 */
    retranslateUi();
}

void Widget::createActions()
{
    saveAction = new QAction(this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(iconSave);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(grabFrameBuffer()));

    exitAction = new QAction(this);
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setIcon(iconQuit);
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    aboutAction = new QAction(this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutDialog()));

    aboutQtAction = new QAction(this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void Widget::createMenus()
{
    fileMenu = new QMenu(this);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    createLanguageMenu();

    aboutMenu = new QMenu(this);
    aboutMenu->addAction(aboutAction);
    aboutMenu->addAction(aboutQtAction);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(fileMenu);
    menuBar->addMenu(languageMenu);
    menuBar->addMenu(aboutMenu);
}

void Widget::createStatusBar()
{
    statusBar = new QStatusBar(menuBar);
    statusBar->setSizeGripEnabled(false);
}

void Widget::createLanguageMenu()
{
    languageMenu = new QMenu(this);

    languageActionGroup = new QActionGroup(this);
    connect(languageActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(switchLanguage(QAction*)));

    QDir qmDir(":/translations");
    QStringList fileNames = qmDir.entryList(QStringList("queens_*.qm"));

    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString locale = fileNames[i];
        locale.remove(0, locale.indexOf('_') + 1);
        locale.chop(3);

        QTranslator translator;
        translator.load(fileNames[i], qmDir.absolutePath());

        QString language = (locale == "en") ? "English" : "Russian";

        langAction = new QAction(tr("&%1").arg(language), this);
        langAction->setCheckable(true);
        langAction->setData(locale);

        languageMenu->addAction(langAction);
        languageActionGroup->addAction(langAction);

        if (language == "English")
            langAction->setChecked(true);
    }
}

void Widget::readSettings()
{
    QString locale = qSettings->value("Language").toString();

    QDir qmDir(":/translations");
    QString qmPath = qmDir.absolutePath();

    appTranslator.load("queens_" + locale, qmPath);
    qtTranslator.load("qt_" + locale, qmPath);

    if (locale == "ru")
        langAction->setChecked(true);
}

void Widget::createGLWidget()
{
    glwgt = new GLWidget(this);
    glWidgetArea = new QScrollArea(this);
    glWidgetArea->setWidget(glwgt);
    glWidgetArea->setWidgetResizable(true);
    glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void Widget::createLay()
{
    lay = new QVBoxLayout;
    lay->setMenuBar(menuBar);
    lay->addWidget(glWidgetArea);

    lay->addWidget(statusBar);
}

void Widget::settingsWidget()
{
    setLayout(lay);
    setFixedSize(320, 360);
}

void Widget::retranslateUi()
{
    aboutTitle = tr("8 Queens Problem");
    aboutBody = tr("<table><tr><td align='center'><img src=':/logo.png'/></td>"
                   "<td align='center'><br><h4>8 Queens Problem</td></h4></tr></table>"
                   "<center><h3>Version 0.1</h3></center>"
                   "<center><h3>(C) EXL, 2013</h3></center>");

    saveAction->setText(tr("&Save as..."));
    saveAction->setStatusTip(tr("Save framebuffer as *.png"));

    exitAction->setText(tr("&Quit"));
    exitAction->setStatusTip(tr("Exit the application"));

    aboutAction->setText(tr("&About"));
    aboutAction->setStatusTip(tr("About the application"));

    aboutQtAction->setText(tr("About &Qt"));
    aboutQtAction->setStatusTip(tr("About the Qt Library's"));

    fileMenu->setTitle(tr("&File"));
    languageMenu->setTitle(tr("&Language"));
    aboutMenu->setTitle(tr("&About"));

    statusBar->showMessage(tr("Ready"));

    glwgt->setStatusTip(tr("8 Queens Problem"));
    glwgt->retranslateGLWidget();

    setWindowTitle(tr("8 Queens Problem"));
}

/* Slots */

void Widget::switchLanguage(QAction * action)
{
    QString locale = action->data().toString();

    qSettings->setValue("Language", locale);

    QDir qmDir(":/translations");
    QString qmPath = qmDir.absolutePath();
    appTranslator.load("queens_" + locale, qmPath);
    qtTranslator.load("qt_" + locale, qmPath);

    retranslateUi();
}

void Widget::grabFrameBuffer()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save *.png file"), "",
                                                    tr("Image File (*.png);;All Files (*)"));
    qDebug() << "Grabbing...";
    QImage image = glwgt->grabFrameBuffer();
    QPixmap::fromImage(image);
    if (image.save(fileName, "PNG"))
    {
        qDebug() << "Grabbed!";
    }
    else
    {
        qDebug() << "Can't write PNG image!";
    }
}

bool Widget::event(QEvent * e)
{
    if (e->type() == QEvent::StatusTip)
    {
        statusBar->showMessage(static_cast<QStatusTipEvent*>(e)->tip());
        return true;
    }
    return QWidget::event(e);
}

void Widget::aboutDialog()
{
    QMessageBox::about(this, aboutTitle, aboutBody);
}

Widget::~Widget()
{
    /**/
}
