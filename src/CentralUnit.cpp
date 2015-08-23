#include <algorithm>

#include "CentralUnit.h"
#include "TextAudibleAlarm.h"
#include "TextView.h"


CentralUnit::CentralUnit()
    : _armed(false)
    , _audibleAlarm(new TextAudibleAlarm)
    , _homeGuardView(new TextView)
    , _sensorManager(new SensorManager)
    , _runningSensorTest(false)
{}

bool CentralUnit::isArmed() const
{
    return _armed;
}

void CentralUnit::arm()
{
    _armed = true;
}

void CentralUnit::disarm()
{
    _armed = false;
}

// used during sensor test
std::string CentralUnit::getSensorStatus() const
{
    return _sensorTestStatus;
}

bool CentralUnit::isValidCode(const std::string& code) const
{
    return code == _securityCode;
}

void CentralUnit::setSecurityCode(const std::string& code)
{
    _securityCode = code;
}

void CentralUnit::enterCode(const std::string& code)
{
    if (isValidCode(code)) {
        disarm();
        _audibleAlarm->silence();
    }
}

std::shared_ptr<SensorManager> CentralUnit::sensorManager()
{
    return _sensorManager;
}

void CentralUnit::onRadioBroadcast(const std::string& packet)
{
    std::string id;
    std::string status;

    // parse the packet
    std::tie(id, status) = _parsePacket(packet);

    // find sensor with id
    Sensor sensor = _sensorManager->getSensor(id);
    if (InvalidId == sensor.getID()) {
        return;
    }

    //trip or reset sensor
    sensor.triggerByStatus(status);

    //get the message from the sensor and display it
    _homeGuardView->showMessage(sensor.getMessage());

    // sound the alarm if armed
    if (isArmed()) {
        _audibleAlarm->sound();
    }

    // check if a sensor test is running and adjust status
    _sensorTest(id, status);
}

void CentralUnit::runSensorTest()
{
    _runningSensorTest = true;
    _sensorTestStatus = SensorStatus::PENDING;

    // clear the status map
    _sensorManager->clearStatusMap();

    for (auto sensor : _sensorManager->sensors()) {
        _sensorManager->setStatus(sensor.getID(), SensorStatus::PENDING);
    }
}

void CentralUnit::_sensorTest(const std::string& id, const std::string& status)
{
    if (_runningSensorTest) {
        if (SensorStatus::TRIPPED == status) {
            _sensorManager->setStatus(id, SensorStatus::PASS);
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
    for (auto statusMap : _sensorManager->sensorStatusMap()) {
        std::string status = statusMap.second;
        if (SensorStatus::PENDING == status) {
            _sensorTestStatus = SensorStatus::FAIL;
            break;
        }
    }
}

bool CentralUnit::_sensorTestDone()
{
    for (auto statusMap : _sensorManager->sensorStatusMap()) {
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
