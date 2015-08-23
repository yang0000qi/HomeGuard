#pragma once

#include <map>
#include <vector>

#include "Sensor.h"


typedef std::map<std::string, std::string> SensorStatusMap;
typedef std::vector<Sensor> SensorList;

class SensorManager {
public:
    Sensor getSensor(const std::string& id) const;
    void registerSensor(const Sensor& sensor);
    void clearStatusMap();
    void setStatus(const std::string id, const std::string status);

    SensorList& sensors() { return _sensors; }
    SensorStatusMap& sensorStatusMap() { return _sensorStatusMap; }

private:
    SensorList _sensors;
    SensorStatusMap _sensorStatusMap;
};
