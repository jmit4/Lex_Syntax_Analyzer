#include "widget.h"
#include "./ui_widget.h"
#include <QPushButton>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include "codeeditor.h"
#include <QTextCharFormat>
#include <QTextBlock>
#include "lexer.h"
#include "parser.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    code_editor = new CodeEditor(this);
    ui->verticalLayout_2->addWidget(code_editor);


    ui->btnCopiar->setIcon(QIcon(":/icons/icons/copia.png"));
    ui->btnPegar->setIcon(QIcon(":/icons/icons/pegar.png"));
    ui->btnCortar->setIcon(QIcon(":/icons/icons/tijeras.png"));

    QPixmap pixmap_q(":/icons/icons/question.png");
    ui->icono_correcto->setPixmap(pixmap_q);
    ui->icono_correcto->setScaledContents(true);

    // QPixmap pixmap_c(":/icons/icons/correcto.png");
    // ui->icono_correcto->setPixmap(pixmap);

    // QPixmap pixmap_i(":/icons/icons/incorrecto.png");
    // ui->icono_correcto->setPixmap(pixmap);

    connect(ui->btnCopiar, &QPushButton::clicked, [=](){
        code_editor->copy();
    });
    connect(ui->btnPegar, &QPushButton::clicked, [=](){
        code_editor->paste();
    });
    connect(ui->btnCortar, &QPushButton::clicked, [=](){
        code_editor->cut();
    });

    connect(code_editor, &CodeEditor::textChanged, this, &Widget::cambiar_texto);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnAbrir_clicked()
{
    //Si hay algo escrito y no se ha guardado, preguntar para guardarlo o deshecharlo
    if(!this->guardado && this->code_editor->toPlainText()!=""){
        int ret = QMessageBox::question(this,"Advertencia",
                                        "¿Desea guardar su código?",
                                        QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        if(ret == QMessageBox::Yes){

            this->on_btnGuardar_clicked();
        }
    }

    QString  fileContent;
    //Save the file to disk
    QString filename = QFileDialog::getOpenFileName(this,"Open File", QString(), tr("Archivos KCOD (*.kcod)"));
    qDebug() << filename;
    set_archivo_name(filename);

    if(filename.isEmpty())
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull()){
        fileContent.append(line+"\n");
        line = in.readLine();
    }
    fileContent.chop(1);
    file.close();
    this->code_editor->clear();
    this->code_editor->setPlainText(fileContent);
    set_archivo_guardado();
    reset_icono_superior();
}


void Widget::on_btnLimpiar_clicked()
{
    //preguntar si se desea guardar el code
    if(!this->guardado && this->code_editor->toPlainText()!=""){
        int ret = QMessageBox::question(this,"Advertencia",
                                        "¿Desea guardar su código?",
                                        QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        if(ret == QMessageBox::Yes){

            this->on_btnGuardar_clicked();
        }
    }
    //limpiar todo
    reset_archivo_name();
    set_archivo_no_guardado();
    code_editor->setPlainText("");
    ui->lblErrores->setText("Errores encontrados:");
    ui->lblTokens->setText("Tokens encontrados");
    ui->listErrores->clear();
    ui->listTokens->clear();
    reset_icono_superior();
}


void Widget::on_btnGuardar_clicked()
{
    if(code_editor->toPlainText() != ""){
        if(!this->guardado){
            if(nombre_archivo==""){
                QString filename = QFileDialog::getSaveFileName(this,
                                                                "Save As",
                                                                QString(),
                                                                tr("Archivos KCOD (*.kcod)"));
                if(filename.isEmpty()){
                    return;
                }
                if(filename.mid(filename.size()-5) != ".kcod"){
                    QMessageBox::warning(this,"Error","Solo se admiten archivos .kcod");
                    return;
                }

                QFile file(filename);
                set_archivo_name(filename);

                //Abrir el archivo
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    // Devuelve true si se ha podido abrir, caso contrario false
                    QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
                    return;
                }

                QTextStream out(&file);

                out << this->code_editor->toPlainText();
                file.close();
            }else{
                //solo sobreescribir con el nombre del archivo anteriormente proporcionado
                QString filename = this->nombre_archivo;
                QFile file(filename);
                //Abrir el archivo
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    // Devuelve true si se ha podido abrir, caso contrario false
                    QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
                    return;
                }

                QTextStream out(&file);
                out << this->code_editor->toPlainText();
                file.close();

            }
            set_archivo_guardado();
        }
    }else{
        QMessageBox::information(this,
                                 "No se puede guardar",
                                 "No es posible guardar, el código no tiene nada");
    }

}


void Widget::on_btnAnalizar_clicked()
{
    if(this->guardado){
        clearTextFormat();
        //Llamar al analizador, pero primero debe ser guardado el archivo
        ui->listErrores->clear();
        ui->listTokens->clear();

        qDebug() << "Llamar al analizador lexico";
        //Leer archivo
        QString fileContent = this->leer_archivo(this->nombre_archivo);
        //Llamada al analizador
        analisis(fileContent);
        qDebug() << "Fin analisis";
        /*
        analizar(fileContent);
        //Pasar lista a los widgets
        qDebug() << "Fin analisis";

        ui->lblTokens->setText("Tokens encontrados: "+QString::number(listaTokens.size()));
        ui->lblErrores->setText("Errores encontrados: "+QString::number(listaErrores.size()));

        qDebug() << "Tamaño tokens: "+ QString::number(listaTokens.size());
        qDebug() << "Tamaño errores: "+ QString::number(listaErrores.size());

        for(int i = 0; i < listaTokens.size(); i++){
            ui->listTokens->addItem(listaTokens[i]->toString());
            qDebug() << "Añado elemento token";
        }
        for(int i = 0; i < listaErrores.size(); i++){
            ui->listErrores->addItem(listaErrores[i]->toString());
            resaltar_error(listaErrores[i]->getLinea());
        }

        for (int i = 0; i < listaTokens.size(); ++i) {
            delete listaTokens[i];
        }
        // Limpiar la lista después de eliminar los elementos
        listaTokens.clear();

        for (int i = 0; i < listaErrores.size(); ++i) {
            delete listaErrores[i];
            qDebug() << "Elimino error";
        }
        */
        // Limpiar la lista después de eliminar los elementos

        set_archivo_guardado();
    }else{
        QMessageBox::information(this,"No se puede guardar","Primero guarda el código");
    }
}


void Widget::on_btnSalir_clicked()
{
    //Preguntar si se desea guardar el archivo, si hay alguno
    if(!this->guardado && this->code_editor->toPlainText()!=""){
        int ret = QMessageBox::question(this,"Advertencia",
                                        "¿Desea guardar su código?",
                                        QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel);
        if(ret == QMessageBox::Yes){
            if(this->nombre_archivo!=""){
                //si hay nombre, entonces solo sobreescribir
                QString filename = this->nombre_archivo;
                QFile file(filename);
                //Abrir el archivo
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    // Devuelve true si se ha podido abrir, caso contrario false
                    QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
                    return;
                }

                QTextStream out(&file);
                out << this->code_editor->toPlainText() << "\n";
                file.close();
            }else{
                //si no hay nombre, pedir uno
                QString filename = QFileDialog::getSaveFileName(this,"Save As", QString(),
                                                                tr("Archivos KCOD (*.kcod)"));
                if(filename.isEmpty()){
                    return;
                }
                if(filename.mid(filename.size()-5) != ".kcod"){
                    QMessageBox::warning(this,"Error","Solo se admiten archivos .kcod");
                    return;
                }

                QFile file(filename);
                set_archivo_name(filename);

                //Abrir el archivo
                if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    // Devuelve true si se ha podido abrir, caso contrario false
                    QMessageBox::warning(this,"Error","No se pudo abrir el archivo");
                    return;
                }

                QTextStream out(&file);

                out << this->code_editor->toPlainText() << "\n";
                file.close();
            }
            set_archivo_guardado();
        }else{
            if(ret == QMessageBox::Cancel){
                return;
            }
        }
        QApplication::quit();
    }else{
        int ret = QMessageBox::question(this,"Advertencia",
                                        "¿Seguro que desea salir?",
                                        QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes){
            //Salir del programa
            delete control;
            QApplication::quit();
        }
    }
}

void Widget::cambiar_texto()
{
    set_archivo_no_guardado();
    reset_icono_superior();
}

void Widget::resaltar_error(int linea)
{
    qDebug() << "Pintar linea: "+QString::number(linea-1);

    //QColor lineColor = QColor(QColor(34, 45, 50)).lighter(160);
    QTextCharFormat fmt;
    fmt.setUnderlineColor(Qt::red);
    fmt.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);

    QTextBlock block;
    block = code_editor->document()->findBlockByLineNumber(linea - 1);
    int blockPos;
    blockPos = block.position();

    QTextCursor text_cursor(code_editor->document());
    text_cursor.setPosition(blockPos);
    text_cursor.select(QTextCursor::LineUnderCursor);
    text_cursor.setCharFormat(fmt);

}

void Widget::clearTextFormat(){
    QTextCursor cursor(code_editor->document());

    // Iterar sobre cada bloque de texto en el documento
    while (!cursor.atEnd()) {
        cursor.select(QTextCursor::BlockUnderCursor);
        // Crear un formato de texto vacío para restablecer el formato
        QTextCharFormat emptyFormat;
        // Aplicar el formato vacío al bloque de texto para eliminar el formato existente
        cursor.setCharFormat(emptyFormat);   // Eliminar cualquier formato de carácter

        cursor.movePosition(QTextCursor::NextBlock);
    }
}

    /*
        Este método es una simulación de el método del analizador sintactico
    */
void Widget::analisis(QString filecontent)
{
    qDebug() << "Todo nais";
    //Crear lexer
    Lexer *lexer = new Lexer(control, filecontent, ui->listTokens, ui->listErrores);
    qDebug() << "Lexer creado";
    Parser *parser = new Parser(control, ui->listErrores, lexer);
    qDebug() << "Parser creado";
    int resultado = parser->parse();

    qDebug() << "**RESULTADO ANALISIS**: "+ QString::number(resultado);



    if(resultado != 1){
        resaltar_error(parser->getError()->getLinea());
        cambiar_icono_incorrecto();
    }else{
        cambiar_icono_correcto();
        QMessageBox::information(this, "Análisis completado", "El código es correcto", QMessageBox::Ok);
    }


    // Token *token = lexer->nextToken();

    // int cont = 0;

    // while(token->getEstado() != 158){
    //     token = lexer->nextToken();
    //     if(token == nullptr){
    //         resaltar_error(lexer->getError()->getLinea());
    //         qDebug() << "Error en vuelta: " +QString::number(cont);
    //         break; //hubo error
    //     }else{
    //         qDebug() << "TOKEN DEVUELTO:" + QString::number(token->getEstado());
    //     }
    //     cont++;
    // }


    //Esto hay que cambiarlo
    //delete control;
}
QString Widget::leer_archivo(const QString &filename){
    QString  fileContent;
    //Save the file to disk
    if(filename.isEmpty()){
        qDebug () << "El nombre del archivo está vacío";
        return "";
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug () << "No se pudo hacer nada";
        return "";
    }
    QTextStream in(&file);
    QString line = in.readLine();

    while(!line.isNull()){
        fileContent.append(line+"\n"); //readLine solo lee hasta \n, pero no lo incluye
        line = in.readLine();
    }
    fileContent.chop(1);
    file.close();
    return fileContent;
}

void Widget::cambiar_icono_correcto()
{
        QPixmap pixmap(":/icons/icons/correcto.png");
        ui->icono_correcto->setPixmap(pixmap);
}

void Widget::cambiar_icono_incorrecto()
{
    QPixmap pixmap(":/icons/icons/incorrecto.png");
    ui->icono_correcto->setPixmap(pixmap);
}

void Widget::set_archivo_guardado()
{
    this->guardado = true;
    ui->archivo_guardado->setText("Guardado");
}

void Widget::set_archivo_no_guardado()
{
    this->guardado = false;
    ui->archivo_guardado->setText("No guardado");
}

void Widget::set_archivo_name(QString nombre)
{
    this->nombre_archivo = nombre;

    QFileInfo fi(nombre);
    QString nombre_corto = fi.fileName();

    ui->archivo_abierto->setText(nombre_corto);
}

void Widget::reset_archivo_name()
{
    this->nombre_archivo = "";
    ui->archivo_abierto->setText("Ningún archivo abierto");
}

void Widget::reset_icono_superior()
{
    QPixmap pixmap(":/icons/icons/question.png");
    ui->icono_correcto->setPixmap(pixmap);
}




