#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include <QString>
#include <QFile>
#include <QDataStream>
#include <QDebug>
#include "Usuario.h"

class LoginManager {
public:
    LoginManager(const QString &archivoUsuarios);
    bool registrarUsuario(const Usuario &usuario, const QString &sueldo, const QList<QString> &clases);
    bool modificarUsuario(const QString &usuarioAnterior, const QString &nuevoUsuario, const QString &nuevaPassword, const QString &nuevoNombre, const QString &nuevoApellido, const QString &nuevoTipoUsuario, const QString &sueldo, const QList<QString> &clases);
    Usuario autenticarUsuario(const QString &usuario, const QString &password);
    QList<QString> obtenerClasesUsuario(const QString &usuario);
    bool eliminarUsuario(const QString &usuario);




private:
    QString archivoUsuarios;
};

#endif // LOGINMANAGER_H
