﻿#pragma once

#include <map>
#include <memory>
#include <vector>

#include "CheckModule.h"
#include "HomeGuardView.h"
#include "Sensor.h"
#include "SensorManager.h"
#include "SecurityPanel.h"
#include "Packets.h"


class CentralUnit {
public:
    CentralUnit();
    void onRadioBroadcast(const std::string& packet);

    std::shared_ptr<SensorManager> sensorManager() { return _sensorManager; }
    std::shared_ptr<CheckModule> checkModule() { return _checkModule; }
    std::shared_ptr<SecurityPanel> securityPanel() { return _securityPanel; }
    std::shared_ptr<HomeGuardView> homeGuardView() { return _homeGuardView; }

private:
    std::shared_ptr<HomeGuardView> _homeGuardView;
    std::shared_ptr<SensorManager> _sensorManager;
    std::shared_ptr<CheckModule> _checkModule;
    std::shared_ptr<SecurityPanel> _securityPanel;
};
