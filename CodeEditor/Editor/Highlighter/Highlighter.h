#pragma once

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>
#include <QMap>

namespace Ryntra::CodeEditor {
    class RikoHighlighter : public QSyntaxHighlighter {
        Q_OBJECT
    public:
        explicit RikoHighlighter(QTextDocument *parent = nullptr);
        void loadTheme(const QString &path);
        void loadLanguage(const QString &path);

    protected:
        void highlightBlock(const QString &text) override;

    private:
        struct HighlightingRule {
            QRegularExpression pattern;
            QTextCharFormat format;
        };

        QVector<HighlightingRule> highlightingRules;
        QRegularExpression commentStartExpression, commentEndExpression;

        QMap<QString, QTextCharFormat> formats;
        QMap<QString, QColor> palette;

        void addRule(const QString &pattern, const QTextCharFormat &format);
    };
} // namespace Ryntra::CodeEditor