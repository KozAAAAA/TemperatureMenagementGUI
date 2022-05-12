#ifndef TEMPERATUREMENAGMENT_H

#define TEMPERATUREMENAGMENT_H

#define TEMP "temp"
#define TIME "time"
#define LOOP "loop"

#include <QObject>
#include <QtDebug>

#include "worker.h"

class MainGui : public QObject
{
    Q_OBJECT
public:
    explicit MainGui(QObject *parent = nullptr);

    //------------------------------INPUT-----------------------------//
public:
    Q_INVOKABLE void setInputParam (const QString& parameter, const quint8& value,const quint8& index);
    Q_INVOKABLE void setInputParam (const QString& parameter, const quint8& value);

    //debug:
    Q_INVOKABLE void printInputParam();

private:
    std::vector<uint16_t> m_tempInputVector;
    std::vector<uint16_t> m_timeInputVector;
    uint8_t m_loopInput;
    //----------------------------------------------------------------//

    //-----------------------------OUTPUT-----------------------------//
public:
    Q_PROPERTY(int tempOutput READ getTempOutput WRITE setTempOutput NOTIFY tempOutputChanged)
    Q_PROPERTY(int timeOutput READ getTimeOutput WRITE setTimeOutput NOTIFY timeOutputChanged)
    Q_PROPERTY(int loopOutput READ getLoopOutput WRITE setLoopOutput NOTIFY loopOutputChanged)
    Q_PROPERTY(int blockOutput READ getBlockOutput WRITE setBlockOutput NOTIFY blockOutputChanged)

    quint16 getTempOutput();
    quint16 getTimeOutput();
    quint8 getLoopOutput();
    quint8 getBlockOutput();

public slots:
    void setTempOutput(const uint16_t& newTemp);
    void setTimeOutput(const uint16_t& newTime);
    void setLoopOutput(const uint8_t& newLoop);
    void setBlockOutput(const uint8_t& newBlock);

private:
    uint16_t m_tempOutput;
    uint16_t m_timeOutput;
    uint8_t m_loopOutput;
    uint8_t m_blockOutput;

signals:
    void tempOutputChanged();
    void timeOutputChanged();
    void loopOutputChanged();
    void blockOutputChanged();
    //----------------------------------------------------------------//

    //----------------------THREAD-COMMUNICATION----------------------//
private:
    Worker* worker;
public:
    Q_INVOKABLE void startTemperatureControl();
    Q_INVOKABLE void endTemperatureControl();
signals:
    void exitThread();
    //----------------------------------------------------------------//
};

#endif // TEMPERATUREMENAGMENT_H
