#include "examen.h"

// Implementación de Pregunta
Pregunta::Pregunta() {}

Pregunta::Pregunta(const QString &enunciado, const QString &tipo, const QString &opciones, const QString &respuestaCorrecta)
    : enunciado(enunciado), tipo(tipo), opciones(opciones), respuestaCorrecta(respuestaCorrecta) {}

QString Pregunta::getEnunciado() const { return enunciado; }
QString Pregunta::getTipo() const { return tipo; }
QString Pregunta::getOpciones() const { return opciones; }
QString Pregunta::getRespuestaCorrecta() const { return respuestaCorrecta; }

void Pregunta::setEnunciado(const QString &enunciado) { this->enunciado = enunciado; }
void Pregunta::setTipo(const QString &tipo) { this->tipo = tipo; }
void Pregunta::setOpciones(const QString &opciones) { this->opciones = opciones; }
void Pregunta::setRespuestaCorrecta(const QString &respuestaCorrecta) { this->respuestaCorrecta = respuestaCorrecta; }

// Implementación de Examen
Examen::Examen() {}

Examen::Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, double duracion)
    : id(id), nombre(nombre), fecha(fecha), hora(hora), duracion(duracion) {}

Examen::Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, double duracion, const QList<Pregunta> &preguntas)
    : id(id), nombre(nombre), fecha(fecha), hora(hora), duracion(duracion), preguntas(preguntas) {}

QString Examen::getID() const { return id; }
QString Examen::getNombre() const { return nombre; }
QString Examen::getFecha() const { return fecha; }
QString Examen::getHora() const { return hora; }
double Examen::getDuracion() const { return duracion; }

void Examen::agregarPregunta(const QString &enunciado, const QString &tipo, const QString &opciones, const QString &respuestaCorrecta) {
    preguntas.append(Pregunta(enunciado, tipo, opciones, respuestaCorrecta));
}

void Examen::eliminarPregunta(int index) {
    if (index >= 0 && index < preguntas.size()) {
        preguntas.removeAt(index);
    }
}

void Examen::setPreguntas(const QList<Pregunta> &preguntas) {
    this->preguntas = preguntas;
}

QList<Pregunta> Examen::getPreguntas() const { return preguntas; }

//Calificar examen comparando respuestas del alumno con respuestas correctas
int Examen::calificarExamen(const QList<QString> &respuestasAlumno) const {
    if (respuestasAlumno.size() != preguntas.size()) {
        return -1; // Error: No se contestaron todas las preguntas
    }

    int puntajeTotal = 0;
    for (int i = 0; i < preguntas.size(); i++) {
        if (respuestasAlumno[i] == preguntas[i].getRespuestaCorrecta()) {
            puntajeTotal += 10; // Cada pregunta vale 10 puntos
        }
    }
    return puntajeTotal;
}
