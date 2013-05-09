#ifndef WIDGET_H
#define WIDGET_H

#include "glwgt.h"

#include <QStatusBar>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QIcon>
#include <QTranslator>
#include <QSettings>
#include <QLabel>
#include <QStatusTipEvent>

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    bool event(QEvent * event);
private:
    QTranslator appTranslator;
    QTranslator qtTranslator;

    QIcon iconSave;
    QIcon iconQuit;

    QAction *saveAction;
    QAction *exitAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
    QActionGroup *languageActionGroup;
    QAction *langAction;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *languageMenu;
    QMenu *aboutMenu;

    GLWidget *glwgt;
    QScrollArea *glWidgetArea;

    QVBoxLayout *lay;

    QString aboutTitle;
    QString aboutBody;

    QLabel *test;
    QStatusBar *statusBar;

    QSettings *qSettings;

    void readSettings();
    void createActions();
    void createMenus();
    void createStatusBar();
    void createLanguageMenu();
    void createGLWidget();
    void createLay();
    void settingsWidget();
    void retranslateUi();
private slots:
    void grabFrameBuffer();
    void aboutDialog();
    void switchLanguage(QAction *);
};

#endif // WIDGET_H
