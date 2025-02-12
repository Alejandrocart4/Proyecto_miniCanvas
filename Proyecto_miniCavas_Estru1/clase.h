 #ifndef CLASE_H
#define CLASE_H

#include <QString>

class Clase {
public:
    Clase();
    Clase(const QString &id, const QString &nombre, const QString &hora,
          int unidadesValorativas, int semestre, int periodo, int año);
    QString getID() const;
    QString getNombre() const;
    QString getHora() const;
    int getUnidadesValorativas() const;
    int getSemestre() const;
    int getPeriodo() const;
    int getAño() const;
    QString getUsuarioAsociado() const;

    void setID(const QString &id);
    void setNombre(const QString &nombre);
    void setHora(const QString &hora);
    void setUnidadesValorativas(int unidades);
    void setSemestre(int semestre);
    void setPeriodo(int periodo);
    void setAño(int año);
    void setUsuarioAsociado(const QString &usuario);

private:
    QString id;
    QString nombre;
    QString hora;
    int unidadesValorativas;
    int semestre;
    int periodo;
    int año;
    QString usuarioAsociado;
};

#endif // CLASE_H
