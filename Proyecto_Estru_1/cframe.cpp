#include "cframe.h"
#include "ui_cframe.h"
#include "qmessagebox.h"

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    ui->btnsalir->setStyleSheet("background-color: rgba(0,0,0,0); border: none;");
    ui->btn_registrar->setStyleSheet("background-color: rgba(0,0,0,0); border: none; color: blue; text-decoration: underline;");
    ui->btn_registrar->setCursor(Qt::PointingHandCursor);


}

cframe::~cframe()
{
    delete ui;
}






void cframe::on_btnsalir_clicked()
{
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmación", "¿Seguro que quieres salir?",
                                      QMessageBox::Yes | QMessageBox::No);

    // Si el usuario presiona "Sí", se cierra la ventana
    if (respuesta == QMessageBox::Yes) {
       QApplication::quit();
    }
}

