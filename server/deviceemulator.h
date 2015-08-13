#ifndef DEVAICEEMULATOR_H
#define DEVAICEEMULATOR_H

#include "ledstate.h"
#include "protocol.h"

#include <QString>
#include <QScopedPointer>

// Эмуляция работы с устройством
class DeviceEmulator
{
public:
    DeviceEmulator(int _successPercent, double _minRate, double _maxRate);
    // Проверка на доступность
    bool deviceEnabled();

    // Получение свойств
    bool stateOn() const { return m_state.on; }
    ELedColor color() const { return m_state.color; }
    double rate() const { return m_state.rate; }

    // Установка свойств
    void setStateOn(bool _stateOn);
    void setColor(ELedColor _color);
    bool setRate(double _rate);

private:
    // Состояние
    LedState m_state;
    // Процент успешных обращений
    int m_successPercent;
    // Минимальная частота
    double m_minRate;
    // Максимальная частота
    double m_maxRate;
};

#endif // DEVAICEEMULATOR_H
