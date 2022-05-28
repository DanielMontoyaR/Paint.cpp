#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QtWidgets>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QInputDialog>
#include <QColorDialog>
#include <QByteArray>
#include <iostream>
#include <queue>
#include <iomanip>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mImage = new QImage(865,465,QImage::Format_ARGB32_Premultiplied);
    //mImage2 = new QImage(200,200,QImage::Format_ARGB32_Premultiplied);

    mAncho = 865;
    mAlto = 465;
    mPainter = new QPainter(mImage); //Clase que permite dibujar sobre una imagen
    mEnabled = false;//Variable que evita que se escriba en el canvas cuando el usuario no está presionando el mouse

    mColor = QColor(Qt::black);//color del trazo predeterminado.

    mSize = 5;//Tamaño predeterminado del trazo
    mFuncion = 1;//Se inicializa la aplicación con la función de lápiz
    clicCounter = 0; //Se inicializan los contadores de clicks para la funcion de la línea recta

    resize(865,465);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete mPainter;
    delete mImage;



}

void MainWindow::paintEvent(QPaintEvent *e){//Evento de pintado

    QPainter painter(this);
    painter.fillRect(mImage->rect(), QColor(255,255,255));//Color predeterminado del canvas
    painter.drawImage(0,0,*mImage);
    e->accept();

}

void MainWindow::mousePressEvent(QMouseEvent *e){ //Evento que detecta cuando el mouse es clickeado


    mEnabled = true;


    QPen pen(mColor); //Creación de un objeto lápiz (pen) que permita escribir en el canvas
    pen.setWidth(mSize); //Tamaño para el lápiz
    mPainter->setPen(pen);//Se establece el lápiz que se va a utilizar.
    pen.setCapStyle(Qt::SquareCap);

    if (mFuncion==1 || mFuncion == 2){//Evalúa si la función actual es el lápiz o el borrador

        mBegin = e->pos();
        e->accept();

        mPainter->drawPoint(e->pos());//Se dibuja un punto en la coordenada agregada

        update();
        e->accept();
    }


    else if (mFuncion ==3){//Evalúa si la función es el lapicero

        mClick = e->pos();//Obtención de la coordenada clickeada por el mouse.
        mPainter->drawPoint(mClick);//Se dibuja un punto en la coordenada agregada

        update();
        e->accept();

        if (clicCounter == 0){//Evalúa que el contador de clicks sea 0 para guardar en una variable el primer punto

            clicCounter++; //Incrementa el valor del contador
            mBegin = e->pos();//Se establece el primer punto presionado

        }
        else{

            clicCounter=0;//Reinicia el valor del contador a 0
            mEnd = e->pos();//Se establece el segundo punto presionado

            trazaLinea(mBegin.x(),mBegin.y(),mEnd.x(),mEnd.y());//Llamada a la función de trazar la línea

        }//End else

    }//End else if

    else if (mFuncion ==4){//Evalúa si la función es la de trazar la forma.
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

    else if (mFuncion == 5){//Evalúa si la función es el color picker
        mClick=e->pos();

        mColor = mImage->pixelColor(mClick);

        mFuncion=1;
    }

    else if(mFuncion ==6){//Evalúa si la función es el paint filler
        mClick=e->pos();
        /**int dirs[8][2]={{0,-1},//Abajo
                      {-1, 0},//Izquierda
                       {0, 1},//Arriba
                       {1, 0}};//Derecha*/

        floodfill(mClick.x(),mClick.y(),mColor);

    }

    update();
    e->accept();//Actualizar el canvas


}

void MainWindow::floodfill(int x, int y, QColor new_color){

    int n = mAncho;
    int m = mAlto;

    QColor old_color=mImage->pixelColor(x,y);//Se asigna el valor del color en la posición inicial
    queue<pair<int,int>> q;//Se crea una cola

    q.push({x,y});//Se agregan los valores x,y a la cola

    if (old_color==new_color){//Compara si el color viejo es igual al nuevo
        return;
    }

    while(!q.empty()){
        //Sacar nodo frontal de la fila y procesarlo
        pair<int,int> node = q.front();
        q.pop();
        int x = node.first;//Se asigna el valor del primer nodo
        int y = node.second;//Se asigna el valor del segundo nodo


        if((x<0 || x>=n || y<0 || y>=m || old_color!=mImage->pixelColor(x,y))){//Condición general, si el x y el y se encuentran dentro del canvas y si el color antiguo es
                                                                               //distinto de la imagen en la posición x,y
            continue;
        }
        else{
            mPainter->drawPoint(x,y);//Dibuja el punto en el canvas
            //Se agregan las diferentes posiciones a las que se puede mover el pixel.
            q.push({x+1,y});
            q.push({x,y+1});
            q.push({x-1,y});
            q.push({x,y-1});

        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){//Evento que ocurre cuando el mouse se mueve

    if (mEnabled == false){//Evalúa si al moverse el mouse este se está presionando
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

            mEnd = e->pos();//Se toma la posición del mouse
            mPainter->setPen(pen);

            mPainter->drawLine(mBegin,mEnd);//Se traza sobre el canvas una linea.

            mBegin = mEnd;

        }
        else if (mFuncion == 3){ // Funcion para la línea recta

        }//End else if

        else if(mFuncion == 4){//Funcion para el ingreso de formas

        }//End else if

        else if(mFuncion == 5){//Función para el color picker

        }
    }

    update();//Actualiza el canvas
    e->accept();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){//Evento que ocurre al dejar de presionar el mouse

    mEnabled = false;//Establece la variable en false para que no se dibuje en el canvas al soltar el botón.
    e->accept();
}

void MainWindow::on_actionAdd_file_triggered()//Función que cierra el programa
{
    close();
}



void MainWindow::on_actionSeleccionar_Tamano_triggered()//Función que permite cambiar el tamaño del canvas
{
    mAncho = QInputDialog::getInt(this, "Ancho del canvas","Ingrese el tamaño del ancho del canvas deseado",865,150,1900);
    mAlto = QInputDialog::getInt(this, "Alto del canvas","Ingrese el tamaño del alto del canvas deseado",465,150,875);

    mImage = new QImage(mAncho,mAlto,QImage::Format_ARGB32_Premultiplied);
    mPainter = new QPainter(mImage);
}



void MainWindow::on_actionLapiz_triggered()//Función de lapiz
{
    mFuncion=1;//Establece la variable en 1 que caracteriza a la función lapiz

    editarTrazo();//Llamada a la función para editar el trazo

}


void MainWindow::on_actionBorrador_triggered()
{
    mFuncion = 2;//Establece la variable en 2 que caracteriza a la función borrador
    mSize = QInputDialog::getInt(this, "Tamaño del borrador","Ingrese el tamaño del borrador que desea utilizar", 10,1,20);

    mColor = Qt::white;//Se establece el color del borrador como blanco.

}

void MainWindow::on_actionLapicero_triggered()//Función de lapicero
{

    clicCounter=0;//Establece el contador de clicks en 0.
    mFuncion = 3;//Establece la variable en 3 que caracteriza a la función lapicero

    editarTrazo();

}

void MainWindow::on_actionFormas_triggered()//Función de creación de formas
{
    mFuncion = 4;//Establece la variable en 4 que caracteriza a la función formas

    forma = QInputDialog::getInt(this, "Tipo de forma","Ingrese la forma que desea agregar. " //Se solicita al usuario ingresar la forma para trabajarla
                                                       "\n1. Cuadrado/Rectángulo"
                                                       "\n2.Triángulo", 1,1,2);


    if(forma == 1){
        lado1 = QInputDialog::getInt(this, "Lado vertical","Ingrese el valor del lado vertical",50,10,200);//Se solicita al usuario ingresar el lado vertical
        lado2 = QInputDialog::getInt(this, "Lado horizontal","Ingrese el valor del lado horizontal",50,10,200);//Se solicita al usuario ingresar el lado horizontal

    }
    else if (forma ==2){
        lado1 = QInputDialog::getInt(this, "Base del triángulo","Ingrese la base del triángulo",50,10,200);//Base del triángulo
        lado2 = QInputDialog::getInt(this, "Alto del triángulo","Ingrese la altura del triángulo",50,10,200);//Altura del triángulo

    }
    editarTrazo();

}

void MainWindow::on_actionColorPicker_triggered()//Función de detectar el color del pixel.
{
    mFuncion = 5;//Establece la variable en 5 que caracteriza a la función colorPIcker

}


void MainWindow::on_actionRellenar_triggered()//Funcion de rellenar
{
    mSize=1;
    mFuncion = 6;//Establece la variable en 6 que caracteriza a la función rellenar

}

void MainWindow::on_actionAcercar_triggered()//Función de acercar
{

}


void MainWindow::on_actionAlejar_triggered()//Función de alejar
{

}





void MainWindow::on_actionAbrir_triggered()//Funcion que abre una imagen
{

    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir archivo"), QDir::currentPath());//Acceder al archivo seleccionado.
    if(!fileName.isEmpty()){
        mImage = new QImage(mAncho,mAlto,QImage::Format_ARGB32_Premultiplied);//Creación de la imagen
        mImage->load(fileName);//Cargar la imagen

        //Se establece el ancho y el alto de la imagen en  las variables enteras
        mAncho = mImage->width();
        mAlto = mImage->height();

        mPainter = new QPainter(mImage);
    }


}


void MainWindow::on_actionGuardar_como_triggered()//Función que guarda el canvas agregando un nombre
{


    QByteArray imageData;//Creación de un ByteArray
    QBuffer buffer(&imageData);//Creación de un buffer

    buffer.open(QIODevice::WriteOnly);

    mImage->save(&buffer,"PNG");//Función que guarda la imagen (predeterminado para png)


    QFileDialog::saveFileContent(imageData);//Función que guarda la imagen


}

void MainWindow::on_actionRotarCanvas_triggered()
{

    int angulo = 45;

    QImage rota = mImage->transformed(QTransform().rotate(angulo));//Se rota la imagen un angulo de 45 grados.

    update();
}



void MainWindow::on_actionAlicarFIltro_triggered()//FUncion de aplicar filtro
{

    int filter = QInputDialog::getInt(this, "Filtro de imagen", "Ingrese el filtro que desea aplicar a la imagen"
                                                                "\n1. Escala de Grises"
                                                                "\n2. Filtro negativo"
                                                                "\n3. Filtro sepia"
                                                                "\n4. Obscurecer "
                                                                "\n5. Aclarar ",1,1,5);



    Filtro(filter);//Llamada al método que aplica el filtro a la imagen.
}


void MainWindow::Filtro(int filterType){//Función que aplica los filtros

    //Inicialización de variables
    //Variables que se obtienen del valor entero de un pixel
    int red;
    int green;
    int blue;

    //Variables que calculan las operaciones para aplicar los filtros
    float grayscale;
    float redscale;
    float bluescale;
    float greenscale;

    if(filterType==1){//Aplicar filtro de escalas de grises.

        for(int x = 0; x<=mAncho-1;x++){//Filas
            for (int y =0 ; y<=mAlto-1;y++){//Columnas

                red = mImage->pixelColor(x,y).red();//Obtiene el valor R del pixel seleccionado
                green = mImage->pixelColor(x,y).green();//Obtiene el valor G del pixel seleccionado
                blue = mImage->pixelColor(x,y).blue();//Obtiene el valor B del pixel seleccionado

                grayscale = 0.3*red+0.59*green+0.11*blue; //Aplica la formula de escala de grises

                mColor = QColor(grayscale,grayscale,grayscale);//Cambia el color de la variable mColor de acuerdo a sus escalas de gris

                QPen pen(mColor);//Creación de un pincel para cambiar el pixel
                pen.setWidth(1);//Tamaño del pincel
                mPainter->setPen(pen);//Asignación del pincel para el mPainter.


                pen.color()=mColor;//Asignación del color del pincel
                mPainter->drawPoint(x,y);//Se realiza el cambio en el color del pixel establecido
                update();//Actualizar el canvas.
            }
        }


    }
    else if (filterType ==2){//Aplicar filtro negativo
        for(int x = 0; x<=mAncho-1;x++){
            for (int y =0 ; y<=mAlto-1;y++){

                //Obtención de valores rgb
                red = mImage->pixelColor(x,y).red();
                green = mImage->pixelColor(x,y).green();
                blue = mImage->pixelColor(x,y).blue();

                //Operación de invertir el color
                redscale =   255 - red;
                greenscale = 255 - green;
                bluescale =  255 - blue;

                mColor=QColor(redscale,greenscale,bluescale);//Asignación de color a la variable mColor

                QPen pen(mColor);
                pen.setWidth(1);
                mPainter->setPen(pen);


                pen.color()=mColor;//Asignación del color del pincel
                mPainter->drawPoint(x,y);//Se realiza el cambio en el color del pixel establecido
                update();
            }
        }

    }
    else if(filterType == 3){// Filtro Sepia

        for(int x = 0; x<=mAncho-1;x++){
            for (int y =0 ; y<=mAlto-1;y++){

                //Obtención de valores rgb
                red = mImage->pixelColor(x,y).red();
                green = mImage->pixelColor(x,y).green();
                blue = mImage->pixelColor(x,y).blue();

                //Operación de establecer el filtro sepia.
                redscale=    red*.393 + green*.769 + blue*.189;
                greenscale = red*.349 + green*.686 + blue*.168;
                bluescale =  red*.272 + green*.534 + blue*.131;

                mColor = QColor(redscale,greenscale,bluescale);//Asignación de color a la variable mColor

                QPen pen(mColor);
                pen.setWidth(1);
                mPainter->setPen(pen);


                pen.color()=mColor;//Asignación del color del pincel
                mPainter->drawPoint(x,y);//Se realiza el cambio en el color del pixel establecido
                update();

            }
        }
    }
    else if(filterType==4){//Filtro oscurecer

        for(int x = 0; x<=mAncho-1;x++){
            for (int y =0 ; y<=mAlto-1;y++){

                //Obtención de valores rgb
                red = mImage->pixelColor(x,y).red();
                green = mImage->pixelColor(x,y).green();
                blue = mImage->pixelColor(x,y).blue();

                //Operación de establecer el filtro oscurecer.
                redscale=    red*.5;
                greenscale = green*.5;
                bluescale =  blue*.5;

                mColor = QColor(redscale,greenscale,bluescale);//Asignación de color a la variable mColor

                QPen pen(mColor);
                pen.setWidth(1);
                mPainter->setPen(pen);


                pen.color()=mColor;//Asignación del color del pincel
                mPainter->drawPoint(x,y);//Se realiza el cambio en el color del pixel establecido
                update();
            }
        }
    }
    else{//Filtro aclarar

        for(int x = 0; x<=mAncho-1;x++){
            for (int y =0 ; y<=mAlto-1;y++){

                //Obtención de valores rgb
                red = mImage->pixelColor(x,y).red();
                green = mImage->pixelColor(x,y).green();
                blue = mImage->pixelColor(x,y).blue();

                //Operación de establecer el filtro aclarar.
                redscale=    red*1.5;
                greenscale = green*1.5;
                bluescale =  blue*1.5;

                mColor = QColor(redscale,greenscale,bluescale);//Asignación de color a la variable mColor

                QPen pen(mColor);
                pen.setWidth(1);
                mPainter->setPen(pen);


                pen.color()=mColor;//Asignación del color del pincel
                mPainter->drawPoint(x,y);//Se realiza el cambio en el color del pixel establecido
                update();

            }
        }

    }

}

void MainWindow::editarTrazo(){//Función que solicita al usuario ingresar el color y el tamaño del trazo

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
    //Asignación de colores con respecto a sus entradas
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

void MainWindow::trazaLinea(int x1,int y1,int x2,int y2){//Función de trazar línea recta

    //Diferencia entre los valores final e inicial de x y de y
    float deltax = x2-x1;
    float deltay = y2-y1;

    //Variables que contienen la posición x y y.
    int posx1 = x1;
    int posx2 = x2;
    int posy1 = y1;
    int posy2 = y2;


    int coordy =0;//Función lineal

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

        if(x1<x2){//Cuando el primer x es menor que el segundo

            float pendiente = deltay/deltax;//Pendiente de la curva


            for(float x=posx1;x<=round(posx2);x+=0.01){//Ciclo que aplica la función lineal
                coordy = round(pendiente*(x-posx1))+posy1;//Fórmula de la función lineal
                mPainter->drawPoint(abs(x),abs(coordy));//Dibujar el punto en una coordenada determinada por el punto x y la función lineal coordy
            }//end for

        }//End if

        else{//Cuando el primer x es mayor que el segundo

            float pendiente = deltay/deltax;//Pendiente de la curva


            for(float x=posx2;x<=round(posx1);x+=0.01){
                coordy = round(pendiente*(x-posx1))+posy1;
                mPainter->drawPoint(abs(x),abs(coordy));
            }//end for

        }

    }
}









