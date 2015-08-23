#pragma once

#include <memory>
#include <string>

#include "AudibleAlarm.h"


class SecurityPanel {
public:
    SecurityPanel();

    bool isArmed() const;
    void arm();
    void disarm();

    bool isValidCode(const std::string& code) const;
    void setSecurityCode(const std::string& code);
    void enterCode(const std::string& code);

    void alarm();
    void silence();
private:
    bool _armed;
    std::shared_ptr<AudibleAlarm> _audibleAlarm;
    std::string _securityCode;    
};

