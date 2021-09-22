#ifndef DELAYED_RADAR_HPP
#define DELAYED_RADAR_HPP

#include "../../../lib/boost/sml.hpp"
#include "../../utilities/timeout_implementation/timeout.hpp"
#include "../../motors/drive_motors.hpp"
#include "../../../lib/boost/sml.hpp"
#include "../../dynamic_data/dynamic_data.hpp"
#include "../../configuration/configurations.hpp"
#include "../../motors/PID_controller.hpp"


namespace sml = boost::sml;

struct DelayedRadar
{
    auto operator()() const
    {
        using namespace sml;
        // Guards
        auto lostOpponent = [] { return !isOpponentDetected(); };
        auto lostLeft  = [lostOpponent] { return getErrorFromOPSensors() < 0 && lostOpponent; };
        auto lostRight = [lostOpponent] { return getErrorFromOPSensors() > 0 && lostOpponent; };
        auto opponentInFront = [] { return (getErrorFromOPSensors() == 0 && isOpponentDetected()); };

        // Funções
        auto rotate_left = [] { driveRobot(0, -1 * robotConfiguration.radarSpeed); std::cout << "left" << std::endl;}; // Talvez um PID seja melhor?
        auto rotate_right = [] { driveRobot(0, robotConfiguration.radarSpeed); std::cout << "right" << std::endl; };     // Talvez um PID seja melhor?
        auto stay_stopped = [] { stopMotors(); std::cout << "stop" << std::endl; };
        auto exitState = [] { setTimeout(2000); std::cout << "Set Timeout" << std::endl; };
        auto seeing = [] { driveRobot(0, pid(getErrorFromOPSensors())); std::cout << "seeing" << std::endl; };

        return make_transition_table(
            *"entry"_s = "setTimeout"_s,

            "setTimeout"_s = "seeing"_s,

            "seeing"_s  + event<LostOpponentAtLeft>  = "rotate_left"_s,
            "seeing"_s  + event<LostOpponentAtRight>  = "rotate_right"_s,
            "seeing"_s  + event<OpponentInFront> = "stay_stopped"_s,

            "rotate_left"_s + event<OpponentDetected> = "seeing"_s,
            "rotate_right"_s + event<OpponentDetected> = "seeing"_s,

            "stay_stopped"_s + event<OpponentDetectedNotInFront> = "seeing"_s,

            "setTimeout"_s    + on_entry<_>  / exitState,
            "seeing"_s        + on_entry<_>  / seeing,
            "rotate_left"_s   + on_entry<_>  / rotate_left,
            "rotate_right"_s  + on_entry<_>  / rotate_right,

            "stay_stopped"_s + on_entry<_> / stay_stopped
            );
    }
};

#endif