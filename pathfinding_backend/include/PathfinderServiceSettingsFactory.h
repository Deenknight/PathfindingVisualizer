#pragma once

#include "IServiceSettingsFactory.h"

class PathfinderServiceSettingsFactory : public IServiceSettingsFactory{

public:

    PathfinderServiceSettingsFactory();
    shared_ptr<Settings> get_settings() const final;

private:

    shared_ptr<Settings> _settings;

};