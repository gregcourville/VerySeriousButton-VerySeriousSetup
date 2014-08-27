#pragma once

#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QIcon>
#include <QtGui/QPushButton>
#include <vector>
#include "vsbprog.h"

class DeviceIconWidget
    : public QPushButton
{
private:
    const QIcon nodevIcon;
    const QIcon vsbIcon;
public:
    explicit DeviceIconWidget(QWidget* parent = 0);
    void setIconToVsb();
    void setIconToNodev();
};

class DeviceSelectorInfoWidget
    : public QLabel
{
public:
    explicit DeviceSelectorInfoWidget(QWidget* parent = 0);
    void setInfo(const std::string& serialNumber);
    void clearInfo();
};

class SelectedDeviceBox
    : public QGroupBox
{
    Q_OBJECT
private:
    const QIcon chooseIcon;
    DeviceIconWidget *iconWidget;
    DeviceSelectorInfoWidget *infoWidget;
    QPushButton *selectButton;
private slots:
    void handleSelectClicked();
signals:
    void selectButtonClicked();
public:
    SelectedDeviceBox(QWidget* parent = 0);
    void setInfo(const std::string& serialNumber);
    void clearInfo();
};
