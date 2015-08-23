﻿#include <algorithm>

#include "CentralUnit.h"
#include "TextAudibleAlarm.h"
#include "TextView.h"


CentralUnit::CentralUnit()
    : _homeGuardView(new TextView)
    , _sensorManager(new SensorManager)
    , _runningSensorTest(false)
{
    _checkModule.setSensorManager(_sensorManager);
}

// used during sensor test
std::string CentralUnit::getSensorStatus() const
{
    return _sensorTestStatus;
}

std::shared_ptr<SensorManager> CentralUnit::sensorManager()
{
    return _sensorManager;
}

SecurityPanel& CentralUnit::securityPanel()
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
    securityPanel().alarm();

    // check if a sensor test is running and adjust status
    _sensorTest(id, status);
}

void CentralUnit::runSensorTest()
{
    _runningSensorTest = true;
    _sensorTestStatus = SensorStatus::PENDING;

    // clear the status map
    sensorManager()->clearStatusMap();

    for (auto sensor : sensorManager()->sensors()) {
        sensorManager()->setStatus(sensor.getID(), SensorStatus::PENDING);
    }
}

void CentralUnit::_sensorTest(const std::string& id, const std::string& status)
{
    if (_runningSensorTest) {
        if (SensorStatus::TRIPPED == status) {
            sensorManager()->setStatus(id, SensorStatus::PASS);
        }

        //terminate test if complete
        if (_sensorTestDone()) {
            _terminateSensorTest();
        }
    }
}

// used during sensor test
void CentralUnit::_terminateSensorTest()
{
    _runningSensorTest = false;

    // look at individual sensor status to determine the overall test status
    _sensorTestStatus = SensorStatus::PASS;
    for (auto statusMap : sensorManager()->sensorStatusMap()) {
        std::string status = statusMap.second;
        if (SensorStatus::PENDING == status) {
            _sensorTestStatus = SensorStatus::FAIL;
            break;
        }
    }
}

bool CentralUnit::_sensorTestDone()
{
    for (auto statusMap : sensorManager()->sensorStatusMap()) {
        std::string testStatus = statusMap.second;
        if (SensorStatus::PENDING == testStatus) {
            return false;
        }
    }
    return true;
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
