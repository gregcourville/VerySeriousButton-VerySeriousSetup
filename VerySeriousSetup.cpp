// © 2014 Greg Courville <Greg_Courville@GregLabs.com>
// 
// This file is part of VerySeriousSetup.
// 
// VerySeriousSetup is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// VerySeriousSetup is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with VerySeriousSetup.  If not, see <http://www.gnu.org/licenses/>.


#include <QtGui/QAction>
#include <QtGui/QDesktopWidget>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtCore/QTimer>
#include <QtGui/QVBoxLayout>
#include <QtGui/QMessageBox>
#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <string>
#include "VerySeriousSetup.h"
#include "DeviceListDialog.h"
#include "vsbprog.h"

const std::string VssMainWindow::swVersion = "0.1 ALPHA";

VssMainWindow::VssMainWindow()
    : appIcon(":/images/app_icon.svg")
{
    deviceSelector = new SelectedDeviceBox(this);
    modeSelector = new VsbModeSelector(this);
    modeSelector->setEnabled(false);
    singlekeyOptionsBox = new SinglekeyOptionsBox(this);
    keyseqOptionsBox = new KeyseqOptionsBox(this);
    bigGoButton = new BigGoButton(this);
    refreshAction = new QAction("Refresh device list", this);
    refreshAction->setShortcut(QKeySequence("F5"));
    devinfoAction = new QAction("Show device info...", this);
    QAction* quitAction = new QAction(this);
    quitAction->setText("Quit");
    QAction* aboutAction = new QAction("About...", this);
    setWindowTitle("Very Serious Setup Tool");
    setWindowIcon(appIcon);
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout(centralWidget());
    setAllControlsLocked(false);

    //TEMP
    QLabel* alphaWarning = new QLabel("NOTICE: This is a pre-release build");
    alphaWarning->setStyleSheet("QLabel {font-weight: bold; color: red;}");
    alphaWarning->setAlignment(Qt::AlignCenter);
    layout->addWidget(alphaWarning);
    //TEMP

    layout->addWidget(deviceSelector);
    layout->addWidget(modeSelector);
    layout->addWidget(singlekeyOptionsBox);
    layout->addWidget(keyseqOptionsBox);
    layout->addStretch();
    layout->addWidget(bigGoButton);
    menuBar()->addMenu("&File")->addAction(quitAction);
    QMenu* deviceMenu = menuBar()->addMenu("Device");
    deviceMenu->addAction(devinfoAction);
    menuBar()->addSeparator();
    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    centralWidget()->setLayout(layout);
    connect(quitAction, SIGNAL(triggered()), SLOT(close()));
    connect(aboutAction, SIGNAL(triggered()), SLOT(showAboutDialog()));
    connect(devinfoAction, SIGNAL(triggered()), SLOT(showDevinfoDialog()));
    connect(bigGoButton, SIGNAL(gobuttonClicked()), SLOT(applyNewConfig()));
    connect(deviceSelector, SIGNAL(selectButtonClicked()),
            SLOT(handleSelectButtonClicked()));
    connect(modeSelector, SIGNAL(newSelectedMode(int)),
            SLOT(setWhichControlsEnabled(int)));
    QTimer::singleShot(0, this, SLOT(autoSelectDevice()));
    statusBar();
}

void VssMainWindow::showAboutDialog()
{
    QDialog aboutDialog(this);
    aboutDialog.setWindowTitle("About");
    aboutDialog.setLayout(new QVBoxLayout(&aboutDialog));
    QString aboutText("<b>Very Serious Setup Tool</b><br>Version ");
    aboutText.append(swVersion.c_str());
    aboutText.append(
        "<br>"
        "&copy; 2014 Greg Courville <Greg_Courville@GregLabs.com><br>"
        "Licensed under the GNU GPL v.3; see LICENSE.txt for details"
    );
    aboutDialog.layout()->addWidget(new QLabel(aboutText, &aboutDialog));
    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok, Qt::Horizontal, &aboutDialog);
    aboutDialog.layout()->addWidget(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), &aboutDialog,
                     SLOT(accept()));
    aboutDialog.exec();
}

void VssMainWindow::showDevinfoDialog()
{
    if(!selectedDevice)
        return;
    QString infoText =
        QString("Device type: %1<br>Version: %2<br>Serial number: %3<br>")
        .arg(selectedDevice->productString.c_str())
        .arg(selectedDevice->releaseNumber.c_str())
        .arg(selectedDevice->serialNumber.c_str());
    QMessageBox::information(this, "Device info", infoText);
}

void VssMainWindow::handleSelectButtonClicked()
{
    DeviceListDialog dialog;
    boost::optional<HidDeviceInfo> dlgSelectedDevice;
    dialog.setDeviceList(VsbDevice::findDevices());
    setAllControlsLocked(true);
    if(dialog.exec() == QDialog::Accepted)
    {
        dlgSelectedDevice = dialog.selectedDevice();
        if(dlgSelectedDevice)
        {
            statusBar()->showMessage("Getting current configuration...");
            try
            {
                setSelectedDevice(*dlgSelectedDevice);
                statusBar()->showMessage(
                    "Successfully loaded current configuration.");
            }
            catch(VsbError err)
            {
                unsetSelectedDevice();
                showError(std::string(
                              "Error getting configuration from device: ")
                          + err.what());
            }
        }
    }
    setAllControlsLocked(false);
}

void VssMainWindow::showError(std::string info)
{
    QMessageBox::warning(this, "Error", info.c_str());
    statusBar()->showMessage(QString("ERROR: ") + info.c_str());
}

void VssMainWindow::unsetSelectedDevice()
{
    devinfoAction->setEnabled(false);
    deviceSelector->clearInfo();
    selectedDevice = boost::none;
    setWhichControlsEnabled(-1);
    setAllControlsLocked(false);
}

void VssMainWindow::setSelectedDevice(const HidDeviceInfo& devInfo)
{
    updateConfigFromDevice(devInfo);
    selectedDevice = devInfo;
    deviceSelector->setInfo(devInfo.serialNumber);
    devinfoAction->setEnabled(true);
    setAllControlsLocked(false);
}

VssMainWindow::~VssMainWindow()
{}

void VssMainWindow::updateConfigFromDevice()
{
    if(selectedDevice)
        updateConfigFromDevice(*selectedDevice);
}

void VssMainWindow::updateConfigFromDevice(const HidDeviceInfo& devInfo)
{
    VsbInfoAndConfig infoAndConfig = VsbProg::getInfoAndConfig(devInfo.path);
    singlekeyOptionsBox->updateFromVsbInfoAndConfig(infoAndConfig);
    keyseqOptionsBox->updateFromVsbInfoAndConfig(infoAndConfig);
    switch(infoAndConfig.config.mode)
    {
    case VsbMode::joystick:
        modeSelector->setSelectedMode(VsbModeSelector::joystickModeId);
        break;
    case VsbMode::singlekey:
        modeSelector->setSelectedMode(VsbModeSelector::singlekeyModeId);
        break;
    case VsbMode::keyseq:
        modeSelector->setSelectedMode(VsbModeSelector::keyseqModeId);
        break;
    }
}

void VssMainWindow::setWhichControlsEnabled(int v)
{
    whichControlsEnabled_ = v;
    if(controlsLocked_)
        return;
    bool enableSinglekeyCtrls = (v==VsbModeSelector::singlekeyModeId);
    bool enableKeyseqCtrls = (v==VsbModeSelector::keyseqModeId);
    singlekeyOptionsBox->setEnabled(enableSinglekeyCtrls);
    keyseqOptionsBox->setEnabled(enableKeyseqCtrls);
}

void VssMainWindow::setWhichControlsEnabled()
{
    setWhichControlsEnabled(whichControlsEnabled_);
}

void VssMainWindow::setAllControlsLocked(bool y)
{
    controlsLocked_ = y;
    setWhichControlsEnabled();
    if(y)
    {
        deviceSelector->setEnabled(false);
        modeSelector->setEnabled(false);
        menuBar()->setEnabled(false);
    }
    else
    {
        deviceSelector->setEnabled(true);
        modeSelector->setEnabled(selectedDevice);
        bigGoButton->setEnabled(selectedDevice);
        menuBar()->setEnabled(true);
    }
}

void VssMainWindow::setAllControlsLocked()
{
    setAllControlsLocked(controlsLocked_);
}

void VssMainWindow::applyNewConfig()
{
    if(!selectedDevice)
        return;
    bigGoButton->setEnabled(false);
    setAllControlsLocked(true);
    statusBar()->showMessage("Sending new configuration to device...");
    bool success = false;
    bool badInput = false;
    try
    {
        switch(modeSelector->selectedMode())
        {
        case VsbModeSelector::joystickModeId:
            VsbProg::setJoystickMode(selectedDevice->path);
            success = true;
            break;
        case VsbModeSelector::singlekeyModeId:
            VsbProg::setSinglekeyMode(selectedDevice->path, singlekeyOptionsBox->getKeystroke());
            success = true;
            break;
        case VsbModeSelector::keyseqModeId:
            try
            {
                KeystrokeSequence seq = keyseqOptionsBox->getKeystrokeSequence();
                VsbProg::setKeyseqMode(selectedDevice->path, seq);
                success = true;
            }
            catch(InvalidKeyseqString err)
            {
                showError(std::string("There's a problem with the key sequence you entered: ") + err.what());
                statusBar()->showMessage("Aborted due to invalid input.");
                badInput = true;
            }
            break;
        }
    }
    catch(VsbError err)
    {
        showError(std::string("Failed to send new configuration to device: ") + err.what());
    }
    if(success)
    {
        updateConfigFromDevice();
        statusBar()->showMessage("New configuration stored successfully!");
    }
    setAllControlsLocked(false);
}

void VssMainWindow::autoSelectDevice()
{
    HidDeviceInfos devInfos = VsbDevice::findDevices();
    for(int i = 0; i < devInfos.size(); ++i)
    {
        try
        {
            setSelectedDevice(devInfos[i]);
            break;
        }
        catch(VsbError err)
        {
            //TODO: Say something?
        }
    }
}

//#include "VerySeriousSetup.moc"
