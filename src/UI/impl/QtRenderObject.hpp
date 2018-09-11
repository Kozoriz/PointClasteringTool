// includes std
#include <vector>

// includes qt
#include <QtCore/qglobal.h>
#include <QVector3D>
#include <QList>
#include <QVariantList>
#include <QQmlListProperty>
#include <QtCore/QObject>

class QtRedebleOject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList Cloude READ Cloude WRITE setCloude NOTIFY CloudeChanged)
public:
    explicit QtRedebleOject( QObject* parent = nullptr );
    virtual ~QtRedebleOject(){}

    // rename read tabs and create new object cloud;
    void read_tabs( );

    QVariantList Cloude();
    void setCloude(QVariantList const& );

signals:
    void CloudeChanged();

private:
    QList<QString> m_tabs_name;
    QVariantList m_cloude;
};
