#pragma once
// clang-format off

/*
    OpenBuilds_BlackBox_X32-XYYZ-NODOOR.h
    Part of Grbl_ESP32

    2022    - Shell Shrader

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/

//Name your machine configuration - this can be viewed real-time using the $i command
#define MACHINE_NAME "OpenBuilds_BlackBox_X32-XYYZ-NODOOR"

//Define the number of Axis being used (not the number of motors needed - ex. XYYZ machine is still 3 axis) 
#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 3 
#define MAX_AXIS 3

/**************************MOTOR SETUP*********************/
#define STEPPERS_DISABLE_PIN    GPIO_NUM_17
#define DEFAULT_INVERT_ST_ENABLE 1

// X motor connects to the 1st driver, and the X port on the case 
#define X_STEP_PIN              GPIO_NUM_12
#define X_DIRECTION_PIN         GPIO_NUM_14

// Y motor connects to the 2nd driver, and the Y port on the case
#define Y_STEP_PIN              GPIO_NUM_27
#define Y_DIRECTION_PIN         GPIO_NUM_26

// Y2 motor connects to the 3rd driver, and the Y2/A port on the case
#define Y2_STEP_PIN              GPIO_NUM_33  
#define Y2_DIRECTION_PIN         GPIO_NUM_32  

// Z Axis motor connects to the 4th driver, and the Z port on the case
#define Z_STEP_PIN              GPIO_NUM_15 
#define Z_DIRECTION_PIN         GPIO_NUM_2 
/**********************************************************/

/********************COOLANT SETUP*************************/
// Coolant output terminal is a switched ground output (low side switch)
// Defaulted to Mist coolant: Turn on with M7 and off with M9
#define COOLANT_MIST_PIN        GPIO_NUM_21
//Option:  Flood coolant - comment out the mist coolant line, and uncomment the below line
// #define COOLANT_FLOOD_PIN		GPIO_NUM_21
/**********************************************************/

/*********** Spindle VFD and Laser Setup ******************/
#define SPINDLE_TYPE          SpindleType::NONE

#define SPINDLE_OUTPUT_PIN      GPIO_NUM_25
#define SPINDLE_ENABLE_PIN      GPIO_NUM_13
#define SPINDLE_DIR_PIN         GPIO_NUM_4

#define DEFAULT_SPINDLE_RPM_MAX     1000
#define DEFAULT_SPINDLE_DELAY_SPINDOWN 10
#define DEFAULT_SPINDLE_DELAY_SPINUP 10
/***********************************************************/

/***********   Input Pins  ******************/
#define PROBE_PIN               GPIO_NUM_22
#define X_LIMIT_PIN             GPIO_NUM_35
#define Y_LIMIT_PIN             GPIO_NUM_34
#define Z_LIMIT_PIN             GPIO_NUM_39
#define CONTROL_SAFETY_DOOR_PIN GPIO_NUM_16
#define MACRO_BUTTON_0_PIN      GPIO_NUM_0      // MODE button
/********************************************/

/*********** CUSTOM PINS ************/
#define GRBL_SPI_FREQ 4000000
#define GRBL_SPI_SS 5
#define GRBL_SPI_MOSI 23
#define GRBL_SPI_MISO 19
#define GRBL_SPI_SCK 18
/************************************/

// Use a custom name for host, AP SSID, and BT GATT
#define CUSTOM_NET_NAME "BlackBox-X32"

// Default configuration - assuming screw TR8*8 screw driven machine in XYYZ config
//steps per mm - use 200 for TR8*8 screws, and 26.667 for belts
#define DEFAULT_X_STEPS_PER_MM 200.0
#define DEFAULT_Y_STEPS_PER_MM 200.0
#define DEFAULT_Z_STEPS_PER_MM 200.0
#define DEFAULT_A_STEPS_PER_MM 200.0

//max speed
#define DEFAULT_X_MAX_RATE 2500.0
#define DEFAULT_Y_MAX_RATE 2500.0
#define DEFAULT_Z_MAX_RATE 2500.0

#define DEFAULT_X_ACCELERATION 50.0
#define DEFAULT_Y_ACCELERATION 50.0
#define DEFAULT_Z_ACCELERATION 50.0

//homing
// Home Z axis to clear workspace, then home X and Y at same time
#define DEFAULT_HOMING_CYCLE_0 bit(Z_AXIS)
#define DEFAULT_HOMING_CYCLE_1 (bit(X_AXIS) | bit(Y_AXIS))
#define DEFAULT_HOMING_PULLOFF 2.5

//Stepper settings
#define DEFAULT_STEP_PULSE_MICROSECONDS 4
#define DEFAULT_STEPPER_IDLE_LOCK_TIME 255

//switches and probes - 1 =  NO switches, 0 = NC switches
#define DEFAULT_INVERT_PROBE_PIN 1
#define DEFAULT_INVERT_LIMIT_PINS 1

//Control Safety Door Switch
#ifdef INVERT_CONTROL_PIN_MASK
#undef INVERT_CONTROL_PIN_MASK
#endif
// For NC Door switch INVERT_CONTROL_PIN_MASK = B00001110
// For NO Door switch INVERT_CONTROL_PIN_MASK = B00001111
// Macro3 | Macro2 | Macro 1| Macr0 |Cycle Start | Feed Hold | Reset | Safety Door
// 1 for NO switch, 0 for NC switch
#define INVERT_CONTROL_PIN_MASK B01111111
