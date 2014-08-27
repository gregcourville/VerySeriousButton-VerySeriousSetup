#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include "KeyseqOptionsBox.h"

InvalidKeyseqString::InvalidKeyseqString(const std::string& arg)
    : std::runtime_error(arg)
{}

KeyseqOptionsBox::KeyseqOptionsBox(QWidget* parent)
    : QGroupBox("Options for key sequence mode", parent)
{
    textEdit = new QTextEdit(this);
    textEdit->setAcceptRichText(false);
    textEdit->setTabChangesFocus(false);
    QGridLayout *layout_ = new QGridLayout(this);
    layout_->addWidget(new QLabel("Key sequence",this), 0, 0);
    layout_->addWidget(textEdit, 0, 1);
    setLayout(layout_);
}

KeyseqOptionsBox::~KeyseqOptionsBox()
{}

void KeyseqOptionsBox::updateFromVsbInfoAndConfig(const VsbInfoAndConfig& infoAndConfig)
{
    setKeystrokeSequence(infoAndConfig.config.keyseqKeyseq);
}

void KeyseqOptionsBox::setKeystrokeSequence(const KeystrokeSequence& seq)
{
    textEdit->setPlainText(seq.toString().c_str());
}

KeystrokeSequence KeyseqOptionsBox::getKeystrokeSequence()
{
    try
    {
        return KeystrokeSequence::fromString(textEdit->toPlainText().toStdString());
    }
    catch(InvalidKeyName err)
    {
        throw InvalidKeyseqString(std::string("'") + err.what() + "' is not a valid key name");
    }
    catch(InvalidModName err)
    {
        throw InvalidKeyseqString(std::string("'") + err.what() + "' is not a valid modifier name");
    }
}

