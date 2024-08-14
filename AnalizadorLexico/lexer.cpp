#include "lexer.h"
#include "matriztran.h"
#include "./ui_widget.h"
#include "widget.h"
#include <QDebug>

Lexer::Lexer(QObject *parent, QString filecontent, QListWidget *tabla_tk, QListWidget *tabla_err)
    :QObject(parent), m_filecontent(filecontent), m_tabla_tk(tabla_tk), m_tabla_err(tabla_err)
{
    //Inicializar valores para el lexico
    no_linea = 1;
    inicio_lex = final_lex = longitud_lexema = 0;
    longitud_cadena =filecontent.size();
}

Lexer::~Lexer()
{
    qDebug() << "Muere Lexer";
}

Token *Lexer::nextToken()
{
    analisis:
    lexema = "";
    if(final_lex >= longitud_cadena){
        return final_archivo;
    }
    edo = 0;
    while(edo <= 19 && final_lex < longitud_cadena){
        caracter = m_filecontent.at(final_lex);
        qDebug() << "Caracter analizado: "+QString(caracter);

        if(caracter.toLatin1() == '\n' && edo == 0){
            no_linea++;
            qDebug() << "Número de línea: "+ QString::number(no_linea);
        }
        col = relaciona(caracter);
        qDebug() << "Columna: "+QString::number(col);
        edo = matriz_tran[edo][col];
        if(edo == 0){
            inicio_lex++;
        }
        qDebug() << "Estado obtenido: "+ QString::number(edo);
        final_lex++;
    }
    if(edo >= 100 && edo <= 130){
        if(pasa_directo(edo)){ // aquí reviso si son +,-,*,/ y pasan directo
            longitud_lexema = final_lex - inicio_lex;
            lexema = m_filecontent.mid(inicio_lex, longitud_lexema);

            qDebug() << "Iniciolex: "+ QString::number(inicio_lex);
        }else{
            final_lex--;
            longitud_lexema = final_lex - inicio_lex;
            lexema = m_filecontent.mid(inicio_lex, longitud_lexema);
            //revisar si cayó en 100, y si es palabra reservada
            if(edo == 100){
                edo = es_palabra_reservada(lexema);
            }
            qDebug() << lexema;
            qDebug() << "Iniciolex 2: "+ QString::number(inicio_lex);
        }
        //crear token
        token = new Token(this->parent(), edo, lexema, no_linea);
        qDebug() << "Se creó el token";
        inicio_lex = final_lex;
        //
        this->m_tabla_tk->addItem(token->toString());
        //Preguntar si es comentario de línea
        if(edo==127){
            //No devolver y pasar a siguiente token
            //Liberar la memoria del token
            liberar_token(token);
            qDebug() << "Fue comentario de línea";
            goto analisis;
        }
        return token; //Devolvemos a sintactico
    }else{
        if(edo >=500){
            //Crear error
            error = new Error(this->parent(), edo, no_linea);
            m_tabla_err->addItem(error->toString());
            if(edo != 506 && edo != 505){
                final_lex--;
            }
            qDebug() << "Se crea error";
            this->huboerror=true;
        }else{ //En caso de que el archivo se haya acabado y dejó algo inconcluso
            if(edo!= 0){
                if(edo == 4
                    || edo == 6
                    || edo == 7
                    || edo == 13
                    || edo == 14
                    || edo == 15
                    || edo == 16
                    || edo == 17)
                {
                    edo = relacionar_errores_finales(edo);
                    qDebug() << "Estado obtenido: "+ QString::number(edo);
                    error = new Error(this->parent(), edo, no_linea);
                    m_tabla_err->addItem(error->toString());
                    qDebug () <<"Se crea el error";
                    this->huboerror=true;
                }else{
                    //Va a faltar el nuevo estado y también si es palabra reservada
                    edo = relacionar_token_finales(edo);
                    longitud_lexema = final_lex - inicio_lex;
                    lexema = m_filecontent.mid(inicio_lex, longitud_lexema);
                    if(edo == 100 || edo == 101){
                        edo = es_palabra_reservada(lexema);

                        qDebug() << "Estado obtenido final: "+ QString::number(edo);
                    }
                    qDebug() << lexema;
                    qDebug() << "Analisis palabra reservada '"+lexema+"'";
                    token = new Token(this->parent(), edo, lexema, no_linea);
                    inicio_lex = final_lex;
                    //Agregamos a la tabla
                    this->m_tabla_tk->addItem(token->toString());
                    //Preguntar si es comentario de línea
                    if(edo==127){
                        //No devolver y pasar a siguiente token
                        liberar_token(token);
                        qDebug() << "Fue comentario de línea";
                        goto analisis;
                    }
                    return token;
                }
            }
        }
    }
    inicio_lex = final_lex;

    if(this->huboerror==true){
        qDebug() << "Retornar nullprt";
        return nullptr;
    }
    //devolver final archivo sólo una vez
    return this->final_archivo;

}

int Lexer::relaciona(QChar caracter)
{
    //Convierte char a numero de columna de la funcion de transición
    if((caracter >= 'A' && caracter <= 'Z') && caracter.toLatin1()!='E'){
        return 0;
    }else if((caracter >= 'a' && caracter <= 'z') && caracter.toLatin1()!='e'){
        return 1;
    } else if(caracter.category() == QChar::Number_DecimalDigit){
        return 2;
    }else{
        switch (caracter.toLatin1()) {
        case '_':
            return 3;
            break;
        case '.':
            return 4;
            break;
        case 'E':
            return 5;
            break;
        case 'e':
            return 6;
            break;
        case '+':
            return 7;
            break;
        case '-':
            return 8;
            break;
        case '/':
            return 9;
            break;
        case '*':
            return 10;
            break;
        case '%':
            return 11;
            break;
        case ',':
            return 12;
            break;
        case ';':
            return 13;
            break;
        case '\'':
            return 14;
            break;
        case '"':
            return 15;
            break;
        case '#':
            return 16;
            break;
        case '{':
            return 17;
            break;
        case '}':
            return 18;
            break;
        case '(':
            return 19;
            break;
        case ')':
            return 20;
            break;
        case '[':
            return 21;
            break;
        case ']':
            return 22;
            break;
        case '&':
            return 23;
            break;
        case '|':
            return 24;
            break;
        case '=':
            return 25;
            break;
        case '>':
            return 26;
            break;
        case '<':
            return 27;
            break;
        case '!':
            return 28;
            break;
        case '\t':
            return 29;
            break;
        case '\n':
            return 30;
            break;
        case ' ':
            return 31;
            break;
        default:
            break;
        }
    }
    return 32;
}

bool Lexer::pasa_directo(int edo)
{
    if((edo >= 105 && edo <= 108)
        || edo == 114
        || edo == 115
        || edo == 110
        || edo == 112
        || edo == 114
        || (edo >= 117 && edo <= 125) // Se incluyo posteriormente 125
        || (edo >= 128 && edo <= 130))
    {
        return true;
    }else{
        return false;
    }
}

int Lexer::es_palabra_reservada(QString lexema)
{
    if (lexema == "lib") {
        return 131;
    } else if (lexema == "class") {
        qDebug() << "Cayó en class";
        return 132;
    } else if (lexema == "int") {
        return 133;
    } else if (lexema == "float") {
        return 134;
    } else if (lexema == "char") {
        return 135;
    } else if (lexema == "string") {
        return 136;
    } else if (lexema == "bool") {
        return 137;
    } else if (lexema == "if") {
        return 138;
    } else if (lexema == "else") {
        return 139;
    }else if(lexema == "elseif"){
        return 140;
    }else if (lexema == "do") {
        return 141;
    } else if (lexema == "dowhile") {
        return 142;
    }else if(lexema == "enddo"){
        return 143;
    } else if (lexema == "while") {
        return 144;
    }else if(lexema == "input"){
        return 145;
    }else if(lexema == "output"){
        return 146;
    }else if (lexema == "def") {
        return 147;
    } else if (lexema == "as") {
        return 148;
    } else if (lexema == "array") {
        return 149;
    } else if (lexema == "endclass") {
        return 150;
    } else if (lexema == "private") {
        return 151;
    } else if (lexema == "public") {
        return 152;
    } else if (lexema == "protected") {
        return 153;
    } else if (lexema == "main") {
        return 154;
    } else if (lexema == "end") {
        return 155;
    } else if(lexema == "endwhile"){
        return 156;
    } else if(lexema == "endif"){
        return 157;
    }else {
        return 101; // Not a reserved word
    }// Not a reserved word
}

int Lexer::relacionar_token_finales(int valor_final)
{
    switch (valor_final) {
    case 1:
        return 100;
        break;
    case 2:
        return 101;
        break;
    case 3:
        return 102;
        break;
    case 5:
        return 103;
        break;
    case 8:
        return 104;
        break;
    case 9:
        return 109;
        break;
    case 10:
        return 111;
        break;
    case 11:
        return 113;
        break;
    case 12:
        return 116;
        break;
    case 18:
        return 126;
        break;
    case 19:
        return 127;
        break;
    default:
        return -1; // Handle cases not explicitly defined
    }
}

int Lexer::relacionar_errores_finales(int valor_final)
{
    switch (valor_final) {
    case 4:
        return 500;
        break;
    case 6:
        return 501;
        break;
    case 7:
        return 502;
        break;
    case 13:
        return 503;
        break;
    case 14:
        return 504;
        break;
    case 15:
        return 505;
        break;
    case 16:
        return 507;
        break;
    case 17:
        return 508;
        break;
    default:
        return -1; // Handle cases not explicitly defined
    }
}

void Lexer::liberar_token(Token *&token)
{
    qDebug() << "Se elimina token en lexer";
    if (token != nullptr) {
        delete token;
        token = nullptr; // Asignar nullptr para evitar problemas de puntero no válido
    }
}

bool Lexer::getHuboerror() const
{
    return huboerror;
}

Error *Lexer::getError() const
{
    return error;
}

void Lexer::setFilecontent(const QString &newFilecontent)
{
    m_filecontent = newFilecontent;
}
