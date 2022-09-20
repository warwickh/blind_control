#pragma once
#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/cover/cover.h"

namespace esphome {
namespace blinds {

class Blinds : public Component, public cover::Cover {
  public:
    void setup() override;
    void loop() override;
    void dump_config() override;
    cover::CoverTraits get_traits() override;
    void control(const cover::CoverCall &call) override;
    Trigger<> *get_open_trigger() const { return this->open_trigger; }
    Trigger<> *get_close_trigger() const { return this->close_trigger; }
    Trigger<> *get_stop_trigger() const { return this->stop_trigger; }    
  private:
    uint32_t last_position_update{0};
    int exact_pos;
    int relative_pos{0};
    cover::CoverOperation current_action{cover::COVER_OPERATION_IDLE};
  protected:
    Trigger<> *open_trigger{new Trigger<>()};
    Trigger<> *close_trigger{new Trigger<>()};
    Trigger<> *stop_trigger{new Trigger<>()};
    bool assumed_state{false};
};

}
}
