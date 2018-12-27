#ifndef REDTRIANGLE_H
#define REDTRIANGLE_H

#include <QWidget>
#include "glbasewidget.h"

class RedTriangle : public GLBaseWidget
{
    Q_OBJECT
public:
    explicit RedTriangle(QWidget *parent = nullptr);
    virtual void initializeGL()override;

signals:

public slots:
};

#endif // REDTRIANGLE_H
