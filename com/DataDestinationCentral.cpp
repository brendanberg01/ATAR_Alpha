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


void DataDestinationCentral::DispatchMessage (const char* message, uint8_t len)
{
    if (len == 2)
    {
        switch (message[0])
        {
            case 0x00:
                m_LedHeartbeat.SetAll(message[1]);
                break;
            case 0x01:
                m_Servo.SetPosition(message[1]);
                break;
            case 0x02:
                if (static_cast<uint8_t>(message[1]) == 0xff)
                {
                    m_Accelerometer.Calibrate();
                }
                break;
        }
    }
}
