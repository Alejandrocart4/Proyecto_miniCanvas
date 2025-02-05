#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
public:
    Usuario();
    Usuario(const QString &usuario, const QString &password, const QString &tipoUsuario, const QString &nombre, const QString &apellido);

    QString getUsuario() const;
    QString getPassword() const;
    QString getTipoUsuario() const;
    QString getNombre() const;
    QString getApellido() const;

    void setUsuario(const QString &usuario);
    void setPassword(const QString &password);
    void setTipoUsuario(const QString &tipoUsuario);
    void setNombre(const QString &nombre);
    void setApellido(const QString &apellido);

private:
    QString usuario;
    QString password;
    QString tipoUsuario;
    QString nombre;
    QString apellido;
};

#endif // USUARIO_H
