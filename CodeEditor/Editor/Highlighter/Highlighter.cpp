#include "Highlighter.h"
#include <QDebug>
#include <QFile>
#include <QXmlStreamReader>

namespace Ryntra::CodeEditor {
    RikoHighlighter::RikoHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    }

    void RikoHighlighter::loadTheme(const QString &path) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open theme file: " << path << ", highlighting will have no effects.";
            return;
        }

        QXmlStreamReader xml(&file);
        palette.clear();
        formats.clear();

        while (!xml.atEnd() && !xml.hasError()) {
            auto token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                if (xml.name() == QStringLiteral("Color")) {
                    auto name = xml.attributes().value("name").toString();
                    auto hex = xml.attributes().value("hex").toString();
                    palette[name] = QColor(hex);
                } else if (xml.name() == QStringLiteral("Style")) {
                    auto name = xml.attributes().value("name").toString();
                    auto colorName = xml.attributes().value("color").toString();
                    auto bold = xml.attributes().value("bold").toString() == "true";
                    auto italic = xml.attributes().value("italic").toString() == "true";

                    QTextCharFormat format;
                    if (palette.contains(colorName)) {
                        format.setForeground(palette[colorName]);
                    } else {
                        format.setForeground(QColor(colorName));
                    }

                    if (bold) {
                        format.setFontWeight(QFont::Bold);
                    }

                    if (italic) {
                        format.setFontItalic(true);
                    }

                    formats[name] = format;
                }
            }
        }

        if (xml.hasError()) {
            qWarning() << "XML Syntax Error in theme: " << xml.errorString();
        }
    }

    void RikoHighlighter::addRule(const QString &pattern, const QTextCharFormat &format) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = format;
        highlightingRules.append(rule);
    }

    void RikoHighlighter::loadLanguage(const QString &path) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning() << "Failed to open language file:" << path;
            return;
        }

        highlightingRules.clear();
        QXmlStreamReader xml(&file);

        while (!xml.atEnd() && !xml.hasError()) {
            QXmlStreamReader::TokenType token = xml.readNext();
            if (token == QXmlStreamReader::StartElement) {
                auto name = xml.name();
                if (name == QStringLiteral("Keyword")) {
                    QString keyword = xml.readElementText();
                    if (!keyword.isEmpty()) {
                        addRule("\\b" + keyword + "\\b", formats.value("Keyword"));
                    }
                } else if (name == QStringLiteral("Number")) {
                    QString pattern = xml.readElementText();
                    if (!pattern.isEmpty()) {
                        addRule(pattern, formats.value("Number"));
                    }
                } else if (name == QStringLiteral("Singleline")) {
                    QString pattern = xml.readElementText();
                    if (!pattern.isEmpty()) {
                        addRule(pattern, formats.value("Comment"));
                    }
                } else if (name == QStringLiteral("Multiline")) {
                    QString pattern = xml.readElementText();
                    int splitIndex = pattern.indexOf("[\\s\\S]*?");
                    if (splitIndex != -1) {
                        QString start = pattern.left(splitIndex);
                        QString end = pattern.mid(splitIndex + 9);
                        commentStartExpression = QRegularExpression(start);
                        commentEndExpression = QRegularExpression(end);
                    } else {
                         // Fallback for standard C-style if regex parsing fails
                        commentStartExpression = QRegularExpression("/\\*");
                        commentEndExpression = QRegularExpression("\\*/");
                    }
                } else if (name == QStringLiteral("String")) {
                    QString pattern = xml.readElementText();
                    if (!pattern.isEmpty()) {
                        addRule(pattern, formats.value("String"));
                    }
                } else if (name == QStringLiteral("Characters")) {
                    QString pattern = xml.readElementText();
                    if (!pattern.isEmpty()) {
                        addRule(pattern, formats.value("String"));
                    }
                }
            }
        }

        rehighlight();
    }

    void RikoHighlighter::highlightBlock(const QString &text) {
        for (const HighlightingRule &rule : highlightingRules) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }

        setCurrentBlockState(0);

        // Multiline comments
        if (commentStartExpression.pattern().isEmpty() || commentEndExpression.pattern().isEmpty())
            return;

        int startIndex = 0;
        if (previousBlockState() != 1) {
            startIndex = text.indexOf(commentStartExpression);
        }

        while (startIndex >= 0) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;

            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + match.capturedLength();
            }

            setFormat(startIndex, commentLength, formats.value("Comment"));
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
        }
    }
} // namespace Ryntra::CodeEditor