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
    std::shared_ptr<CheckModule> checkModule();
    SecurityPanel& securityPanel();
    void onRadioBroadcast(const std::string& packet);

private:
    PacketTulpe _parsePacket(const std::string& packet);

private:
    std::shared_ptr<HomeguardView> _homeGuardView;
    std::shared_ptr<SensorManager> _sensorManager;
    std::shared_ptr<CheckModule> _checkModule;

    SecurityPanel _securityPanel;
    std::string _sensorTestStatus;
};
