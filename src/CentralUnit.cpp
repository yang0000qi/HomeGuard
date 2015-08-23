#include <algorithm>

#include "CentralUnit.h"
#include "TextAudibleAlarm.h"
#include "TextView.h"


CentralUnit::CentralUnit()
    : _homeGuardView(new TextView)
    , _sensorManager(new SensorManager)
    , _checkModule(new CheckModule)
    , _securityPanel(new SecurityPanel)
{
    _checkModule->setSensorManager(_sensorManager);
}

std::shared_ptr<SensorManager> CentralUnit::sensorManager()
{
    return _sensorManager;
}

std::shared_ptr<CheckModule> CentralUnit::checkModule()
{
    return _checkModule;
}

std::shared_ptr<SecurityPanel> CentralUnit::securityPanel()
{
    return _securityPanel;
}

void CentralUnit::onRadioBroadcast(const std::string& packet)
{
    std::string id;
    std::string status;

    // parse the packet
    std::tie(id, status) = _parsePacket(packet);

    // find sensor with id
    Sensor sensor = sensorManager()->getSensor(id);
    if (InvalidId == sensor.getID()) {
        return;
    }

    //trip or reset sensor
    sensor.triggerByStatus(status);

    //get the message from the sensor and display it
    _homeGuardView->showMessage(sensor.getMessage());

    // sound the alarm if armed
    securityPanel()->alarm();

    // check if a sensor test is running and adjust status
    checkModule()->check(id, status);
}

PacketTulpe CentralUnit::_parsePacket(const std::string& packet)
{
    std::string id;
    std::string status;

    // parse the packet
    size_t splitPosition = packet.find(',');
    if (splitPosition != std::string::npos) {
        id = packet.substr(0, splitPosition);
        status = packet.substr(splitPosition + 1);
    }

    return make_tuple(id, status);
}
