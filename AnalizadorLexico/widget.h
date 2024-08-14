#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "codeeditor.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Ui::Widget *ui;

private slots:
    void on_btnAbrir_clicked();

    void on_btnLimpiar_clicked();

    void on_btnGuardar_clicked();

    void on_btnAnalizar_clicked();

    void on_btnSalir_clicked();

    void cambiar_texto();

    void resaltar_error(int linea);

    void clearTextFormat();

private:
    QObject* control = new QObject(nullptr);
    CodeEditor *code_editor;
    bool guardado;
    QString nombre_archivo;
    //Método de prueba para ver cómo funciona
    void analisis(QString filecontent);
    QString leer_archivo(const QString &filename);
    void cambiar_icono_correcto();
    void cambiar_icono_incorrecto();
    void set_archivo_guardado();
    void set_archivo_no_guardado();
    void set_archivo_name(QString nombre);
    void reset_archivo_name();
    void reset_icono_superior();
};
#endif // WIDGET_H
