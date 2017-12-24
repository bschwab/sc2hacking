#include <sc2api/sc2_api.h>

#include <iostream>

using namespace sc2;

class Bot : public Agent {
public:
    virtual void OnGameStart() final {
        std::cout << "Hello, World we are getting started!" << std::endl;
    }

    void OnUnitCreated(const sc2::Unit* unit) final {
        // When a unit is created, note it here
        std::cout << "Unit created, tag:" << unit->tag << std::endl;
    }

    virtual void OnStep() final {
        std::cout << Observation()->GetGameLoop() << std::endl;

        // Print out the amount of Minerals & Vespene that we have
        std::cout << "Minerals: " << Observation()->GetMinerals() <<
            " Vespene: " << Observation()->GetVespene() << std::endl;    
    }
};

int main(int argc, char* argv[]) {

    Coordinator coordinator;
    coordinator.LoadSettings(argc, argv);

    Bot bot;
    coordinator.SetParticipants({
        CreateParticipant(Race::Terran, &bot),
        CreateComputer(Race::Zerg)
        });

    coordinator.LaunchStarcraft();
    coordinator.StartGame(sc2::kMapBelShirVestigeLE);

    while (coordinator.Update()) {
    }

    return 0;
}
