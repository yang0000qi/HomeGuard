﻿#include "CentralUnit.h"
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
    std::tie(id, status) = Packets::parse(packet);

    Sensor sensor = sensorManager()->getSensor(id);
    if (InvalidId == sensor.id()) {
        return;
    }

    sensor.triggerByStatus(status);
    homeGuardView()->showMessage(sensor.message());
    securityPanel()->alarm();
    checkModule()->check(id, status);
}
