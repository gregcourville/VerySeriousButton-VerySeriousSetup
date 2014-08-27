#include <QtGui/QDesktopWidget>
#include <QtGui/QHBoxLayout>
#include "VsbModeSelector.h"

VsbModeButton::VsbModeButton(const QIcon& icon, const QString labelText,
                             QWidget* parent)
    : QToolButton(parent)
{
    setIcon(icon);
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setCheckable(true);
    setText(labelText);
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred));
    QDesktopWidget desktop;
    setFixedWidth((int)(1.6 * desktop.logicalDpiX()));
    setFixedHeight((int)(1.1 * desktop.logicalDpiY()));
    setIconSize(QSize(0.7*desktop.logicalDpiX(), 0.7*desktop.logicalDpiY()));
    setStyleSheet("QToolButton{padding: 10px;}");
}

VsbModeButton::~VsbModeButton()
{}

VsbModeSelector::VsbModeSelector(QWidget* parent)
    : QGroupBox("Select mode", parent),
      joystickModeIcon(":/images/mode_joystick.svg"),
      keyseqModeIcon(":/images/mode_keyseq.svg"),
      singlekeyModeIcon(":/images/mode_singlekey.svg")
{
    joystickButton = new VsbModeButton(
        joystickModeIcon, QString("Joystick button"), this);
    singlekeyButton = new VsbModeButton(
        singlekeyModeIcon, QString("Single key"), this);
    keyseqButton = new VsbModeButton(
        keyseqModeIcon, QString("Key sequence"), this);
    buttonGroup = new QButtonGroup(this);
    buttonGroup->addButton(joystickButton, joystickModeId);
    buttonGroup->addButton(singlekeyButton, singlekeyModeId);
    buttonGroup->addButton(keyseqButton, keyseqModeId);
    buttonGroup->setExclusive(true);
    setLayout(new QHBoxLayout(this));
    layout()->addWidget(joystickButton);
    layout()->addWidget(singlekeyButton);
    layout()->addWidget(keyseqButton);
    QObject::connect(buttonGroup, SIGNAL(buttonPressed(int)),
                     this, SLOT(handleButtonPressed(int)));
}

VsbModeSelector::~VsbModeSelector()
{}

int VsbModeSelector::selectedMode()
{
    return buttonGroup->checkedId();
}

void VsbModeSelector::handleButtonPressed(int x)
{
    emit newSelectedMode(x);
}

void VsbModeSelector::setSelectedMode(int x)
{
    VsbModeButton *button = (VsbModeButton *)buttonGroup->button(x);
    if(!button)
        return; //TODO: Maybe handle this intelligently?
    button->setChecked(true);
    handleButtonPressed(x);
}

//#include "VsbModeSelector.moc"
