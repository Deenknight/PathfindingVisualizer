#include "PathfinderResourceFactory.h"
#include "PathfinderServiceSettingsFactory.h"
#include "PathfinderService.h"

int main(int argc, char** argv){
    auto resource_factory = make_shared<PathfinderResourceFactory>();
    auto setting_factory = make_shared<PathfinderServiceSettingsFactory>();

    PathfinderService service(resource_factory, setting_factory);

    service.start();

    return 0;
}