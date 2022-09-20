import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import automation
from esphome.components import cover
from esphome.const import (
    CONF_ID,
    CONF_CLOSE_ACTION,
    CONF_OPEN_ACTION,
    CONF_STOP_ACTION,
)

blinds_ns = cg.esphome_ns.namespace('blinds')
Blinds = blinds_ns.class_('Blinds', cover.Cover, cg.Component)

CONFIG_SCHEMA = cover.COVER_SCHEMA.extend({
    cv.GenerateID(): cv.declare_id(Blinds),
    cv.Required(CONF_OPEN_ACTION): automation.validate_automation(single=True),
    cv.Required(CONF_CLOSE_ACTION): automation.validate_automation(single=True),
    cv.Required(CONF_STOP_ACTION): automation.validate_automation(single=True),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await cover.register_cover(var, config)
    await automation.build_automation(
        var.get_stop_trigger(), [], config[CONF_STOP_ACTION]
    )
    await automation.build_automation(
        var.get_open_trigger(), [], config[CONF_OPEN_ACTION]
    )
    await automation.build_automation(
        var.get_close_trigger(), [], config[CONF_CLOSE_ACTION]
    )


