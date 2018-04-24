// includes std
#include <vector>

// includes qt
#include <QtCore/qglobal.h>
#include <QList>
#include <QQmlListProperty>
#include <QtCore/QObject>

class QtRedebleOject : public QObject
{
    Q_OBJECT
public:
    explicit QtRedebleOject( QObject* parent = nullptr );

    // rename read tabs and create new object cloud;
    void read_tabs( );

private:
    QList< QString > m_tabs_name;
};
