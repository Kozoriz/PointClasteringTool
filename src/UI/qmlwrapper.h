#ifndef QMLWRAPPER_H
#define QMLWRAPPER_H

#include <QObject>

class QmlWrapper : public QObject
{
  Q_OBJECT
public:
  explicit QmlWrapper(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QMLWRAPPER_H