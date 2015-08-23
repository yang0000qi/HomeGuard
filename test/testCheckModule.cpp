#include "catch.hpp"
#define private public
#include "CentralUnit.h"


TEST_CASE("run sensor test", "[CheckModule,unit]") {
    CentralUnit cu;
    Sensor s1("1", "door", SensorType::DOOR);
    Sensor s2("2", "window", SensorType::WINDOW);

    cu.sensorManager()->registerSensor(s1);
    cu.checkModule()->runSensorTest();
    cu.onRadioBroadcast("1,NOT_TRIPPED");
    CHECK(cu.checkModule()->status() == SensorStatus::PENDING);
    cu.onRadioBroadcast("1,TRIPPED");
    CHECK(cu.checkModule()->status() == SensorStatus::PASS);

    s1.reset();
    cu.sensorManager()->registerSensor(s2);
    cu.checkModule()->runSensorTest();
    cu.onRadioBroadcast("1,NOT_TRIPPED");
    cu.onRadioBroadcast("2,NOT_TRIPPED");
    CHECK(cu.checkModule()->status() == SensorStatus::PENDING);
    cu.onRadioBroadcast("1,TRIPPED");
    cu.onRadioBroadcast("2,TRIPPED");
    CHECK(cu.checkModule()->status() == SensorStatus::PASS);
}
