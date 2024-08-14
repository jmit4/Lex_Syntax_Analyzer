#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QListWidget>
#include <QStack>
#include <QList>
#include "lexer.h"
#include "token.h"
#include "error.h"

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser(QObject *parent = nullptr, QListWidget *tabla_err = nullptr, Lexer *lex = nullptr);
    ~Parser();
    int parse();
    Error *getError() const;

private:
    Token* token;
    Error* error;

    QStack<int> stack;
    int** producciones = new int*[76];
    int sizes[76] = {6,0,4,0,9,1,1,1,3,0,2,0,4,3,0,1,1,1,1,1,5,3,3,3,2,2,2,0,3,2,0,4,0,3,2,0,2,2,0,2,2,1,2,0,2,2,0,2,2,2,2,2,2,0,1,1,1,1,1,1,1,1,1,1,1,3,1,5,5,8,0,6,0,2,6,7};
    QListWidget* m_tabla_err;
    Lexer* lexer;
    Token* getNextToken();

    void vaciarPila();
    void inicializarPila();
    void liberarToken(Token *&token);
    QString relacionarTokenConGramema(int estado);
};

#endif // PARSER_H
