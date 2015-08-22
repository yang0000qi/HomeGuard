#include "Sensor.h"


#define MESSAGE_MAP(type, tripped, normal) \
    _messageMap[(type)] = {[&]() { return (tripped); },\
                           [&]() { return (normal); }}

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
    MESSAGE_MAP(SensorType::DOOR,
                _location + " is open",
                _location + " is closed");

    MESSAGE_MAP(SensorType::WINDOW,
                _location + " is ajar",
                _location + " is sealed");

    MESSAGE_MAP(SensorType::MOTION,
                "Motion detected in " + _location,
                _location + " is motionless");

    MESSAGE_MAP(SensorType::FIRE,
                _location + " is on FIRE!",
                _location + " temperature is normal");

    MESSAGE_MAP(SensorType::NONE,
                "default",
                "default");
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
