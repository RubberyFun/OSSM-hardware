#include "stepper.h"

FastAccelStepperEngine stepperEngine = FastAccelStepperEngine();
FastAccelStepper *stepper = nullptr;
class StrokeEngine Stroker;

void initStepper() {
    stepperEngine.init();
    stepper = stepperEngine.stepperConnectToPin(Pins::Driver::motorStepPin);
    if (stepper) {
        stepper->setDirectionPin(Pins::Driver::motorDirectionPin, false);
        stepper->setEnablePin(Pins::Driver::motorEnablePin, true);
        stepper->setAutoEnable(false);
    }

    // disable motor briefly in case we are against a hard stop.
    digitalWrite(Pins::Driver::motorEnablePin, HIGH);
    
    // Feed watchdog during long delay to prevent timeout
    for (int i = 0; i < 60; i++) {
        vTaskDelay(pdMS_TO_TICKS(10)); // 10ms * 60 = 600ms total
        yield(); // Allow other tasks to run and feed watchdog
    }
    
    digitalWrite(Pins::Driver::motorEnablePin, LOW);
    vTaskDelay(pdMS_TO_TICKS(100)); // Non-blocking delay
}
