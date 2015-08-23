#pragma once

#include <map>
#include <vector>

#include "Sensor.h"


typedef std::map<std::string, std::string> SensorStatusMap;
typedef std::vector<Sensor> SensorList;


class SensorManager {
public:
    void registerSensor(const Sensor& sensor);
    SensorList& sensors();
    Sensor getSensor(const std::string& id) const;
    SensorStatusMap& sensorStatusMap();
    void clearStatusMap();
    void setStatus(const std::string id, const std::string status);

private:
    SensorList _sensors;
    SensorStatusMap _sensorStatusMap;
};
