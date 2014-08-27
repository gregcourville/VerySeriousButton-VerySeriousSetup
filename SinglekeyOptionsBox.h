#pragma once

#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include "vsbprog.h"

class ModifierKeyGrid
    : public QWidget
{
private:
    QCheckBox *lShift;
    QCheckBox *lAlt;
    QCheckBox *lGui;
    QCheckBox *lCtrl;
    QCheckBox *rShift;
    QCheckBox *rAlt;
    QCheckBox *rGui;
    QCheckBox *rCtrl;
public:
    explicit ModifierKeyGrid(QWidget* parent = 0);
    virtual ~ModifierKeyGrid();
    void setMods(uint8_t mods);
    uint8_t getMods();
};

class SinglekeyOptionsBox
    : public QGroupBox
{
    Q_OBJECT
private:
  QComboBox* keynameSelector;
  ModifierKeyGrid* modGrid;
public:
    SinglekeyOptionsBox(QWidget* parent = 0);
    void updateFromVsbInfoAndConfig(const VsbInfoAndConfig& infoAndConfig);
    void setKeystroke(const Keystroke& keystroke);
    Keystroke getKeystroke();
    virtual ~SinglekeyOptionsBox();
};
