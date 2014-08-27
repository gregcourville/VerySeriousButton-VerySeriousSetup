#pragma once

#include <stdexcept>
#include <QtGui/QGroupBox>
#include <QtGui/QWidget>
#include <QtGui/QTextEdit>
#include "vsbprog.h"

class InvalidKeyseqString
: public std::runtime_error
{
public:
    explicit InvalidKeyseqString(const std::string& __arg);
};

class KeyseqOptionsBox
    : public QGroupBox
{
    Q_OBJECT
private:
  QTextEdit *textEdit;
public:
    KeyseqOptionsBox(QWidget* parent = 0);
    virtual ~KeyseqOptionsBox();
    void updateFromVsbInfoAndConfig(const VsbInfoAndConfig& infoAndConfig);
    KeystrokeSequence getKeystrokeSequence();
    void setKeystrokeSequence(const KeystrokeSequence& seq);
};
