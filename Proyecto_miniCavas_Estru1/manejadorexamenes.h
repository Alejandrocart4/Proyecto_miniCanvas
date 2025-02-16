#ifndef MANEJADOREXAMENES_H
#define MANEJADOREXAMENES_H

#include <QList>
#include "examen.h"

class ManejadorExamenes {
public:
    ManejadorExamenes(const QString &archivo);

    bool agregarExamen(const Examen &examen);
    bool modificarExamen(const QString &idViejo, const Examen &nuevoExamen);
    bool eliminarExamen(const QString &id);
    QList<Examen> obtenerExamenes();

private:
    QString archivoExamenes;
};

#endif // MANEJADOREXAMENES_H
