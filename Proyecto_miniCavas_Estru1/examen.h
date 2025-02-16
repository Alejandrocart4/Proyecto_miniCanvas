#ifndef EXAMEN_H
#define EXAMEN_H

#include <QString>
#include <QList>

class Examen {
public:
    Examen();
    Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, int duracion);

    QString getID() const;
    QString getNombre() const;
    QString getFecha() const;
    QString getHora() const;
    int getDuracion() const;

    void setID(const QString &id);
    void setNombre(const QString &nombre);
    void setFecha(const QString &fecha);
    void setHora(const QString &hora);
    void setDuracion(int duracion);

private:
    QString id;
    QString nombre;
    QString fecha;
    QString hora;
    int duracion;
};

#endif // EXAMEN_H
