#include "manejadorclases.h"
#include <QFile>
#include <QDataStream>
#include <QDebug>

ManejadorClases::ManejadorClases(const QString &archivo) {
    archivoClases = archivo;
    cargarListaEnlazada();
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
        << clase.getPeriodo() << clase.getAño();

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

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;

        if (cid == idViejo) {
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

bool ManejadorClases::asignarMaestro(const QString &idClase, const QString &maestro) {
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

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;

        if (cid == idClase) {
            qDebug() << "Asignando maestro " << maestro << " a la clase " << idClase;
            usuarioAsociado = maestro;
            modificado = true;
        }

        out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoClases);

    return modificado;
}

bool ManejadorClases::matricularAlumnos(const QString &idClase, const QStringList &alumnos){
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "🚨 Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    QList<QString> alumnosMatriculados;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        in >> alumnosMatriculados;

        if (cid == idClase) {
            for (const QString &alumno : alumnos) {
                if (!alumnosMatriculados.contains(alumno)) {
                    alumnosMatriculados.append(alumno);
                }
            }
            modificado = true;
        }

        out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
        out << alumnosMatriculados;
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoClases);

    return modificado;
}

QList<QString> ManejadorClases::obtenerAlumnosMatriculados(const QString &idClase) {
    QFile file(archivoClases);
    QList<QString> alumnosMatriculados;

    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "🚨 Error: No se pudo abrir el archivo de clases.";
        return alumnosMatriculados;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    QList<QString> alumnos;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        in >> alumnos;

        if (cid == idClase) {
            alumnosMatriculados = alumnos;
            break;
        }
    }

    file.close();
    return alumnosMatriculados;
}

bool ManejadorClases::desmatricularAlumnos(const QString &idClase, const QStringList &alumnos)
{
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "🚨 Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    QList<QString> alumnosMatriculados;
    bool modificado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        in >> alumnosMatriculados;

        if (cid == idClase) {
            for (const QString &alumno : alumnos) {
                alumnosMatriculados.removeAll(alumno);
            }
            modificado = true;
        }

        out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
        out << alumnosMatriculados;
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoClases);

    return modificado;
}

// 👇 Cargar Clases en Lista Enlazada
void ManejadorClases::cargarListaEnlazada() {
    listaClases = nullptr;
    QFile file(archivoClases);

    if (!file.open(QIODevice::ReadOnly)) return;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        Clase nuevaClase(cid, nombre, hora, unidades, semestre, periodo, año);
        nuevaClase.setUsuarioAsociado(usuarioAsociado);

        NodoClase *nuevoNodo = new NodoClase{nuevaClase, {}, listaClases};
        listaClases = nuevoNodo;
    }

    file.close();
}

// 👇 Obtener Clases desde Lista Enlazada
QList<Clase> ManejadorClases::obtenerClases() {
    QList<Clase> clases;
    NodoClase *actual = listaClases;

    while (actual) {
        clases.append(actual->clase);
        actual = actual->siguiente;
    }

    return clases;
}

// 👇 Eliminar Clase y Guardar en la Pila de Restauración
bool ManejadorClases::eliminarClase(const QString &id) {
    QFile file(archivoClases);
    QFile tempFile("temp_clases.bin");

    if (!file.open(QIODevice::ReadOnly) || !tempFile.open(QIODevice::WriteOnly)) {
        qDebug() << "🚨 Error: No se pudo abrir el archivo.";
        return false;
    }

    QDataStream in(&file);
    QDataStream out(&tempFile);
    in.setVersion(QDataStream::Qt_6_0);
    out.setVersion(QDataStream::Qt_6_0);

    QString cid, nombre, hora, usuarioAsociado;
    int unidades, semestre, periodo, año;
    QList<QString> alumnosMatriculados;
    bool eliminado = false;

    while (!in.atEnd()) {
        in >> cid >> nombre >> hora >> unidades >> semestre >> periodo >> año >> usuarioAsociado;
        in >> alumnosMatriculados;

        if (cid == id) {
            eliminado = true;
            qDebug() << "Eliminando clase:" << id;
            qDebug() << "Desvinculando maestro: " << usuarioAsociado;
            qDebug() << "Eliminando alumnos: " << alumnosMatriculados;

            // 🔹 NO escribir esta clase en el nuevo archivo (se elimina)
        } else {
            out << cid << nombre << hora << unidades << semestre << periodo << año << usuarioAsociado;
            out << alumnosMatriculados;
        }
    }

    file.close();
    tempFile.close();
    file.remove();
    tempFile.rename(archivoClases);

    return eliminado;
}

// 👇 Restaurar Última Clase Eliminada desde la Pila
bool ManejadorClases::restaurarClaseEliminada() {
    if (pilaTareasCompletadas.empty()) return false;

    QString idClase = pilaTareasCompletadas.top();
    pilaTareasCompletadas.pop();

    return true;
}

// 👇 Agregar Tarea a la Pila (Completadas)
bool ManejadorClases::agregarTareaCompletada(const QString &tarea) {
    pilaTareasCompletadas.push(tarea);
    return true;
}

// 👇 Restaurar Última Tarea Completada desde la Pila
bool ManejadorClases::restaurarUltimaTarea() {
    if (pilaTareasCompletadas.empty()) return false;

    pilaTareasCompletadas.pop();
    return true;
}

// 👇 Agregar Tarea a la Cola (FIFO)
bool ManejadorClases::agregarTareaEnCola(const QString &tarea) {
    colaTareas.push(tarea);
    return true;
}

// 👇 Ejecutar la Siguiente Tarea en la Cola
QString ManejadorClases::ejecutarSiguienteTarea() {
    if (colaTareas.empty()) return "";

    QString tarea = colaTareas.front();
    colaTareas.pop();
    return tarea;
}

