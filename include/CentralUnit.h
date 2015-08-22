#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "AudibleAlarm.h"
#include "HomeguardView.h"
#include "Sensor.h"


typedef std::map<std::string, std::string> SensorStatusMap;
typedef std::tuple<std::string, std::string> PacketTulpe;
typedef std::vector<Sensor> SensorList;

class CentralUnit {
public:
    CentralUnit();

    bool isArmed() const;
    void arm();
    void disarm();

    bool isValidCode(const std::string& code) const;
    void setSecurityCode(const std::string& code);
    void enterCode(const std::string& code);

    SensorList& getSensors();
    SensorStatusMap& getSensorStatusMap();
    void registerSensor(const Sensor& sensor);
    void onRadioBroadcast(const std::string& packet);
    void runSensorTestPrepare();
    Sensor getSensor(const std::string& id) const;
    std::string getSensorStatus() const;

private:
    void _sensorTest(const std::string& id, const std::string& status);
    void _terminateSensorTest();
    PacketTulpe _parsePacket(const std::string& packet);

private:
    std::string _sensorTestStatus;
    bool _armed;
    std::string _securityCode;
    std::shared_ptr<AudibleAlarm> _audibleAlarm;
    std::shared_ptr<HomeguardView> _homeGuardView;
    SensorList _sensors;
    bool _runningSensorTest;
    SensorStatusMap _sensorStatusMap;
};
