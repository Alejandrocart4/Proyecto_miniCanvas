#include "LoginManager.h"

LoginManager::LoginManager(const QString &archivoUsuarios) {
    this->archivoUsuarios = archivoUsuarios;
}


bool LoginManager::registrarUsuario(const Usuario &usuario) {
    QFile file(archivoUsuarios);
    if (!file.open(QIODevice::Append)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);
    out << usuario.getUsuario() << usuario.getPassword() << usuario.getTipoUsuario() << usuario.getNombre() << usuario.getApellido();
    file.flush();
    file.close();
    return true;
}

QList<QString> LoginManager::obtenerClasesUsuario(const QString &usuario)
{
    QFile file(archivoUsuarios);
    QList<QString> clases;

    if (!file.open(QIODevice::ReadOnly)) {
        return clases;
    }

    QDataStream in(&file);
    QString u, p, tipo, nombre, apellido, clase;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        if (u == usuario) {
            while (!in.atEnd()) {
                in >> clase;
                if (clase.isEmpty()) break;
                clases.append(clase);
            }
        }
    }

    file.close();
    return clases;
}


// Autenticar usuario y devolver su objeto completo
Usuario LoginManager::autenticarUsuario(const QString &usuario, const QString &password) {
    QFile file(archivoUsuarios);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo binario: " << archivoUsuarios;
        return Usuario();
    }

    QDataStream in(&file);
    //in.setVersion(QDataStream::Qt_5_15); // Asegurar compatibilidad
    QString u, p, tipo, nombre, apellido;

    qDebug() << "Buscando usuario:" << usuario;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        u = u.trimmed();
        p = p.trimmed();

        qDebug() << "Usuario en archivo:" << u;

        if (u == usuario.trimmed() && (password.isEmpty() || p == password.trimmed())) {
            qDebug() << "Usuario encontrado: " << usuario;
            file.close();
            return Usuario(u, p, tipo, nombre, apellido);
        }
    }

    file.close();
    qDebug() << "Usuario no encontrado";
    return Usuario();
}
bool LoginManager::eliminarUsuario(const QString &usuario)
{
    QFile file(archivoUsuarios);
    QFile tempFile("temp.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);

    QString u, p, tipo, nombre, apellido;
    bool eliminado = false;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        if (u != usuario) {  // Solo copiamos los usuarios que NO sean el que queremos eliminar
            out << u << p << tipo << nombre << apellido;
        } else {
            eliminado = true;  // Se marca como eliminado
        }
    }

    file.close();
    tempFile.close();

    file.remove();
    tempFile.rename(archivoUsuarios);

    return eliminado;
}

bool LoginManager::modificarUsuario(const QString &usuarioAnterior, const QString &nuevoUsuario, const QString &nuevaPassword, const QString &nuevoNombre, const QString &nuevoApellido, const QString &nuevoTipoUsuario)
{
    QFile file(archivoUsuarios);
    QFile tempFile("temp.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    out.setVersion(QDataStream::Qt_6_0);

    QString u, p, tipo, nombre, apellido;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        qDebug() << "Leyendo usuario:" << u;

        if (u == usuarioAnterior) {
            qDebug() << "Modificando usuario: " << usuarioAnterior << " por " << nuevoUsuario;
            out << nuevoUsuario << nuevaPassword << nuevoTipoUsuario << nuevoNombre << nuevoApellido;
            modificado = true;
        } else {
            out << u << p << tipo << nombre << apellido;
        }
    }

    file.close();
    tempFile.close();

    file.remove();
    tempFile.rename(archivoUsuarios);

    if (!modificado) {
        qDebug() << "Error: No se encontró el usuario en el archivo binario.";
    }

    return modificado;
}
