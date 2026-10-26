#ifndef SKYGUARD_API_H
#define SKYGUARD_API_H

#include "skyguard_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void skyguard_init(void);
void skyguard_step(const skyguard_sensor_data_t* sensor_in, skyguard_control_output_t* control_out);
void skyguard_reset(void);

#ifdef __cplusplus
}
#endif

#endif // SKYGUARD_API_H