#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QDesktopWidget>
#include <boost/foreach.hpp>
#include <boost/format/format_fwd.hpp>
#include "VsbDeviceSelector.h"

DeviceIconWidget::DeviceIconWidget(QWidget* parent)
    : QPushButton(parent),
      nodevIcon(":/images/dev_none.svg"),
      vsbIcon(":/images/dev_vsb.svg")
{
    setFlat(true);
    QDesktopWidget desktop;
    setIconSize(QSizeF(
                    0.4 * desktop.logicalDpiX(),
                    0.4 * desktop.logicalDpiY()
                ).toSize());
    setIconToNodev();
}

void DeviceIconWidget::setIconToVsb()
{
    setIcon(vsbIcon);
}

void DeviceIconWidget::setIconToNodev()
{
    setIcon(nodevIcon);
}

DeviceSelectorInfoWidget::DeviceSelectorInfoWidget(QWidget* parent)
    : QLabel(parent)
{
    clearInfo();
}

void DeviceSelectorInfoWidget::setInfo(const std::string& serialNumber)
{
    setText(QString("<b>Very Serious Button</b><br>Serial number: ") + QString(serialNumber.c_str()));
}

void DeviceSelectorInfoWidget::clearInfo()
{
    setText("(no device selected)");
}

SelectedDeviceBox::SelectedDeviceBox(QWidget* parent)
    : QGroupBox("Select device", parent),
      chooseIcon(":/images/choose.svg")
{
    iconWidget = new DeviceIconWidget(this);
    infoWidget = new DeviceSelectorInfoWidget(this);
    selectButton = new QPushButton("Choose...", this);
    selectButton->setIcon(chooseIcon);
    QHBoxLayout* layout_ = new QHBoxLayout(this);
    layout_->addWidget(iconWidget, 0, Qt::AlignLeft | Qt::AlignVCenter);
    layout_->addWidget(infoWidget, 1);
    layout_->addWidget(selectButton, 0, Qt::AlignRight | Qt::AlignVCenter);
    QObject::connect(selectButton, SIGNAL(clicked()), this, SLOT(handleSelectClicked()));
}

void SelectedDeviceBox::setInfo(const std::string& serialNumber)
{
    infoWidget->setInfo(serialNumber);
    iconWidget->setIconToVsb();
}

void SelectedDeviceBox::clearInfo()
{
    infoWidget->clearInfo();
    iconWidget->setIconToNodev();
}

void SelectedDeviceBox::handleSelectClicked()
{
    emit selectButtonClicked();
}

//#include "VsbDeviceSelector.moc"
