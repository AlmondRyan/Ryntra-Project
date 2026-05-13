#include "MainWindow.h"
#include "../Editor/Editor/CodeEditor.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QVBoxLayout>

namespace Ryntra::CodeEditor {
    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
        setupCentralWidget();
        setupMenuBar();
        setupStatusBar();

        resize(1024, 768);
        addNewTab();
    }

    void MainWindow::setupMenuBar() {
        QMenu *fileMenu = menuBar()->addMenu("File");
        QMenu *editMenu = menuBar()->addMenu("Edit");
        QMenu *helpMenu = menuBar()->addMenu("Help");

        fileMenu->addAction("New", QKeySequence::New, this, &MainWindow::addNewTab);
        fileMenu->addAction("Open", QKeySequence::Open, this, &MainWindow::openFile);
        fileMenu->addAction("Save", QKeySequence::Save, this, &MainWindow::saveFile);
        fileMenu->addAction("Exit", this, &MainWindow::close);

        editMenu->addAction("Undo", QKeySequence::Undo, this, &MainWindow::undo);
        editMenu->addAction("Redo", QKeySequence::Redo, this, &MainWindow::redo);
        editMenu->addAction("Cut", QKeySequence::Cut, this, &MainWindow::cut);
        editMenu->addAction("Copy", QKeySequence::Copy, this, &MainWindow::copy);
        editMenu->addAction("Paste", QKeySequence::Paste, this, &MainWindow::paste);

        helpMenu->addAction("About");
    }

    void MainWindow::setupStatusBar() {
        statusLabel = new QLabel(this);
        statusBar()->addPermanentWidget(statusLabel);
        updateStatusBar();
    }

    void MainWindow::setupCentralWidget() {
        tabWidget = new QTabWidget(this);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        setCentralWidget(tabWidget);

        connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
        connect(tabWidget, &QTabWidget::tabCloseRequested, [this](int index) {
            if (tabWidget->count() > 1) {
                tabWidget->removeTab(index);
            }
        });
    }

    void MainWindow::addNewTab() {
        auto *editor = new CodeEditor(this);
        int index = tabWidget->addTab(editor, "Untitled");
        tabWidget->setCurrentIndex(index);

        connect(editor, &CodeEditor::cursorPositionChanged, this, &MainWindow::updateStatusBar);

        updateStatusBar();
    }

    void MainWindow::onTabChanged(int index) {
        Q_UNUSED(index);
        updateStatusBar();
    }

    void MainWindow::updateStatusBar() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            QTextCursor cursor = editor->textCursor();
            int line = cursor.blockNumber() + 1;
            int col = cursor.columnNumber() + 1;
            QString fileName = tabWidget->tabText(tabWidget->currentIndex());

            statusLabel->setText(QString("File: %1 | Line: %2, Col: %3").arg(fileName).arg(line).arg(col));
        } else {
            statusLabel->clear();
        }
    }

    void MainWindow::openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File");
        if (fileName.isEmpty())
            return;

        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot open file: " + file.errorString());
            return;
        }

        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        auto *currentEditor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        bool reused = false;
        if (currentEditor && currentEditor->document()->isEmpty() && tabWidget->tabText(tabWidget->currentIndex()) == "Untitled") {
            currentEditor->setPlainText(content);
            tabWidget->setTabText(tabWidget->currentIndex(), QFileInfo(fileName).fileName());
            tabWidget->setTabToolTip(tabWidget->currentIndex(), fileName);
            reused = true;
        }

        if (!reused) {
            addNewTab();
            auto *newEditor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
            if (newEditor) {
                newEditor->setPlainText(content);
                tabWidget->setTabText(tabWidget->currentIndex(), QFileInfo(fileName).fileName());
                tabWidget->setTabToolTip(tabWidget->currentIndex(), fileName);
            }
        }
        updateStatusBar();
    }

    void MainWindow::saveFile() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (!editor) return;

        QString fileName = tabWidget->tabToolTip(tabWidget->currentIndex());
        if (fileName.isEmpty() || fileName == "Untitled") {
            fileName = QFileDialog::getSaveFileName(this, "Save File");
            if (fileName.isEmpty()) return;
        }

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Cannot save file: " + file.errorString());
            return;
        }

        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();

        tabWidget->setTabText(tabWidget->currentIndex(), QFileInfo(fileName).fileName());
        tabWidget->setTabToolTip(tabWidget->currentIndex(), fileName);
        updateStatusBar();
    }

    void MainWindow::cut() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            editor->cut();
        }
    }

    void MainWindow::copy() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            editor->copy();
        }
    }

    void MainWindow::paste() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            editor->paste();
        }
    }

    void MainWindow::undo() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            editor->undo();
        }
    }

    void MainWindow::redo() {
        auto *editor = qobject_cast<CodeEditor *>(tabWidget->currentWidget());
        if (editor) {
            editor->redo();
        }
    }
} // namespace Ryntra::CodeEditor