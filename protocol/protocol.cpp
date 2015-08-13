#include "protocol.h"

#include <QStringBuilder>
#include <QStringList>

ECommand Protocol::str2Request(const QString &str, bool *ok)
{
    *ok = false;
    if(!initStrConvertation(str)) {
        return MaxCommand;
    }
    QString commandStr = str;
    commandStr.chop(1);
    QStringList parts = commandStr.split(QLatin1Char(' '));
    if(parts.size() < 1 || parts.size() > 2) {
        return MaxCommand;
    }
    ECommand command = str2Command(parts[0], ok);
    if(!ok) {
        return MaxCommand;
    }
    if(parts.size() > 1) {
        if(!fillArgument(command, parts[1])) {
            return MaxCommand;
        }
    }
    *ok = true;
    return command;
}

QString Protocol::request2Str(ECommand command)
{
    QString arg;
    switch(command) {
    case SetLedState: {
        arg = stateOn2Str(m_state.on);
        break;
    }
    case SetLedColor: {
        arg = color2Str(m_state.color);
        break;
    }
    case SetLedRate: {
        arg = QString::number(m_state.rate, 'f');
        break;
    }
    default:
        break;
    }
    return request2StrPrivate(command, arg);
}

bool Protocol::str2Response(const QString &str, ECommand command, bool *ok)
{
    *ok = false;
    if(!initStrConvertation(str)) {
        return false;
    }
    QString responseStr = str;
    responseStr.chop(1);
    QStringList parts = responseStr.split(QLatin1Char(' '));
    if(parts.size() < 1 || parts.size() > 2) {
        return false;
    }
    bool response = str2Ok(parts[0], ok);
    if(!ok) {
        return false;
    }
    if(parts.size() > 1) {
        if(!fillArgument(command, parts[1])) {
            return false;
        }
    }
    *ok = true;
    return response;
}

QString Protocol::response2Str(bool response, ECommand command)
{
    QString arg;
    if(response) {
        switch(command) {
        case GetLedState: {
            arg = stateOn2Str(m_state.on);
            break;
        }
        case GetLedColor: {
            arg = color2Str(m_state.color);
            break;
        }
        case GetLedRate: {
            arg = QString::number(m_state.rate, 'f');
            break;
        }
        default:
            break;
        }
    }
    return response2StrPrivate(response, arg);
}

void Protocol::setStateOn(bool _stateOn)
{
    m_state.on = _stateOn;
}

void Protocol::setColor(ELedColor _color)
{
    m_state.color = _color;
}

void Protocol::setRate(double _rate)
{
    m_state.rate = _rate;
}

QString Protocol::request2StrPrivate(ECommand command, const QString &arg)
{
    QString commsndStr = command2Str(command);
    if(!arg.isEmpty()) {
        commsndStr = commsndStr % QLatin1Char(' ') % arg;
    }
    return commsndStr % QLatin1Char('\n');
}

QString Protocol::response2StrPrivate(bool response, const QString &arg)
{
    QString responseStr = ok2Str(response);
    if(!arg.isEmpty()) {
        responseStr = responseStr % QLatin1Char(' ') % arg;
    }
    return responseStr % QLatin1Char('\n');
}

ECommand Protocol::str2Command(const QString &str, bool *ok)
{
    static QHash<QString, ECommand> hash;
    if(hash.isEmpty()) {
        hash[QLatin1String("set-led-state")] = SetLedState;
        hash[QLatin1String("get-led-state")] = GetLedState;
        hash[QLatin1String("set-led-color")] = SetLedColor;
        hash[QLatin1String("get-led-color")] = GetLedColor;
        hash[QLatin1String("set-led-rate")] = SetLedRate;
        hash[QLatin1String("get-led-rate")] = GetLedRate;
    }
    if(!hash.contains(str)) {
        *ok = false;
        return MaxCommand;
    }
    *ok = true;
    return hash[str];
}

QString Protocol::command2Str(ECommand command)
{
    static QHash<ECommand, QString> hash;
    if(hash.isEmpty()) {
        hash[SetLedState] = QLatin1String("set-led-state");
        hash[GetLedState] = QLatin1String("get-led-state");
        hash[SetLedColor] = QLatin1String("set-led-color");
        hash[GetLedColor] = QLatin1String("get-led-color");
        hash[SetLedRate] = QLatin1String("set-led-rate");
        hash[GetLedRate] = QLatin1String("get-led-rate");
        hash[MaxCommand] = QString();
    }
    if(!hash.contains(command)) {
        return QString();
    }
    return hash[command];
}

bool Protocol::str2Ok(const QString &str, bool *ok)
{
    *ok = true;
    if(str.compare(QLatin1String("OK")) == 0) {
        return true;
    }
    if(str.compare(QLatin1String("FAILED")) == 0) {
        return false;
    }
    *ok = false;
    return false;
}

QString Protocol::ok2Str(bool ok)
{
    if(ok) {
        return QLatin1String("OK");
    }
    return QLatin1String("FAILED");
}

bool Protocol::str2StateOn(const QString &str, bool *ok)
{
    *ok = true;
    if(str.compare(QLatin1String("on")) == 0) {
        return true;
    }
    if(str.compare(QLatin1String("off")) == 0) {
        return false;
    }
    *ok = false;
    return false;
}

QString Protocol::stateOn2Str(bool on)
{
    if(on) {
        return QLatin1String("on");
    }
    return QLatin1String("off");
}

ELedColor Protocol::str2Color(const QString &str, bool *ok)
{
    static QHash<QString, ELedColor> hash;
    if(hash.isEmpty()) {
        hash[QLatin1String("red")] = RedColor;
        hash[QLatin1String("green")] = GreenColor;
        hash[QLatin1String("blue")] = BlueColor;
    }
    if(!hash.contains(str)) {
        *ok = false;
        return MaxColor;
    }
    *ok = true;
    return hash[str];
}

QString Protocol::color2Str(ELedColor color)
{
    static QHash<ELedColor, QString> hash;
    if(hash.isEmpty()) {
        hash[RedColor] = QLatin1String("red");
        hash[GreenColor] = QLatin1String("green");
        hash[BlueColor] = QLatin1String("blue");
        hash[MaxColor] = QString();
    }
    if(!hash.contains(color)) {
        return QString();
    }
    return hash[color];
}

bool Protocol::initStrConvertation(const QString &str)
{
    m_state.on = false;
    m_state.color = MaxColor;
    m_state.rate = 0;
    return str.endsWith(QLatin1Char('\n'));
}

bool Protocol::fillArgument(ECommand command, const QString &str)
{
    bool ok = false;
    switch(command) {
    case SetLedState:
    case GetLedState: {
        m_state.on = str2StateOn(str, &ok);
        break;
    }
    case SetLedColor:
    case GetLedColor: {
        m_state.color = str2Color(str, &ok);
        break;
    }
    case SetLedRate:
    case GetLedRate: {
        m_state.rate = str.toDouble(&ok);
        break;
    }
    default:
        break;
    }
    return ok;
}
