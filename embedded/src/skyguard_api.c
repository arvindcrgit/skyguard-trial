#include "skyguard_api.h"
#include <stdio.h>
static uint8_t current_mode = 0; // 0: INIT

void skyguard_init(void) {
    current_mode = 1; // Transition to NAV mode on startup
}


void skyguard_step(const skyguard_sensor_data_t* sensor_in, skyguard_control_output_t* control_out) {
    if (!sensor_in || !control_out) return;

    // Failsafe FSM: Low battery (<10.5V) or GPS loss triggers Return-To-Launch (RTL)
    if (sensor_in->battery_voltage < 10.5f || !sensor_in->gps_valid) {
        current_mode = 3; // Mode 3 = RTL
    } 
    // Obstacle Failsafe: Distance below 2.0 meters triggers Avoidance
    else if (sensor_in->obstacle_distance > 0.0f && sensor_in->obstacle_distance < 2.0f) {
        current_mode = 2; // Mode 2 = AVOID
    } 
    else if (current_mode != 3) {
        current_mode = 1; // Mode 1 = NAV
    }

    // Command Motor Outputs based on Active Mode
    control_out->flight_mode = current_mode;
    if (current_mode == 3) {
        // RTL Throttle Configuration
        control_out->motor_speeds[0] = 0.5f;
        control_out->motor_speeds[1] = 0.5f;
        control_out->motor_speeds[2] = 0.5f;
        control_out->motor_speeds[3] = 0.5f;
    } else {
        // Nominal Flight Throttle
        control_out->motor_speeds[0] = 0.6f;
        control_out->motor_speeds[1] = 0.6f;
        control_out->motor_speeds[2] = 0.6f;
        control_out->motor_speeds[3] = 0.6f;
    }
}

void skyguard_reset(void) {
    current_mode = 0;
}