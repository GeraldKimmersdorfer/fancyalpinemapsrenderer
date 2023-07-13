#ifndef TIMERFRONTENDMANAGER_H
#define TIMERFRONTENDMANAGER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QColor>

#include "gl_engine/TimerManager.h"

class TimerFrontendObject : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ get_name)
    Q_PROPERTY(QString group READ get_group)
    Q_PROPERTY(float last_measurement READ get_last_measurement)
    Q_PROPERTY(float average READ get_average)
    Q_PROPERTY(float quick_average READ get_quick_average)
    Q_PROPERTY(QColor color READ get_color)
    Q_PROPERTY(QList<float> measurements MEMBER m_measurements)

public:

    static constexpr const QColor timer_colors[] = {
        QColor(255, 0, 0),      // red
        QColor(0, 255, 255),    // cyan
        QColor(125, 0, 255),    // violet
        QColor(125, 255, 0),    // spring green
        QColor(255, 0, 255),    // magenta
        QColor(0, 125, 255),    // ocean
        QColor(0, 255, 0),      // green
        QColor(255, 125, 0),    // orange
        QColor(0, 0, 255),      // blue
        QColor(0, 255, 125),    // turquoise
        QColor(255, 255, 0),    // yellow
        QColor(255, 0, 125)     // raspberry
    };

    static int timer_color_index;

    void add_measurement(float value);
    float get_last_measurement();
    float get_average();
    float get_quick_average() { return m_quick_average; }


    QString get_name() { return m_name; }
    QString get_group() { return m_group; }
    QColor get_color() { return m_color;    }

    TimerFrontendObject(const QString& name, const QString& group, const int queue_size = 30, const float average_weight = 1.0/30.0f, const float first_value = 0.0 );

    bool operator!=(const TimerFrontendObject& rhs) const
    {
        // ToDo compare for difference
        return true;
    }

private:
    QString m_name;
    QString m_group;
    QList<float> m_measurements;
    QColor m_color;
    float m_new_weight = 1.0/30.0;
    float m_old_weight = 29.0/30.0;
    float m_quick_average = 0.0f;
    int m_queue_size = 30;

};

class TimerFrontendManager : public QObject
{
    Q_OBJECT

public:
//TimerFrontendManager(QObject *parent = nullptr);
    TimerFrontendManager(const TimerFrontendManager& src);
    ~TimerFrontendManager();
    TimerFrontendManager();

    // Copy assignment
    TimerFrontendManager& operator=(const TimerFrontendManager& other);
    bool operator!=(const TimerFrontendManager& other);

public slots:
    void receive_measurements(QList<gl_engine::qTimerReport> values);

signals:
    void updateTimingList(QList<TimerFrontendObject*> data);

private:
    QList<TimerFrontendObject*> m_timer;
    QMap<QString, TimerFrontendObject*> m_timer_map;

};


#endif // TIMERFRONTENDMANAGER_H