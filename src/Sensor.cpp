#include "Sensor.h"


Sensor::Sensor(const std::string& id,
               const std::string& location,
               SensorType type)
    : _id(id)
    , _location(location)
    , _type(type)
    , _tripped(false)
{}


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
    if (_id != InvalidId) {
        if ("TRIPPED" == status) {
            trip();
        } else {
            reset();
        }
    }
}

// FIXME!!
std::string Sensor::getMessage() const
{
    std::string message = "default";
    if (isTripped()) {
        if (SensorType::DOOR == _type)
            message = _location + " is open";
        else if (SensorType::WINDOW == _type)
            message = _location + " is ajar";
        else if (SensorType::MOTION == _type)
            message = "Motion detected in " + _location;
        else if (SensorType::FIRE == _type)
            message = _location + " is on FIRE!";
    } else {
        if (SensorType::DOOR == _type)
            message = _location + " is closed";
        else if (SensorType::WINDOW == _type)
            message = _location + " is sealed";
        else if (SensorType::MOTION == _type)
            message = _location + " is motionless";
        else if (SensorType::FIRE == _type)
            message = _location + " temperature is normal";
    }
    return message;
}
