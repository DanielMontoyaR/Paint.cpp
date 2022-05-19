#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    QPainter *mPainter; //Pincel
    QImage *mImage; //Imagen
    QPoint mBegin;// Inicio
    QPoint mEnd; //FIn
    QColor mColor; // color
    bool mEnabled; //Estado de activación
    int mSize; //Tamaño


};
#endif // MAINWINDOW_H
