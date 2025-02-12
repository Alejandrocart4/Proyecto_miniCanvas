#ifndef MANEJADORCLASES_H
#define MANEJADORCLASES_H

#include <QString>
#include <QList>
#include "clase.h"

class ManejadorClases {
public:
    ManejadorClases(const QString &archivo);

    bool agregarClase(const Clase &clase);
    bool modificarClase(const QString &idViejo, const Clase &nuevaClase);
    bool eliminarClase(const QString &id);
    QList<Clase> obtenerClases();

private:
    QString archivoClases;
};

#endif // MANEJADORCLASES_H
