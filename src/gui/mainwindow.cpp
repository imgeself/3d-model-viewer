#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>

RenderWidget *renderWidget;

const int INTENSITY_DIVIDE_FACTOR = 20;
const int AMBIENT_DIVIDE_FACTOR = 50;
const int SPECULAR_DIVIDE_FACTOR = 50;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->settingsWidget->close();
    renderWidget = ui->renderWidget;

    // I can't set this in ui designer.
    ui->settingsLayout->setAlignment(Qt::AlignTop);

    // Set default values for sliders.
    ui->intensitySlider->setValue((int) (renderWidget->mScene.mainLight.intensity * INTENSITY_DIVIDE_FACTOR));
    ui->ambientSlider->setValue((int) (renderWidget->mScene.mainLight.ambientStrength * AMBIENT_DIVIDE_FACTOR));
    ui->specularSlider->setValue((int) (renderWidget->mScene.mainLight.specularStrength * SPECULAR_DIVIDE_FACTOR));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{

    QString filename = QFileDialog::getOpenFileName(this,"Open 3D Model");

    Model model;
    model.loadFromFilename(filename.toStdString());

    renderWidget->mScene.mainModel = model;
    renderWidget->mRenderer.cleanUp();
    renderWidget->mScene.mainCamera.reset();
    renderWidget->initializeGL();
    renderWidget->resizeGL(renderWidget->width(), renderWidget->height());
    renderWidget->update();

}

void MainWindow::on_actionReset_Position_triggered()
{
    renderWidget->mScene.mainModel.resetModelMatrix();
    renderWidget->mScene.mainCamera.reset();
    renderWidget->update();
}

void MainWindow::on_actionSettings_triggered(bool checked)
{
    if (checked)
        ui->settingsWidget->show();
    else
        ui->settingsWidget->close();
}

void MainWindow::on_intensitySlider_sliderMoved(int position)
{
    renderWidget->mScene.mainLight.intensity = (float) position / INTENSITY_DIVIDE_FACTOR;
    renderWidget->update();
}

void MainWindow::on_ambientSlider_sliderMoved(int position)
{
    renderWidget->mScene.mainLight.ambientStrength = (float) position / AMBIENT_DIVIDE_FACTOR;
    renderWidget->update();
}

void MainWindow::on_specularSlider_sliderMoved(int position)
{
    renderWidget->mScene.mainLight.specularStrength = (float) position / SPECULAR_DIVIDE_FACTOR;
    renderWidget->update();
}

void MainWindow::on_lightColorButton_clicked()
{
    QColor initial;
    initial.setRedF(renderWidget->mScene.mainLight.color.x);
    initial.setGreenF(renderWidget->mScene.mainLight.color.y);
    initial.setBlueF(renderWidget->mScene.mainLight.color.z);

    QColor color = QColorDialog::getColor(initial, this, "Select Light Color");
    renderWidget->mScene.mainLight.color.x = (float) color.redF();
    renderWidget->mScene.mainLight.color.y = (float) color.greenF();
    renderWidget->mScene.mainLight.color.z = (float) color.blueF();
    renderWidget->update();
}

void MainWindow::on_bgColorButton_clicked()
{
    QColor initial;
    initial.setRedF(renderWidget->mRenderer.mBackgroundColor.x);
    initial.setGreenF(renderWidget->mRenderer.mBackgroundColor.y);
    initial.setBlueF(renderWidget->mRenderer.mBackgroundColor.z);

    QColor color = QColorDialog::getColor(initial, this, "Select Background Color");
    renderWidget->mRenderer.mBackgroundColor.x = (float) color.redF();
    renderWidget->mRenderer.mBackgroundColor.y = (float) color.greenF();
    renderWidget->mRenderer.mBackgroundColor.z = (float) color.blueF();
    renderWidget->update();
}

void MainWindow::on_actionWireframe_triggered(bool checked)
{
    renderWidget->mRenderer.wireframeMode = checked;
    renderWidget->update();
}
