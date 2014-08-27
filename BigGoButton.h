#pragma once

#include <QtGui/QIcon>
#include <QtGui/QWidget>

class BigGoButton
    : public QWidget
{
    Q_OBJECT
private:
    const QIcon goIcon;
private slots:
    void handleGobuttonClicked();
public:
    explicit BigGoButton(QWidget* parent = 0);
    virtual ~BigGoButton();
signals:
    void gobuttonClicked();
};
