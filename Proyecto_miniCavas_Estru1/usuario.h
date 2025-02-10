#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
public:
    Usuario();
    Usuario(const QString &usuario, const QString &password, const QString &tipoUsuario,
            const QString &nombre, const QString &apellido, const QString &sueldo = "");
    QString getUsuario() const;
    QString getPassword() const;
    QString getTipoUsuario() const;
    QString getNombre() const;
    QString getApellido() const;
    QString getSueldo() const;

    void setUsuario(const QString &usuario);
    void setPassword(const QString &password);
    void setTipoUsuario(const QString &tipoUsuario);
    void setNombre(const QString &nombre);
    void setApellido(const QString &apellido);
    void setSueldo(const QString &sueldo);

private:
    QString usuario;
    QString password;
    QString tipoUsuario;
    QString nombre;
    QString apellido;
    QString sueldo;
};

#endif // USUARIO_H
