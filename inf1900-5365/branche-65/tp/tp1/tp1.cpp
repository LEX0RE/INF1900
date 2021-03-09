#include <avr/io.h> 
#include <util/delay_basic.h>

int main()
{
    DDRA = 0xff;
    uint8_t compteur = 0;

    for(;;)
    {
        compteur++;
        if (compteur==0) 
        {
            PORTA=00000001;
            void _delay_loop_1(uint8_t __count);
            void _delay_loop_1(uint8_t __count);
        }
        else if (compteur==1)
        {
            PORTA=00000010;
            void _delay_loop_1(uint8_t __count);
            void _delay_loop_1(uint8_t __count);
        }
        else
        {
            PORTA=00000000;
            void _delay_loop_1(uint8_t __count);
        }
    }
    return 0;
}