#include "Sensor.h"


Sensor::Sensor(const std::string& id,
               const std::string& location,
               Type type)
    : id(id)
    , location(location)
    , type(type)
    , tripped(false)
{}


std::string Sensor::getID() const
{
    return id;
}

std::string Sensor::getLocation() const
{
    return location;
}

Sensor::Type Sensor::getType() const
{
    return type;
}

bool Sensor::isTripped() const
{
    return tripped;
}

void Sensor::trip()
{
    tripped = true;
}

void Sensor::reset()
{
    tripped = false;
}

void Sensor::triggerByStatus(const std::string status)
{
    if (id != InvalidId) {
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
    if (tripped) {
        if (Sensor::DOOR == type)
            message = location + " is open";
        else if (Sensor::WINDOW == type)
            message = location + " is ajar";
        else if (Sensor::MOTION == type)
            message = "Motion detected in " + location;
        else if (Sensor::FIRE == type)
            message = location + " is on FIRE!";
    } else {
        if (Sensor::DOOR == type)
            message = location + " is closed";
        else if (Sensor::WINDOW == type)
            message = location + " is sealed";
        else if (Sensor::MOTION == type)
            message = location + " is motionless";
        else if (Sensor::FIRE == type)
            message = location + " temperature is normal";
    }
    return message;
}
