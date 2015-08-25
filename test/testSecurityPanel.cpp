#include "catch.hpp"
#define private public
#include "MockAudibleAlarm.h"
#include "SecurityPanel.h"


TEST_CASE("test security panel", "[SecurityPanel,unit]") {
    SecurityPanel sp;
    sp._audibleAlarm.reset(dynamic_cast<AudibleAlarm *>(new MockAudibleAlarm));
    std::shared_ptr<MockAudibleAlarm> mockAlarm =
        std::dynamic_pointer_cast<MockAudibleAlarm>(sp._audibleAlarm);
    sp.setSecurityCode("this is correct password");
    CHECK(sp.isValidCode("this is not correct password") == false);
    CHECK(sp.isValidCode("this is correct password") == true);

    sp.arm();
    CHECK(sp.isArmed() == true);
    sp.alarm();
    CHECK(mockAlarm->alarmed == true);
    sp.enterCode("this is not correct password");
    CHECK(sp.isArmed() == true);
    sp.enterCode("this is correct password");
    CHECK(sp.isArmed() == false);
    CHECK(mockAlarm->alarmed == false);
}
