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
    out << usuario.getUsuario() << usuario.getPassword() << usuario.getTipoUsuario()
        << usuario.getNombre() << usuario.getApellido();

    if (usuario.getTipoUsuario() == "Maestro") {
        out << usuario.getSueldo();
        out << usuario.getProfesion();
    } else if (usuario.getTipoUsuario() == "Alumno") {
        out << usuario.getCarrera();
    }

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
    QString u, p, tipo, nombre, apellido, sueldo, profesion, carrera;

    qDebug() << "Buscando usuario:" << usuario;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        u = u.trimmed();
        p = p.trimmed();

        if (tipo == "Maestro") {
            in >> sueldo;
            in >> profesion;
            qDebug() << "Leyendo profesión: " << profesion;
        } else if (tipo == "Alumno") {
            in >> carrera;
            qDebug() << "Leyendo carrera: " << carrera;
        }

        qDebug() << "Usuario en archivo:" << u;

        if (u == usuario && (password.isEmpty() || p == password)) {
            return Usuario(u, p, tipo, nombre, apellido, sueldo, profesion, carrera);
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
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString u, p, tipo, nombre, apellido, sueldo, profesion, carrera;
    bool eliminado = false;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        if (tipo == "Maestro") {
            in >> sueldo;
            in >> profesion;
        } else if (tipo == "Alumno") {
            in >> carrera;
        }

        if (u == usuario) {
            eliminado = true;
        } else {
            out << u << p << tipo << nombre << apellido;
            if (tipo == "Maestro") {
                out << sueldo;
                out << profesion;
            } else if (tipo == "Alumno") {
                out << carrera;
            }
        }
    }

    file.close();
    tempFile.close();

    file.remove();
    tempFile.rename(archivoUsuarios);

    return eliminado;
}

bool LoginManager::modificarUsuario(const QString &usuarioAnterior, const QString &nuevoUsuario,
                                    const QString &nuevaPassword, const QString &nuevoNombre,
                                    const QString &nuevoApellido, const QString &nuevoTipoUsuario,
                                    const QString &nuevoSueldo, const QString &nuevaProfesion,
                                    const QString &nuevaCarrera){
    QFile file(archivoUsuarios);
    QFile tempFile("temp.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    out.setVersion(QDataStream::Qt_6_0);

    QString u, p, tipo, nombre, apellido, sueldo, profesion, carrera;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> u >> p >> tipo >> nombre >> apellido;
        if (tipo == "Maestro") {
            in >> sueldo;
            in >> profesion;
        } else if (tipo == "Alumno") {
            in >> carrera;
        }

        if (u == usuarioAnterior) {
            qDebug() << "Modificando usuario: " << usuarioAnterior << " por " << nuevoUsuario;
            out << nuevoUsuario << nuevaPassword << nuevoTipoUsuario << nuevoNombre << nuevoApellido;

            if (nuevoTipoUsuario == "Maestro") {
                out << nuevoSueldo;
                out << nuevaProfesion;  // 🔹 Guardar nueva profesión.
                qDebug() << "Guardando nueva profesión: " << nuevaProfesion;
            } else if (nuevoTipoUsuario == "Alumno") {
                out << nuevaCarrera;    // 🔹 Guardar nueva carrera
                qDebug() << "Guardando nueva carrera: " << nuevaCarrera;
            }
            modificado = true;
        } else {
            out << u << p << tipo << nombre << apellido;
            if (tipo == "Maestro") {
                out << sueldo;
                out << profesion;
            } else if (tipo == "Alumno") {
                out << carrera;
            }
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
