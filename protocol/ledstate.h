#ifndef LEDSTATE_H
#define LEDSTATE_H

#include "protocol_global.h"

// ����
enum PROTOCOLSHARED_EXPORT ELedColor {
    RedColor,
    GreenColor,
    BlueColor,

    MaxColor
};

// ��������� ����������
struct PROTOCOLSHARED_EXPORT LedState
{
    LedState();

    // ��������
    bool on;
    // ����
    ELedColor color;
    // �������
    double rate;
};



#endif // LEDSTATE_H
