#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogInputPin.hpp"

#include "mcu/usart/UARTDataSource.hpp"
#include "mcu/usart/UARTConnection.hpp"
#include "mcu/usart/UARTInterruptSlaveConnection.hpp"

#include "periph/Accelerometer.hpp"
#include "periph/IRRangeFinder.hpp"
#include "periph/ToggleSwitchCollection.hpp"
#include "periph/LightEmittingDiode.hpp"

#include "com/DataSourceSensor.hpp"
#include "com/DataDestinationCentral.hpp"


int main ()
{
    AnalogInputController analogInputController;

    Accelerometer accelerometer(analogInputController);
    accelerometer.RegisterAxis(0x04, 0x00);
    accelerometer.RegisterAxis(0x05, 0xff);

    IRRangeFinder rangeRF(0x01, analogInputController);
    IRRangeFinder rangeRB(0x02, analogInputController);
    IRRangeFinder rangeLB(0x03, analogInputController);
    IRRangeFinder rangeLF(0x00, analogInputController);

    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB5);

    // TODO: servo library

    analogInputController.Enable();

    DataSourceSensor dataSourceSensor(accelerometer, rangeRF,
                                      rangeRB, rangeLB, rangeLF);

    DataDestinationCentral dataDestinationCentral(ledHeartbeat);
    UARTInterruptSlaveConnection uartCentral(
        0x00, 38400, dataDestinationCentral, 0x00, dataSourceSensor);

    sei();

    _delay_ms(1000);

    accelerometer.Calibrate();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        uartCentral.ReceiveData();
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
