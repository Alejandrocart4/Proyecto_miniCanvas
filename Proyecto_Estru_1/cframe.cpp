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

    // Conectar el clic del botón a una función
    //connect(ui->btnsalir, &QPushButton::clicked, this, &MainWindow::onBotonInvisibleClickeado);

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

