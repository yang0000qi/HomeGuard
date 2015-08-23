#include "SecurityPanel.h"
#include "TextAudibleAlarm.h"


SecurityPanel::SecurityPanel()
    : _armed(false)
    , _audibleAlarm(new TextAudibleAlarm)
    , _securityCode("")
{}

bool SecurityPanel::isArmed() const
{
    return _armed;
}

void SecurityPanel::arm()
{
    _armed = true;
}

void SecurityPanel::disarm()
{
    _armed = false;
}

bool SecurityPanel::isValidCode(const std::string& code) const
{
    return code == _securityCode;
}

void SecurityPanel::setSecurityCode(const std::string& code)
{
    _securityCode = code;
}

void SecurityPanel::enterCode(const std::string& code)
{
    if (isValidCode(code)) {
        disarm();
        silence();
    }
}

void SecurityPanel::alarm()
{
    if (isArmed()) {
        _audibleAlarm->sound();
    }
}

void SecurityPanel::silence()
{
    _audibleAlarm->silence();
}
