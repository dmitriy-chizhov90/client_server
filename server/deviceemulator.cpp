#include "deviceemulator.h"

DeviceEmulator::DeviceEmulator(int _successPercent, double _minRate, double _maxRate)
    : m_successPercent(_successPercent)
    , m_minRate(_minRate)
    , m_maxRate(_maxRate)
{
    m_state.on = qrand() % 2;
    m_state.color = static_cast<ELedColor>(qrand() % MaxColor);
    m_state.rate = qrand() % 6;
}

bool DeviceEmulator::deviceEnabled()
{
    if((qrand() % 100) > m_successPercent) {
        return false;
    }
    return true;
}

void DeviceEmulator::setStateOn(bool _stateOn)
{
    m_state.on = _stateOn;
}

void DeviceEmulator::setColor(ELedColor _color)
{
    m_state.color = _color;
}

bool DeviceEmulator::setRate(double _rate)
{
    if(_rate < m_minRate)
        return false;
    if(_rate > m_maxRate)
        return false;
    m_state.rate = _rate;
    return true;
}
