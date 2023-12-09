#ifndef _AXP2101_H_
#define _AXP2101_H_

#include "utility/I2C_PORT.h"

/* AXP173 device address */
#define AXP2101_ADDR 0x34
#define AW9523_ADDR  0x58

enum power_mode {
    POWER_MODE_USB_IN_BUS_IN = 0,
    POWER_MODE_USB_IN_BUS_OUT,
    POWER_MODE_USB_OUT_BUS_IN,
    POWER_MODE_USB_OUT_BUS_OUT,
};

class AXP2101 : public I2C_PORT {
   private:
    uint16_t _getMin(uint16_t a, uint16_t b);
    uint16_t _getMax(uint16_t a, uint16_t b);
    uint16_t _getMid(uint16_t input, uint16_t min, uint16_t max);

   public:
    enum OUTPUT_CHANNEL {
        OP_DLDO1 = 0x99,
    };
    enum ADC_CHANNEL {
        ADC_TS = 0,
        ADC_APS_V,
        ADC_VBUS_C,
        ADC_VBUS_V,
        ADC_ACIN_C,
        ADC_ACIN_V,
        ADC_BAT_C,
        ADC_BAT_V,
    };
    enum CHARGE_CURRENT {
        CHG_100mA = 0,
        CHG_190mA,
        CHG_280mA,
        CHG_360mA,
        CHG_450mA,
        CHG_550mA,
        CHG_630mA,
        CHG_700mA,
        CHG_780mA,
        CHG_880mA,
        CHG_960mA,
        CHG_1000mA,
        CHG_1080mA,
        CHG_1160mA,
        CHG_1240mA,
        CHG_1320mA,
    };
    enum COULOMETER_CTRL {
        COULOMETER_RESET = 5,
        COULOMETER_PAUSE,
        COULOMETER_ENABLE,
    };

    /* Init */
    bool begin(TwoWire* wire = &Wire1);
    
    /* help functions */
    bool _getRegisterBit(uint8_t subaddress, int bit);
    void _setRegisterBit(uint8_t subaddress, int bit);
    /* Power input state */
    // bool isACINExist();
    // bool isACINAvl();

    bool isVBUSGood();
    bool getBatFetState();
    bool isBatConnect();
    bool getBatCurrentDir();

    bool isAXP173OverTemp();

    bool isCharging();
    bool isDischarging();
    bool isStandby();
    bool isPowerOn();
    bool isVBUSIn();

    bool isBatExist();
    bool isChargeCsmaller();
    /* Power output control */
    void setOutputEnable(OUTPUT_CHANNEL channel, bool state);
    void setOutputVoltage(OUTPUT_CHANNEL channel, uint16_t voltage);
    /* Basic control */
    void powerOFF();  ////
    /* Charge control */
    void setChargeEnable(bool state);
    void setChargeCurrent(CHARGE_CURRENT current);
    /* ADC control */

    // void setADCEnable(ADC_CHANNEL channel, bool state);  //
    void setAllADC(bool state);

#define XPOWERS_AXP2101_ADC_CHANNEL_CTRL                 (0x30)
    void enableVbusVoltageMeasure();
    void enableBattVoltageMeasure();
    void enableSystemVoltageMeasure();
    void enableTemperatureMeasure();

    /* Coulometer control */
    void setCoulometer(COULOMETER_CTRL option, bool state);
    /* Coulometer data */
    uint32_t getCoulometerChargeData();
    uint32_t getCoulometerDischargeData();
    float getCoulometerData();
    /* BAT data */
    // float getBatVoltage();

#define XPOWERS_AXP2101_ADC_DATA_RELUST6                 (0x3A)
#define XPOWERS_AXP2101_ADC_DATA_RELUST7                 (0x3B)
    uint16_t getSystemVoltage();

#define XPOWERS_AXP2101_ADC_DATA_RELUST0                 (0x34)
#define XPOWERS_AXP2101_ADC_DATA_RELUST1                 (0x35)
    uint16_t getBatVoltage();
    float getBatCurrent();
    float getBatLevel();
    float getBatPower();
    /* VBUS data */
    // float getVBUSVoltage();
#define XPOWERS_AXP2101_ADC_DATA_RELUST4                 (0x38)
#define XPOWERS_AXP2101_ADC_DATA_RELUST5                 (0x39)
    uint16_t getVBUSVoltage();
    float getVBUSCurrent();

    /* Temperature data */
#define XPOWERS_AXP2101_CONVERSION(raw)                 (22.0 + (7274 - raw) / 20.0)
#define XPOWERS_AXP2101_ADC_DATA_RELUST8                 (0x3C)
#define XPOWERS_AXP2101_ADC_DATA_RELUST9                 (0x3D)
    float getTemperature();
    float getAXP173Temp();
    float getTSTemp();

    void coreS3_init();
    void coreS3_AW9523_init();

    // Power Manage
    void setBusOutEn(bool state);
    void setUsbOtgEn(bool state);
    void setBoostEn(bool state);
    void setBoostBusOutEn(bool state);
    void powerModeSet(power_mode mode);

    void coreS3_VBUS_boost(bool state);
    bool isSDCardExist();
};

#endif