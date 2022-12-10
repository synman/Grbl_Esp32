/*
  Commands.cpp - GRBL_ESP command class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "../Grbl.h"

#ifdef __cplusplus
extern "C" {
#endif
esp_err_t esp_task_wdt_reset();
#ifdef __cplusplus
}
#endif

namespace WebUI {
    bool COMMANDS::restart_ESP_module = false;
    bool COMMANDS::deep_sleep_ESP_module = false;

    /*
     * delay is to avoid with asyncwebserver and may need to wait sometimes
     */
    void COMMANDS::wait(uint32_t milliseconds) {
        uint32_t timeout = millis();
        esp_task_wdt_reset();  //for a wait 0;
        //wait feeding WDT
        while ((millis() - timeout) < milliseconds) {
            esp_task_wdt_reset();
        }
    }

    bool COMMANDS::isLocalPasswordValid(char* password) {
        if (!password) {
            return true;
        }
        char c;
        //limited size
        if ((strlen(password) > MAX_LOCAL_PASSWORD_LENGTH) || (strlen(password) < MIN_LOCAL_PASSWORD_LENGTH)) {
            return false;
        }

        //no space allowed
        for (int i = 0; i < strlen(password); i++) {
            c = password[i];
            if (c == ' ') {
                return false;
            }
        }
        return true;
    }

    /**
     * Restart ESP
     */
    void COMMANDS::restart_ESP() { restart_ESP_module = true; }

    /**
     * deep sleep
    */
    void COMMANDS::deep_sleep_ESP() { deep_sleep_ESP_module = true; }


    /**
     * Handle not critical actions that must be done in sync environement
     */
    void COMMANDS::handle() {
        COMMANDS::wait(0);
        //in case of restart requested
        if (restart_ESP_module) {
            ESP.restart();
            while (1) {}
        }
        if (deep_sleep_ESP_module) {
            // put grbl to sleep
            if (sys.state != State::Sleep) {
                spindle->set_state(SpindleState::Disable, 0);  // De-energize
                grbl_send(CLIENT_ALL, "[MSG:Spindle Disabled]\r\n");
                coolant_off();
                grbl_send(CLIENT_ALL, "[MSG:Coolant Off]\r\n");
                motors_set_disable(true);  // Disable steppers
                grbl_send(CLIENT_ALL, "[MSG:Steppers Disabled]\r\n");
                protocol_exec_rt_system();
                delay_msec(5000, DwellMode::Dwell);
            }
            // now we go to deep sleep (hibernate)
            esp_sleep_pd_config(ESP_PD_DOMAIN_MAX, ESP_PD_OPTION_OFF);
            esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,   ESP_PD_OPTION_OFF);
            esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
            esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
            esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL,         ESP_PD_OPTION_OFF);

            uint64_t sleep_time = 31536000 * 1000000ULL; // for one year
            esp_sleep_enable_timer_wakeup(sleep_time);
            grbl_send(CLIENT_ALL, "[MSG:Entering Deep Sleep Hibernation]\r\n");
            esp_deep_sleep_start();

            // we should never get here
            ESP.restart();
            while (1) {}
        }
    }
}
