#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
//#include <QResizeEvent>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class cframe;
}
QT_END_NAMESPACE

class cframe : public QMainWindow
{
    Q_OBJECT

public:
    cframe(QWidget *parent = nullptr);
    ~cframe();

  void setUsuarioActivo(const QString &usuario);

private slots:
    void on_btnsalir_clicked();

    void on_btn_Login_clicked();

    void on_btn_registrar_clicked();

    void on_btn_CrearUsuario_clicked();

    void on_pushButton_2_clicked();

    void on_btnVerPasswordLogin_clicked();

    void on_pushButton_3_clicked();


    void on_btnBuscarUsuario_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();


    void on_btnBuscarUsuarioEditar_clicked();

    void on_btnGuardarCambioUsuario_clicked();

    void on_btnEditarUsuario_clicked();


    void on_comboBoxTipoUsuario_activated(int index);

    //void on_comboBoxTipoUsuarioModificar_activated(int index);

    void on_comboBoxTipoUsuarioModificar_activated(int index);

    void on_pushButton_6_clicked();


    void on_btnCrearClase_clicked();

    void on_pushButton_5_clicked();

    void on_btnBuscarClaseModificar_clicked();


    void on_btnGuardarCambiosClas_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_btnAsignarMaestro_clicked();

    void on_pushButton_10_clicked();

    void on_btnMatricularAlumno_clicked();


    void on_btnDesmatricularAlumno_clicked();

    void on_pushButton_11_clicked();



    void on_comboBoxClaseMatricularAlumno_currentIndexChanged(int index);

    void on_btnBuscarClaseEliminar_clicked();

    void on_btnEliminarClase_clicked();

    void on_pushButton_15_clicked();

    void on_btnAgregarPreguntaCrear_clicked();

    void on_btnEliminarPreguntaCrear_clicked();

    void on_btnCrearExamen_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_btnModificarExamen_clicked();

    void on_comboBoxExamenModificar_currentIndexChanged(int index);

    void on_btnEliminarExamen_clicked();


    void on_btnIniciarExamen_clicked();

private:
    Ui::cframe *ui;
    bool passwordVisibleRegistro = false;
    bool passwordVisibleLogin = false;
    void mostrarTablaClases(bool visible);
    QString usuarioActivo;
    QString usuarioAnterior;
    void cargarClasesEnComboBoxModificar();
    QString idClaseAnterior;
    void cargarClasesEnComboBoxAsignarMaestro();
    void cargarMaestrosEnComboBox();
    void cargarClasesEnComboBoxMatricularAlumno();
    void cargarAlumnosDisponibles();
    void cargarAlumnosMatriculados();
    void actualizarUI();

   void debugMostrarUsuarios();
   void debugMostrarAlumnosMatriculados();
   void cargarClasesEnComboBoxEliminar();
   void cargarClasesDeMaestro(QComboBox *comboBox);
   void actualizarOpcionesRespuestaCrear(int row, int column);
   void cargarExamenesEnComboBox();
   void actualizarOpcionesRespuestaModificar(int row, int column);
   void cargarClasesEnComboBoxEliminarEx();
   void cargarExamenesEnComboBoxEliminar();

   void iniciarExamen();




};
#endif // CFRAME_H
