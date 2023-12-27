#ifndef __GP_LED_CONTROLLER_H_
#define __GP_LED_CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GP_LEDSTATUS_ON     0
#define GP_LEDSTATUS_OFF    1

#define GP_LEDCONTROLLER_ERROR_NOERROR            0
#define GP_LEDCONTROLLER_ERROR_ALLOCFAILED        1
#define GP_LEDCONTROLLER_ERROR_NOTINITIALIZED     2
#define GP_LEDCONTROLLER_ERROR_ALREADYINITIALIZED 3



typedef struct led_controller gp_led_controller_t;
typedef enum led_modes {
  ON = 0,
  OFF = 1,
  BLINKING = 2
} gp_led_modes_t;

uint8_t gp_ledController_init(gp_led_controller_t**, void(*)(uint8_t));
uint8_t gp_ledController_setOff(gp_led_controller_t*);
uint8_t gp_ledController_setOn(gp_led_controller_t*);
uint8_t gp_ledController_setBlinking(gp_led_controller_t*, uint16_t);
uint8_t gp_ledController_handle(gp_led_controller_t*, uint64_t);

#ifdef __cplusplus
}
#endif

#endif // __GP_LED_CONTROLLER_H_
