#include "LoginManager.h"

LoginManager::LoginManager(const QString &archivoUsuarios) {
    this->archivoUsuarios = archivoUsuarios;
}

// Agregar usuario al archivo binario
bool LoginManager::registrarUsuario(const Usuario &usuario) {
    QFile file(archivoUsuarios);
    if (!file.open(QIODevice::Append)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream out(&file);
    out << usuario.getUsuario() << usuario.getPassword() << usuario.getTipoUsuario() << usuario.getNombre() << usuario.getApellido();
    file.close();
    return true;
}

// Autenticar usuario y devolver su objeto completo
Usuario LoginManager::autenticarUsuario(const QString &usuario, const QString &password) {
    QFile file(archivoUsuarios);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return Usuario();
    }

    QDataStream in(&file);
    QString u, p, tipo, nombre, apellido;
    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        if (u == usuario && p == password) {
            file.close();
            return Usuario(u, p, tipo, nombre, apellido);
        }
    }

    file.close();
    return Usuario(); // Retorna un usuario vacío si no lo encuentra
}
