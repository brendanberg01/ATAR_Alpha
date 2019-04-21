#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogInputPin.hpp"

#include "mcu/usart/UARTConnection.hpp"

#include "periph/LightEmittingDiode.hpp"
#include "periph/Acceleromter.hpp"


int main ()
{
    // TODO: interrupt handler
    UARTConnection uartCentral(0, 38400);

    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB5);

    AnalogInputController analogInputController;

    // TODO: outsource
    AnalogInputPin sharpRF(0x01, 4);
    analogInputController.RegisterAnalogPin(&sharpRF);
    AnalogInputPin sharpRB(0x02, 4);
    analogInputController.RegisterAnalogPin(&sharpRB);
    AnalogInputPin sharpLB(0x03, 4);
    analogInputController.RegisterAnalogPin(&sharpLB);
    AnalogInputPin sharpLF(0x00, 4);
    analogInputController.RegisterAnalogPin(&sharpLF);

    Acceleromter acceleromter(0x04, 0xff, 0x05, analogInputController);

    analogInputController.Enable();

    sei();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    { }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
