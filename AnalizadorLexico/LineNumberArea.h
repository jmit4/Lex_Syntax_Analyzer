#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QPalette>

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor)
    {
        QFont font("Bahnschrift", 9);
        this->setFont(font);

    }

    QSize sizeHint() const override
    {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    CodeEditor *codeEditor;
};

#endif // LINENUMBERAREA_H
