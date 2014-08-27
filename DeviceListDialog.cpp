#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QPushButton>
#include <QtCore/QVariant>
#include <boost/foreach.hpp>
#include "DeviceListDialog.h"

#include <iostream> //DEBUG

DeviceListDialog::DeviceListDialog()
{
    //selectButton = new QPushButton("Select", this);
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttonBox->button(QDialogButtonBox::Ok)->setText("Select");
    listBox = new QComboBox(this);
    //TODO: Make list box multi-line, or use a table thing instead
    setLayout(new QVBoxLayout(this));
    layout()->addWidget(new QLabel("Available devices:",this));
    layout()->addWidget(listBox);
    layout()->addWidget(buttonBox);
    setWindowTitle("Select device");
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void DeviceListDialog::setDeviceList(const std::vector<HidDeviceInfo>& newDevInfos)
{
    devInfos = newDevInfos;
    listBox->clear();
    for(int i = 0; i < devInfos.size(); ++i)
    {
        listBox->addItem((devInfos[i].productString + " #" + devInfos[i].serialNumber).c_str(), QVariant(i));
        listBox->setEnabled(true);
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    if(!listBox->count())
    {
        listBox->addItem("(no devices connected?)", QVariant(-1));
        listBox->setEnabled(false);
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

boost::optional<HidDeviceInfo> DeviceListDialog::selectedDevice()
{
    if((listBox->currentIndex() < 0) || (listBox->itemData(listBox->currentIndex()).toInt() < 0))
        return boost::none;
    return devInfos[listBox->currentIndex()];
}


//#include "DeviceListDialog.moc"
