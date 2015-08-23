#pragma once

#include "HomeGuardView.h"


class TextView : public HomeGuardView
{
public:
	virtual void showMessage(const std::string& message);
};
