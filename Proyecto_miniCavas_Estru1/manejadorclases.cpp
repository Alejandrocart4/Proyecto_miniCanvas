#include "manejadorclases.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

ManejadorClases::ManejadorClases(const QString &archivo) {
    archivoClases = archivo;
}

QList<Clase> ManejadorClases::obtenerClases() {
    QFile file(archivoClases);
    QList<Clase> clases;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el archivo de clases.";
        return clases;  // ✅ Devuelve lista vacía si hay error
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora;
    int unidades, semestre, periodo, año;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año;
        qDebug() << "Leyendo clase:" << cid << nombre << hora << unidades << semestre << periodo << año;  // ✅ Depuración
        clases.append(Clase(cid, nombre, hora, unidades, semestre, periodo, año));
    }

    file.close();
    return clases;
}

bool ManejadorClases::agregarClase(const Clase &clase) {
    QFile file(archivoClases);
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);
    out << clase.getID() << clase.getNombre() << clase.getHora()
        << clase.getUnidadesValorativas() << clase.getSemestre()
        << clase.getPeriodo() << clase.getAño() << clase.getUsuarioAsociado();

    file.close();
    return true;
}

bool ManejadorClases::modificarClase(const QString &idViejo, const Clase &nuevaClase) {
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora;
    int unidades, semestre, periodo, año;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año;

        if (cid == idViejo) {
            // ✅ Guardamos la nueva clase
            out << nuevaClase.getID() << nuevaClase.getNombre() << nuevaClase.getHora()
                << nuevaClase.getUnidadesValorativas() << nuevaClase.getSemestre()
                << nuevaClase.getPeriodo() << nuevaClase.getAño();
            modificado = true;
            qDebug() << "Clase modificada: " << nuevaClase.getID();
        } else {
            out << cid << nombre << hora << unidades << semestre << periodo << año;
        }
    }

    file.close();
    tempFile.close();

    // Reemplazar el archivo original con el archivo temporal
    file.remove();
    tempFile.rename(archivoClases);

    return modificado;
}

bool ManejadorClases::eliminarClase(const QString &id) {
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        if (cid != id) {
            out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
        }
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoClases);

    return true;
}
