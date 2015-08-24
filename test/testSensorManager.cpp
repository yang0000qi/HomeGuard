#include "catch.hpp"
#define private public
#include "CentralUnit.h"


TEST_CASE("test find sensor by id", "[SensorManager,unit]") {
    CentralUnit cu;

    SECTION("find the sensor") {
        Sensor s1("1", "door", SensorType::DOOR);
        Sensor s2("2", "window", SensorType::FIRE);
        Sensor s3("3", "cell", SensorType::WINDOW);
        cu.sensorManager()->registerSensor(s1);
        cu.sensorManager()->registerSensor(s2);
        cu.sensorManager()->registerSensor(s3);

        Sensor s = cu.sensorManager()->getSensor("1");
        CHECK(s.id() == "1");
        CHECK(s.location() == "door");
        CHECK(s.type() == SensorType::DOOR);

        s = cu.sensorManager()->getSensor("3");
        CHECK(s.id() == "3");
        CHECK(s.location() == "cell");
        CHECK(s.type() == SensorType::WINDOW);
    }

    SECTION("no sensor in CentralUnit") {
        Sensor s = cu.sensorManager()->getSensor("1");

        CHECK(s.id() == InvalidId);
        CHECK(s.location() == "No place");
        CHECK(s.type() == SensorType::NONE);
    }
}
