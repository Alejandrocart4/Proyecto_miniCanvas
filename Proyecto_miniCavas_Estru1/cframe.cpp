#include "cframe.h"
#include "ui_cframe.h"
#include "qmessagebox.h"
#include "loginmanager.h"

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    ui->btnsalir->setStyleSheet("background-color: rgba(0,0,0,0); border: none;");
    ui->btn_registrar->setStyleSheet("background-color: rgba(0,0,0,0); border: none; color: blue; text-decoration: underline;");
    ui->btn_registrar->setCursor(Qt::PointingHandCursor);

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

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


    if (respuesta == QMessageBox::Yes) {
        QApplication::quit();
    }
}


void cframe::on_btn_Login_clicked()
{
    QString usuario = ui->lineEditUsuario->text();
    QString password = ui->lineEditPassword->text();


    LoginManager loginManager("usuarios.bin");

    Usuario usuarioAutenticado = loginManager.autenticarUsuario(usuario, password);




    QString tipoUsuario = usuarioAutenticado.getTipoUsuario();
    QString nombreCompleto = usuarioAutenticado.getNombre() + " " + usuarioAutenticado.getApellido();

    // Mostrar mensaje de bienvenida



    if (tipoUsuario == "Registro") {
         QMessageBox::information(this, "Bienvenido", "¡Bienvenido, " + nombreCompleto + "!");
        ui->stackedWidget->setCurrentIndex(1); // Ir a ventana de Registro
    } else if (tipoUsuario == "Maestro") {
         QMessageBox::information(this, "Bienvenido", "¡Bienvenido, " + nombreCompleto + "!");
        ui->stackedWidget->setCurrentIndex(2); // Ir a ventana de Maestro
    } else if (tipoUsuario == "Alumno") {
         QMessageBox::information(this, "Bienvenido", "¡Bienvenido, " + nombreCompleto + "!");
        ui->stackedWidget->setCurrentIndex(3); // Ir a ventana de Alumno
    } else     if (usuario.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Debe de llenar todos los espacios.");
        return;
    } else{
        QMessageBox::warning(this, "Error", "El usuario no ha sido registrado. Pida a REGISTRO que le cree una cuenta.");
        return;
    }

}


void cframe::on_btn_registrar_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void cframe::on_btn_CrearUsuario_clicked()
{

    QString usuario = ui->lineEditNuevoUsuario->text();
    QString password = ui->lineEditNuevoPassword->text();
    QString confirmarPassword = ui->lineEditConfirmarPassword->text();
    QString tipoUsuario = ui->comboBoxTipoUsuario->currentText();
    QString nombre = ui->lineEditNombre->text();
    QString apellido = ui->lineEditApellido->text();

    if (usuario.isEmpty() || password.isEmpty() || confirmarPassword.isEmpty() || tipoUsuario.isEmpty() || nombre.isEmpty() || apellido.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    if (password != confirmarPassword) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    Usuario nuevoUsuario(usuario, password, tipoUsuario, nombre, apellido);

    LoginManager loginManager("usuarios.bin");
    if (loginManager.registrarUsuario(nuevoUsuario)) {
        QMessageBox::information(this, "Éxito", "Usuario creado exitosamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo crear el usuario.");
    }

    ui->lineEditNuevoUsuario->clear();
    ui->lineEditNuevoPassword->clear();
    ui->lineEditConfirmarPassword->clear();
    ui->comboBoxTipoUsuario->setCurrentIndex(0);
    ui->lineEditNombre->clear();
    ui->lineEditApellido->clear();

}


void cframe::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->lineEditUsuario->clear();
    ui->lineEditPassword->clear();
    ui->lineEditNuevoUsuario->clear();
    ui->lineEditNuevoPassword->clear();
    ui->lineEditConfirmarPassword->clear();
    ui->comboBoxTipoUsuario->setCurrentIndex(0);
    ui->lineEditNombre->clear();
    ui->lineEditApellido->clear();
}


void cframe::on_btnVerPasswordLogin_clicked()
{
    passwordVisibleLogin = !passwordVisibleLogin;
    ui->lineEditPassword->setEchoMode(passwordVisibleLogin ? QLineEdit::Normal : QLineEdit::Password);

    // Cambiar icono del botón
     ui->btnVerPasswordLogin->setIcon(QIcon(passwordVisibleLogin ? ":/Imagenes/showpassword.png" : ":/Imagenes/ocultarcontra.png"));
}

