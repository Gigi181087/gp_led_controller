#include "LED.h"
#include <stdlib.h>

#define __assertinitialized(x) do{ if(x == NULL) {last_error = GP_LEDCONTROLLER_ERROR_NOTINITIALIZED; return GP_LEDCONTROLLER_ERROR_NOTINITIALIZED;}} while(0)
#define __assertnotinitialized(x) do{ if(x != NULL) { last_error = GP_LEDCONTROLLER_ERROR_ALREADYINITIALIZED; return GP_LEDCONTROLLER_ERROR_ALREADYINITIALIZED; }} while(0)

struct led_controller {
    uint8_t mode;
    uint16_t frequency;
    uint64_t next_step;
    uint8_t current_state;

    void (*led_set)(uint8_t);
};

uint8_t last_error;

uint8_t gp_ledController_init(gp_led_t** led_param, void(*led_function)(uint8_t)) {
  //__assertnotinitialized(led_param);

  if((*led_param = (gp_led_t*)malloc(sizeof(gp_led_t))) == NULL) {

    return GP_LEDCONTROLLER_ERROR_ALLOCFAILED;
  }
  (*led_param)->mode = 0;
  (*led_param)->current_state = 0;
  (*led_param)->frequency = 0;
  (*led_param)->led_set = led_function;
  (*led_param)->next_step = 0;

  return GP_LEDCONTROLLER_ERROR_NOERROR;
}

uint8_t gp_ledController_setOn(gp_led_t* led_param) {
  __assertinitialized(led_param);

  led_param->mode = 1;
  led_param->frequency = 0;
  led_param->next_step = 0;

  return GP_LEDCONTROLLER_ERROR_NOERROR;
}

uint8_t gp_ledController_setOff(gp_led_t* led_param) {
  __assertinitialized(led_param);

  led_param->mode = 0;
  led_param->frequency = 0;
  led_param->next_step = 0;

  return GP_LEDCONTROLLER_ERROR_NOERROR;
}

uint8_t gp_ledController_setBlinking(gp_led_t* led_param, uint16_t frequency_param) {
  __assertinitialized(led_param);

  led_param->mode = 2;
  led_param->frequency = frequency_param;

  return GP_LEDCONTROLLER_ERROR_NOERROR;
}

uint8_t gp_ledController_handle(gp_led_t* led_param, uint64_t system_time_param) {
  __assertinitialized(led_param);

  if(led_param->mode == 2) {

    if(system_time_param >= led_param->next_step) {
      led_param->current_state ^= 0x1;
      led_param->led_set(led_param->current_state);

      while(system_time_param >= led_param->next_step) {
        led_param->next_step += (1000 / led_param->frequency);
      }
      
    
    }

  } else if(led_param->mode != led_param->current_state) {
    led_param->current_state = led_param->mode;
    led_param->led_set(led_param->mode);
  }

  return GP_LEDCONTROLLER_ERROR_NOERROR;
}

uint64_t gp_ledController_getStatus(gp_led_t* led_param) {
    
    return led_param->next_step;


}
