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

    bool registrarUsuario(const Usuario &usuario);
    QString autenticarUsuario(const QString &usuario, const QString &password);

private:
    QString archivoUsuarios;
};

#endif // LOGINMANAGER_H
