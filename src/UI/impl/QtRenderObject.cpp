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

QtRedebleOject::QtRedebleOject( QObject* parent )
    : QObject( parent )
{
}

void
QtRedebleOject::read_tabs( )
{
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

QVariantList QtRedebleOject::Cloude()
{
  return m_cloude;
}

void QtRedebleOject::setCloude(const QVariantList& cloude)
{
  if(cloude.empty())
    return;

   m_cloude = cloude;

   emit CloudeChanged();

}
