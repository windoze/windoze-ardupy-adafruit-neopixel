#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "py/obj.h"
#include "shared-bindings/util.h"

void common_hal_adafruit_neopixel_construct(abstract_module_t * self, uint32_t pin_ctrl);
void common_hal_adafruit_neopixel_deinit(abstract_module_t * self);
void common_hal_adafruit_neopixel_set_color(abstract_module_t * self, uint32_t pixel, uint32_t color);
void common_hal_adafruit_neopixel_show(abstract_module_t * self);

extern const mp_obj_type_t adafruit_neopixel_type;

m_generic_make(adafruit_neopixel) {
    enum { ARG_clk, ARG_dat,  };
    static const mp_arg_t allowed_args[] = {
        { MP_QSTR_pin,  MP_ARG_INT ,{.u_int = -1}},
        { MP_QSTR_num,  MP_ARG_INT ,{.u_int = -1}},
    };
    abstract_module_t * self = new_abstruct_module(type);
    mp_arg_val_t        vals[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_check_num(n_args, n_kw, 2, 2, false);
    mp_arg_parse_all_kw_array(n_args, n_kw, args, MP_ARRAY_SIZE(allowed_args), allowed_args, vals);

    common_hal_adafruit_neopixel_construct(self, vals[ARG_pin].u_int, vals[ARG_dat].u_int);
    return self;
}

mp_obj_t adafruit_neopixel_set_color(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    common_hal_adafruit_neopixel_set_color(
        (abstract_module_t *)(pos_args[0]), 
        (uint32_t)mp_obj_get_int(pos_args[1]), 
        (uint32_t)mp_obj_get_int(pos_args[2])
    );
    return mp_const_none;
}

mp_obj_t adafruit_neopixel_show(size_t n_args, const mp_obj_t * pos_args, mp_map_t * kw_args){
    common_hal_adafruit_neopixel_show(
        (abstract_module_t *)(pos_args[0])
    );
    return mp_const_none;
}

void adafruit_neopixel_obj_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest){
    generic_method_lookup(self_in, attr, dest);
}


MP_DEFINE_CONST_FUN_OBJ_KW(adafruit_neopixel_set_color_obj, 3, adafruit_neopixel_set_color);
MP_DEFINE_CONST_FUN_OBJ_KW(adafruit_neopixel_show_obj, 1, adafruit_neopixel_show);

const mp_rom_map_elem_t adafruit_neopixel_locals_dict_table[] = {
    // instance methods
    { MP_ROM_QSTR(MP_QSTR_deinit),          MP_ROM_PTR(&adafruit_neopixel_deinit_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),       MP_ROM_PTR(&default___enter___obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),        MP_ROM_PTR(&adafruit_neopixel_obj___exit___obj) },
    { MP_ROM_QSTR(MP_QSTR_set_color),       MP_ROM_PTR(&adafruit_neopixel_set_color_obj) },
    { MP_ROM_QSTR(MP_QSTR_show),            MP_ROM_PTR(&adafruit_neopixel_show_obj) },
};

const mp_obj_type_t adafruit_neopixel_type = {
    {&mp_type_type},
    .name = MP_QSTR_adafruit_neopixel,
    .make_new = adafruit_neopixel_make_new,
    .locals_dict = (mp_obj_t)&adafruit_neopixel_locals_dict_table,
    .attr = &adafruit_neopixel_obj_attr,
};
