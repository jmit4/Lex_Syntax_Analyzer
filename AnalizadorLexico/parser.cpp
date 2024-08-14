#include "parser.h"
#include "lexer.h"
#include "error.h"
#include "token.h"
#include "matrizpred.h"
#include <QDebug>


Parser::Parser(QObject *parent, QListWidget *tabla_err, Lexer* lex)
    : QObject(parent), m_tabla_err(tabla_err), lexer(lex)
{
    qDebug() << "Se está creando Parser";
    //Agregar elementos al parser


    for (int i = 0; i < 76; ++i) {
        if (sizes[i] > 0) {
            qDebug() << "Todo nais4";
            producciones[i] = new int[sizes[i]];
            qDebug() << "Todo nais2";
        } else {
            producciones[i] = nullptr;
            qDebug() << "Todo nais3";
        }
         qDebug() << "Todo nais";
    }

    // Asignar valores a cada array
    producciones[0] = new int[6]{150, 9, 2, 101, 132, 1};
    producciones[1] = nullptr; // tamaño 0
    producciones[2] = new int[4]{1, 123, 101, 131};
    producciones[3] = nullptr; // tamaño 0
    producciones[4] = new int[9]{2, 123, 8, 5, 148, 4, 101, 3, 147};
    producciones[5] = new int[1]{152};
    producciones[6] = new int[1]{151};
    producciones[7] = new int[1]{153};
    producciones[8] = new int[3]{4, 101, 124};
    producciones[9] = nullptr; // tamaño 0
    producciones[10] = new int[2]{6, 149};
    producciones[11] = nullptr; // tamaño 0
    producciones[12] = new int[4]{122, 7, 102, 121};
    producciones[13] = new int[3]{7, 102, 124};
    producciones[14] = nullptr; // tamaño 0
    producciones[15] = new int[1]{133};
    producciones[16] = new int[1]{134};
    producciones[17] = new int[1]{135};
    producciones[18] = new int[1]{137};
    producciones[19] = new int[1]{136};
    producciones[20] = new int[5]{155, 10, 120, 119, 154};
    producciones[21] = new int[3]{10, 123, 11};
    producciones[22] = new int[3]{10, 123, 28};
    producciones[23] = new int[3]{10, 123, 29};
    producciones[24] = new int[2]{10, 30};
    producciones[25] = new int[2]{10, 33};
    producciones[26] = new int[2]{10, 34};
    producciones[27] = nullptr; // tamaño 0
    producciones[28] = new int[3]{15, 109, 12};
    producciones[29] = new int[2]{13, 101};
    producciones[30] = nullptr; // tamaño 0
    producciones[31] = new int[4]{122, 14, 15, 121};
    producciones[32] = nullptr; // tamaño 0
    producciones[33] = new int[3]{14, 15, 124};
    producciones[34] = new int[2]{16, 17};
    producciones[35] = nullptr; // tamaño 0
    producciones[36] = new int[2]{15, 118};
    producciones[37] = new int[2]{18, 19};
    producciones[38] = nullptr; // tamaño 0
    producciones[39] = new int[2]{17, 117};
    producciones[40] = new int[2]{20, 116};
    producciones[41] = new int[1]{20};
    producciones[42] = new int[2]{21, 22};
    producciones[43] = nullptr; // tamaño 0
    producciones[44] = new int[2]{22, 26};
    producciones[45] = new int[2]{23, 24};
    producciones[46] = nullptr; // tamaño 0
    producciones[47] = new int[2]{22, 105};
    producciones[48] = new int[2]{22, 106};
    producciones[49] = new int[2]{25, 27};
    producciones[50] = new int[2]{24, 107};
    producciones[51] = new int[2]{24, 108};
    producciones[52] = new int[2]{24, 130};
    producciones[53] = nullptr; // tamaño 0
    producciones[54] = new int[1]{110};
    producciones[55] = new int[1]{115};
    producciones[56] = new int[1]{111};
    producciones[57] = new int[1]{112};
    producciones[58] = new int[1]{113};
    producciones[59] = new int[1]{114};
    producciones[60] = new int[1]{102};
    producciones[61] = new int[1]{103};
    producciones[62] = new int[1]{104};
    producciones[63] = new int[1]{125};
    producciones[64] = new int[1]{126};
    producciones[65] = new int[3]{120, 15, 119};
    producciones[66] = new int[1]{12};
    producciones[67] = new int[5]{120, 4, 101, 119, 145};
    producciones[68] = new int[5]{120, 14, 15, 119, 146};
    producciones[69] = new int[8]{157, 32, 31, 10, 120, 15, 119, 138};
    producciones[70] = nullptr; // tamaño 0
    producciones[71] = new int[6]{31, 10, 120, 15, 119, 140};
    producciones[72] = nullptr; // tamaño 0
    producciones[73] = new int[2]{10, 139};
    producciones[74] = new int[6]{156, 10, 120, 15, 119, 144};
    producciones[75] = new int[7]{143, 120, 15, 119, 142, 10, 141};


    // QList<int> elementos = {150, 9, 2, 101, 132, 1};

    // this->producciones[0] = element

    // elementos = {};
    // this->producciones[1] = elementos;
    // qDebug() << "Todo nais 2";

    // elementos = {1, 123, 101, 131};

    // this->producciones[2] = elementos;

    // elementos = {};
    // this->producciones[3] = elementos;

    // elementos = {2, 123, 8, 5, 148, 4, 101, 3, 147};

    // this->producciones[4] = elementos;

    // elementos = {152};
    // this->producciones[5] = elementos;

    // elementos = {151};
    // this->producciones[6] = elementos;

    // elementos = {153};
    // this->producciones[7] = elementos;

    // elementos = {4, 101, 124};

    // this->producciones[8] = elementos;

    // elementos = {};
    // this->producciones[9] = elementos;

    // elementos = {6, 149};

    // this->producciones[10] = elementos;

    // elementos = {};
    // this->producciones[11] = elementos;

    // elementos = {122, 7, 102, 121};

    // this->producciones[12] = elementos;

    // elementos = {7, 102, 124};

    // this->producciones[13] = elementos;

    // elementos = {};
    // this->producciones[14] = elementos;

    // elementos = {133};
    // this->producciones[15] = elementos;

    // elementos = {134};
    // this->producciones[16] = elementos;

    // elementos = {135};
    // this->producciones[17] = elementos;

    // elementos = {137};
    // this->producciones[18] = elementos;

    // elementos = {136};
    // this->producciones[19] = elementos;

    // elementos = {155, 10, 120, 119, 154};

    // this->producciones[20] = elementos;

    // elementos = {10, 123, 11};

    // this->producciones[21] = elementos;

    // elementos = {10, 123, 28};

    // this->producciones[22] = elementos;

    // elementos = {10, 123, 29};

    // this->producciones[23] = elementos;

    // elementos = {10, 30};

    // this->producciones[24] = elementos;

    // elementos = {10, 33};

    // this->producciones[25] = elementos;

    // elementos = {10, 34};

    // this->producciones[26] = elementos;

    // elementos = {};
    // this->producciones[27] = elementos;

    // elementos = {15, 109, 12};

    // this->producciones[28] = elementos;

    // elementos = {13, 101};

    // this->producciones[29] = elementos;

    // elementos = {};
    // this->producciones[30] = elementos;

    // elementos = {122, 14, 15, 121};

    // this->producciones[31] = elementos;

    // elementos = {};
    // this->producciones[32] = elementos;

    // elementos = {14, 15, 124};

    // this->producciones[33] = elementos;

    // elementos = {16, 17};

    // this->producciones[34] = elementos;

    // elementos = {};
    // this->producciones[35] = elementos;

    // elementos = {15, 118};

    // this->producciones[36] = elementos;

    // elementos = {18, 19};

    // this->producciones[37] = elementos;

    // elementos = {};
    // this->producciones[38] = elementos;

    // elementos = {17, 117};

    // this->producciones[39] = elementos;

    // elementos = {20, 116};

    // this->producciones[40] = elementos;

    // elementos = {20};
    // this->producciones[41] = elementos;

    // elementos = {21, 22};

    // this->producciones[42] = elementos;

    // elementos = {};
    // this->producciones[43] = elementos;

    // elementos = {22, 26};

    // this->producciones[44] = elementos;

    // elementos = {23, 24};

    // this->producciones[45] = elementos;

    // elementos = {};
    // this->producciones[46] = elementos;

    // elementos = {22, 105};

    // this->producciones[47] = elementos;

    // elementos = {22, 106};

    // this->producciones[48] = elementos;

    // elementos = {25, 27};

    // this->producciones[49] = elementos;

    // elementos = {24, 107};

    // this->producciones[50] = elementos;

    // elementos = {24, 108};

    // this->producciones[51] = elementos;

    // elementos = {24, 130};

    // this->producciones[52] = elementos;

    // elementos = {};
    // this->producciones[53] = elementos;

    // elementos = {110};
    // this->producciones[54] = elementos;

    // elementos = {115};
    // this->producciones[55] = elementos;

    // elementos = {111};
    // this->producciones[56] = elementos;

    // elementos = {112};
    // this->producciones[57] = elementos;

    // elementos = {113};
    // this->producciones[58] = elementos;

    // elementos = {114};
    // this->producciones[59] = elementos;

    // elementos = {102};
    // this->producciones[60] = elementos;

    // elementos = {103};
    // this->producciones[61] = elementos;

    // elementos = {104};
    // this->producciones[62] = elementos;

    // elementos = {125};
    // this->producciones[63] = elementos;

    // elementos = {126};
    // this->producciones[64] = elementos;

    // elementos = {120, 15, 119};

    // this->producciones[65] = elementos;

    // elementos = {12};
    // this->producciones[66] = elementos;

    // elementos = {120, 4, 101, 119, 146};

    // this->producciones[67] = elementos;

    // elementos = {120, 14, 15, 119, 145};

    // this->producciones[68] = elementos;

    // elementos = {157, 32, 31, 10, 120, 15, 119, 138};

    // this->producciones[69] = elementos;

    // elementos = {};
    // this->producciones[70] = elementos;

    // elementos = {31, 10, 120, 15, 119, 140};

    // this->producciones[71] = elementos;

    // elementos = {};
    // this->producciones[72] = elementos;

    // elementos = {10, 139};

    // this->producciones[73] = elementos;

    // elementos = {156, 10, 120, 15, 119, 144};

    // this->producciones[74] = elementos;

    // elementos = {143, 120, 15, 119, 142, 10, 141};

    // this->producciones[75] = elementos;

    qDebug() << "Todo nais 3";

}

Parser::~Parser()
{

    for (int i = 0; i < 76; ++i) {
        if (producciones[i] != nullptr) {
            delete[] producciones[i];
        }
    }
    delete[] producciones;
    qDebug() << "Muere Parser";
}

Token *Parser::getNextToken()
{
    return this->lexer->nextToken();
}


//-1 error léxico, 0 error sintactico, 1 sin errores
int Parser::parse()
{
    qDebug() << "Inicia analisis sintaxis";
    inicializarPila();
    int tope;
    int estado_token;
    int no_prod;
    int no_linea = 1;

    token = getNextToken();
    if(token!= nullptr){
        if(token->getEstado() != 158){
            no_linea = token->no_linea();
        }
    }else{
        return -1;
    }
    do{
        qDebug() << "Vuelta";
        if(token == nullptr){
            qDebug() << "Error en vuelta: ";
            this->error = lexer->getError();
            return -1; //Error de léxico
        }else{
            estado_token = token->getEstado();
            qDebug() << "TOKEN DEVUELTO:" + QString::number(token->getEstado());
            tope = stack.top();

            //Si es un terminal
            if(tope >= 100){
                if(tope == estado_token && tope == 158){
                    liberarToken(token);
                    qDebug() << "Tope: " + QString::number(tope);
                    qDebug() << "estado token: " + QString::number(estado_token);
                    return 1;
                }else{
                    if(tope == estado_token && tope != 158){
                        qDebug() << "Tope: " + QString::number(tope);
                        stack.pop();
                        liberarToken(token);
                        token = getNextToken();
                        if(token != nullptr){
                            if(token->getEstado() != 158){
                                no_linea = token->no_linea();
                            }
                        }else{
                            this->error = lexer->getError();
                            liberarToken(token);
                            return -1;
                        }
                    }else{
                        //Esperaba un X
                        error = new Error(this->parent(), 635, no_linea);
                        qDebug() << "Tope: " + QString::number(tope);
                        error->setMensaje(error->getMensaje()+"'"+relacionarTokenConGramema(tope)+"'");
                        m_tabla_err->addItem(error->toString());
                        liberarToken(token);
                        return 0;
                    }
                }
            }else{ //No es un terminal
                no_prod = obtenerProduccion(tope, estado_token-101);
                qDebug() << "No. prod en celda: " + QString::number(no_prod);
                if(no_prod < 600){
                    stack.pop();

                    for (int j = 0; j < sizes[no_prod]; ++j) {
                        stack.push(producciones[no_prod][j]);
                    }
                    // foreach (int elemento, this->producciones[no_prod]) {
                    //     qDebug() << "Elemento: " + QString::number(elemento);
                    //     stack.push(elemento);
                    // }
                }else{
                    qDebug() << "*ERROR, esperaba alguno de los first de X";
                    qDebug() << "Número de línea parser: " + QString::number(no_linea);
                    error = new Error(this->parent(), no_prod, no_linea);
                    m_tabla_err->addItem(error->toString());
                    liberarToken(token);
                    return 0;
                }
            }
        }
        if(stack.isEmpty()){
            qDebug() << "La pila está vacía";
        }else{
            qDebug() << "La pila no está vacía";
        }

    }while(!(token->getEstado() == 158 && stack.isEmpty()));
    liberarToken(token);
    return 1;
}

Error *Parser::getError() const
{
    return error;
}

void Parser::inicializarPila()
{
    //Vaciar pila
    vaciarPila();
    //Inicializar pila con valores $PROGRAM
    this->stack.push(158);
    this->stack.push(0);
}

void Parser::liberarToken(Token*& token)
{
    qDebug() << "Se elimina token";
    if (token != nullptr) {
        delete token;
        token = nullptr; // Asignar nullptr para evitar problemas de puntero no válido
    }
}

QString Parser::relacionarTokenConGramema(int estado)
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
        return "lib";
        break;
    case 132:
        return "class";
        break;
    case 133:
        return "int";
        break;
    case 134:
        return "float";
        break;
    case 135:
        return "char";
        break;
    case 136:
        return "string";
        break;
    case 137:
        return "bool";
        break;
    case 138:
        return "if";
        break;
    case 139:
        return "else";
        break;
    case 140:
        return "elseif";
        break;
    case 141:
        return "do";
        break;
    case 142:
        return "dowhile";
        break;
    case 143:
        return "enddo";
        break;
    case 144:
        return "while";
        break;
    case 145:
        return "input";
        break;
    case 146:
        return "output";
        break;
    case 147:
        return "def";
        break;
    case 148:
        return "as";
        break;
    case 149:
        return "array";
        break;
    case 150:
        return "endclass";
        break;
    case 151:
        return "private";
        break;
    case 152:
        return "public";
        break;
    case 153:
        return "protected";
        break;
    case 154:
        return "main";
        break;
    case 155:
        return "end";
        break;
    case 156:
        return "endwhile";
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
void Parser::vaciarPila(){
    this->stack.clear();
}
