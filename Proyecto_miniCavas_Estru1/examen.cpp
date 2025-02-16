#include "examen.h"

Examen::Examen() {}

Examen::Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, int duracion)
    : id(id), nombre(nombre), fecha(fecha), hora(hora), duracion(duracion) {}

QString Examen::getID() const { return id; }
QString Examen::getNombre() const { return nombre; }
QString Examen::getFecha() const { return fecha; }
QString Examen::getHora() const { return hora; }
int Examen::getDuracion() const { return duracion; }

void Examen::setID(const QString &id) { this->id = id; }
void Examen::setNombre(const QString &nombre) { this->nombre = nombre; }
void Examen::setFecha(const QString &fecha) { this->fecha = fecha; }
void Examen::setHora(const QString &hora) { this->hora = hora; }
void Examen::setDuracion(int duracion) { this->duracion = duracion; }
