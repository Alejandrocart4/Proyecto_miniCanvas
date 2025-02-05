#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

class Usuario {
public:
    Usuario();
    Usuario(const QString &usuario, const QString &password, const QString &rol);

    QString getUsuario() const;
    QString getPassword() const;
    QString getRol() const;

    void setUsuario(const QString &usuario);
    void setPassword(const QString &password);
    void setRol(const QString &rol);

private:
    QString usuario;
    QString password;
    QString rol;
};

#endif // USUARIO_H
