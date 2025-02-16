#ifndef MANEJADORCLASES_H
#define MANEJADORCLASES_H

#include <QString>
#include <QList>
#include <stack>
#include <queue>
#include <map>
#include "clase.h"

// 👇 Estructura de Lista Enlazada (Para Clases y Alumnos)
struct NodoClase {
    Clase clase;
    QList<QString> alumnosAsignados;
    NodoClase *siguiente;
};

class ManejadorClases {
public:
    ManejadorClases(const QString &archivo);

    bool agregarClase(const Clase &clase);
    bool modificarClase(const QString &idViejo, const Clase &nuevaClase);
    bool eliminarClase(const QString &id);
    bool restaurarClaseEliminada();

    bool asignarMaestro(const QString &idClase, const QString &maestro);
    bool matricularAlumnos(const QString &idClase, const QStringList &alumnos);
    bool desmatricularAlumnos(const QString &idClase, const QStringList &alumnos);

    bool agregarTareaCompletada(const QString &tarea);
    bool restaurarUltimaTarea();

    bool agregarTareaEnCola(const QString &tarea);
    QString ejecutarSiguienteTarea();

    QList<Clase> obtenerClases();
    QList<QString> obtenerAlumnosMatriculados(const QString &idClase);

private:
    QString archivoClases;
    NodoClase *listaClases;  // 👈 Lista Enlazada para manejar Clases y Alumnos

    std::stack<QString> pilaTareasCompletadas;  // 👈 Pila para manejar tareas completadas
    std::queue<QString> colaTareas;  // 👈 Cola para ejecutar tareas en orden FIFO

    void cargarListaEnlazada();
};

#endif // MANEJADORCLASES_H
