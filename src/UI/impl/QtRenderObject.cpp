#include "QtRenderObject.hpp"

// includes qt
#include <QDir>
#include <QFile>
#include <QString>
#include <QtDebug>
#include <QQuickItem>
#include <QObject>

// includes std
#include <iostream>

#include "../Render.hpp"
#include "utils/logger.h"

CREATE_LOGGER("UI")

QtRedebleOject::QtRedebleOject( QObject* parent )
    : QObject( parent )
{
  LOG_AUTO_TRACE();
}

void
QtRedebleOject::read_tabs( )
{
  LOG_AUTO_TRACE();
  QString list_file;
  m_tabs_name.clear( );
  // TODO: move to file with constants
  QDir dir_data( "/home/vzabila/DIPLOM/PointClasteringTool/DataPoint/" );

  Q_ASSERT_X( dir_data.exists( ), "read_tabs()", "Error read file sysytem" );

  dir_data.setSorting( QDir::Name );
  QFileInfoList list = dir_data.entryInfoList( );

  for ( int i = 2; i < list.size( ); ++i )
  {
      QFileInfo fileInfo = list.at( i );
      m_tabs_name.push_back( fileInfo.fileName( ) );
  }
  qDebug( ) << "Log";
}

void QtRedebleOject::setRenderer(Render *renderer)
{
  LOG_AUTO_TRACE();
  m_renderer = renderer;
}

QVariantList QtRedebleOject::Cloude()
{
  return m_cloude;
}

QString QtRedebleOject::openedFile()
{
  return m_openedFile;
}

void QtRedebleOject::setCloude(const QVariantList& cloude)
{
  LOG_AUTO_TRACE();
  if(cloude.empty())
    return;

   m_cloude = cloude;

   emit CloudeChanged();

}

void QtRedebleOject::setOpenedFile(QString filename)
{
  LOG_AUTO_TRACE();
  m_openedFile = QUrl(filename).path();
  m_renderer->newFileOpened(m_openedFile.toLocal8Bit().constData());
}
