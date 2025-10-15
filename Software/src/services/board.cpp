#include "board.h"

bool USE_SPEED_KNOB_AS_LIMIT = true;

void initBoard() {
    Serial.begin(115200);
    ESP_LOGI("BOARD", "Board initialization starting...");

    pinMode(Pins::Remote::encoderSwitch,
            INPUT_PULLDOWN);  // Rotary Encoder Pushbutton

    pinMode(Pins::Driver::motorEnablePin, OUTPUT);
    pinMode(Pins::Wifi::resetPin, INPUT_PULLDOWN);
    // TODO: Remove wifi toggle pin
    //    pinMode(Pins::Wifi::controlTogglePin, LOCAL_CONTROLLER); // choose
    //    between WIFI_CONTROLLER and LOCAL_CONTROLLER
    // Set analog pots (control knobs)
    pinMode(Pins::Remote::speedPotPin, INPUT);
    adcAttachPin(Pins::Remote::speedPotPin);

    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);  // allows us to read almost full 3.3V range
    
    ESP_LOGI("BOARD", "Initializing stepper...");
    initStepper();
    yield(); // Feed watchdog after stepper init
    
    ESP_LOGI("BOARD", "Initializing encoder...");
    initEncoder();
    yield(); // Feed watchdog after encoder init
    
    ESP_LOGI("BOARD", "Initializing LED...");
    initLED();
    yield(); // Feed watchdog after LED init
    
    ESP_LOGI("BOARD", "Board initialization completed successfully");
}
