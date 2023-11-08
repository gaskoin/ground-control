#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>

#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_wifi.h"

#include "Communication.hpp"
#include "Config.hpp"

/*
 * Unfortunatelly there is no other way since ESP does not provide additional parameters
 * in esp_now_register_send_cb and esp_now_register_recv_cb
 */
static EventDispatcher *dispatcher;

static void onDataReceived(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int length);

Logger *Communication::log = Logger::getInstance();

void Communication::nvsInit()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void Communication::wifiInit()
{
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    ESP_ERROR_CHECK(esp_wifi_set_mode(Config::getWifiMode()));
    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_set_channel(Config::getWifiChannel(), WIFI_SECOND_CHAN_NONE));
    ESP_ERROR_CHECK(esp_wifi_set_protocol(Config::getWifiInterface(), WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N | WIFI_PROTOCOL_LR));
}

void Communication::espnowInit()
{
    ESP_ERROR_CHECK(esp_now_init());
    ESP_ERROR_CHECK(esp_now_register_recv_cb(onDataReceived));
    ESP_ERROR_CHECK(esp_now_set_pmk(Config::getPrimaryMasterKey().data()));
}

Communication::Communication(EventDispatcher *eventDispatcher)
{
    dispatcher = eventDispatcher;
}

Communication *Communication::init(EventDispatcher *eventDispatcher)
{
    Communication *communication = new Communication(eventDispatcher);
    communication->nvsInit();
    communication->wifiInit();
    communication->espnowInit();
    communication->connect(BROADCAST_MAC);

    return communication;
}

bool Communication::isBroadcast(std::vector<uint8_t> address)
{
    return address == BROADCAST_MAC;
}

void Communication::connect(const std::vector<uint8_t> address)
{
    this->peerAddress = std::move(address);
    if (esp_now_is_peer_exist(peerAddress.data()))
        return;

    log->info(TAG, "Registering new peer %02x:%02x:%02x:%02x:%02x:%02x", MAC2STR(peerAddress));

    bool isBroadcast = this->isBroadcast(peerAddress);
    esp_now_peer_info_t peer;
    peer.channel = Config::getWifiChannel();
    peer.ifidx = Config::getWifiInterface();
    peer.encrypt = !isBroadcast;
    std::copy(peerAddress.begin(), peerAddress.end(), std::begin(peer.peer_addr));

    if (!isBroadcast)
    {
        std::vector<uint8_t> lmk = Config::getLocalMasterKey();
        std::copy(lmk.begin(), lmk.end(), std::begin(peer.lmk));
    }

    esp_now_add_peer(&peer);
}

std::vector<uint8_t> Communication::getLocalAddress()
{
    uint8_t buffer[ADDRESS_SIZE];
    esp_read_mac(buffer, Config::getMacType());
    return std::vector<uint8_t>(buffer, buffer + 6);
}

static void onDataReceived(const esp_now_recv_info_t *esp_now_info, const uint8_t *data, int length)
{
    if (dispatcher != nullptr)
        dispatcher->dispatch(data, length);
}