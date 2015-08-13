#ifndef DEVAICEEMULATOR_H
#define DEVAICEEMULATOR_H

#include "ledstate.h"
#include "protocol.h"

#include <QString>
#include <QScopedPointer>

// �������� ������ � �����������
class DeviceEmulator
{
public:
    DeviceEmulator(int _successPercent, double _minRate, double _maxRate);
    // �������� �� �����������
    bool deviceEnabled();

    // ��������� �������
    bool stateOn() const { return m_state.on; }
    ELedColor color() const { return m_state.color; }
    double rate() const { return m_state.rate; }

    // ��������� �������
    void setStateOn(bool _stateOn);
    void setColor(ELedColor _color);
    bool setRate(double _rate);

private:
    // ���������
    LedState m_state;
    // ������� �������� ���������
    int m_successPercent;
    // ����������� �������
    double m_minRate;
    // ������������ �������
    double m_maxRate;
};

#endif // DEVAICEEMULATOR_H
