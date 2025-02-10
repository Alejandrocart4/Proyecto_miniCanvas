#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(const QString &usuario, const QString &password, const QString &tipoUsuario, const QString &nombre, const QString &apellido, const QString &sueldo, const QList<QString> &clases){
    this->usuario = usuario;
    this->password = password;
    this->tipoUsuario = tipoUsuario;
    this->nombre = nombre;
    this->apellido = apellido;
    this->sueldo = sueldo;
    this->clases = clases;
}

QString Usuario::getUsuario() const { return usuario; }
QString Usuario::getPassword() const { return password; }
QString Usuario::getTipoUsuario() const { return tipoUsuario; }
QString Usuario::getNombre() const { return nombre; }
QString Usuario::getApellido() const { return apellido; }

void Usuario::setUsuario(const QString &usuario) { this->usuario = usuario; }
void Usuario::setPassword(const QString &password) { this->password = password; }
void Usuario::setTipoUsuario(const QString &tipoUsuario) { this->tipoUsuario = tipoUsuario; }
void Usuario::setNombre(const QString &nombre) { this->nombre = nombre; }
void Usuario::setApellido(const QString &apellido) { this->apellido = apellido; }
