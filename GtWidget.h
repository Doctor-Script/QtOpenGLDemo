#ifndef GT_GTWIDGET_H
#define GT_GTWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

namespace gt {

class GtWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GtWidget(QWidget *parent = nullptr);
    ~GtWidget() {
        arrayBuf.destroy();
        indexBuf.destroy();
    }

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    QOpenGLShaderProgram program;

    QOpenGLTexture *texture;

    QMatrix4x4 projection;

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
};

} // namespace gt

#endif // GT_GTWIDGET_H
