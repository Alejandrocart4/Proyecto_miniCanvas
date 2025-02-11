#include "clase.h"

Clase::Clase() {}

Clase::Clase(const QString &id, const QString &nombre, const QString &hora,
             int unidadesValorativas, int semestre, int periodo, int año,
             const QString &usuarioAsociado)
{
    this->id = id;
    this->nombre = nombre;
    this->hora = hora;
    this->unidadesValorativas = unidadesValorativas;
    this->semestre = semestre;
    this->periodo = periodo;
    this->año = año;
    this->usuarioAsociado = usuarioAsociado;
}

QString Clase::getID() const { return id; }
QString Clase::getNombre() const { return nombre; }
QString Clase::getHora() const { return hora; }
int Clase::getUnidadesValorativas() const { return unidadesValorativas; }
int Clase::getSemestre() const { return semestre; }
int Clase::getPeriodo() const { return periodo; }
int Clase::getAño() const { return año; }
QString Clase::getUsuarioAsociado() const { return usuarioAsociado; }

void Clase::setID(const QString &id) { this->id = id; }
void Clase::setNombre(const QString &nombre) { this->nombre = nombre; }
void Clase::setHora(const QString &hora) { this->hora = hora; }
void Clase::setUnidadesValorativas(int unidades) { this->unidadesValorativas = unidades; }
void Clase::setSemestre(int semestre) { this->semestre = semestre; }
void Clase::setPeriodo(int periodo) { this->periodo = periodo; }
void Clase::setAño(int año) { this->año = año; }
void Clase::setUsuarioAsociado(const QString &usuario) { this->usuarioAsociado = usuario; }
