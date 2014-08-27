#pragma once

#include <QtGui/QMainWindow>
#include <QtGui/QIcon>
#include <boost/optional.hpp>
#include "vsbprog.h"
#include "VsbDeviceSelector.h"
#include "VsbModeSelector.h"
#include "SinglekeyOptionsBox.h"
#include "KeyseqOptionsBox.h"
#include "BigGoButton.h"

class VssMainWindow
    : public QMainWindow
{
    Q_OBJECT
private:
    static const std::string swVersion;
    QAction *refreshAction;
    QAction *devinfoAction;
    bool controlsLocked_;
    int whichControlsEnabled_;
    const QIcon appIcon;
    SelectedDeviceBox *deviceSelector;
    VsbModeSelector *modeSelector;
    SinglekeyOptionsBox *singlekeyOptionsBox;
    KeyseqOptionsBox *keyseqOptionsBox;
    BigGoButton *bigGoButton;
    void setAllControlsLocked(bool y);
    void setAllControlsLocked();
    void setWhichControlsEnabled();
    void updateConfigFromDevice(const HidDeviceInfo& devInfo);
    boost::optional<HidDeviceInfo> selectedDevice;
    void setSelectedDevice(const HidDeviceInfo& devInfo);
    void unsetSelectedDevice();
    void showError(std::string info);
private slots:
    void setWhichControlsEnabled(int v);
    void applyNewConfig();
    void handleSelectButtonClicked();
    void updateConfigFromDevice();
    void autoSelectDevice();
    void showAboutDialog();
    void showDevinfoDialog();
public:
    VssMainWindow();
    virtual ~VssMainWindow();
public slots:

};

