//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataDestinationCentral.hpp>


DataDestinationCentral::DataDestinationCentral (SingleColorLED& ledHeartbeat)
    : m_LedHeartbeat(ledHeartbeat)
{ }


void DataDestinationCentral::DispatchMessage (const char* message, uint8_t len)
{
    if ((len == 1) && (message[0] == '1'))
    {
        m_LedHeartbeat.Flip();
    }
}
