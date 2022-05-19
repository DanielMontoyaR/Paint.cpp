#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QInputDialog>
#include <QColorDialog>

#define SIZE 5

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mImage = new QImage(QWidget::size(),QImage::Format_ARGB32_Premultiplied);

    mPainter = new QPainter(mImage);
    mEnabled = false;

    mColor = QColor(Qt::black);
    mSize = SIZE;


}

MainWindow::~MainWindow()
{
    delete ui;
    delete mPainter;
    delete mImage;



}

void MainWindow::paintEvent(QPaintEvent *e){

    QPainter painter(this);
    painter.fillRect(mImage->rect(), Qt::white);
    painter.drawImage(0,0,*mImage);
    e->accept();

}

void MainWindow::mousePressEvent(QMouseEvent *e){


    mEnabled = true;
    mBegin = e->pos();
    e->accept();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){

    if (mEnabled == false){
        e->accept();
        return;
    }

    QPen pen(mColor);
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(mSize);
    mEnd = e->pos();
    mPainter->setPen(pen);

    mPainter->drawLine(mBegin,mEnd);
    mBegin = mEnd;
    update();
    e->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){

    mEnabled = false;
    e->accept();
}

void MainWindow::on_actionAdd_file_triggered()
{
    close();
}


void MainWindow::on_actionAbrir_triggered()
{

}


void MainWindow::on_actionGuardar_triggered()
{

}


void MainWindow::on_actionGuardar_como_triggered()
{

}


void MainWindow::on_actionSeleccionar_Tamano_triggered()
{
    int ancho = QInputDialog::getInt(this, "Ancho del canvas","Ingrese el tamaño del ancho del canvas deseado");
    int alto = QInputDialog::getInt(this, "Alto del canvas","Ingrese el tamaño del alto del canvas deseado");
    mImage = new QImage(ancho,alto,QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);

}


void MainWindow::on_actionAcercar_triggered()
{

}


void MainWindow::on_actionAlejar_triggered()
{

}


void MainWindow::on_actionLapiz_triggered()
{
    mSize = QInputDialog::getInt(this, "Tamaño del Lapiz","Ingrese el tamaño del lapiz que desea utilizar", 5,1);

    mColor = QColorDialog::getColor(mColor,this, "Color del lápiz");

    update();
}


void MainWindow::on_actionLapicero_triggered()
{

}


void MainWindow::on_actionBorrador_triggered()
{
    mSize = QInputDialog::getInt(this, "Tamaño del borrador","Ingrese el tamaño del borrador que desea utilizar", 5,1);

    mColor = QColor(Qt::white);
}

void MainWindow::on_actionFormas_triggered()
{

}


void MainWindow::on_actionRellenar_triggered()
{

}



