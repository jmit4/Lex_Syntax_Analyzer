#ifndef TOKEN_H
#define TOKEN_H

#include <QObject>

class Token : public QObject
{
    Q_OBJECT
private:
    int m_estado;
    QString m_lexema;
    QString m_gramema;
    int m_no_linea;


public:
    explicit Token(QObject* parent = nullptr, int estado = 0, QString lexema = "", int no_linea = 0);
    ~Token();
    QString getLexema() const;
    QString getGramema() const;
    int getEstado() const;
    QString toString();
    QString relacionarConGramema(int estado);

    int no_linea() const;
};

#endif // TOKEN_H
