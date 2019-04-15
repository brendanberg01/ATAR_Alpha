#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/DigitalOutputPin.hpp"
#include "mcu/usart/UARTConnection.hpp"


int main ()
{
    DigitalOutputPin dop(&PORTB, PB5);
    dop.Disable();

    UARTConnection uartCentral(0, 115200);
    int i = 1000;

    sei();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    {
        if (uartCentral.DataAvailable())
        {
            switch (uartCentral.ReadByte())
            {
                case '0':
                    dop.Disable();
                    uartCentral.WriteString("0\n");
                    break;
                case '1':
                    dop.Enable();
                    uartCentral.WriteString("1\n");
                    break;
                case 'e':
                    uartCentral.WriteString("echo\n");
                default:
                    break;
            }
        }

        if (i == 0)
        {
            i = 1000;
            dop.Set(!dop.GetState());
        }
        --i;
        _delay_ms(1);
    }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
