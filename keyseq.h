 

#pragma once

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include "bytestring.h"

namespace KeyMods
{
  const uint8_t lCtrl = 0x01;
  const uint8_t lShift = 0x02;
  const uint8_t lAlt = 0x04;
  const uint8_t lGui = 0x08;
  const uint8_t rCtrl = 0x10;
  const uint8_t rShift = 0x20;
  const uint8_t rAlt = 0x40;
  const uint8_t rGui = 0x80;
};

class InvalidKeyName : public std::runtime_error
{
public:
    explicit InvalidKeyName(const std::string& __arg);
};

class InvalidKeycode : public std::runtime_error
{
public:
    explicit InvalidKeycode(const std::string& __arg);
};

class InvalidModName : public std::runtime_error
{
public:
    explicit InvalidModName(const std::string& __arg);
};

class Keystroke
{
private:
    uint8_t mods_;
    ByteString keyCodes_;
public:
    static const std::map<const std::string, uint8_t>& allKeycodes();
    static const std::map<const std::string, uint8_t>& allMods();
    const static char* sepStr;
    static Keystroke fromString(const std::string& s, uint8_t extraMods=0);
    static uint8_t modFromString(const std::string inp);
    static uint8_t keycodeFromString(const std::string inp);
    static std::string keycodeToString(uint8_t keycode);
    static std::vector<std::string> modsToStrings(uint8_t mods);
    uint8_t mods() const;
    const ByteString& keycodes() const;
    bool hasMod(uint8_t mod) const;
    int numKeys() const;
    uint8_t keycode(int i) const;
    std::string keyName(int i) const;
    std::string toString() const;
    bool empty() const;
    Keystroke(const ByteString& keyCodes = ByteString(), uint8_t mods=0);
};

class KeystrokeSequence
    : public std::vector<Keystroke>
{
public:
    const static char* sepStr;
    static KeystrokeSequence fromString(const std::string& s);
    std::string toString() const;
};
