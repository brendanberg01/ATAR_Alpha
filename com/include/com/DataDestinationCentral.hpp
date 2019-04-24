//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_ALPHA_DATADESTINATIONCENTRAL_HPP
#define ATAR_ALPHA_DATADESTINATIONCENTRAL_HPP

#include "mcu/usart/UARTDataDestination.hpp"

#include "periph/Accelerometer.hpp"
#include "periph/LightEmittingDiode.hpp"
#include "periph/Servo.hpp"


class DataDestinationCentral : public UARTDataDestination
{
public:

    DataDestinationCentral (SingleColorLED& ledHeartbeat, Servo& servo,
                            Accelerometer& accelerometer);

    void DispatchMessage (const char* message, uint8_t len) override;


private:

    SingleColorLED& m_LedHeartbeat;

    Servo& m_Servo;

    Accelerometer& m_Accelerometer;


};


#endif //ATAR_ALPHA_DATADESTINATIONCENTRAL_HPP
