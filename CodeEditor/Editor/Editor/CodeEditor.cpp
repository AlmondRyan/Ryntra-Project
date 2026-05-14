#include "CodeEditor.h"
#include "../Highlighter/Color.h"
#include "../Highlighter/Highlighter.h"
#include "LineNumberArea.h"

#include <QPainter>
#include <QTextBlock>

namespace Ryntra::CodeEditor {
    CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent) {
        lineNumberArea = new LineNumberArea(this);
        QFont font("Consolas", 10);
        setFont(font);
        connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
        connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
        connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

        updateLineNumberAreaWidth(0);
        highlightCurrentLine();

        QPalette palette = this->palette();
        palette.setColor(QPalette::Base, Base);
        palette.setColor(QPalette::Text, Text);
        palette.setColor(QPalette::Highlight, Surface1);
        palette.setColor(QPalette::HighlightedText, Text);
        setPalette(palette);

        RikoHighlighter *highlighter = new RikoHighlighter(this->document());
        highlighter->loadTheme(":/Editor/Resources/ColorScheme/CatppuccinMacchiato.xml");
        highlighter->loadLanguage(":/Editor/Resources/LanguageDefinition/Ryntra.xml");
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    int CodeEditor::lineNumberAreaWidth() {
        int digits = 1;
        int max = qMax(1, blockCount());
        while (max >= 10) {
            max /= 10;
            ++digits;
        }
        int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

        int fontSize = font().pointSize();
        if (fontSize > 12) {
            space += (fontSize - 12) * 0.8;
        }

        int minWidth = fontMetrics().horizontalAdvance("999") + 16;
        if (space < minWidth) {
            space = minWidth;
        }

        return space;
    }

    void CodeEditor::updateLineNumberAreaWidth(int newBlockCount) {
        Q_UNUSED(newBlockCount)
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
    }

    void CodeEditor::updateLineNumberArea(const QRect &rect, int dy) {
        if (dy)
            lineNumberArea->scroll(0, dy);
        else
            lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
        if (rect.contains(viewport()->rect()))
            updateLineNumberAreaWidth(0);
    }

    void CodeEditor::indentSelection() const {
        QTextCursor cursor = this->textCursor();
        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();

        cursor.setPosition(start);
        int startBlock = cursor.blockNumber();
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        int endBlock = cursor.blockNumber();

        cursor.beginEditBlock();
        for (int i = startBlock; i <= endBlock; i++) {
            cursor.movePosition(QTextCursor::StartOfBlock);
            cursor.insertText("    ");
            cursor.movePosition(QTextCursor::NextBlock);
        }
        cursor.endEditBlock();
    }

    void CodeEditor::unindentSelection() const {
        QTextCursor cursor = textCursor();
        cursor.beginEditBlock();

        int start = cursor.selectionStart();
        int end = cursor.selectionEnd();

        cursor.setPosition(start);
        QTextBlock startBlock = cursor.block();

        cursor.setPosition(end);
        QTextBlock endBlock = cursor.block();

        QTextBlock block = startBlock;

        while (block.isValid()) {
            QTextCursor lineCursor(block);
            lineCursor.movePosition(QTextCursor::StartOfBlock);

            QString text = block.text();

            if (text.startsWith("    ")) {
                lineCursor.movePosition(QTextCursor::NextCharacter,
                                        QTextCursor::KeepAnchor, 4);
                lineCursor.removeSelectedText();
            } else if (text.startsWith("\t")) {
                lineCursor.movePosition(QTextCursor::NextCharacter,
                                        QTextCursor::KeepAnchor, 1);
                lineCursor.removeSelectedText();
            } else {
                int spaces = 0;
                while (spaces < 4 && spaces < text.length() && text[spaces] == ' ') {
                    spaces++;
                }
                if (spaces > 0) {
                    lineCursor.movePosition(QTextCursor::NextCharacter,
                                            QTextCursor::KeepAnchor, spaces);
                    lineCursor.removeSelectedText();
                }
            }

            if (block == endBlock)
                break;

            block = block.next();
        }

        cursor.endEditBlock();
    }

    void CodeEditor::resizeEvent(QResizeEvent *event) {
        QPlainTextEdit::resizeEvent(event);
        QRect cr = contentsRect();
        lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
    }

    void CodeEditor::wheelEvent(QWheelEvent *event) {
        if (event->modifiers() & Qt::ControlModifier) {
            int delta = event->angleDelta().y();
            if (delta != 0) {
                QFont currentFont = font();
                int newSize = currentFont.pointSize() + (delta > 0 ? 1 : -1);
                if (newSize >= 6 && newSize <= 72) {
                    currentFont.setPointSize(newSize);
                    setFont(currentFont);
                }
            }
            event->accept();
            return;
        }
        QPlainTextEdit::wheelEvent(event);
    }

    void CodeEditor::highlightCurrentLine() {
        QList<QTextEdit::ExtraSelection> extraSelections;
        if (!isReadOnly()) {
            QTextEdit::ExtraSelection selection;
            QColor lineColor = QColor(240, 240, 245, 30);
            selection.format.setBackground(lineColor);
            // selection.format.setForeground(Qt::white);
            selection.format.setProperty(QTextFormat::FullWidthSelection, true);
            selection.cursor = textCursor();
            selection.cursor.clearSelection();
            extraSelections.append(selection);
        }
        setExtraSelections(extraSelections);
    }

    void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event) {
        QPainter painter(lineNumberArea);

        QColor bgColor = palette().color(QPalette::Base);
        painter.fillRect(event->rect(), bgColor);

        int rightEdge = lineNumberArea->width() - 1;
        painter.setPen(Qt::white);
        painter.drawLine(rightEdge, event->rect().top(),
                         rightEdge, event->rect().bottom());

        QTextBlock block = firstVisibleBlock();
        int blockNumber = block.blockNumber();
        int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
        int bottom = top + qRound(blockBoundingRect(block).height());

        QColor textColor = palette().color(QPalette::Text);
        textColor = textColor.darker(110);
        painter.setPen(textColor);

        while (block.isValid() && top <= event->rect().bottom()) {
            if (block.isVisible() && bottom >= event->rect().top()) {
                QString number = QString::number(blockNumber + 1);
                painter.drawText(0, top, lineNumberArea->width() - 4, fontMetrics().height(),
                                 Qt::AlignRight, number);
            }
            block = block.next();
            top = bottom;
            bottom = top + qRound(blockBoundingRect(block).height());
            ++blockNumber;
        }
    }

    void CodeEditor::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Tab) {
            QTextCursor cursor = textCursor();
            if (event->modifiers() & Qt::ShiftModifier) {
                if (cursor.hasSelection()) {
                    unindentSelection();
                } else {
                    unindentSelection();
                }
            } else if (cursor.hasSelection()) {
                indentSelection();
            } else {
                insertPlainText("    ");
            }
            return;
        }

        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            QTextCursor cursor = textCursor();
            QTextBlock currentBlock = cursor.block();
            QString currentText = currentBlock.text();
            int positionInBlock = cursor.position() - currentBlock.position();
            QTextBlock nextBlock = currentBlock.next();
            QString nextText = nextBlock.isValid() ? nextBlock.text().trimmed() : "";

            QString indent;
            for (int i = 0; i < currentText.size(); ++i) {
                QChar ch = currentText.at(i);
                if (ch == ' ' || ch == '\t') {
                    indent.append(ch);
                } else {
                    break;
                }
            }

            QString textBeforeCursor = currentText.left(positionInBlock);
            QString textAfterCursor = currentText.mid(positionInBlock);

            cursor.beginEditBlock();

            bool atEndOfBraceLine = textBeforeCursor.trimmed().endsWith("{") && textAfterCursor.trimmed().isEmpty();
            if (atEndOfBraceLine && nextText == "}") {
                cursor.insertText("\n");
                cursor.insertText(indent + "    ");
                QTextCursor innerCursor = cursor;
                cursor.insertText("\n");
                cursor.insertText(indent);
                setTextCursor(innerCursor);
            } else if (textBeforeCursor.trimmed().endsWith("{") && textAfterCursor.trimmed().startsWith("}")) {
                cursor.insertText("\n");
                cursor.insertText(indent + "    ");
                QTextCursor innerCursor = cursor;
                cursor.insertText("\n");
                cursor.insertText(indent);

                // This is really important for best user experience of indentation logic
                // Move cursor up to the end of line of current close brace
                innerCursor.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 1);
                innerCursor.movePosition(QTextCursor::EndOfLine, QTextCursor::MoveAnchor, 1);
                setTextCursor(innerCursor);
            } else {
                bool increaseIndent = textBeforeCursor.trimmed().endsWith("{");
                QString newIndent = indent;
                if (increaseIndent) {
                    newIndent.append("    ");
                }
                cursor.insertText("\n");
                cursor.insertText(newIndent);
            }

            cursor.endEditBlock();
            return;
        }

        QString text = event->text();
        if (text.size() == 1) {
            QChar ch = text.at(0);

            if (ch == ')' || ch == ']' || ch == '}' || ch == '"' || ch == '\'') {
                QTextCursor cursor = textCursor();
                cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor);
                QString nextChar = cursor.selectedText();
                if (nextChar == QString(ch)) {
                    cursor.clearSelection();
                    setTextCursor(cursor);
                    return;
                }
            }

            QChar closingBracket;
            bool isOpeningBracket = false;
            if (ch == '(') {
                closingBracket = ')';
                isOpeningBracket = true;
            } else if (ch == '[') {
                closingBracket = ']';
                isOpeningBracket = true;
            } else if (ch == '{') {
                closingBracket = '}';
                isOpeningBracket = true;
            } else if (ch == '"') {
                closingBracket = '"';
                isOpeningBracket = true;
            } else if (ch == '\'') {
                closingBracket = '\'';
                isOpeningBracket = true;
            }

            if (isOpeningBracket) {
                QTextCursor cursor = textCursor();
                cursor.beginEditBlock();
                QPlainTextEdit::keyPressEvent(event);
                cursor = textCursor();
                cursor.insertText(QString(closingBracket));
                cursor.movePosition(QTextCursor::PreviousCharacter);
                setTextCursor(cursor);
                cursor.endEditBlock();
                return;
            }
        }

        QPlainTextEdit::keyPressEvent(event);
    }

} // namespace Ryntra::CodeEditor