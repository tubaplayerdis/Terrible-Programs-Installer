#include "pch.h"
#include "Startup.hpp"

void DebugTools::Startup::Init()
{
}

DebugTools::Helpers::StoreApplication::StoreApplication(bool available, std::string download, double version)
{
	Aviability = available;
	Download = download;
	Version = version;
}
