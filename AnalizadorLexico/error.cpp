#include "error.h"
#include <QDebug>

Error::Error(QObject *parent, int estado, int no_linea)
    : QObject(parent), m_estado(estado), m_no_linea(no_linea) // inicializar el error con su estado terminal y no linea
{
    // Darle un mensaje con el constructor

    switch (this->m_estado) {
    //ERRORES LÉXICOS
    case 500:
        this->mensaje = "Para constante real, se esperaba un dígito";
        break;
    case 501:
        this->mensaje = "Para notación científica, se esperaba un +, - o dígito";
        break;
    case 502:
        this->mensaje = "Para notación científica, se esperaba un dígito";
        break;
    case 503:
        this->mensaje = "Token & no reconocido, ¿quiso decir &&?";
        break;
    case 504:
        this->mensaje = "Token | no reconocido, ¿quiso decir ||?";
        break;
    case 505:
        this->mensaje = "Constante carácter vacía o inconclusa";
        break;
    case 506:
        this->mensaje = "Elemento no reconocido por el lenguaje";
        break;
    case 507:
        this->mensaje = "Cierre de carácter ' faltante";
        break;
    case 508:
        this->mensaje = "Cierre de cadena \" faltante";
        break;
    //ERRORES SINTACTICOS

    case 600:
        this->mensaje = "Archivo vacío"; break;
    case 601:
        this->mensaje = "El código debe contener al menos una clase"; break;
    case 602:
        this->mensaje = "Error en importación de librerías, debe empezar con 'lib'"; break;
    case 603:
        this->mensaje = "Se esperaba una declaración con 'def' o una clase con 'class'"; break;
    case 604:
        this->mensaje = "Se esperaba un modificador de acceso 'private', 'public' o 'protected'"; break;
    case 605:
        this->mensaje = "Se esperaba una ','"; break;
    case 606:
        this->mensaje = "Se esperaba un tipo"; break;
    case 607:
        this->mensaje = "Error en definición de la dimensión del array, inicia con '['"; break;
    case 608:
        this->mensaje = "Se esperaba una ','"; break;
    case 609:
        this->mensaje = "Se esperaba un tipo válido"; break;
    case 610:
        this->mensaje = "Error en definición del bloque principal, hace falta 'main'"; break;
    case 611:
        this->mensaje = "Se esperaba una sentencia, el final de una sentencia o el final de main: 'end'"; break;
    case 612:
        this->mensaje = "Una asignación empieza con un identificador"; break;
    case 613:
        this->mensaje = "Se esperaba un '[' para la declaración de la dimensión, op. relacional, '&&', '||', op. aritmético."; break;
    case 614:
        this->mensaje = "Se esperaba una ',' para agregar más expresiones"; break;
    case 615:
        this->mensaje = "Una expresión inicia con un identificador, un '!' o un '('"; break;
    case 616:
        this->mensaje = "Se esperaba un '||' o directamente el final de la expresión"; break;
    case 617:
        this->mensaje = "Se espera constante, '(', o identificador"; break;
    case 618:
        this->mensaje = "Se esperaba un '||', '&&' o el final de la expresión"; break;
    case 619:
        this->mensaje = "Se esperaba una constante, identificador, '!' o '(expresión)'"; break;
    case 620:
        this->mensaje = "Se esperaba una constante, identificador o '(expresión)'"; break;
    case 621:
        this->mensaje = "Se esperaba un operador relacional, operador lógico o el fin de la expresión"; break;
    case 622:
        this->mensaje = "Se esperaba una constante, identificador o '(expresión)'"; break;
    case 623:
        this->mensaje = "Se esperaba '+', '-', operador relacional, '&&', '||' o el final de la expresión"; break;
    case 624:
        this->mensaje = "Se esperaba constante, identificador o '(expresión)'"; break;
    case 625:
        this->mensaje = "Se esperaba operador aritmético, relacional, '&&', '||' o el final de la expresión"; break;
    case 626:
        this->mensaje = "Se esperaba un operador relacional"; break;
    case 627:
        this->mensaje = "Se esperaba una constante, identificador o '(expresión)'"; break;
    case 628:
        this->mensaje = "Se esperaba 'onput'"; break;
    case 629:
        this->mensaje = "Se esperaba 'input'"; break;
    case 630:
        this->mensaje = "Se esperaba 'if'"; break;
    case 631:
        this->mensaje = "Se esperaba 'else', 'elseif' o 'endif'"; break;
    case 632:
        this->mensaje = "Se esperaba un 'else' o 'endif'"; break;
    case 633:
        this->mensaje = "Se esperaba 'while'"; break;
    case 634:
        this->mensaje = "Se esperaba 'do'"; break;
    case 635:
        this->mensaje = "Se esperaba un(a) "; break;

    default:
        // Manejar el caso por defecto (valor de m_estado no reconocido)
        this->mensaje = "Error léxico no reconocido";
        break;
    }
    setTipoError(this->m_estado);
}

Error::~Error()
{
    qDebug() << "Murió el error";
}

QString Error::toString()
{
    return "[Error "+this->tipo_error+" "+QString::number(this->m_estado)+" ] en línea "+QString::number(this->m_no_linea)+" :"+this->mensaje;
}

int Error::getLinea()
{
    return this->m_no_linea;
}

void Error::setMensaje(const QString &newMensaje)
{
    mensaje = newMensaje;
}

QString Error::getMensaje() const
{
    return mensaje;
}
void Error::setTipoError(int edo){
    if(edo < 600){
        this->tipo_error = "léxico";
    }else if(edo < 700){
        this->tipo_error = "sintáctico";
    }else{
        this->tipo_error = "desconocido";
    }
}
