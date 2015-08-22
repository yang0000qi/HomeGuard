#include "CentralUnit.h"
#include "Sensor.h"
#include "TextAudibleAlarm.h"
#include "TextView.h"


CentralUnit::CentralUnit()
    : _armed(false)
    , _audibleAlarm(new TextAudibleAlarm)
    , _homeGuardView(new TextView)
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

SensorStatusMap& CentralUnit::getSensorStatusMap()
{
    return _sensorStatusMap;
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

SensorList& CentralUnit::getSensors()
{
    return _sensors;
}

Sensor CentralUnit::getSensor(const std::string& id) const
{
    Sensor result(InvalidId, "No place", SensorType::NONE);

    for (auto sensor : _sensors) {
        if (id == sensor.getID())
            return sensor;
    }

    return result;
}

void CentralUnit::registerSensor(const Sensor& sensor)
{
    _sensors.push_back(sensor);
}

void CentralUnit::onRadioBroadcast(const std::string& packet)
{
    std::string id;
    std::string status;

    // parse the packet
    std::tie(id, status) = _parsePacket(packet);

    // find sensor with id
    Sensor sensor = getSensor(id);
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
    _sensorStatusMap.clear();

    for (auto sensor : _sensors) {
        _sensorStatusMap[sensor.getID()] = SensorStatus::PENDING;
    }
}

// used during sensor test
void CentralUnit::_terminateSensorTest()
{
    _runningSensorTest = false;

    // look at individual sensor status to determine the overall test status
    _sensorTestStatus = SensorStatus::PASS;
    for (auto statusMap : _sensorStatusMap) {
        std::string status = statusMap.second;
        if (SensorStatus::PENDING == status) {
            _sensorTestStatus = SensorStatus::FAIL;
            break;
        }
    }
}

bool CentralUnit::_sensorTestDone()
{
    for (auto statusMap : _sensorStatusMap) {
        std::string testStatus = statusMap.second;
        if (SensorStatus::PENDING == testStatus) {
            return false;
        }
    }
    return true;
}

void CentralUnit::_sensorTest(const std::string& id, const std::string& status)
{
    if (_runningSensorTest) {
        if (SensorStatus::TRIPPED == status) {
            _sensorStatusMap[id] = SensorStatus::PASS;
        }

        //terminate test if complete
        if (_sensorTestDone()) {
            _terminateSensorTest();
        }
    }
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
