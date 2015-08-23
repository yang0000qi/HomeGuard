#pragma once

#include <string>


class HomeGuardView
{
public:
    virtual void showMessage(const std::string& message) = 0;
};
