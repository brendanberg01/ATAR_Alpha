//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataDestinationCentral.hpp>


DataDestinationCentral::DataDestinationCentral (SingleColorLED& ledHeartbeat,
                                                Servo& servo,
                                                Accelerometer& accelerometer)
    : m_LedHeartbeat(ledHeartbeat), m_Servo(servo),
    m_Accelerometer(accelerometer)
{
    ledHeartbeat.SetAll(0x00);
    m_Servo.SetPosition(0x7f);
}


void DataDestinationCentral::DispatchMessage (const unsigned char* message,
                                              uint8_t len)
{
    if (len == 1)
    {
        switch (message[0])
        {
            case 0xf0: // START
                m_Accelerometer.Calibrate();
                break;
            case 0xf1: // HEARTBEAT ON
                m_LedHeartbeat.Enable();
                break;
            case 0xf2: // HEARTBEAT OFF
                m_LedHeartbeat.Disable();
                break;
            default:
                break;
        }
    }

    if (len == 2)
    {
        switch (message[0])
        {
            case 0x00: // SERVO
                m_Servo.SetPosition(message[1]);
                break;
            default:
                break;
        }
    }
}
