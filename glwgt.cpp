#include "glwgt.h"

#include <iostream> // for debug
#include <QDebug>

#include <QKeyEvent>
#include <qmath.h>
#include <QTimer>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    lgt->setQueen(0);
    a = 0;

    string_ren5 = "1";
    retranslateGLWidget();

    font = new QFont("Courier", 9);

    data.load(":/queen.png");
    gldata = QGLWidget::convertToGLFormat(data);
    resize(data.size());
}

void GLWidget::retranslateGLWidget()
{
    string_ren = tr("This program shows how to solve");
    string_ren2 = tr("the problem of the eight queens");
    string_ren3 = tr("Use arrow to change");
    string_ren4 = "<- ";
    string_ren6 = " ->";
}

void GLWidget::initializeGL()
{
    glEnable(GL_NORMALIZE);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);

    /* For Alpha */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLoadIdentity();
    glOrtho(-2.0, 10.0, -2.0, 10.0, -1.0, 1.0);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    drawGrid(1);

    renderText(40, 20, string_ren, *font);
    renderText(40, 35, string_ren2, *font);
    renderText(60, 270, string_ren3, *font);
    renderText(200, 270, string_ren4, *font);
    renderText(215, 270, string_ren5, *font);

    if(a > 8)
        renderText(224, 270, string_ren6, *font);
    else
        renderText(217, 270, string_ren6, *font);

    glLineWidth(1);

    restructRes(a);

    glPopMatrix();
}

void GLWidget::restructRes(int a)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if(boards[a][i][j] == 1)
                drawPoint(i + 0.5, j + 0.5);
        }
    }
}

void GLWidget::reverse(double *i, double *j)
{
    double swap = 0;
    swap = 8 - *i;
    *i = *j;
    *j = swap;
}

void GLWidget::drawPoint(double i, double j)
{
    reverse(&i, &j);
    glRasterPos2i(i, j);
    glDrawPixels(data.width(), data.height(), GL_RGBA, GL_UNSIGNED_BYTE, gldata.bits());
}

void GLWidget::drawGrid(double step)
{
    glColor3f(0.0, 0.0, 0.0);

    for(int i = 0; i < 8; i+=step)
    {
        for(int j = 0; j < 8; j+=step)
        {
            if ((!(i%2) && !(j%2)) || ((i%2) && (j%2)))
            {
                glBegin(GL_QUADS);
                glVertex2f(0 + i, 0 + j);
                glVertex2f(0 + i, 1 + j);
                glVertex2f(1 + i, 1 + j);
                glVertex2f(1 + i, 0 + j);
                glEnd();
            }
        }
    }

    for (int i = 0; i <= 8; i+=step)
    {
        if (i == 0 || i == 8)
        {
            glLineWidth(2);
            glColor3f(0.5, 0.0, 0.0);
        }
        else
        {
            glLineWidth(1);
            glColor3f(0.8, 0.8, 0.8);
        }
        glBegin(GL_LINES);
        glVertex2f(i, 8);
        glVertex2f(i, 0);
        glVertex2f(8, i);
        glVertex2f(0, i);
        glEnd();
    }
    glColor3f(0.0, 0.0, 0.0);
}

void GLWidget::keyPressEvent(QKeyEvent * keyEvent)
{
    switch (keyEvent->key())
    {
    case Qt::Key_Left:
        if (a <= 0)
        {
            a = 0;
            string_ren5 = "1";
        }
        else
        {
            a-=1;
            string_ren5 = QString("%1").arg(a+1);
        }
        break;

    case Qt::Key_Right:
        if (a >= 91)
        {
            a = 91;
            string_ren5 = "92";
        }
        else
        {
            a+=1;
            string_ren5 = QString("%1").arg(a+1);
        }
        break;
    }
    updateGL();
}

void GLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
}

GLWidget::~GLWidget()
{
    /* destructor */
}
