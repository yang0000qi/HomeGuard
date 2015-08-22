#include "Sensor.h"
#include "CentralUnit.h"

int main(int argc, char *argv[])
{
    CentralUnit cu;
    Sensor s("1", "door", Sensor::Type::DOOR);
    cu.registerSensor(s);
    cu.onRadioBroadcast("1,TRIPPED");
    return 0;
}
