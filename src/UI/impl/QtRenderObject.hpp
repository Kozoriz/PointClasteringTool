// includes std
#include <vector>

// includes qt
#include <QtCore/qglobal.h>
#include <QVector3D>
#include <QList>
#include <QVariantList>
#include <QStringList>
#include <QQmlListProperty>
#include <QtCore/QObject>


class Render;

class QtRedebleOject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString openedFile READ openedFile WRITE setOpenedFile NOTIFY openedFileChanged)
  Q_PROPERTY(QString cloudChoosen READ cloudChoosen WRITE setCloudChoosen NOTIFY cloudChoosenChanged)
  Q_PROPERTY(QVariant newPoint READ newPoint WRITE addNewPoint NOTIFY newPointAdded)
  Q_PROPERTY(QString addedCloudName READ addedCloudName WRITE addCloudToList NOTIFY cloudNameAdded)
public:
  explicit QtRedebleOject( QObject* parent = nullptr );
  virtual ~QtRedebleOject(){}

  // rename read tabs and create new object cloud;
//  void read_tabs( );

  // members get
  // members set
  void setRenderer(Render* renderer);

  // Q properties get
  QString openedFile();
  QString cloudChoosen();
  QVariant newPoint();
  QString addedCloudName();

  // Q properties set
  void setOpenedFile(QString filename);
  void setCloudChoosen(QString cloudname);
  void addNewPoint(QVariant point);
  void addCloudToList(QString name);

signals:
  void openedFileChanged();
  void cloudChoosenChanged();
  void newPointAdded();
  void cloudNameAdded();

private:
  Render* m_renderer;

  QString m_openedFile;
  QString m_choosenCloud;
  QVariant m_newPoint;
  QString m_addedCloudName;
};
