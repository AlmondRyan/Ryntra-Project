#include "MainWindow/MainWindow.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char **argv) {
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    Ryntra::CodeEditor::MainWindow window;
    window.showMaximized();
    return QApplication::exec();
}