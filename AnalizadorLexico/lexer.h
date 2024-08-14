#ifndef LEXER_H
#define LEXER_H

#include <QObject>
#include "token.h"
#include "error.h"
#include <QListWidget>

class Lexer : public QObject
{
    Q_OBJECT
public:
    explicit Lexer(QObject* parent = nullptr,
                   QString filecontent = "",
                   QListWidget* tabla_tk = nullptr,
                   QListWidget* tabla_err = nullptr);
    ~Lexer();

    Token* lexicalAnalysis();
    Token* nextToken();
    bool getHuboerror() const;

    Error *getError() const;

    void setFilecontent(const QString &newFilecontent);

private:
    Token* token;
    Token* final_archivo = new Token(this->parent(), 158, "$", 0);

    Error* error;

    QListWidget* m_tabla_tk;
    QListWidget* m_tabla_err;

    int final_lex;
    int inicio_lex;
    int edo;
    int col;
    int longitud_cadena;
    int no_linea;
    int longitud_lexema;
    int edo_palabra_reservada;
    QString m_filecontent;
    QString lexema;
    QChar caracter;
    int relaciona(QChar caracter);
    bool pasa_directo(int edo);
    int es_palabra_reservada(QString lexema);
    int relacionar_token_finales(int valor_final);
    int relacionar_errores_finales(int valor_final);
    bool huboerror;
    void liberar_token(Token*& token);

};

#endif // LEXER_H
