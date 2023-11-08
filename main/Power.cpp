#include <cstring>
#include "freertos/FreeRTOS.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "Power.hpp"

#define I2C_MASTER_SCL_IO 22
#define I2C_MASTER_SDA_IO 21
#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 100000

static int readI2C(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len);
static int writeI2C(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len);

static const char *TAG = "Power";
Logger *Power::log = Logger::getInstance();

Power::Power() {}

void Power::pmuInit()
{
    pmu = new XPowersPMU();

    if (!pmu->begin(AXP2101_SLAVE_ADDRESS, readI2C, writeI2C))
        log->error(TAG, "PMU not available");

    log->info(TAG, "Chip ID: 0x%x", pmu->getChipID());

    log->info(TAG, "Setting voltage and current limit to 4.36V 1000mA");
    pmu->setVbusVoltageLimit(XPOWERS_AXP2101_VBUS_VOL_LIM_4V36);
    pmu->setVbusCurrentLimit(XPOWERS_AXP2101_VBUS_CUR_LIM_1000MA);

    log->info(TAG, "Setting VSYS power down voltage to 3.0V");
    pmu->setSysPowerDownVoltage(3000);

    pmu->disableTSPinMeasure();
    pmu->enableBattDetection();
    pmu->enableVbusVoltageMeasure();
    pmu->enableBattVoltageMeasure();
    pmu->enableSystemVoltageMeasure();
    pmu->setChargingLedMode(XPOWERS_CHG_LED_CTRL_CHG);

    // gpioInit();
    pmu->disableIRQ(XPOWERS_AXP2101_ALL_IRQ);
    pmu->clearIrqStatus();
    pmu->enableIRQ(XPOWERS_AXP2101_PKEY_SHORT_IRQ);

    log->info(TAG, "Setting Precharge current: 200mA");
    pmu->setPrechargeCurr(XPOWERS_AXP2101_PRECHARGE_200MA);
    log->info(TAG, "Setting Charge Termination Current: 25mA");
    pmu->setChargerTerminationCurr(XPOWERS_AXP2101_CHG_ITERM_25MA);

    log->info(TAG, "Setting Charge Constant Current: 1.0A");
    pmu->setChargerConstantCurr(XPOWERS_AXP2101_CHG_CUR_1000MA);

    log->info(TAG, "Setting Charge Target Voltage : 4.2V");
    pmu->setChargeTargetVoltage(XPOWERS_AXP2101_CHG_VOL_4V2);

    pmu->setLowBatWarnThreshold(10);
    pmu->setLowBatShutdownThreshold(5);
    pmu->fuelGaugeControl(true, true);

    pmu->disableDC2();
    pmu->disableDC3();
    pmu->disableDC4();
    pmu->disableDC5();

    pmu->disableALDO1();
    pmu->disableALDO2();
    pmu->disableALDO3();
    pmu->disableALDO4();

    pmu->disableBLDO1();
    pmu->disableBLDO2();

    pmu->disableDLDO1();
    pmu->disableDLDO2();
}

Power *Power::init()
{
    Power *power = new Power();
    power->pmuInit();
    return power;
}

void Power::resetIrqState()
{
    pmu->clearIrqStatus();
}

static int readI2C(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len)
{
    return i2c_master_write_read_device(I2C_MASTER_NUM, devAddr, &regAddr, 1, data, len, pdMS_TO_TICKS(1000));
}

static int writeI2C(uint8_t devAddr, uint8_t regAddr, uint8_t *data, uint8_t len)
{
    uint8_t write_buf[len + 1];
    write_buf[0] = regAddr;
    std::memcpy(write_buf + 1, data, len);

    return i2c_master_write_to_device(I2C_MASTER_NUM, devAddr, write_buf, len + 1, pdMS_TO_TICKS(1000));
}