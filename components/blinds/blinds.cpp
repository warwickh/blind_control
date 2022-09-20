#include "venetian_blinds.h"
#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace blinds {

static const char *TAG = "blinds.cover";

using namespace esphome::cover;

void Blinds::dump_config() {
    LOG_COVER("", "Blinds", this);
}

void VenetianBlinds::setup() {   
    auto restore = this->restore_state_();
    if (restore.has_value()) {
        restore->apply(this);
    } else {
        this->position = 0.0;
        this->tilt = 0.0;
    }
        exact_pos = this->position;
        exact_tilt = this->tilt;
}

CoverTraits Blinds::get_traits() {
    auto traits = CoverTraits();
    traits.set_is_assumed_state(this->assumed_state);
    return traits;
}

void Blinds::control(const CoverCall &call) {
    if (call.get_stop()) {
        relative_pos = 0;
        relative_tilt = 0;
        this->stop_trigger->trigger();
        this->current_action = COVER_OPERATION_IDLE;
        this->publish_state();
    }
}
void Blinds::loop() {
    uint32_t current_time = millis();

};

}
}
