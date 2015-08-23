#include "SensorManager.h"


void SensorManager::registerSensor(const Sensor& sensor)
{
    _sensors.push_back(sensor);
}

SensorStatusMap& SensorManager::sensorStatusMap()
{
    return _sensorStatusMap;
}

SensorList& SensorManager::sensors()
{
    return _sensors;
}

Sensor SensorManager::getSensor(const std::string& id) const
{
    Sensor none(InvalidId, "No place", SensorType::NONE);

    for (auto sensor : _sensors) {
        if (id == sensor.getID())
            return sensor;
    }

    return none;    
}

void SensorManager::clearStatusMap()
{
    _sensorStatusMap.clear();
}

void SensorManager::setStatus(const std::string id, const std::string status)
{
    _sensorStatusMap[id] = status;
}