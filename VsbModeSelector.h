#pragma once

#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QToolButton>
#include <QtGui/QButtonGroup>

class VsbModeButton : public QToolButton
{
    Q_OBJECT
public:
    VsbModeButton(const QIcon& icon, const QString labelText, QWidget* parent = 0);
    ~VsbModeButton();
};

class VsbModeSelector
    : public QGroupBox
{
    Q_OBJECT
private:
    const QIcon keyseqModeIcon;
    const QIcon singlekeyModeIcon;
    const QIcon joystickModeIcon;
    VsbModeButton *keyseqButton;
    VsbModeButton *singlekeyButton;
    VsbModeButton *joystickButton;
    QButtonGroup *buttonGroup;
public:
    static const int joystickModeId = 1;
    static const int singlekeyModeId = 2;
    static const int keyseqModeId = 3;
    VsbModeSelector(QWidget* parent = 0);
    virtual ~VsbModeSelector();
    int selectedMode();
    void setSelectedMode(int x);
private slots:
    void handleButtonPressed(int x);
signals:
    void newSelectedMode(int x);
};
