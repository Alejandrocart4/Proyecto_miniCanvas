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
    ui->tableClasesUsuario->setVisible(false);

    ui->btnsalir->setStyleSheet("background-color: rgba(0,0,0,0); border: none;");
    ui->btn_registrar->setStyleSheet("background-color: rgba(0,0,0,0); border: none; color: blue; text-decoration: underline;");
    ui->btn_registrar->setCursor(Qt::PointingHandCursor);

    ui->lineEditPassword->setEchoMode(QLineEdit::Password);

    ui->comboBoxTipoUsuarioModificar->addItem("Alumno");
    ui->comboBoxTipoUsuarioModificar->addItem("Maestro");
    ui->comboBoxTipoUsuarioModificar->addItem("Registro");

    ui->lineEditUsuarioModificar->setReadOnly(false);

    ui->spinBoxSueldoNuevo->setVisible(false);
    ui->lblSueldo->setVisible(false);
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

void cframe::on_comboBoxTipoUsuario_currentIndexChanged(int index)
{
    QString tipoUsuario = ui->comboBoxTipoUsuario->currentText();

    // Si el usuario es "Maestro", mostrar el sueldo
    if (tipoUsuario == "Maestro") {
        ui->spinBoxSueldoNuevo->setVisible(true);
        ui->lblSueldo->setVisible(true);
    } else {
        ui->spinBoxSueldoNuevo->setVisible(false);
    }
}

void cframe::on_btn_CrearUsuario_clicked()
{

    QString usuario = ui->lineEditNuevoUsuario->text();
    QString password = ui->lineEditNuevoPassword->text();
    QString confirmarPassword = ui->lineEditConfirmarPassword->text();
    QString tipoUsuario = ui->comboBoxTipoUsuario->currentText();
    QString nombre = ui->lineEditNombre->text();
    QString apellido = ui->lineEditApellido->text();
    QString sueldo = "0.00";
    QList<QString> clases;

    if (usuario.isEmpty() || password.isEmpty() || confirmarPassword.isEmpty() || tipoUsuario.isEmpty() || nombre.isEmpty() || apellido.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    if (password != confirmarPassword) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    Usuario nuevoUsuario(usuario, password, tipoUsuario, nombre, apellido, sueldo, clases);

    LoginManager loginManager("usuarios.bin");
    if (loginManager.registrarUsuario(nuevoUsuario, sueldo, clases)) {
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
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmación", "¿Seguro que quieres salir?",
                                      QMessageBox::Yes | QMessageBox::No);


    if (respuesta == QMessageBox::Yes) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->lineEditUsuario->clear();
        ui->lineEditPassword->clear();
        ui->lineEditNuevoUsuario->clear();
        ui->lineEditNuevoPassword->clear();
        ui->lineEditConfirmarPassword->clear();
        ui->comboBoxTipoUsuario->setCurrentIndex(0);
        ui->lineEditNombre->clear();
        ui->lineEditApellido->clear();
        ui->stackedWidget_2->setCurrentIndex(0);
    }
    }

void cframe::on_btnVerPasswordLogin_clicked()
{
    passwordVisibleLogin = !passwordVisibleLogin;
    ui->lineEditPassword->setEchoMode(passwordVisibleLogin ? QLineEdit::Normal : QLineEdit::Password);

    // Cambiar icono del botón
     ui->btnVerPasswordLogin->setIcon(QIcon(passwordVisibleLogin ? ":/Imagenes/showpassword.png" : ":/Imagenes/ocultarcontra.png"));
}

void cframe::on_pushButton_3_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
}

void cframe::on_btnBuscarUsuario_clicked()
{
    QString usuarioBuscado = ui->lineEditBuscarUsuario->text();
    if (usuarioBuscado.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un usuario.");
        return;
    }

    LoginManager loginManager("usuarios.bin");
    Usuario usuarioEncontrado = loginManager.autenticarUsuario(usuarioBuscado, "");

    if (usuarioEncontrado.getUsuario().isEmpty()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
        return;
    }

    ui->lblNombreUsuario->setText(usuarioEncontrado.getNombre());
    ui->lblApellidoUsuario->setText(usuarioEncontrado.getApellido());

    ui->tableClasesUsuario->clear();
    ui->tableClasesUsuario->setRowCount(0);

    if (usuarioEncontrado.getTipoUsuario() == "Registro") {
        mostrarTablaClases(false);
    } else {
        QList<QString> clases = loginManager.obtenerClasesUsuario(usuarioBuscado);
        for (const QString &clase : clases) {
            int row = ui->tableClasesUsuario->rowCount();
            ui->tableClasesUsuario->insertRow(row);
            ui->tableClasesUsuario->setItem(row, 0, new QTableWidgetItem(clase));
        }
        mostrarTablaClases(true);
    }
}

void cframe::mostrarTablaClases(bool visible)
{
    ui->tableClasesUsuario->setVisible(visible);
}

void cframe::on_pushButton_8_clicked()
{
    QString usuario = ui->lineEditBuscarUsuario->text();
    if (usuario.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un usuario a eliminar.");
        return;
    }

    LoginManager loginManager("usuarios.bin");
    Usuario usuarioEncontrado = loginManager.autenticarUsuario(usuario, "");

    if (usuarioEncontrado.getUsuario().isEmpty()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
        return;
    }

    QString advertencia = "¿Está seguro de que desea eliminar este usuario?";
    if (usuarioEncontrado.getTipoUsuario() != "Registro") {
        advertencia += "\nSe perderán las clases asignadas a este usuario.";
    }

    QMessageBox::StandardButton confirmacion;
    confirmacion = QMessageBox::warning(this, "Confirmación", advertencia, QMessageBox::Yes | QMessageBox::No);

    if (confirmacion == QMessageBox::Yes) {
        if (loginManager.eliminarUsuario(usuario)) {
            QMessageBox::information(this, "Éxito", "Usuario eliminado correctamente.");
            ui->lineEditBuscarUsuario->clear();
            ui->lblNombreUsuario->clear();
            ui->lblApellidoUsuario->clear();
            ui->tableClasesUsuario->clear();
            ui->tableClasesUsuario->setRowCount(0);
            mostrarTablaClases(false);
        } else {
            QMessageBox::critical(this, "Error", "No se pudo eliminar el usuario.");
        }
    }
}


void cframe::on_pushButton_4_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
}



void cframe::on_btnBuscarUsuarioEditar_clicked()
{
    QString usuarioBuscado = ui->lineEditBuscarUsuarioEditar->text(); // Obtener usuario ingresado en la búsqueda
    if (usuarioBuscado.isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingrese un usuario para buscar.");
        return;
    }

    LoginManager loginManager("usuarios.bin");
    Usuario usuarioEncontrado = loginManager.autenticarUsuario(usuarioBuscado, "");

    if (usuarioEncontrado.getUsuario().isEmpty()) {
        QMessageBox::warning(this, "Error", "Usuario no encontrado.");
        return;
    }


    usuarioAnterior = usuarioEncontrado.getUsuario();


    ui->lineEditUsuarioModificar->setText(usuarioEncontrado.getUsuario());
    ui->lineEditUsuarioModificar->setReadOnly(false);


    ui->lineEditNombreModificar->setText(usuarioEncontrado.getNombre());
    ui->lineEditApellidoModificar->setText(usuarioEncontrado.getApellido());
    ui->lineEditNuevaPasswordModificar->setText(usuarioEncontrado.getPassword());
    ui->lineEditConfirmarPasswordModificar->clear();


    int index = ui->comboBoxTipoUsuarioModificar->findText(usuarioEncontrado.getTipoUsuario());
    if (index != -1) {
        ui->comboBoxTipoUsuarioModificar->setCurrentIndex(index);
    }

    qDebug() << "Usuario a modificar encontrado:" << usuarioAnterior;
}

void cframe::setUsuarioActivo(const QString &usuario)
{
    usuarioActivo = usuario;
    ui->lineEditUsuarioModificar->setText(usuario);
}


void cframe::on_btnGuardarCambioUsuario_clicked()
{
    QString nuevoUsuario = ui->lineEditUsuarioModificar->text();
    QString nuevoNombre = ui->lineEditNombreModificar->text();
    QString nuevoApellido = ui->lineEditApellidoModificar->text();
    QString nuevaPassword = ui->lineEditNuevaPasswordModificar->text();
    QString confirmarPassword = ui->lineEditConfirmarPasswordModificar->text();
    QString nuevoTipoUsuario = ui->comboBoxTipoUsuarioModificar->currentText();
    QString nuevoSueldo = "0.00";
    QList<QString> nuevasClases;


    qDebug() << "Intentando modificar el usuario:" << usuarioAnterior << " por " << nuevoUsuario;

    /*if (nuevoTipoUsuario == "Maestro") {
        nuevoSueldo = QString::number(ui->spinBoxSueldoModificar->value(), 'f', 2);
        if (nuevoSueldo.toDouble() <= 0) {
            QMessageBox::warning(this, "Error", "Debe ingresar un sueldo válido para el maestro.");
            return;
        }
    }*/

    if (nuevoUsuario.isEmpty() || nuevoNombre.isEmpty() || nuevoApellido.isEmpty() || nuevaPassword.isEmpty() || confirmarPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    // Verificar que ambas contraseñas coincidan
    if (nuevaPassword != confirmarPassword) {
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    /*for (int i = 0; i < ui->listWidgetClasesModificar->count(); ++i) {
        nuevasClases.append(ui->listWidgetClasesModificar->item(i)->text());
    }*/

    LoginManager loginManager("usuarios.bin");

    if (loginManager.modificarUsuario(usuarioAnterior, nuevoUsuario, nuevaPassword, nuevoNombre, nuevoApellido, nuevoTipoUsuario, nuevoSueldo, nuevasClases)) {
        QMessageBox::information(this, "Éxito", "Usuario modificado correctamente.");
        usuarioAnterior = nuevoUsuario;  // Actualizar el usuario modificado
        ui->lineEditUsuarioModificar->setText(nuevoUsuario);
        //ui->spinBoxSueldoModificar->setValue(nuevoSueldo.toDouble());
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar el usuario.");
    }
}


void cframe::on_btnEditarUsuario_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

