#ifndef LEDSTATE_H
#define LEDSTATE_H

#include "protocol_global.h"

// Цвет
enum PROTOCOLSHARED_EXPORT ELedColor {
    RedColor,
    GreenColor,
    BlueColor,

    MaxColor
};

// Состояние устройства
struct PROTOCOLSHARED_EXPORT LedState
{
    LedState();

    // Включено
    bool on;
    // Цвет
    ELedColor color;
    // Частота
    double rate;
};



#endif // LEDSTATE_H
