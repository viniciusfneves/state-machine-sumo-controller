#pragma once

#include <PS4Controller.h>

#define MAX_BREATH_BRIGHTNESS 200
#define BREATH_COLOR_DECAY 20

namespace ps4LightCtrl {
    int16_t r_buf, g_buf, b_buf;
    int16_t r_var, g_var, b_var;
    int16_t r, g, b;
    bool    timeToChange     = false;
    bool    switchController = true;
}  // namespace ps4LightCtrl

namespace ps4Timestamps {
    unsigned long lastControllerUpdateTimestamp = 0UL;
    unsigned long lastlightUpdateTimestamp      = 0UL;
}  // namespace ps4Timestamps

enum class LightMode {
    l_static,
    flashing,
    fast_flashing,
    slow_flashing,
    flashing_dual_colors,
    slow_flashing_dual_colors,
    breathing
};

enum class Vibration {
    none,
    weak,
    strong
};

#define SET_UNIQUE_COLOR(_r, _g, _b)          \
    ps4LightCtrl::r     = _r;                 \
    ps4LightCtrl::g     = _g;                 \
    ps4LightCtrl::b     = _b;                 \
    ps4LightCtrl::r_var = BREATH_COLOR_DECAY; \
    ps4LightCtrl::g_var = BREATH_COLOR_DECAY; \
    ps4LightCtrl::b_var = BREATH_COLOR_DECAY

#define SET_DUAL_COLORS(r1, g1, b1, r2, g2, b2) \
    ps4LightCtrl::r     = r1;                   \
    ps4LightCtrl::g     = g1;                   \
    ps4LightCtrl::b     = b1;                   \
    ps4LightCtrl::r_buf = r2;                   \
    ps4LightCtrl::g_buf = g2;                   \
    ps4LightCtrl::b_buf = b2;                   \
    ps4LightCtrl::r_var = BREATH_COLOR_DECAY;   \
    ps4LightCtrl::g_var = BREATH_COLOR_DECAY;   \
    ps4LightCtrl::b_var = BREATH_COLOR_DECAY

#define SET_BREATHING_COLOR(_r, _g, _b) \
    ps4LightCtrl::r_buf = _r;           \
    ps4LightCtrl::g_buf = _g;           \
    ps4LightCtrl::b_buf = _b

// time define o tempo(us) no qual as luzes devem alternar
#define DUAL_COLOR_FLASHING_LIGHT_HANDLER(time)                                               \
    ps4LightCtrl::timeToChange = (micros() - ps4Timestamps::lastlightUpdateTimestamp) > time; \
    if (!ps4LightCtrl::timeToChange)                                                          \
        return;                                                                               \
    if (ps4LightCtrl::switchController)                                                       \
        PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);                        \
    else                                                                                      \
        PS4.setLed(ps4LightCtrl::r_buf, ps4LightCtrl::g_buf, ps4LightCtrl::b_buf);            \
    ps4LightCtrl::switchController ^= 1;                                                      \
    ps4Timestamps::lastlightUpdateTimestamp = micros();                                       \
    PS4.setFlashRate(255, 0);                                                                 \
    PS4.sendToController();                                                                   \
    return

// timing define a velocidade do breathing, sendo um valor mais baixo, o mais rápido
#define BREATHING_LIGHT_HANDLER(timing)                                                                                                                                                                                  \
    if (((ps4LightCtrl::r == 0) * (ps4LightCtrl::g == 0) * (ps4LightCtrl::b == 0))) {                                                                                                                                    \
        ps4LightCtrl::r_var = ps4LightCtrl::r_buf / timing;                                                                                                                                                              \
        ps4LightCtrl::g_var = ps4LightCtrl::g_buf / timing;                                                                                                                                                              \
        ps4LightCtrl::b_var = ps4LightCtrl::b_buf / timing;                                                                                                                                                              \
    }                                                                                                                                                                                                                    \
    if (ps4LightCtrl::switchController) {                                                                                                                                                                                \
        ps4LightCtrl::r += ps4LightCtrl::r_var;                                                                                                                                                                          \
        ps4LightCtrl::g += ps4LightCtrl::g_var;                                                                                                                                                                          \
        ps4LightCtrl::b += ps4LightCtrl::b_var;                                                                                                                                                                          \
        if (((ps4LightCtrl::r + ps4LightCtrl::r_var) > MAX_BREATH_BRIGHTNESS) + ((ps4LightCtrl::g + ps4LightCtrl::g_var) > MAX_BREATH_BRIGHTNESS) + ((ps4LightCtrl::b + ps4LightCtrl::b_var) > MAX_BREATH_BRIGHTNESS)) { \
            ps4LightCtrl::switchController ^= 1;                                                                                                                                                                         \
        }                                                                                                                                                                                                                \
    } else {                                                                                                                                                                                                             \
        ps4LightCtrl::r -= ps4LightCtrl::r_var;                                                                                                                                                                          \
        ps4LightCtrl::g -= ps4LightCtrl::g_var;                                                                                                                                                                          \
        ps4LightCtrl::b -= ps4LightCtrl::b_var;                                                                                                                                                                          \
        if (((ps4LightCtrl::r - ps4LightCtrl::r_var) <= 0) * ((ps4LightCtrl::g - ps4LightCtrl::g_var) <= 0) * ((ps4LightCtrl::b - ps4LightCtrl::b_var) <= 0)) {                                                          \
            ps4LightCtrl::switchController ^= 1;                                                                                                                                                                         \
            SET_UNIQUE_COLOR(0, 0, 0);                                                                                                                                                                                   \
        }                                                                                                                                                                                                                \
    }                                                                                                                                                                                                                    \
    ps4LightCtrl::r = constrain(ps4LightCtrl::r, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    ps4LightCtrl::g = constrain(ps4LightCtrl::g, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    ps4LightCtrl::b = constrain(ps4LightCtrl::b, 0, MAX_BREATH_BRIGHTNESS);                                                                                                                                              \
    PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);                                                                                                                                                       \
    PS4.setFlashRate(255, 0);                                                                                                                                                                                            \
    PS4.sendToController();                                                                                                                                                                                              \
    return

void configController(const LightMode& mode, const Vibration vibro = Vibration::none) {
    switch (vibro) {
        case Vibration::none:
            PS4.setRumble(0, 0);
            break;

        case Vibration::weak:
            PS4.setRumble(92, 127);
            break;

        case Vibration::strong:
            PS4.setRumble(170, 255);
            break;
    }
    switch (mode) {
        case LightMode::l_static:
            PS4.setFlashRate(255, 0);
            break;

        case LightMode::flashing:
            PS4.setFlashRate(127, 127);
            break;

        case LightMode::slow_flashing:
            PS4.setFlashRate(255, 255);
            break;

        case LightMode::fast_flashing:
            PS4.setFlashRate(92, 92);
            break;

        case LightMode::flashing_dual_colors:
            DUAL_COLOR_FLASHING_LIGHT_HANDLER(190000);

        case LightMode::slow_flashing_dual_colors:
            DUAL_COLOR_FLASHING_LIGHT_HANDLER(450000);

        case LightMode::breathing:
            BREATHING_LIGHT_HANDLER(80);

        default:
            PS4.setFlashRate(255, 0);
            break;
    }
    PS4.setLed(ps4LightCtrl::r, ps4LightCtrl::g, ps4LightCtrl::b);
    PS4.sendToController();
}
