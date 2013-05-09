#ifndef GLWGT_H
#define GLWGT_H

#include "logic.h"

#include <QtOpenGL/QGLWidget>

class GLWidget: public QGLWidget
{
    Q_OBJECT
public:
    GLWidget(QWidget *parent = 0);
    void retranslateGLWidget();
    ~GLWidget();
protected:
    void resizeGL(int w, int h);
    void paintGL();
    void initializeGL();
    virtual void keyPressEvent(QKeyEvent *keyEvent);
private:
    int a;
    QString string_ren;
    QString string_ren2;
    QString string_ren3;
    QString string_ren4;
    QString string_ren5;
    QString string_ren6;
    void restructRes(int);
    void drawGrid(double);
    void debugBoard();
    void reverse(double*, double*);
    void drawPoint(double, double);
    Logic *lgt;
    QFont *font;
    QImage data, gldata;
};

#endif // GLWGT_H
