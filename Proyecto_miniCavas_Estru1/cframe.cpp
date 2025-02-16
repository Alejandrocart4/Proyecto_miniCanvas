#include "cframe.h"
#include "ui_cframe.h"
#include "qmessagebox.h"
#include "loginmanager.h"
#include "clase.h"
#include "manejadorclases.h"
#include "manejadorexamenes.h"
#include <QList>
#include <QComboBox>
#include "examen.h"

cframe::cframe(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::cframe)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    ui->tableClasesUsuario->setVisible(false);

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
    cargarClasesEnComboBoxAsignarMaestro();
    cargarMaestrosEnComboBox();
    cargarClasesEnComboBoxMatricularAlumno();
    //cargarAlumnosDisponibles();
    cargarAlumnosMatriculados();

    debugMostrarUsuarios();
    debugMostrarAlumnosMatriculados();

    cargarClasesEnComboBoxEliminar();
    cargarClasesEnComboBoxMatricularAlumno();

    cargarClasesDeMaestro(ui->comboBoxClaseCrear);
    cargarClasesDeMaestro(ui->comboBoxClaseModificar);
    cargarClasesDeMaestro(ui->comboBoxClaseEliminar);



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
        ui->stackedWidget->setCurrentIndex(3); // Ir a ventana de Maestro
    } else if (tipoUsuario == "Alumno") {
         QMessageBox::information(this, "Bienvenido", "¡Bienvenido, " + nombreCompleto + "!");
        ui->stackedWidget->setCurrentIndex(2); // Ir a ventana de Alumno
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
    actualizarUI();
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
    ui->comboBoxBuscarClaseModificar->clear();  // Limpiar el ComboBox

    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    for (const Clase &clase : listaClases) {
        ui->comboBoxBuscarClaseModificar->addItem(clase.getID());  // Añadir ID de clase
    }

    // Verificar cuántas clases se cargaron en el ComboBox
    qDebug() << "Clases cargadas en ComboBox: " << ui->comboBoxBuscarClaseModificar->count();
}

void cframe::on_pushButton_5_clicked()
{
    actualizarUI();
    ui->stackedWidget_2->setCurrentIndex(5);
}

void cframe::on_btnBuscarClaseModificar_clicked()
{
    QString idBuscado = ui->comboBoxBuscarClaseModificar->currentText(); // Obtener ID de la clase seleccionada
    if (idBuscado.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase para modificar.");
        return;
    }

    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    for (const Clase &clase : listaClases) {
        if (clase.getID() == idBuscado) {
            idClaseAnterior = clase.getID();  // Guardamos el ID original antes de modificar
            ui->lineEditIDClaseModificar->setText(clase.getID());
            ui->lineEditNombreClaseModificar->setText(clase.getNombre());
            ui->timeEditHoraClaseModificar->setTime(QTime::fromString(clase.getHora(), "HH:mm"));
            ui->spinBoxUVModificar->setValue(clase.getUnidadesValorativas());
            ui->spinBoxAnioModificar->setValue(clase.getAño());


            int indexSemestre = clase.getSemestre() - 1;
            if (indexSemestre >= 0 && indexSemestre < ui->comboBoxSemestreModificar->count()) {
                ui->comboBoxSemestreModificar->setCurrentIndex(indexSemestre);
            } else {
                qDebug() << "Error: Semestre fuera de rango - " << clase.getSemestre();
            }

            int indexPeriodo = (clase.getPeriodo() == 1) ? 0 : 1;
            if (indexPeriodo >= 0 && indexPeriodo < ui->comboBoxPeriodoModificar->count()) {
                ui->comboBoxPeriodoModificar->setCurrentIndex(indexPeriodo);
            } else {
                qDebug() << "Error: Periodo fuera de rango - " << clase.getPeriodo();
            }

            qDebug() << "Clase encontrada: " << clase.getID();
            qDebug() << "Semestre seleccionado: " << indexSemestre;
            qDebug() << "Periodo seleccionado: " << indexPeriodo;

            return;
        }
    }

    QMessageBox::warning(this, "Error", "No se encontró la clase.");
}

void cframe::on_btnGuardarCambiosClas_clicked()
{
    qDebug() << "Botón Modificar Clase presionado";

    if (idClaseAnterior.isEmpty()) {
        QMessageBox::warning(this, "Error", "No hay una clase seleccionada para modificar.");
        qDebug() << "Error: idClaseAnterior está vacío.";
        return;
    }

    QString nuevoID = ui->lineEditIDClaseModificar->text();
    QString nuevoNombre = ui->lineEditNombreClaseModificar->text();
    QString nuevaHora = ui->timeEditHoraClaseModificar->time().toString("HH:mm");
    int nuevasUV = ui->spinBoxUVModificar->value();
    int nuevoSemestre = ui->comboBoxSemestreModificar->currentIndex() + 1;
    int nuevoPeriodo = (ui->comboBoxPeriodoModificar->currentIndex() == 0) ? 1 : 2;
    int nuevoAño = ui->spinBoxAnioModificar->value();

    qDebug() << "Datos nuevos:";
    qDebug() << "ID Anterior:" << idClaseAnterior << "-> Nuevo ID:" << nuevoID;
    qDebug() << "Nombre:" << nuevoNombre << ", Hora:" << nuevaHora;
    qDebug() << "UV:" << nuevasUV << ", Semestre:" << nuevoSemestre;
    qDebug() << "Periodo:" << nuevoPeriodo << ", Año:" << nuevoAño;

    Clase nuevaClase(nuevoID, nuevoNombre, nuevaHora, nuevasUV, nuevoSemestre, nuevoPeriodo, nuevoAño);
    ManejadorClases manejador("clases.bin");

    bool exito = manejador.modificarClase(idClaseAnterior, nuevaClase);

    if (exito) {
        QMessageBox::information(this, "Éxito", "Clase modificada correctamente.");
        qDebug() << "Clase modificada con éxito.";
        cargarClasesEnComboBoxModificar();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar la clase.");
        qDebug() << "Error: No se pudo modificar la clase.";
    }
}

void cframe::on_pushButton_7_clicked()
{
    actualizarUI();
    ui->stackedWidget_2->setCurrentIndex(6);
}

void cframe::on_pushButton_9_clicked()
{
    actualizarUI();
    ui->stackedWidget_2->setCurrentIndex(7);
}

void cframe::cargarClasesEnComboBoxAsignarMaestro()
{
    ui->comboBoxClaseAsignarMaestro->clear();
    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    if (listaClases.isEmpty()) {
        qDebug() << "No se encontraron clases en clases.bin";
        return;
    }

    for (const Clase &clase : listaClases) {
        ui->comboBoxClaseAsignarMaestro->addItem(clase.getID());
    }

    ui->comboBoxClaseAsignarMaestro->update();
    qDebug() << "Clases cargadas en comboBoxClaseAsignarMaestro: " << ui->comboBoxClaseAsignarMaestro->count();
}

void cframe::cargarMaestrosEnComboBox()
{
    ui->comboBoxMaestroAsignar->clear();
    LoginManager manejadorUsuarios("usuarios.bin");

    QList<Usuario> listaUsuarios = manejadorUsuarios.obtenerUsuarios();

    if (listaUsuarios.isEmpty()) {
        qDebug() << "No se encontraron usuarios en usuarios.bin";
        return;
    }

    for (const Usuario &usuario : listaUsuarios) {
        if (usuario.getTipoUsuario() == "Maestro") {
            QString nombreCompleto = usuario.getNombre() + " " + usuario.getApellido();  // ✅ Mostrar "Nombre Apellido"
            ui->comboBoxMaestroAsignar->addItem(nombreCompleto, usuario.getUsuario());  // ✅ Guardar el usuario como dato interno
        }
    }

    ui->comboBoxMaestroAsignar->update();
    qDebug() << "Maestros cargados en comboBoxMaestroAsignar: " << ui->comboBoxMaestroAsignar->count();
}

void cframe::on_btnAsignarMaestro_clicked()
{
    QString idClase = ui->comboBoxClaseAsignarMaestro->currentText();
    QString maestro = ui->comboBoxMaestroAsignar->currentData().toString();  // ✅ Obtener usuario real del maestro

    if (idClase.isEmpty() || maestro.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase y un maestro.");
        return;
    }

    ManejadorClases manejador("clases.bin");

    if (manejador.asignarMaestro(idClase, maestro)) {
        QMessageBox::information(this, "Éxito", "Maestro asignado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo asignar el maestro.");
    }
}

void cframe::on_pushButton_10_clicked()
{
    actualizarUI();
    ui->stackedWidget_3->setCurrentIndex(1);
}

void cframe::cargarClasesEnComboBoxMatricularAlumno(){
    ui->comboBoxClaseMatricularAlumno->clear();
    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    if (listaClases.isEmpty()) {
        qDebug() << "No se encontraron clases en clases.bin";
        return;
    }

    for (const Clase &clase : listaClases) {
        ui->comboBoxClaseMatricularAlumno->addItem(clase.getID());
    }

    ui->comboBoxClaseMatricularAlumno->update();
    qDebug() << "Clases cargadas en comboBoxClaseMatricularAlumno: " << ui->comboBoxClaseMatricularAlumno->count();
}

void cframe::cargarAlumnosDisponibles(){
    ui->listWidgetAlumnosDisponibles->clear();
    QString idClase = ui->comboBoxClaseMatricularAlumno->currentText();

    if (idClase.isEmpty()) {
        qDebug() << "No hay clase seleccionada. Esperando selección.";
        return;
    }

    ManejadorClases manejador("clases.bin");
    QList<QString> alumnosMatriculados = manejador.obtenerAlumnosMatriculados(idClase);

    LoginManager manejadorUsuarios("usuarios.bin");
    QList<Usuario> listaUsuarios = manejadorUsuarios.obtenerUsuarios();

    if (listaUsuarios.isEmpty()) {
        qDebug() << "No se encontraron usuarios en usuarios.bin";
        return;
    }

    qDebug() << "Cargando alumnos disponibles para la clase " << idClase;

    for (const Usuario &usuario : listaUsuarios) {
        if (usuario.getTipoUsuario() == "Alumno") {
            if (!alumnosMatriculados.contains(usuario.getUsuario())) {
                QString nombreCompleto = usuario.getNombre() + " " + usuario.getApellido();

                QListWidgetItem *item = new QListWidgetItem(nombreCompleto);
                item->setData(Qt::UserRole, usuario.getUsuario());
                ui->listWidgetAlumnosDisponibles->addItem(item);

                qDebug() << "Alumno agregado a la lista: " << nombreCompleto << " (Usuario: " << usuario.getUsuario() << ")";
            }
        }
    }

    ui->listWidgetAlumnosDisponibles->update();
    qDebug() << "Total alumnos disponibles: " << ui->listWidgetAlumnosDisponibles->count();
}

void cframe::cargarAlumnosMatriculados(){
    ui->listWidgetAlumnosMatriculados->clear();
    QString idClase = ui->comboBoxClaseMatricularAlumno->currentText();

    if (idClase.isEmpty()) {
        qDebug() << "No hay clase seleccionada.";
        return;
    }

    ManejadorClases manejador("clases.bin");
    QList<QString> alumnosMatriculados = manejador.obtenerAlumnosMatriculados(idClase);

    LoginManager manejadorUsuarios("usuarios.bin");
    QList<Usuario> listaUsuarios = manejadorUsuarios.obtenerUsuarios();

    qDebug() << "Cargando alumnos matriculados en la clase " << idClase;

    for (const QString &usuario : alumnosMatriculados) {
        for (const Usuario &datosUsuario : listaUsuarios) {
            if (datosUsuario.getUsuario() == usuario) {
                QString nombreCompleto = datosUsuario.getNombre() + " " + datosUsuario.getApellido();

                QListWidgetItem *item = new QListWidgetItem(nombreCompleto);  // ✅ Mostrar en la lista
                item->setData(Qt::UserRole, usuario);  // ✅ Guardar usuario internamente
                ui->listWidgetAlumnosMatriculados->addItem(item);

                qDebug() << "✔ Alumno matriculado mostrado: " << nombreCompleto << " (Usuario: " << usuario << ")";
            }
        }
    }

    ui->listWidgetAlumnosMatriculados->update();
    qDebug() << "Total alumnos matriculados: " << ui->listWidgetAlumnosMatriculados->count();
}

void cframe::on_btnMatricularAlumno_clicked(){
    QString idClase = ui->comboBoxClaseMatricularAlumno->currentText();
    QList<QListWidgetItem *> seleccionados = ui->listWidgetAlumnosDisponibles->selectedItems();

    if (idClase.isEmpty() || seleccionados.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase y al menos un alumno.");
        return;
    }

    ManejadorClases manejador("clases.bin");
    QStringList alumnos;

    for (QListWidgetItem *item : seleccionados) {
        QString usuario = item->data(Qt::UserRole).toString();
        alumnos.append(usuario);
    }

    if (manejador.matricularAlumnos(idClase, alumnos)) {
        QMessageBox::information(this, "Éxito", "Alumnos matriculados correctamente.");
        cargarAlumnosDisponibles();
        cargarAlumnosMatriculados();
    } else {
        QMessageBox::critical(this, "Error", "No se pudieron matricular los alumnos.");
    }
}

void cframe::on_btnDesmatricularAlumno_clicked()
{
    QString idClase = ui->comboBoxClaseMatricularAlumno->currentText();
    QList<QListWidgetItem *> seleccionados = ui->listWidgetAlumnosMatriculados->selectedItems();

    if (idClase.isEmpty() || seleccionados.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase y al menos un alumno.");
        return;
    }

    ManejadorClases manejador("clases.bin");
    QStringList alumnos;

    for (QListWidgetItem *item : seleccionados) {
        QString usuario = item->data(Qt::UserRole).toString();
        alumnos.append(usuario);
    }

    if (manejador.desmatricularAlumnos(idClase, alumnos)) {
        QMessageBox::information(this, "Éxito", "Alumnos desmatriculados correctamente.");
        cargarAlumnosDisponibles();
        cargarAlumnosMatriculados();
    } else {
        QMessageBox::critical(this, "Error", "No se pudieron desmatricular los alumnos.");
    }
}

void cframe::on_pushButton_11_clicked()
{
    actualizarUI();
     ui->stackedWidget_3->setCurrentIndex(0);
}

void cframe::debugMostrarUsuarios()
{
    LoginManager manejadorUsuarios("usuarios.bin");
    QList<Usuario> listaUsuarios = manejadorUsuarios.obtenerUsuarios();

    qDebug() << "Usuarios encontrados en usuarios.bin:";
    for (const Usuario &usuario : listaUsuarios) {
        qDebug() << "Usuario:" << usuario.getUsuario()
        << ", Nombre:" << usuario.getNombre()
        << ", Apellido:" << usuario.getApellido()
        << ", Tipo:" << usuario.getTipoUsuario();
    }
}

void cframe::debugMostrarAlumnosMatriculados()
{
    QString idClase = ui->comboBoxClaseMatricularAlumno->currentText();
    if (idClase.isEmpty()) {
        qDebug() << "No hay clase seleccionada.";
        return;
    }

    ManejadorClases manejador("clases.bin");
    QList<QString> alumnosMatriculados = manejador.obtenerAlumnosMatriculados(idClase);

    qDebug() << "Alumnos matriculados en la clase" << idClase << ":";
    for (const QString &alumno : alumnosMatriculados) {
        qDebug() << alumno;
    }
}

void cframe::on_comboBoxClaseMatricularAlumno_currentIndexChanged(int index)
{
    Q_UNUSED(index);
    cargarAlumnosDisponibles();
    cargarAlumnosMatriculados();
}

void cframe::cargarClasesEnComboBoxEliminar()
{
    ui->comboBoxClaseEliminar->clear();
    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    if (listaClases.isEmpty()) {
        qDebug() << "No se encontraron clases en clases.bin";
        return;
    }

    for (const Clase &clase : listaClases) {
        ui->comboBoxClaseEliminar->addItem(clase.getID());
    }

    ui->comboBoxClaseEliminar->update();
    qDebug() << "Clases cargadas en comboBoxClaseEliminar: " << ui->comboBoxClaseEliminar->count();
}

void cframe::on_btnBuscarClaseEliminar_clicked()
{
    QString idClase = ui->comboBoxClaseEliminar->currentText();

    if (idClase.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase para buscar.");
        return;
    }

    ManejadorClases manejador("clases.bin");
    LoginManager manejadorUsuarios("usuarios.bin");
    QList<Clase> listaClases = manejador.obtenerClases();
    QList<Usuario> listaUsuarios = manejadorUsuarios.obtenerUsuarios();

    for (const Clase &clase : listaClases) {
        if (clase.getID() == idClase) {
            ui->labelMostrarNombreClase->setText(clase.getNombre());
            QString usuarioMaestro = clase.getUsuarioAsociado();


            QString nombreMaestro = "Desconocido";
            for (const Usuario &usuario : listaUsuarios) {
                if (usuario.getUsuario() == usuarioMaestro) {
                    nombreMaestro = usuario.getNombre() + " " + usuario.getApellido();
                    break;
                }
            }
            ui->labelMaestroClaseEliminar->setText(nombreMaestro);
            ui->listWidgetAlumnosClaseEliminar->clear();
            QList<QString> alumnosMatriculados = manejador.obtenerAlumnosMatriculados(idClase);

            for (const QString &alumnoUsuario : alumnosMatriculados) {
                for (const Usuario &usuario : listaUsuarios) {
                    if (usuario.getUsuario() == alumnoUsuario) {
                        QString nombreCompleto = usuario.getNombre() + " " + usuario.getApellido();
                        ui->listWidgetAlumnosClaseEliminar->addItem(nombreCompleto);
                        break;
                    }
                }
            }

            qDebug() << "Información de la clase cargada: " << clase.getNombre();
            return;
        }
    }

    QMessageBox::warning(this, "Error", "No se encontró la clase seleccionada.");
}

void cframe::on_btnEliminarClase_clicked()
{
    QString idClase = ui->comboBoxClaseEliminar->currentText();

    if (idClase.isEmpty()) {
        QMessageBox::warning(this, "Error", "Seleccione una clase para eliminar.");
        return;
    }

    QMessageBox::StandardButton confirmacion;
    confirmacion = QMessageBox::warning(this, "Confirmación",
                                        "⚠ Si elimina esta clase, se desvincularán el maestro y los alumnos asignados.\n"
                                        "¿Está seguro de que desea continuar?",
                                        QMessageBox::Yes | QMessageBox::No);

    if (confirmacion == QMessageBox::No) {
        return;
    }

    ManejadorClases manejador("clases.bin");

    if (manejador.eliminarClase(idClase)) {
        QMessageBox::information(this, "Éxito", "Clase eliminada correctamente.");

        actualizarUI();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo eliminar la clase.");
    }
}

void cframe::actualizarUI()
{
    // Limpiar y recargar los elementos en la ventana de MODIFICAR CLASE
    ui->comboBoxBuscarClaseModificar->clear();
    ui->lineEditIDClaseModificar->clear();
    ui->lineEditNombreClaseModificar->clear();
    ui->timeEditHoraClaseModificar->clear();
    ui->spinBoxUVModificar->setValue(1);
    ui->comboBoxSemestreModificar->setCurrentIndex(0);
    ui->comboBoxPeriodoModificar->setCurrentIndex(0);
    ui->spinBoxAnioModificar->setValue(QDate::currentDate().year());
    cargarClasesEnComboBoxModificar();

    // Limpiar y recargar los elementos en la ventana de ELIMINAR CLASE
    ui->comboBoxClaseEliminar->clear();
    ui->labelMostrarNombreClase->clear();
    ui->labelMaestroClaseEliminar->clear();
    ui->listWidgetAlumnosClaseEliminar->clear();
    cargarClasesEnComboBoxEliminar();

    //  Limpiar y recargar los elementos en la ventana de ASIGNAR CLASE
    ui->comboBoxClaseAsignarMaestro->clear();
    ui->comboBoxMaestroAsignar->clear();
    cargarClasesEnComboBoxAsignarMaestro();
    cargarMaestrosEnComboBox();

    //  Limpiar y recargar los elementos en la ventana de MATRICULAR ALUMNOS
    ui->comboBoxClaseMatricularAlumno->clear();
    ui->listWidgetAlumnosDisponibles->clear();
    ui->listWidgetAlumnosMatriculados->clear();
    cargarClasesEnComboBoxMatricularAlumno();
}

void cframe::on_pushButton_15_clicked()
{
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmación", "¿Seguro que quieres salir?",
                                      QMessageBox::Yes | QMessageBox::No);


    if (respuesta == QMessageBox::Yes) {
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget_4->setCurrentIndex(0);
    }
}

void cframe::cargarClasesDeMaestro(QComboBox *comboBox)
{
    comboBox->clear();
    QString usuarioMaestro = usuarioActivo;

    ManejadorClases manejador("clases.bin");
    QList<Clase> listaClases = manejador.obtenerClases();

    for (const Clase &clase : listaClases) {
        if (clase.getUsuarioAsociado() == usuarioMaestro) {
            comboBox->addItem(clase.getID());
        }
    }
}

void cframe::on_btnAgregarPreguntaCrear_clicked()
{
    int row = ui->tablePreguntasCrear->rowCount();
    ui->tablePreguntasCrear->insertRow(row);

    // **Enunciado de la Pregunta**
    QTableWidgetItem *enunciado = new QTableWidgetItem();
    ui->tablePreguntasCrear->setItem(row, 0, enunciado);

    // **Tipo de Pregunta (Verdadero/Falso, Selección Múltiple, Enumerada)**
    QComboBox *comboTipo = new QComboBox();
    comboTipo->addItems({"Verdadero/Falso", "Selección Múltiple", "Enumerada"});
    ui->tablePreguntasCrear->setCellWidget(row, 1, comboTipo);

    // **Opciones de Respuesta (separadas por `;`)**
    QTableWidgetItem *opciones = new QTableWidgetItem();
    ui->tablePreguntasCrear->setItem(row, 2, opciones);

    // **ComboBox para Seleccionar Respuesta Correcta**
    QComboBox *comboCorrecta = new QComboBox();
    ui->tablePreguntasCrear->setCellWidget(row, 3, comboCorrecta);

    // Conectar cambio en opciones para actualizar el ComboBox de respuestas correctas
    connect(ui->tablePreguntasCrear, &QTableWidget::cellChanged, this, &cframe::actualizarOpcionesRespuestaCrear);
}

void cframe::actualizarOpcionesRespuestaCrear(int row, int column)
{
    if (column == 2) {  // Solo actualizar si se modifican las opciones de respuesta
        QString opcionesTexto = ui->tablePreguntasCrear->item(row, 2)->text();
        QStringList opciones = opcionesTexto.split(";");

        QComboBox *comboCorrecta = qobject_cast<QComboBox*>(ui->tablePreguntasCrear->cellWidget(row, 3));
        if (comboCorrecta) {
            comboCorrecta->clear();
            comboCorrecta->addItems(opciones);
        }
    }
}

void cframe::on_btnEliminarPreguntaCrear_clicked()
{
    int row = ui->tablePreguntasCrear->currentRow();  // Obtener la fila seleccionada
    if (row >= 0) {
        ui->tablePreguntasCrear->removeRow(row);  // Eliminar la fila si hay una seleccionada
    } else {
        QMessageBox::warning(this, "Error", "Seleccione una pregunta para eliminar.");
    }
}

void cframe::cargarExamenesEnComboBox()
{
    ui->comboBoxExamenModificar->clear();

    ManejadorExamenes manejador("examenes.bin");
    QList<Examen> listaExamenes = manejador.obtenerExamenes();

    if (listaExamenes.isEmpty()) {
        QMessageBox::warning(this, "No hay exámenes", "No hay exámenes disponibles para modificar.");
        return;
    }

    for (const Examen &examen : listaExamenes) {
        if (!examen.getID().isEmpty()) {  // Evitar IDs vacíos o valores erróneos
            qDebug() << "Cargando examen en ComboBox (ID):" << examen.getID();
            ui->comboBoxExamenModificar->addItem(examen.getID());
        }
    }
}

void cframe::on_btnCrearExamen_clicked()
{
    QString idClase = ui->comboBoxClaseCrear->currentText();
    QString idExamen = ui->lineEditIDExamenCrear->text();
    QString nombreExamen = ui->lineEditNombreExamenCrear->text();
    QString fecha = ui->dateEditFechaCrear->date().toString("yyyy-MM-dd");
    QString hora = ui->timeEditHoraCrear->time().toString("HH:mm");
    double duracion = ui->doubleSpinBoxDuracionCrear->value();

    if (idClase.isEmpty() || idExamen.isEmpty() || nombreExamen.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    Examen nuevoExamen(idExamen, nombreExamen, fecha, hora, duracion);

    for (int i = 0; i < ui->tablePreguntasCrear->rowCount(); i++) {
        QString enunciado = ui->tablePreguntasCrear->item(i, 0)->text();
        QComboBox *comboTipo = qobject_cast<QComboBox*>(ui->tablePreguntasCrear->cellWidget(i, 1));
        QString tipoPregunta = comboTipo->currentText();
        QString opciones = ui->tablePreguntasCrear->item(i, 2)->text();
        QComboBox *comboCorrecta = qobject_cast<QComboBox*>(ui->tablePreguntasCrear->cellWidget(i, 3));
        QString respuestaCorrecta = comboCorrecta->currentText();

        nuevoExamen.agregarPregunta(enunciado, tipoPregunta, opciones, respuestaCorrecta);
    }

    ManejadorExamenes manejadorExamenes("examenes.bin");
    if (manejadorExamenes.agregarExamen(nuevoExamen)) {
        QMessageBox::information(this, "Éxito", "Examen creado correctamente.");

         cargarExamenesEnComboBox();
        ui->comboBoxExamenModificar->update();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo crear el examen.");
    }
}

void cframe::on_pushButton_12_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}

void cframe::on_pushButton_13_clicked()
{
    cargarExamenesEnComboBox();
    ui->stackedWidget_4->setCurrentIndex(2);
}

void cframe::on_pushButton_14_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(3);
}

void cframe::on_btnModificarExamen_clicked()
{
    QString idViejo = ui->comboBoxExamenModificar->currentText();
    QString idNuevo = ui->lineEditIDExamenModificar->text();
    QString nombreNuevo = ui->lineEditNombreExamenModificar->text();
    QString fechaNueva = ui->dateEditFechaModificar->date().toString("yyyy-MM-dd");
    QString horaNueva = ui->timeEditHoraModificar->time().toString("HH:mm");
    double duracionNueva = ui->doubleSpinBoxDuracionModificar->value();

    if (idNuevo.isEmpty() || nombreNuevo.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos son obligatorios.");
        return;
    }

    Examen nuevoExamen(idNuevo, nombreNuevo, fechaNueva, horaNueva, duracionNueva);

    for (int i = 0; i < ui->tablePreguntasModificar->rowCount(); i++) {
        QString enunciado = ui->tablePreguntasModificar->item(i, 0)->text();
        QComboBox *comboTipo = qobject_cast<QComboBox*>(ui->tablePreguntasModificar->cellWidget(i, 1));
        QString tipoPregunta = comboTipo->currentText();
        QString opciones = ui->tablePreguntasModificar->item(i, 2)->text();
        QComboBox *comboCorrecta = qobject_cast<QComboBox*>(ui->tablePreguntasModificar->cellWidget(i, 3));
        QString respuestaCorrecta = comboCorrecta->currentText();

        nuevoExamen.agregarPregunta(enunciado, tipoPregunta, opciones, respuestaCorrecta);
    }

    ManejadorExamenes manejadorExamenes("examenes.bin");
    if (manejadorExamenes.modificarExamen(idViejo, nuevoExamen)) {
        QMessageBox::information(this, "Éxito", "Examen modificado correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo modificar el examen.");
    }
}

void cframe::on_comboBoxExamenModificar_currentIndexChanged(int index)
{
    QString idExamen = ui->comboBoxExamenModificar->currentText();
    if (idExamen.isEmpty()) return;

    ManejadorExamenes manejador("examenes.bin");
    Examen examen = manejador.obtenerExamen(idExamen);

    if (examen.getID().isEmpty()) {
        QMessageBox::warning(this, "Error", "No se encontró el examen seleccionado.");
        return;
    }

    // Cargar datos generales del examen
    ui->lineEditIDExamenModificar->setText(examen.getID());
    ui->lineEditNombreExamenModificar->setText(examen.getNombre());
    ui->dateEditFechaModificar->setDate(QDate::fromString(examen.getFecha(), "yyyy-MM-dd"));
    ui->timeEditHoraModificar->setTime(QTime::fromString(examen.getHora(), "HH:mm"));
    ui->doubleSpinBoxDuracionModificar->setValue(examen.getDuracion());
/*
    // Cargar preguntas en la tabla
    ui->tablePreguntasModificar->setRowCount(0);
    for (const Pregunta &pregunta : examen.getPreguntas()) {
        int row = ui->tablePreguntasModificar->rowCount();
        ui->tablePreguntasModificar->insertRow(row);

        // Enunciado
        QTableWidgetItem *enunciado = new QTableWidgetItem(pregunta.getEnunciado());
        ui->tablePreguntasModificar->setItem(row, 0, enunciado);

        // Tipo de pregunta
        QComboBox *comboTipo = new QComboBox();
        comboTipo->addItems({"Verdadero/Falso", "Selección Múltiple", "Enumerada"});
        comboTipo->setCurrentText(pregunta.getTipo());
        ui->tablePreguntasModificar->setCellWidget(row, 1, comboTipo);

        // Opciones de Respuesta
        QTableWidgetItem *opciones = new QTableWidgetItem(pregunta.getOpciones());
        ui->tablePreguntasModificar->setItem(row, 2, opciones);

        // Respuesta Correcta
        QComboBox *comboCorrecta = new QComboBox();
        QStringList opcionesLista = pregunta.getOpciones().split(";");
        comboCorrecta->addItems(opcionesLista);
        comboCorrecta->setCurrentText(pregunta.getRespuestaCorrecta());
        ui->tablePreguntasModificar->setCellWidget(row, 3, comboCorrecta);
    }*/

    qDebug() << "Cargando preguntas del examen:" << examen.getID();
    qDebug() << "Total de preguntas:" << examen.getPreguntas().size();

    ui->tablePreguntasModificar->setRowCount(0);

    for (const Pregunta &pregunta : examen.getPreguntas()) {
        qDebug() << "  Agregando pregunta a la tabla:" << pregunta.getEnunciado();
    }
}

