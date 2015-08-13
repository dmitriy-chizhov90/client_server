#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "protocol_global.h"
#include "ledstate.h"

#include <QHash>
#include <QString>

// Команда
enum PROTOCOLSHARED_EXPORT ECommand {
    SetLedState,
    GetLedState,
    SetLedColor,
    GetLedColor,
    SetLedRate,
    GetLedRate,

    MaxCommand
};

// Протокол передачи данных
class PROTOCOLSHARED_EXPORT Protocol
{
public:
    // Преобразование запроса в формат передачи данных
    ECommand str2Request(const QString &str, bool *ok);
    QString request2Str(ECommand command);
    // Преобразование ответа в формат передачи данных
    bool str2Response(const QString &str, ECommand command, bool *ok);
    QString response2Str(bool response, ECommand command);

    // Получение аргументов
    bool on() const { return m_state.on; }
    ELedColor color() const { return m_state.color; }
    double rate() const { return m_state.rate; }
    // Установка аргументов
    void setStateOn(bool _stateOn);
    void setColor(ELedColor _color);
    void setRate(double _rate);

private:
    // Компановка в строку передачи данных
    static QString request2StrPrivate(ECommand command, const QString &arg);
    static QString response2StrPrivate(bool response, const QString &arg);
    // Преобразование команды
    static ECommand str2Command(const QString &str, bool *ok);
    static QString command2Str(ECommand command);
    // Преобразование информации об успешности выполнения запроса
    static bool str2Ok(const QString &str, bool *ok);
    static QString ok2Str(bool ok);
    // Преобразование состояния
    static bool str2StateOn(const QString &str, bool *ok);
    static QString stateOn2Str(bool on);
    // Преобразование цвета
    static ELedColor str2Color(const QString &str, bool *ok);
    static QString color2Str(ELedColor color);
    // Подготовка к конвертации
    bool initStrConvertation(const QString &str);
    // Преобразование аргумента
    bool fillArgument(ECommand command, const QString &str);

    // Аргументы команд и ответов
    // Состояние устройства
    LedState m_state;
};

#endif // PROTOCOL_H
