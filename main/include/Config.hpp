#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <cstdint>
#include <vector>

#include "freertos/FreeRTOS.h"

#include "esp_mac.h"
#include "esp_now.h"

static std::vector<uint8_t> localMasterKey {0x39, 0x34, 0x62, 0x32, 0x38, 0x63, 0x64, 0x61, 0x37, 0x36, 0x63, 0x39, 0x34, 0x34, 0x32, 0x62};
static std::vector<uint8_t> primaryMasterKey {0x39, 0x39, 0x32, 0x64, 0x38, 0x61, 0x34, 0x61, 0x34, 0x64, 0x35, 0x34, 0x34, 0x37, 0x39, 0x32};

class Config
{
private:
    Config(){};
    ~Config(){};

public:
    // Hardware specific
    static std::vector<uint8_t> getPrimaryMasterKey() { return primaryMasterKey; }
    static std::vector<uint8_t> getLocalMasterKey() { return localMasterKey; }
    static wifi_mode_t getWifiMode() { return WIFI_MODE_STA; }
    static wifi_interface_t getWifiInterface() { return WIFI_IF_STA; }
    static int getWifiChannel() { return 1; }
    static esp_mac_type_t getMacType() {return ESP_MAC_WIFI_STA;}

    // Application specific
    static uint32_t getBroadcastPeriod() { return 30 * 1000; }
    static uint32_t getInputMonitorPeriod() { return 50; }
    static uint16_t getIgnitionDelay() { return 10000; }
    static uint16_t getDisplayRate() { return 100; }
    static uint16_t getAllowedLaunchpadInactivityPeriod() { return 5000; }
    static uint16_t getLaunchpadInactivityMonitorPeriod() { return 100; }
    static uint16_t getLowBatteryVoltage() { return 3400; }
};

#endif
