#include "Modules/ModuleManager.h"
#include "GridlineCore.h"

class FGridlineModule : public FDefaultGameModuleImpl {
public:
    virtual void StartupModule() override {
        FDefaultGameModuleImpl::StartupModule();
        gridline::Grid Grid(4, 4); gridline::Battle Battle;
        const bool Ready = Battle.move(Grid, {1, 0}, 2);
        UE_LOG(LogTemp, Display, TEXT("Gridline core startup: %s"), Ready ? TEXT("ready") : TEXT("failed"));
    }
};
IMPLEMENT_PRIMARY_GAME_MODULE(FGridlineModule, Gridline, "Gridline");
