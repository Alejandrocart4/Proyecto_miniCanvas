#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
public:
    Usuario();
    Usuario(const QString &usuario, const QString &password, const QString &tipoUsuario,
            const QString &nombre, const QString &apellido, const QString &sueldo = "",
            const QString &profesion = "", const QString &carrera = "");
    QString getUsuario() const;
    QString getPassword() const;
    QString getTipoUsuario() const;
    QString getNombre() const;
    QString getApellido() const;
    QString getSueldo() const;
    QString getProfesion() const;
    QString getCarrera() const;

    void setUsuario(const QString &usuario);
    void setPassword(const QString &password);
    void setTipoUsuario(const QString &tipoUsuario);
    void setNombre(const QString &nombre);
    void setApellido(const QString &apellido);
    void setSueldo(const QString &sueldo);
    void setProfesion(const QString &profesion);
    void setCarrera(const QString &carrera);

private:
    QString usuario;
    QString password;
    QString tipoUsuario;
    QString nombre;
    QString apellido;
    QString sueldo;
    QString profesion;
    QString carrera;
};

#endif // USUARIO_H
