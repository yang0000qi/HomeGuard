#include "SensorManager.h"


void SensorManager::registerSensor(const Sensor& sensor)
{
    _sensors.push_back(sensor);
}

Sensor SensorManager::getSensor(const std::string& id) const
{
    Sensor none(InvalidId, "No place", SensorType::NONE);

    for (auto sensor : _sensors) {
        if (id == sensor.id())
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
