#include "manejadorExamenes.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

ManejadorExamenes::ManejadorExamenes(const QString &archivo) {
    archivoExamenes = archivo;
}

QList<Examen> ManejadorExamenes::obtenerExamenes() {
    QFile file(archivoExamenes);
    QList<Examen> examenes;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "No se pudo abrir el archivo de exámenes.";
        return examenes;  // ✅ Devuelve lista vacía si hay error
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    QString id, nombre, fecha, hora;
    int duracion;

    while (!in.atEnd()) {
        in >> id >> nombre >> fecha >> hora >> duracion;
        qDebug() << "Leyendo examen:" << id << nombre << fecha << hora << duracion;
        examenes.append(Examen(id, nombre, fecha, hora, duracion));
    }

    file.close();
    return examenes;
}

bool ManejadorExamenes::agregarExamen(const Examen &examen) {
    QFile file(archivoExamenes);
    if (!file.open(QIODevice::Append | QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_0);
    out << examen.getID() << examen.getNombre() << examen.getFecha()
        << examen.getHora() << examen.getDuracion();

    file.close();
    return true;
}

bool ManejadorExamenes::modificarExamen(const QString &idViejo, const Examen &nuevoExamen) {
    QFile file(archivoExamenes);
    QFile tempFile("temp_examenes.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString id, nombre, fecha, hora;
    int duracion;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> id >> nombre >> fecha >> hora >> duracion;

        if (id == idViejo) {
            out << nuevoExamen.getID() << nuevoExamen.getNombre() << nuevoExamen.getFecha()
            << nuevoExamen.getHora() << nuevoExamen.getDuracion();
            modificado = true;
        } else {
            out << id << nombre << fecha << hora << duracion;
        }
    }

    file.close();
    tempFile.close();

    file.remove();
    tempFile.rename(archivoExamenes);

    return modificado;
}

bool ManejadorExamenes::eliminarExamen(const QString &id) {
    QFile file(archivoExamenes);
    QFile tempFile("temp_examenes.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString eid, nombre, fecha, hora;
    int duracion;
    bool eliminado = false;

    while (!in.atEnd()) {
        in >> eid >> nombre >> fecha >> hora >> duracion;

        if (eid == id) {
            eliminado = true;  // No lo escribimos en el archivo nuevo
        } else {
            out << eid << nombre << fecha << hora << duracion;
        }
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoExamenes);

    return eliminado;
}
