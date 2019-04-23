//
// Created by Brendan Berg on 2019-04-23.
//

#ifndef ATAR_ALPHA_DATASOURCESENSOR_HPP
#define ATAR_ALPHA_DATASOURCESENSOR_HPP

#include "mcu/usart/UARTDataSource.hpp"

#include "periph/Accelerometer.hpp"
#include "periph/IRRangeFinder.hpp"


class DataSourceSensor : public UARTDataSource
{
public:

    DataSourceSensor (Accelerometer& accelerometer,
                      IRRangeFinder& rangeRF, IRRangeFinder& rangeRB,
                      IRRangeFinder& rangeLB, IRRangeFinder& rangeLF);


protected:

    void UpdateMessage () override;


private:

    Accelerometer& m_Accelerometer;

    IRRangeFinder& m_RangeRF;

    IRRangeFinder& m_RangeRB;

    IRRangeFinder& m_RangeLB;

    IRRangeFinder& m_RangeLF;


};


#endif //ATAR_ALPHA_DATASOURCESENSOR_HPP
