#pragma once

#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include "CheckModule.h"
#include "HomeguardView.h"
#include "Sensor.h"
#include "SensorManager.h"
#include "SecurityPanel.h"


typedef std::tuple<std::string, std::string> PacketTulpe;

class CentralUnit {
public:
    CentralUnit();

    std::shared_ptr<SensorManager> sensorManager();
    SecurityPanel& securityPanel();
    std::string getSensorStatus() const;
    void onRadioBroadcast(const std::string& packet);
    void runSensorTest();

private:
    void _sensorTest(const std::string& id, const std::string& status);
    void _terminateSensorTest();
    PacketTulpe _parsePacket(const std::string& packet);
    bool _sensorTestDone();

private:
    std::shared_ptr<HomeguardView> _homeGuardView;
    std::shared_ptr<SensorManager> _sensorManager;
    bool _runningSensorTest;

    SecurityPanel _securityPanel;
    CheckModule _checkModule;
    std::string _sensorTestStatus;
};
