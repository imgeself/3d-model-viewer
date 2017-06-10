#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionReset_Position_triggered();

    void on_actionSettings_triggered(bool checked);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
