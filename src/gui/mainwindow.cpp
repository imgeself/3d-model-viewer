#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

RenderWidget *renderWidget;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->settingsWidget->close();
    renderWidget = ui->renderWidget;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
   QString filename = QFileDialog::getOpenFileName(this,"Open 3D Model","",tr("All Files (*.*)"));

   Model model;
   model.loadFromFilename(filename.toStdString());

   renderWidget->mModel = model;
   renderWidget->mRenderer.cleanUp();
   renderWidget->mCamera.reset();
   renderWidget->initializeGL();
   renderWidget->resizeGL(renderWidget->width(), renderWidget->height());
   renderWidget->update();

}

void MainWindow::on_actionReset_Position_triggered()
{
    renderWidget->mModel.resetModelMatrix();
    renderWidget->mCamera.reset();
    renderWidget->update();
}

void MainWindow::on_actionSettings_triggered(bool checked)
{
    if (checked)
        ui->settingsWidget->show();
    else
        ui->settingsWidget->close();
}
