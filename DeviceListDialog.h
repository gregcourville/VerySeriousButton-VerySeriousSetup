#pragma once

#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QComboBox>
#include <vector>
#include <map>
#include <boost/optional.hpp>
#include "vsbprog.h"

class DeviceListDialog
: public QDialog
{
  Q_OBJECT
private:
  QDialogButtonBox* buttonBox;
  QComboBox* listBox;
  HidDeviceInfos devInfos;
public:
    boost::optional< HidDeviceInfo > selectedDevice();
    explicit DeviceListDialog();
    void setDeviceList(const std::vector<HidDeviceInfo>& devInfos);
};