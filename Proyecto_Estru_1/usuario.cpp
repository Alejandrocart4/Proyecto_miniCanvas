#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(const QString &usuario, const QString &password, const QString &rol) {
    this->usuario = usuario;
    this->password = password;
    this->rol = rol;
}

QString Usuario::getUsuario() const { return usuario; }
QString Usuario::getPassword() const { return password; }
QString Usuario::getRol() const { return rol; }

void Usuario::setUsuario(const QString &usuario) { this->usuario = usuario; }
void Usuario::setPassword(const QString &password) { this->password = password; }
void Usuario::setRol(const QString &rol) { this->rol = rol; }
