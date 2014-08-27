#include <QtGui/QDesktopWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include "BigGoButton.h"

BigGoButton::BigGoButton(QWidget* parent)
    : QWidget(parent),
      goIcon(":/images/go.svg")
{
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    layout_->addStretch();
    QPushButton* button = new QPushButton("Apply new configuration", this);
    QDesktopWidget desktop;
    button->setMinimumWidth((int)(2.4 * desktop.logicalDpiX()));
    button->setMinimumHeight((int)(0.5 * desktop.logicalDpiY()));
    button->setIconSize(
        QSize(0.3*desktop.logicalDpiX(), 0.3*desktop.logicalDpiY()));
    button->setIcon(goIcon);
    layout_->addWidget(button);
    layout_->addStretch();
    setLayout(layout_);
    QObject::connect(
        button, SIGNAL(clicked()), this, SLOT(handleGobuttonClicked()));
}

BigGoButton::~BigGoButton()
{}

void BigGoButton::handleGobuttonClicked()
{
    emit gobuttonClicked();
}

//#include "BigGoButton.moc"
