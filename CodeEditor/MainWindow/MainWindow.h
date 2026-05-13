#pragma once

#include <QMainWindow>
#include <QTabWidget>
#include <QLabel>

namespace Ryntra::CodeEditor {
    class CodeEditor;

    class MainWindow : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override = default;

    private slots:
        void updateStatusBar();
        void onTabChanged(int index);
        void openFile();
        void saveFile();
        void cut();
        void copy();
        void paste();
        void undo();
        void redo();

    private:
        void setupMenuBar();
        void setupStatusBar();
        void setupCentralWidget();
        void addNewTab();

        QTabWidget *tabWidget;
        QLabel *statusLabel;
    };
}