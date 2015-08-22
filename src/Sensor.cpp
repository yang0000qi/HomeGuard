#include "Sensor.h"


Sensor::Sensor(const std::string& id,
               const std::string& location,
               SensorType type)
    : _id(id)
    , _location(location)
    , _type(type)
    , _tripped(false)
{
    _initSensorMessageMap();
}

void Sensor::_initSensorMessageMap()
{
    _messageMap[SensorType::DOOR] =
        {[&]() { return _location + " is open"; },
         [&]() { return _location + " is closed"; }};

    _messageMap[SensorType::WINDOW] = {
        [&]() { return _location + " is ajar";  },
        [&]() { return _location + " is sealed"; }};

    _messageMap[SensorType::MOTION] = {
        [&]() { return "Motion detected in " + _location; },
        [&]() { return _location + " is motionless";}};

    _messageMap[SensorType::FIRE] = {
        [&]() {return _location + " is on FIRE!"; },
        [&]() {return _location + " temperature is normal"; }};

    _messageMap[SensorType::NONE] = {
        [&]() { return "default"; },
        [&]() { return "default"; }};
}

std::string Sensor::getID() const
{
    return _id;
}

std::string Sensor::getLocation() const
{
    return _location;
}

SensorType Sensor::getType() const
{
    return _type;
}

bool Sensor::isTripped() const
{
    return _tripped;
}

void Sensor::trip()
{
    _tripped = true;
}

void Sensor::reset()
{
    _tripped = false;
}

void Sensor::triggerByStatus(const std::string status)
{
    if (getID() != InvalidId) {
        if ("TRIPPED" == status) {
            trip();
        } else {
            reset();
        }
    }
}

std::string Sensor::getMessage() const
{
    auto message = _messageMap.at(getType());
    return isTripped() ? message.tripped() : message.normal();
}
