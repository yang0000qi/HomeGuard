#include "CentralUnit.h"
#include "TextView.h"


CentralUnit::CentralUnit()
    : _homeGuardView(new TextView)
    , _sensorManager(new SensorManager)
    , _checkModule(new CheckModule)
    , _securityPanel(new SecurityPanel)
{
    _checkModule->setSensorManager(_sensorManager);
}

void CentralUnit::onRadioBroadcast(const std::string& packet)
{
    std::string id, status;
    std::tie(id, status) = _parsePacket(packet);

    Sensor sensor = sensorManager()->getSensor(id);
    if (InvalidId == sensor.getID()) {
        return;
    }

    sensor.triggerByStatus(status);
    homeGuardView()->showMessage(sensor.message());
    securityPanel()->alarm();
    checkModule()->check(id, status);
}

PacketTulpe CentralUnit::_parsePacket(const std::string& packet)
{
    std::string id;
    std::string status;

    size_t splitPosition = packet.find(',');
    if (splitPosition != std::string::npos) {
        id = packet.substr(0, splitPosition);
        status = packet.substr(splitPosition + 1);
    }

    return make_tuple(id, status);
}
