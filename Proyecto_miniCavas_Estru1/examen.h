#ifndef EXAMEN_H
#define EXAMEN_H

#include <QString>
#include <QList>
#include <stack>
#include <queue>

class Pregunta {
public:
    Pregunta();
    Pregunta(const QString &enunciado, const QString &tipo, const QString &opciones, const QString &respuestaCorrecta);

    QString getEnunciado() const;
    QString getTipo() const;
    QString getOpciones() const;
    QString getRespuestaCorrecta() const;

    void setEnunciado(const QString &enunciado);
    void setTipo(const QString &tipo);
    void setOpciones(const QString &opciones);
    void setRespuestaCorrecta(const QString &respuestaCorrecta);

private:
    QString enunciado;
    QString tipo;
    QString opciones;
    QString respuestaCorrecta;
};

class Examen {
public:
    Examen();
    Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, double duracion);
    Examen(const QString &id, const QString &nombre, const QString &fecha, const QString &hora, double duracion, const QList<Pregunta> &preguntas);

    QString getID() const;
    QString getNombre() const;
    QString getFecha() const;
    QString getHora() const;
    double getDuracion() const;

    // Métodos para manejar preguntas
    void agregarPregunta(const QString &enunciado, const QString &tipo, const QString &opciones, const QString &respuestaCorrecta);
    void eliminarPregunta(int index);
    QList<Pregunta> getPreguntas() const;
    int calificarExamen(const QList<QString> &respuestasAlumno) const;
    void setPreguntas(const QList<Pregunta> &preguntas);

private:
    QString id;
    QString nombre;
    QString fecha;
    QString hora;
    double duracion;
    QList<Pregunta> preguntas;
};

#endif // EXAMEN_H
