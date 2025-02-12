#include "cframe.h"
#include "ui_cframe.h"
#include "qmessagebox.h"
#include "loginmanager.h"
#include "clase.h"
#include "manejadorclases.h"
#include <QList>

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

    ui->lblsueldo->setVisible(false);
    ui->dSb_SueldoMaestroregistro->setVisible(false);
    ui->lblsueldoModificar->setVisible(false);
    ui->dSb_SueldoMaestroModificar->setVisible(false);
    ui->lblProfesionRegistro->setVisible(false);
    ui->lineEditProfesionRegistro->setVisible(false);
    ui->lblCarreraRegistro->setVisible(false);
    ui->lineEditCarreraRegistro->setVisible(false);
    ui->lblProfesionModificar->setVisible(false);
    ui->lineEditProfesionModificar->setVisible(false);
    ui->lblCarreraModificar->setVisible(false);
    ui->lineEditCarreraModificar->setVisible(false);

    // Configurar valores en los ComboBox
    ui->comboBoxSemestre->clear();
    ui->comboBoxSemestre->addItems({"1", "2"});

    ui->comboBoxPeriodo->clear();
    ui->comboBoxPeriodo->addItems({"Ordinario", "Intersemestral"});

    // Configurar los SpinBox
    ui->spinBoxAnio->setRange(2020, 2050);
    ui->spinBoxAnio->setValue(2024);

    ui->spinBoxUV->setRange(1, 10);
    ui->spinBoxUV->setValue(3);

    cargarClasesEnComboBoxModificar();


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

void cframe::on_btn_CrearUsuario_clicked()
{

    QString usuario = ui->lineEditNuevoUsuario->text();
    QString password = ui->lineEditNuevoPassword->text();
    QString confirmarPassword = ui->lineEditConfirmarPassword->text();
    QString tipoUsuario = ui->comboBoxTipoUsuario->currentText();
    QString nombre = ui->lineEditNombre->text();
    QString apellido = ui->lineEditApellido->text();
    QString sueldo = "0.00";
    QString profesion = "";
    QString carrera = "";


    if (tipoUsuario == "Maestro") {
        sueldo = QString::number(ui->dSb_SueldoMaestroregistro->value(), 'f', 2);
        profesion = ui->lineEditProfesionRegistro->text();  // 🔹 Capturar profesión
        qDebug() << "Capturando datos para Maestro - Sueldo: " << sueldo << ", Profesión: " << profesion;
    }
    else if (tipoUsuario == "Alumno") {
        carrera = ui->lineEditCarreraRegistro->text();  // 🔹 Capturar carrera
        qDebug() << "Capturando datos para Alumno - Carrera: " << carrera;
    }

    if (usuario.isEmpty() || password.isEmpty() || confirmarPassword.isEmpty() || tipoUsuario.isEmpty() || nombre.isEmpty() || apellido.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    if (password != confirmarPassword) {
        QMessageBox::warning(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    Usuario nuevoUsuario(usuario, password, tipoUsuario, nombre, apellido, sueldo, profesion, carrera);
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
    ui->dSb_SueldoMaestroregistro->setValue(0.00);
    ui->lineEditProfesionRegistro->clear();
    ui->lineEditCarreraRegistro->clear();

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

void cframe::on_btnBuscarUsuarioEditar_clicked(){
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

    if (usuarioEncontrado.getTipoUsuario() == "Maestro") {
        ui->lblsueldoModificar->setVisible(true);
        ui->dSb_SueldoMaestroModificar->setVisible(true);
        ui->dSb_SueldoMaestroModificar->setValue(usuarioEncontrado.getSueldo().toDouble()); // Asigna sueldo
        ui->lblProfesionModificar->setVisible(true);
        ui->lineEditProfesionModificar->setVisible(true);
        ui->lineEditProfesionModificar->setText(usuarioEncontrado.getProfesion()); // Asigna profesión

        ui->lblCarreraModificar->setVisible(false);
        ui->lineEditCarreraModificar->setVisible(false);
        qDebug() << "Usuario Maestro encontrado. Mostrando sueldo y profesión.";
    }
    else if (usuarioEncontrado.getTipoUsuario() == "Alumno") {
        ui->lblsueldoModificar->setVisible(false);
        ui->dSb_SueldoMaestroModificar->setVisible(false);
        ui->lblProfesionModificar->setVisible(false);
        ui->lineEditProfesionModificar->setVisible(false);

        ui->lblCarreraModificar->setVisible(true);
        ui->lineEditCarreraModificar->setVisible(true);
        ui->lineEditCarreraModificar->setText(usuarioEncontrado.getCarrera()); // Asigna carrera
        qDebug() << "Usuario Alumno encontrado. Mostrando carrera.";
    }
    else {  // Si es tipo "Registro"
        ui->lblsueldoModificar->setVisible(false);
        ui->dSb_SueldoMaestroModificar->setVisible(false);
        ui->lblProfesionModificar->setVisible(false);
        ui->lineEditProfesionModificar->setVisible(false);
        ui->lblCarreraModificar->setVisible(false);
        ui->lineEditCarreraModificar->setVisible(false);
        qDebug() << "Usuario Registro encontrado. Ocultando sueldo, profesión y carrera.";
    }

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
    QString nuevaProfesion = "";
    QString nuevaCarrera = "";

    if (nuevoTipoUsuario == "Maestro") {
        nuevoSueldo = QString::number(ui->dSb_SueldoMaestroModificar->value(), 'f', 2);
        nuevaProfesion = ui->lineEditProfesionModificar->text();  // 🔹 Capturar profesión
        qDebug() << "Capturando datos para Maestro - Sueldo: " << nuevoSueldo << ", Profesión: " << nuevaProfesion;
    }
    else if (nuevoTipoUsuario == "Alumno") {
        nuevaCarrera = ui->lineEditCarreraModificar->text();  // 🔹 Capturar carrera
        qDebug() << "Capturando datos para Alumno - Carrera: " << nuevaCarrera;
    }

    qDebug() << "Intentando modificar el usuario:" << usuarioAnterior << " por " << nuevoUsuario;

    if (nuevoUsuario.isEmpty() || nuevoNombre.isEmpty() || nuevoApellido.isEmpty() || nuevaPassword.isEmpty() ||
        confirmarPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    // Verificar que ambas contraseñas coincidan
    if (nuevaPassword != confirmarPassword) {
        QMessageBox::critical(this, "Error", "Las contraseñas no coinciden.");
        return;
    }

    LoginManager loginManager("usuarios.bin");

    if (loginManager.modificarUsuario(usuarioAnterior, nuevoUsuario, nuevaPassword, nuevoNombre, nuevoApellido,
                                      nuevoTipoUsuario,nuevoSueldo, nuevaProfesion, nuevaCarrera)) {
        QMessageBox::information(this, "Éxito", "Usuario modificado correctamente.");
        usuarioAnterior = nuevoUsuario;  // Actualizar el usuario modificado
        ui->lineEditUsuarioModificar->setText(nuevoUsuario);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar el usuario.");
    }
}

void cframe::on_btnEditarUsuario_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(3);
}

void cframe::on_comboBoxTipoUsuario_activated(int index)
{
    QString tipoUsuario = ui->comboBoxTipoUsuario->itemText(index);

    if (tipoUsuario == "Maestro") {
        ui->lblsueldo->setVisible(true);
        ui->dSb_SueldoMaestroregistro->setVisible(true);
        ui->lblProfesionRegistro->setVisible(true);
        ui->lineEditProfesionRegistro->setVisible(true);

        ui->lblCarreraRegistro->setVisible(false);
        ui->lineEditCarreraRegistro->setVisible(false);
    }
    else if (tipoUsuario == "Alumno") {
        ui->lblsueldo->setVisible(false);
        ui->dSb_SueldoMaestroregistro->setVisible(false);
        ui->lblProfesionRegistro->setVisible(false);
        ui->lineEditProfesionRegistro->setVisible(false);

        ui->lblCarreraRegistro->setVisible(true);
        ui->lineEditCarreraRegistro->setVisible(true);
    }
    else {  // Si es tipo "Registro"
        ui->lblsueldo->setVisible(false);
        ui->dSb_SueldoMaestroregistro->setVisible(false);
        ui->lblProfesionRegistro->setVisible(false);
        ui->lineEditProfesionRegistro->setVisible(false);
        ui->lblCarreraRegistro->setVisible(false);
        ui->lineEditCarreraRegistro->setVisible(false);
    }
}

void cframe::on_comboBoxTipoUsuarioModificar_activated(int index)
{
    QString tipoUsuario = ui->comboBoxTipoUsuarioModificar->itemText(index);

    if (tipoUsuario == "Maestro") {
        ui->lblsueldoModificar->setVisible(true);
        ui->dSb_SueldoMaestroModificar->setVisible(true);
        ui->lblProfesionModificar->setVisible(true);
        ui->lineEditProfesionModificar->setVisible(true);

        ui->lblCarreraModificar->setVisible(false);
        ui->lineEditCarreraModificar->setVisible(false);
    }
    else if (tipoUsuario == "Alumno") {
        ui->lblsueldoModificar->setVisible(false);
        ui->dSb_SueldoMaestroModificar->setVisible(false);
        ui->lblProfesionModificar->setVisible(false);
        ui->lineEditProfesionModificar->setVisible(false);

        ui->lblCarreraModificar->setVisible(true);
        ui->lineEditCarreraModificar->setVisible(true);
    }
    else {  // Si es tipo "Registro"
        ui->lblsueldoModificar->setVisible(false);
        ui->dSb_SueldoMaestroModificar->setVisible(false);
        ui->lblProfesionModificar->setVisible(false);
        ui->lineEditProfesionModificar->setVisible(false);
        ui->lblCarreraModificar->setVisible(false);
        ui->lineEditCarreraModificar->setVisible(false);
    }

}

void cframe::on_pushButton_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(4);
}

void cframe::on_btnCrearClase_clicked()
{
    QString id = ui->lineEditIDClase->text();
    QString nombre = ui->lineEditNombreClase->text();
    QString hora = ui->timeEditHoraClase->time().toString("HH:mm");
    int unidadesValorativas = ui->spinBoxUV->value();
    int semestre = ui->comboBoxSemestre->currentText().toInt();
    //QString periodo = ui->comboBoxPeriodo->currentText();
    int año = ui->spinBoxAnio->value();

    int periodo = (ui->comboBoxPeriodo->currentText() == "Ordinario") ? 1 : 2;

    if (id.isEmpty() || nombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }


    Clase nuevaClase(id, nombre, hora, unidadesValorativas, semestre, periodo, año);
    ManejadorClases manejador("clases.bin");

    if (manejador.agregarClase(nuevaClase)) {
        QMessageBox::information(this, "Éxito", "Clase creada exitosamente.");
        // Limpiar los campos después de registrar
        ui->lineEditIDClase->clear();
        ui->lineEditNombreClase->clear();
        ui->timeEditHoraClase->setTime(QTime(8, 0));
        ui->spinBoxUV->setValue(3);
        ui->comboBoxSemestre->setCurrentIndex(0);
        ui->comboBoxPeriodo->setCurrentIndex(0);
        ui->spinBoxAnio->setValue(2024);
    } else {
        QMessageBox::critical(this, "Error", "No se pudo crear la clase.");
    }
}

void cframe::cargarClasesEnComboBoxModificar() {
    ui->comboBoxBuscarClase->clear();  // Limpiar comboBox

    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    for (const Clase &clase : listaClases) {
        ui->comboBoxBuscarClase->addItem(clase.getID());  // Agregar ID de la clase
    }

    if (listaClases.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "No hay clases disponibles para modificar.");
    }
}

void cframe::on_btnGuardarCambiosClase_clicked() {
    QString nuevoID = ui->lineEditIDClaseModificar->text();
    QString nuevoNombre = ui->lineEditNombreClaseModificar->text();
    QString nuevaHora = ui->timeEditHoraClaseModificar->time().toString("HH:mm");
    int nuevasUV = ui->spinBoxUVModificar->value();
    int nuevoSemestre = ui->comboBoxSemestreModificar->currentIndex() + 1;
    int nuevoPeriodo = (ui->comboBoxPeriodoModificar->currentIndex() == 0) ? 1 : 2;
    int nuevoAño = ui->spinBoxAnioModificar->value();

    if (nuevoID.isEmpty() || nuevoNombre.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    Clase nuevaClase(nuevoID, nuevoNombre, nuevaHora, nuevasUV, nuevoSemestre, nuevoPeriodo, nuevoAño);
    ManejadorClases manejador("clases.bin");

    bool exito = manejador.modificarClase(idClaseAnterior, nuevaClase);

    if (exito) {
        QMessageBox::information(this, "Éxito", "Clase modificada correctamente.");
        cargarClasesEnComboBoxModificar();  // 🔄 Recargar el ComboBox con los datos actualizados
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar la clase.");
    }
}

void cframe::on_pushButton_5_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(5);
}

void cframe::on_btnBuscarClaseModificar_clicked()
{
    QString idClaseBuscada = ui->comboBoxBuscarClase->currentText();
    if (idClaseBuscada.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase para modificar.");
        return;
    }

    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    for (const Clase &clase : listaClases) {
        if (clase.getID() == idClaseBuscada) {
            // Guardar ID anterior por si se modifica
            idClaseAnterior = clase.getID();

            // Llenar los campos con los datos actuales de la clase
            ui->lineEditIDClaseModificar->setText(clase.getID());
            ui->lineEditNombreClaseModificar->setText(clase.getNombre());
            ui->timeEditHoraClaseModificar->setTime(QTime::fromString(clase.getHora(), "HH:mm"));
            ui->spinBoxUVModificar->setValue(clase.getUnidadesValorativas());
            ui->comboBoxSemestreModificar->setCurrentIndex(clase.getSemestre() - 1);
            ui->comboBoxPeriodoModificar->setCurrentIndex(clase.getPeriodo() == 1 ? 0 : 1);
            ui->spinBoxAnioModificar->setValue(clase.getAño());

            qDebug() << "Clase cargada para modificar: " << clase.getID();
            return;
        }
    }

    QMessageBox::warning(this, "Error", "No se encontró la clase.");
}

