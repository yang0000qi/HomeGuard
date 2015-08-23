#include "SecurityPanel.h"
#include "TextAudibleAlarm.h"


SecurityPanel::SecurityPanel()
    : _armed(false)
    , _audibleAlarm(new TextAudibleAlarm)
    , _securityCode("")
{}

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
