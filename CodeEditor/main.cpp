#include "MainWindow/MainWindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QFile>

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    QFile file(":/MainWindow/Style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        a.setStyleSheet(file.readAll());
        file.close();
    }

    Ryntra::CodeEditor::MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}