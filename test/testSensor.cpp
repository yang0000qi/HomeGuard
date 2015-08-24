#include "catch.hpp"
#define private public
#include "Sensor.h"


TEST_CASE("test get sensor message", "[Sensor,unit]") {
    Sensor s1(InvalidId, "no location", SensorType::NONE);
    CHECK(s1.message() == "default");

    Sensor s2("2", "door", SensorType::DOOR);
    s2.trip();
    CHECK(s2.message() == "door is open");
    s2.reset();
    CHECK(s2.message() == "door is closed");

    Sensor s3("3", "fan", SensorType::MOTION);
    s3.trip();
    CHECK(s3.message() == "Motion detected in fan");
    s3.reset();
    CHECK(s3.message() == "fan is motionless");
}
