#include "renderwidget.h"
#include "../rengine/renderer.h"

Renderer renderer = Renderer::getInstance();
Model model("../../object/nanosuit.obj");
Camera camera;

RenderWidget::RenderWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
    setMouseTracking(true);
}

void RenderWidget::initializeGL()
{
    makeCurrent();
    Scene scene;
    scene.mModel = &model;
    scene.mainCamera = camera;

    renderer.setActiveScene(scene);
    renderer.prepare();
}

void RenderWidget::paintGL()
{
    renderer.render();
}

void RenderWidget::resizeGL(int w, int h)
{
    renderer.resize(w,h);
}

Qt::MouseButton clickedButton = Qt::NoButton;
int clickX = -1;
int clickY = -1;

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    clickedButton = event->button();
    clickX = event->x();
    clickY = event->y();
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    clickedButton = Qt::NoButton;
    clickX = -1;
    clickY = -1;
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    float sensitivity = 0.6f;
    // left click
    if (clickedButton == Qt::LeftButton) {
        float xoffset = event->x() - clickX;
        clickX = event->x();

        xoffset *= sensitivity;

        model.rotateHorizontally(xoffset);

    }
    // right click
    else if (clickedButton == Qt::RightButton) {
        float yoffset = clickY - event->y();
        float xoffset = event->x() - clickX;
        clickY = event->y();
        clickX = event->x();

        float speed = 0.01f;
        xoffset *= sensitivity * speed;
        yoffset *= sensitivity * speed;

        if (xoffset > 0) {
          camera.move(RIGHTWARD, xoffset);
        } else if (xoffset < 0){
          camera.move(LEFTWARD, -xoffset);
        }

        if (yoffset > 0) {
          camera.move(UPWARD, yoffset);
        } else if (yoffset < 0){
          camera.move(DOWNWARD, -yoffset);
        }

    }

    // middle click
    else if (clickedButton == Qt::MidButton) {
        float yoffset = clickY - event->y();
        clickY = event->y();

        yoffset *= sensitivity;

        model.rotateVertically(yoffset);
    }

    update();
}

void RenderWidget::wheelEvent(QWheelEvent *event)
{
    float speed = event->delta() / 1000.0;
    if (speed >= 0) {
        camera.move(FORWARD, speed);
    } else {
        camera.move(BACKWARD, -speed);
    }

    update();
}
