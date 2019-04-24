//
// Created by Brendan Berg on 2019-04-23.
//

#include <com/DataSourceSensor.hpp>


DataSourceSensor::DataSourceSensor (Accelerometer& accelerometer,
                                    IRRangeFinder& rangeRF,
                                    IRRangeFinder& rangeRB,
                                    IRRangeFinder& rangeLB,
                                    IRRangeFinder& rangeLF)
    : UARTDataSource(16), m_Accelerometer(accelerometer), m_RangeRF(rangeRF),
    m_RangeRB(rangeRB), m_RangeLB(rangeLB), m_RangeLF(rangeLF)
{ }


void DataSourceSensor::UpdateMessage ()
{
    auto accelX = m_Accelerometer.GetAcceleration(0);
    m_Message[0] = accelX >> 8;
    m_Message[1] = accelX & 0xff;
    auto accelZ = m_Accelerometer.GetAcceleration(1);
    m_Message[2] = accelZ >> 8;
    m_Message[3] = accelZ & 0xff;
    m_Message[4] = m_Accelerometer.GetClimbAngle(1, 0);

    m_Message[5] = m_RangeRF.GetRawDistance();
    m_Message[6] = 0x00;
    m_Message[7] = m_RangeRB.GetRawDistance();
    m_Message[8] = 0x00;
    m_Message[9] = m_RangeLB.GetRawDistance();
    m_Message[10] = 0x00;
    m_Message[11] = m_RangeLF.GetRawDistance();
    m_Message[12] = 0x00;

    m_Message[13] = 0x00;
    m_Message[14] = 0x00;
    m_Message[15] = 0x00;
}
