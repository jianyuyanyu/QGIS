/***************************************************************************
  qgstiledsceneproviderguimetadata.h
  --------------------------------------
    begin                : June 2023
    copyright            : (C) 2023 by Nyall Dawson
    email                : nyall dot dawson at gmail dot com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSTILEDSCENEPROVIDERGUIMETADATA_H
#define QGSTILEDSCENEPROVIDERGUIMETADATA_H

///@cond PRIVATE
#define SIP_NO_FILE

#include <QList>
#include <QMainWindow>

#include "qgsproviderguimetadata.h"

class QgsTiledSceneProviderGuiMetadata : public QgsProviderGuiMetadata
{
  public:
    QgsTiledSceneProviderGuiMetadata();

    QList<QgsDataItemGuiProvider *> dataItemGuiProviders() override;
    QList<QgsSourceSelectProvider *> sourceSelectProviders() override;
};

///@endcond

#endif // QGSTILEDSCENEPROVIDERGUIMETADATA_H
