#include "token.h"
#include <QDebug>

int Token::no_linea() const
{
    return m_no_linea;
}

Token::Token(QObject *parent, int estado, QString lexema, int no_linea)
    : QObject(parent), m_estado(estado), m_lexema(lexema), m_no_linea(no_linea)
{
    //Vamos a inicializar dandole el granema según el estado
    // Esto se va a tener que cambiar

    this->m_gramema = relacionarConGramema(this->m_estado);
}

Token::~Token()
{
    qDebug() << "Murió el token :"+m_lexema;
}

QString Token::getLexema() const
{
    return m_lexema;
}


QString Token::getGramema() const
{
    return m_gramema;
}

int Token::getEstado() const
{
    return m_estado;
}

QString Token::toString()
{
    return "("+m_lexema+", "+m_gramema+")";

}

QString Token::relacionarConGramema(int estado)
{
    switch (estado) {
    case 100:
        return "Palabra reservada";
        break;
    case 101:
        return "Identificador";
        break;
    case 102:
        return "Entero";
        break;
    case 103:
        return "Real";
        break;
    case 104:
        return "Notación científica";
        break;
    case 105:
        return "Suma";
        break;
    case 106:
        return "Resta";
        break;
    case 107:
        return "Multiplicación";
        break;
    case 108:
        return "División";
        break;
    case 109:
        return "Asignación";
        break;
    case 110:
        return "Igual";
        break;
    case 111:
        return "Menor que";
        break;
    case 112:
        return "Menor o igual que";
        break;
    case 113:
        return "Mayor que";
        break;
    case 114:
        return "Mayor o igual que";
        break;
    case 115:
        return "Diferente";
        break;
    case 116:
        return "Operador NOT";
        break;
    case 117:
        return "Operador AND";
        break;
    case 118:
        return "Operador OR";
        break;
    case 119:
        return "Paréntesis abierto";
        break;
    case 120:
        return "Paréntesis cerrado";
        break;
    case 121:
        return "Corchete abierto";
        break;
    case 122:
        return "Corchete cerrado";
        break;
    case 123:
        return "Punto y coma";
        break;
    case 124:
        return "Coma";
        break;
    case 125:
        return "Carácter";
        break;
    case 126:
        return "Cadena de caracteres";
        break;
    case 127:
        return "Comentario de línea";
        break;
    case 128:
        return "Llave abierta";
        break;
    case 129:
        return "Llave cerrada";
        break;
    case 130:
        return "Operador módulo";
        break;

    case 131:
    case 132:
    case 133:
    case 134:
    case 135:
    case 136:
    case 137:
    case 138:
    case 139:
    case 140:
    case 141:
    case 142:
    case 143:
    case 144:
    case 145:
    case 146:
    case 147:
    case 148:
    case 149:
    case 150:
    case 151:
    case 152:
    case 153:
    case 154:
    case 155:
    case 156:
    case 157:

        return "Palabra reservada";
        break;
    case 158:
        return "Final del archivo";
        break;
    default:
        return "Gramema no reconocido";
        break;
    }
    return "Gramema no reconocido";
}

