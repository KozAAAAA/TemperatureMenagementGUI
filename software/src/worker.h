#pragma once

#include "pch.h"
#include "settings.h"

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker(const std::array<quint16,4>&,
                    const std::array<quint16,4>&,
                    const quint8&);
    ~Worker();

    //------------------------------INPUT-----------------------------//
private:
    const std::array<quint16, 4> m_tempInputVector;
    const std::array<quint16, 4> m_timeInputVector;
    const quint8 m_loopInput;

    bool m_threadActive;

public slots:
    void setThreadNotActive();
    //----------------------------------------------------------------//

    //-----------------------------OUTPUT-----------------------------//
private:
    float m_currentTemp;
    quint32 m_currentTime;
    quint8 m_currentLoop;
    quint8 m_currentBlock;

signals:
    void currentTemp(const quint16);
    void currentTime(const quint32);
    void currentLoop(const quint8);
    void currentBlock(const quint8);
    void currentError(const QString);

    void relayIsOn();
    void relayIsOff();
    //----------------------------------------------------------------//

    //-----------------------------METHODS----------------------------//
private:
    QElapsedTimer m_timer;
    bool m_isRelayOn;
    QString m_pwd;
    QString m_scriptPath;
    QString m_txtPath;


    void run() override; //thread
    void hysteresis();

    float getTempSensor();
    void setRelayOn();
    void setRelayOff();

    void outputReset();

    void setFanOn();
    void setFanOff();

    //----------------------------------------------------------------//
};
