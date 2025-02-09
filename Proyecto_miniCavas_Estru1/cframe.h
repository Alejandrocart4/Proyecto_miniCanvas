#ifndef CFRAME_H
#define CFRAME_H

#include <QMainWindow>
//#include <QResizeEvent>

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

private:
    Ui::cframe *ui;
    bool passwordVisibleRegistro = false;
    bool passwordVisibleLogin = false;
    void mostrarTablaClases(bool visible);
    QString usuarioActivo;
    QString usuarioAnterior;
};
#endif // CFRAME_H
