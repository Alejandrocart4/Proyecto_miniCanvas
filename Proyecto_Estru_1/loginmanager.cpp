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
    out << usuario.getUsuario() << usuario.getPassword() << usuario.getRol();
    file.close();
    return true;
}

// Autenticar usuario leyendo desde el archivo binario
QString LoginManager::autenticarUsuario(const QString &usuario, const QString &password) {
    QFile file(archivoUsuarios);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return "";
    }

    QDataStream in(&file);
    QString u, p, r;
    while (!in.atEnd()) {
        in >> u >> p >> r;
        if (u == usuario && p == password) {
            file.close();
            return r; // Retorna el rol del usuario
        }
    }

    file.close();
    return ""; // No encontrado
}
