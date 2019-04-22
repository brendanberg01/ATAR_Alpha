#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogInputPin.hpp"

#include "mcu/usart/UARTDataSource.hpp"
#include "mcu/usart/UARTConnection.hpp"
#include "mcu/usart/UARTInterruptSlaveConnection.hpp"

#include "periph/LightEmittingDiode.hpp"
#include "periph/Accelerometer.hpp"


class SensorData : public UARTDataSource
{
public:

    explicit SensorData (Accelerometer& accelerometer)
        : UARTDataSource(16), m_Accelerometer(accelerometer)
    { }


protected:

    void UpdateMessage () override
    {
        auto accelX = m_Accelerometer.GetAcceleration(0);
        auto accelZ = m_Accelerometer.GetAcceleration(1);
        auto angle = m_Accelerometer.GetClimbAngle(1, 0);
        m_Message[0] = accelX >> 8;
        m_Message[1] = accelX & 0xff;
        m_Message[2] = accelZ >> 8;
        m_Message[3] = accelZ & 0xff;
        m_Message[4] = angle;
    }


protected:

    Accelerometer& m_Accelerometer;


};


int main ()
{
    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB5);

    AnalogInputController analogInputController;

//    // TODO: outsource
//    AnalogInputPin sharpRF(0x01, 4);
//    analogInputController.RegisterAnalogPin(&sharpRF);
//    AnalogInputPin sharpRB(0x02, 4);
//    analogInputController.RegisterAnalogPin(&sharpRB);
//    AnalogInputPin sharpLB(0x03, 4);
//    analogInputController.RegisterAnalogPin(&sharpLB);
//    AnalogInputPin sharpLF(0x00, 4);
//    analogInputController.RegisterAnalogPin(&sharpLF);

    Accelerometer accelerometer(analogInputController);
    accelerometer.RegisterAxis(0x04, 0x00);
    accelerometer.RegisterAxis(0x05, 0xff);

    analogInputController.Enable();

    SensorData sensorData(accelerometer);
    UARTInterruptSlaveConnection uartCentral(0x00, 38400, 0x00, sensorData);

    sei();

    _delay_ms(1000);

    accelerometer.Calibrate();

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        while (uartCentral.DataAvailable())
        {
            if (uartCentral.ReadByte() == '1')
            {
                ledHeartbeat.Flip();
            }
        }
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
