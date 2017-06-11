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
    void on_intensitySlider_sliderMoved(int position);

    void on_ambientSlider_sliderMoved(int position);

    void on_specularSlider_sliderMoved(int position);

    void on_lightColorButton_clicked();

    void on_bgColorButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
