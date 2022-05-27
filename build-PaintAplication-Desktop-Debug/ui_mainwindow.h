/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd_file;
    QAction *actionAbrir;
    QAction *actionGuardar;
    QAction *actionGuardar_como;
    QAction *actionSeleccionar_Tamano;
    QAction *actionAcercar;
    QAction *actionAlejar;
    QAction *actionLapiz;
    QAction *actionLapicero;
    QAction *actionBorrador;
    QAction *actionFormas;
    QAction *actionRellenar;
    QAction *actionColorPicker;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuCanvas;
    QMenu *menuTrazo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(876, 466);
        actionAdd_file = new QAction(MainWindow);
        actionAdd_file->setObjectName(QString::fromUtf8("actionAdd_file"));
        actionAbrir = new QAction(MainWindow);
        actionAbrir->setObjectName(QString::fromUtf8("actionAbrir"));
        actionGuardar = new QAction(MainWindow);
        actionGuardar->setObjectName(QString::fromUtf8("actionGuardar"));
        actionGuardar_como = new QAction(MainWindow);
        actionGuardar_como->setObjectName(QString::fromUtf8("actionGuardar_como"));
        actionSeleccionar_Tamano = new QAction(MainWindow);
        actionSeleccionar_Tamano->setObjectName(QString::fromUtf8("actionSeleccionar_Tamano"));
        actionAcercar = new QAction(MainWindow);
        actionAcercar->setObjectName(QString::fromUtf8("actionAcercar"));
        actionAlejar = new QAction(MainWindow);
        actionAlejar->setObjectName(QString::fromUtf8("actionAlejar"));
        actionLapiz = new QAction(MainWindow);
        actionLapiz->setObjectName(QString::fromUtf8("actionLapiz"));
        actionLapicero = new QAction(MainWindow);
        actionLapicero->setObjectName(QString::fromUtf8("actionLapicero"));
        actionBorrador = new QAction(MainWindow);
        actionBorrador->setObjectName(QString::fromUtf8("actionBorrador"));
        actionFormas = new QAction(MainWindow);
        actionFormas->setObjectName(QString::fromUtf8("actionFormas"));
        actionRellenar = new QAction(MainWindow);
        actionRellenar->setObjectName(QString::fromUtf8("actionRellenar"));
        actionColorPicker = new QAction(MainWindow);
        actionColorPicker->setObjectName(QString::fromUtf8("actionColorPicker"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 876, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCanvas = new QMenu(menubar);
        menuCanvas->setObjectName(QString::fromUtf8("menuCanvas"));
        menuTrazo = new QMenu(menubar);
        menuTrazo->setObjectName(QString::fromUtf8("menuTrazo"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuCanvas->menuAction());
        menubar->addAction(menuTrazo->menuAction());
        menuFile->addAction(actionAdd_file);
        menuFile->addAction(actionAbrir);
        menuFile->addAction(actionGuardar);
        menuFile->addAction(actionGuardar_como);
        menuCanvas->addAction(actionSeleccionar_Tamano);
        menuCanvas->addAction(actionAcercar);
        menuCanvas->addAction(actionAlejar);
        menuTrazo->addAction(actionLapiz);
        menuTrazo->addAction(actionLapicero);
        menuTrazo->addAction(actionBorrador);
        menuTrazo->addAction(actionFormas);
        menuTrazo->addAction(actionRellenar);
        menuTrazo->addAction(actionColorPicker);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionAdd_file->setText(QCoreApplication::translate("MainWindow", "Cerrar", nullptr));
        actionAbrir->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        actionGuardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        actionGuardar_como->setText(QCoreApplication::translate("MainWindow", "Guardar como", nullptr));
        actionSeleccionar_Tamano->setText(QCoreApplication::translate("MainWindow", "Seleccionar Tama\303\261o", nullptr));
        actionAcercar->setText(QCoreApplication::translate("MainWindow", "Acercar ", nullptr));
        actionAlejar->setText(QCoreApplication::translate("MainWindow", "Alejar ", nullptr));
        actionLapiz->setText(QCoreApplication::translate("MainWindow", "Lapiz", nullptr));
        actionLapicero->setText(QCoreApplication::translate("MainWindow", "Lapicero", nullptr));
        actionBorrador->setText(QCoreApplication::translate("MainWindow", "Borrador", nullptr));
        actionFormas->setText(QCoreApplication::translate("MainWindow", "Formas", nullptr));
        actionRellenar->setText(QCoreApplication::translate("MainWindow", "Rellenar", nullptr));
        actionColorPicker->setText(QCoreApplication::translate("MainWindow", "ColorPicker", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "Archivo", nullptr));
        menuCanvas->setTitle(QCoreApplication::translate("MainWindow", "Canvas", nullptr));
        menuTrazo->setTitle(QCoreApplication::translate("MainWindow", "Trazo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
