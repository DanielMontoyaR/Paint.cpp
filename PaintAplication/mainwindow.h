#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPainter;
class QImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

private slots:

    //Creación de funciones llamadas al seleccionarlas en la interfaz
    void on_actionAdd_file_triggered();

    void on_actionAbrir_triggered();

    void on_actionGuardar_triggered();

    void on_actionGuardar_como_triggered();

    void on_actionSeleccionar_Tamano_triggered();

    void on_actionAcercar_triggered();

    void on_actionAlejar_triggered();

    void on_actionLapiz_triggered();

    void on_actionLapicero_triggered();

    void on_actionBorrador_triggered();

    void on_actionFormas_triggered();

    void on_actionRellenar_triggered();

    void on_actionColorPicker_triggered();

    //Creación de funciones para las distintas características de trazado.

    void editarTrazo();//Solicita al usuario ingresar el color y tamaño del trazo a utilizar

    void trazaLinea(int x1,int y1,int x2,int y2);//Función par trazar la línea recta

    void floodfill(int x, int y, QColor new_color);



private:
    Ui::MainWindow *ui;//Interfaz de usuario.
    QPainter *mPainter; //Pincel
    QImage *mImage; //Imagen
    QImage *mImage2;//Imagen importada
    QPoint mClick;//Coordenada de click
    QPoint mBegin;// Coordena de click primaria
    QPoint mEnd; //Coordenada de click secundaria
    QColor mColor; // Color para el editor del canvas
    bool mEnabled; //Estado de activación si se clickea es verdadero sino es falso
    int mSize; //Tamaño del lapiz
    int mAncho; //Ancho del canvas
    int mAlto; //Alto del canvas
    int mFuncion; //Tipo de función a utilizar en el canvas.
    int Color; //Identificador del color para pixeles.
    int matrizCanvas[1900][875];
    int clicCounter;//Contador de clics para la función de lapicero.
    int forma;//Tipo de forma a implementar en el canvas.
    int lado1;//Lado del rectángulo, cuadrado y base del triángulo.
    int lado2;//Lado del rectángulo, cuadrado y alto del triángulo.




};
#endif // MAINWINDOW_H
