#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QInputDialog>
#include <QColorDialog>
#include <iostream>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mImage = new QImage(865,465,QImage::Format_ARGB32_Premultiplied);
    //mImage2 = new QImage(200,200,QImage::Format_ARGB32_Premultiplied);


    mPainter = new QPainter(mImage);
    mEnabled = false;

    mColor = QColor(Qt::black);

    mSize = 5;
    mFuncion = 1;
    clicCounter = 0;



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
    //painter.fillRect(mImage2->rect(), Qt::red);
    painter.drawImage(0,0,*mImage);
    //painter.drawImage(0,0,*mImage2);


    e->accept();

}

void MainWindow::mousePressEvent(QMouseEvent *e){


    mEnabled = true;


    QPen pen(mColor); //Creación de un lápiz que permita escribir en el canvas
    pen.setWidth(mSize); //Tamaño para el lápiz
    mPainter->setPen(pen);
    pen.setCapStyle(Qt::SquareCap);

    if (mFuncion==1 || mFuncion == 2){

        mBegin = e->pos();
        e->accept();

        mPainter->drawPoint(e->pos());

        update();
        e->accept();
    }


    else if (mFuncion ==3){

        mClick = e->pos();
        mPainter->drawPoint(mClick);

        update();
        e->accept();
        if (clicCounter == 0){

            clicCounter++;
            mBegin = e->pos();

        }
        else{

            clicCounter=0;
            mEnd = e->pos();

            trazaLinea(mBegin.x(),mBegin.y(),mEnd.x(),mEnd.y());//Llamada a la función de trazar la línea

        }//End else

    }//End else if

    else if (mFuncion ==4){
        mClick=e->pos();
        mPainter->drawPoint(mClick);

        if (forma == 1){//Condición para crear el cuadrado / rectángulo
            trazaLinea(mClick.x(),mClick.y(),mClick.x()+lado2,mClick.y());//Trazado de la línea horizontal superior

            trazaLinea(mClick.x(),mClick.y()+lado1,mClick.x()+lado2,mClick.y()+lado1);//Trazado de la línea horizontal inferior

            trazaLinea(mClick.x(),mClick.y(),mClick.x(),mClick.y()+lado1);//Trazado de la línea vertical izquierda

            trazaLinea(mClick.x()+lado2,mClick.y(),mClick.x()+lado2,mClick.y()+lado1);//Trazado de la línea vertical derecha
        }//End if

        else{//Creación del Triángulo

            trazaLinea(mClick.x(),mClick.y(),mClick.x(),mClick.y()+lado2);//Trazado de la altura del triángulo.

            trazaLinea(mClick.x(),mClick.y()+lado2,mClick.x()+lado1,mClick.y()+lado2);//Trazado de la base del triángulo.

            trazaLinea(mClick.x(),mClick.y(),mClick.x()+lado1,mClick.y()+lado2);//Trazado de la hipotenusa del triángulo.

        }//End else

    }


    update();
    e->accept();


}

void MainWindow::mouseMoveEvent(QMouseEvent *e){

    if (mEnabled == false){
        e->accept();
        return;
    }
    else{

        QPen pen(mColor); //Creación de un lápiz que permita escribir en el canvas
        pen.setWidth(mSize); //Tamaño para el lápiz
        mPainter->setPen(pen);
        pen.setCapStyle(Qt::SquareCap);


        if (mFuncion == 1 || mFuncion ==2){ //Funcion de lápiz y borrador


            pen.setCapStyle(Qt::SquareCap); //Tipo de trazo para el lápiz

            mEnd = e->pos();
            mPainter->setPen(pen);

            mPainter->drawLine(mBegin,mEnd);

            mBegin = mEnd;

        }
        else if (mFuncion == 3){ // Funcion para la línea recta

        }//End else if

        else if(mFuncion == 4){//Funcion para el ingreso de formas

        }//End else if
    }

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


void MainWindow::on_actionSeleccionar_Tamano_triggered()//Listo
{
    mAncho = QInputDialog::getInt(this, "Ancho del canvas","Ingrese el tamaño del ancho del canvas deseado",865,150,1900);
    mAlto = QInputDialog::getInt(this, "Alto del canvas","Ingrese el tamaño del alto del canvas deseado",465,150,875);
    mImage = new QImage(mAncho,mAlto,QImage::Format_ARGB32_Premultiplied);
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
    mFuncion=1;

    editarTrazo();

}


void MainWindow::on_actionLapicero_triggered()
{

    clicCounter=0;
    mFuncion = 3;

    editarTrazo();

}


void MainWindow::on_actionBorrador_triggered()
{
    mFuncion = 2;
    mSize = QInputDialog::getInt(this, "Tamaño del borrador","Ingrese el tamaño del borrador que desea utilizar", 10,1,20);

    mColor = Qt::white;

    //actionLapiz.setEnabled(false);

    /*

    }*/

}

void MainWindow::on_actionFormas_triggered()
{
    mFuncion = 4;

    forma = QInputDialog::getInt(this, "Tipo de forma","Ingrese la forma que desea agregar. "
                                                       "\n1. Cuadrado/Rectángulo"
                                                       "\n2.Triángulo", 1,1,2);


    if(forma == 1){
        lado1 = QInputDialog::getInt(this, "Lado 1","Ingrese el valor del primer lado",50,10,200);
        lado2 = QInputDialog::getInt(this, "Lado 2","Ingrese el valor segundo lado",50,10,200);

    }
    else if (forma ==2){
        lado1 = QInputDialog::getInt(this, "Base del triángulo","Ingrese la base del triángulo",50,10,200);
        lado2 = QInputDialog::getInt(this, "Alto del triángulo","Ingrese la altura del triángulo",50,10,200);

    }
    editarTrazo();

}


void MainWindow::on_actionRellenar_triggered()
{

}



void MainWindow::editarTrazo(){

    mSize = QInputDialog::getInt(this, "Tamaño del trazo","Ingrese el tamaño del trazo que desea utilizar", 5,1,10);

    Color = QInputDialog::getInt(this, "Color del trazo","Ingrese el cololr de trazo deseado. "
                                                             "\n1. Azul "
                                                             "\n2. Verde "
                                                             "\n3. Amarillo "
                                                             "\n4. Naranja "
                                                             "\n5. Rojo"
                                                             "\n6. Morado"
                                                             "\n7. Cafe"
                                                             "\n8. Gris"
                                                             "\n9. Negro"
                                                             "\n10. Blanco",9,1,10);
    if(Color == 1){
        mColor = QColor(0,0,255);
    }
    else if (Color == 2){
        mColor = QColor(0,255,0);
    }
    else if (Color == 3){
        mColor = QColor(255,230,0);
    }
    else if (Color == 4){
        mColor = QColor(255,165,0);
    }
    else if (Color == 5){
        mColor = QColor(255,0,0);
    }
    else if (Color == 6){
        mColor = QColor(179,82,255);
    }
    else if (Color == 7){
        mColor = QColor(191,117,55);
    }
    else if (Color == 8){
        mColor = QColor(180,180,180);
    }
    else if (Color == 9){
        mColor = QColor(0,0,0);
    }
    else{
        mColor = QColor(255,255,255);
    }

    update();
}

void MainWindow::trazaLinea(int x1,int y1,int x2,int y2){

    float deltax = x2-x1;
    float deltay = y2-y1;
    int posx1 = x1;
    int posx2 = x2;
    int posy1 = y1;
    int posy2 = y2;
    int coordy =0;

    //float pendiente = deltax/deltay;

    if(deltax == 0 && deltay == 0){//Si el primer y segundo punto seleccioando son iguales no se ejecuta ninguna función de trazado de línea.

        return;

    }
    else if (deltax == 0){//Si las x son iguales la linea es vertical

        if(y1>y2){//Evalúa si y1 es mayor que y2.
            posy1 = y2;
            posy2 = y1;
        }//End if

        else{
            posy1=y1;
            posy2=y2;
        }//End else

        for(int y =posy1;y<=posy2;y++){
            mPainter->drawPoint(x1,y);
        }


    }
    else if(deltay == 0){//Si las y son iguales la linea es horizontal

        if(x1>x2){//Evalúa si y1 es mayor que y2.
            posx1 = x2;
            posx2 = x1;
        }//End if

        else{
            posx1=x1;
            posx2=x2;
        }//End else

        for(int x =posx1;x<=posx2;x++){
            mPainter->drawPoint(x,y1);
        }
    }
    else{ //Condición para trazar líneas que no son horizontales o verticales.

        deltax = posx2-posx1;
        deltay = posy2-posy1;

        if(x1<x2){

            float pendiente = deltay/deltax;


            for(float x=posx1;x<=round(posx2);x+=0.01){//
                coordy = round(pendiente*(x-posx1))+posy1;
                mPainter->drawPoint(abs(x),abs(coordy));
            }//end for

        }//End if

        else{

            float pendiente = deltay/deltax;


            for(float x=posx2;x<=round(posx1);x+=0.01){
                coordy = round(pendiente*(x-posx1))+posy1;
                mPainter->drawPoint(abs(x),abs(coordy));
            }//end for

        }

    }
}

