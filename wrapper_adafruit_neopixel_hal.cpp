#include "Adafruit_NeoPixel/Adafruit_NeoPixel.h"
extern "C"{
#include "py/mphal.h"
#include "py/nlr.h"
#include "py/objtype.h"
#include "py/runtime.h"
#include "shared-bindings/util.h"
}

#define neopixel     (*(Adafruit_NeoPixel *)self->module)
void * operator new(size_t, void *);

extern "C"{
    void common_hal_adafruit_neopixel_construct(abstract_module_t * self, uint32_t pin_ctrl, uint32_t n){
        self->module = new(m_new_obj(Adafruit_NeoPixel))(Adafruit_NeoPixel(n, pin_ctrl));
        neopixel.begin();
    }
    void common_hal_adafruit_neopixel_deinit(abstract_module_t * self){
        neopixel.~Adafruit_NeoPixel();
    }
    void common_hal_adafruit_neopixel_set_color(abstract_module_t * self, uint32_t pixel, uint32_t color){
        neopixel.setPixelColor(pixel, color);
    }
    void common_hal_adafruit_neopixel_show(abstract_module_t * self){
        neopixel.show();
    }
}
