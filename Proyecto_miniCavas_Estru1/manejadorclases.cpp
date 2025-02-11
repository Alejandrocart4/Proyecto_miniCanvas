#include "manejadorclases.h"
#include <QFile>
#include <QDataStream>

ManejadorClases::ManejadorClases(const QString &archivo) {
    archivoClases = archivo;
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

bool ManejadorClases::modificarClase(const QString &id, const Clase &nuevaClase) {
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;

        if (cid == id) {
            out << nuevaClase.getID() << nuevaClase.getNombre() << nuevaClase.getHora()
            << nuevaClase.getUnidadesValorativas() << nuevaClase.getSemestre()
            << nuevaClase.getPeriodo() << nuevaClase.getAño() << nuevaClase.getUsuarioAsociado();
            modificado = true;
        } else {
            out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
        }
    }

    file.close();
    tempFile.close();
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
