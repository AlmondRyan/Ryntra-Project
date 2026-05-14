#pragma once

#include <QPlainTextEdit>
#include <QWidget>

namespace Ryntra::CodeEditor {
    class CodeEditor : public QPlainTextEdit {
        Q_OBJECT
    public:
        explicit CodeEditor(QWidget *parent = nullptr);

        void lineNumberAreaPaintEvent(QPaintEvent *event);
        int lineNumberAreaWidth();

    protected:
        void resizeEvent(QResizeEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

    private slots:
        void updateLineNumberAreaWidth(int newBlockCount);
        void highlightCurrentLine();
        void updateLineNumberArea(const QRect &rect, int dy);

    private:
        void indentSelection() const;
        void unindentSelection() const;

        QWidget *lineNumberArea;
    };
}