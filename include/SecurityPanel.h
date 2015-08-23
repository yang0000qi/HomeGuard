#pragma once

#include <memory>
#include <string>

#include "AudibleAlarm.h"


class SecurityPanel {
public:
    SecurityPanel();

    void enterCode(const std::string& code);
    void alarm();
    void silence();

    bool isArmed() const { return _armed; }
    void arm() { _armed = true; }
    void disarm() { _armed = false; }

    bool isValidCode(const std::string& code) const {
        return code == _securityCode;
    }

    void setSecurityCode(const std::string& code) {
        _securityCode = code;
    }

private:
    bool _armed;
    std::shared_ptr<AudibleAlarm> _audibleAlarm;
    std::string _securityCode;
};
