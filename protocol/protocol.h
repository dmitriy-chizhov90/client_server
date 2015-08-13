#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "protocol_global.h"
#include "ledstate.h"

#include <QHash>
#include <QString>

// �������
enum PROTOCOLSHARED_EXPORT ECommand {
    SetLedState,
    GetLedState,
    SetLedColor,
    GetLedColor,
    SetLedRate,
    GetLedRate,

    MaxCommand
};

// �������� �������� ������
class PROTOCOLSHARED_EXPORT Protocol
{
public:
    // �������������� ������� � ������ �������� ������
    ECommand str2Request(const QString &str, bool *ok);
    QString request2Str(ECommand command);
    // �������������� ������ � ������ �������� ������
    bool str2Response(const QString &str, ECommand command, bool *ok);
    QString response2Str(bool response, ECommand command);

    // ��������� ����������
    bool on() const { return m_state.on; }
    ELedColor color() const { return m_state.color; }
    double rate() const { return m_state.rate; }
    // ��������� ����������
    void setStateOn(bool _stateOn);
    void setColor(ELedColor _color);
    void setRate(double _rate);

private:
    // ���������� � ������ �������� ������
    static QString request2StrPrivate(ECommand command, const QString &arg);
    static QString response2StrPrivate(bool response, const QString &arg);
    // �������������� �������
    static ECommand str2Command(const QString &str, bool *ok);
    static QString command2Str(ECommand command);
    // �������������� ���������� �� ���������� ���������� �������
    static bool str2Ok(const QString &str, bool *ok);
    static QString ok2Str(bool ok);
    // �������������� ���������
    static bool str2StateOn(const QString &str, bool *ok);
    static QString stateOn2Str(bool on);
    // �������������� �����
    static ELedColor str2Color(const QString &str, bool *ok);
    static QString color2Str(ELedColor color);
    // ���������� � �����������
    bool initStrConvertation(const QString &str);
    // �������������� ���������
    bool fillArgument(ECommand command, const QString &str);

    // ��������� ������ � �������
    // ��������� ����������
    LedState m_state;
};

#endif // PROTOCOL_H
