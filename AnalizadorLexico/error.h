#ifndef ERROR_H
#define ERROR_H

#include <QObject>

class Error : public QObject
{
    Q_OBJECT

public:
    explicit Error(QObject *parent = nullptr, int estado = 0, int no_linea = 0); // para que no cree con parametros en conversiones, ni cosas raras
    ~Error();
    QString toString();
    int getLinea();

    void setMensaje(const QString &newMensaje);

    QString getMensaje() const;

private:
    int m_estado;
    int m_no_linea;
    QString mensaje;
    QString tipo_error;
    void setTipoError(int edo);
};

#endif // ERROR_H

