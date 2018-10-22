// includes std
#include <vector>

// includes qt
#include <QtCore/qglobal.h>
#include <QVector3D>
#include <QList>
#include <QVariantList>
#include <QQmlListProperty>
#include <QtCore/QObject>


class Render;

class QtRedebleOject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QVariantList Cloude READ Cloude WRITE setCloude NOTIFY CloudeChanged)
  Q_PROPERTY(QString openedFile READ openedFile WRITE setOpenedFile NOTIFY openedFileChanged)
public:
  explicit QtRedebleOject( QObject* parent = nullptr );
  virtual ~QtRedebleOject(){}

  // rename read tabs and create new object cloud;
  void read_tabs( );

  // members get
  // members set
  void setRenderer(Render* renderer);

  // Q properties get
  QVariantList Cloude();
  QString openedFile();

  // Q properties set
  void setCloude(QVariantList const& );
  void setOpenedFile(QString filename);

signals:
  void CloudeChanged();
  void openedFileChanged();

private:
  QList<QString> m_tabs_name;
  QVariantList m_cloude;

  Render* m_renderer;
  QString m_openedFile;
};
