/***************************************************************************
                         qgsalgorithmlinedensity.cpp
                         ---------------------
    begin                : December 2019
    copyright            : (C) 2019 by Clemens Raffler
    email                : clemens dot raffler at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsalgorithmlinedensity.h"
#include "qgscircle.h"
#include "qgsgeometryengine.h"
#include "qgsrasterfilewriter.h"

///@cond PRIVATE

QString QgsLineDensityAlgorithm::name() const
{
  return QStringLiteral( "linedensity" );
}

QString QgsLineDensityAlgorithm::displayName() const
{
  return QObject::tr( "Line density" );
}

QStringList QgsLineDensityAlgorithm::tags() const
{
  return QObject::tr( "density,kernel,line,line density,interpolation,weight" ).split( ',' );
}

QString QgsLineDensityAlgorithm::group() const
{
  return QObject::tr( "Interpolation" );
}

QString QgsLineDensityAlgorithm::groupId() const
{
  return QStringLiteral( "interpolation" );
}

void QgsLineDensityAlgorithm::initAlgorithm( const QVariantMap & )
{
  addParameter( new QgsProcessingParameterFeatureSource( QStringLiteral( "INPUT" ), QObject::tr( "Input line layer" ), QList<int>() << static_cast<int>( Qgis::ProcessingSourceType::VectorLine ) ) );
  addParameter( new QgsProcessingParameterField( QStringLiteral( "WEIGHT" ), QObject::tr( "Weight field " ), QVariant(), QStringLiteral( "INPUT" ), Qgis::ProcessingFieldParameterDataType::Numeric, false, true ) );
  addParameter( new QgsProcessingParameterDistance( QStringLiteral( "RADIUS" ), QObject::tr( "Search radius" ), 10, QStringLiteral( "INPUT" ), false, 0 ) );
  addParameter( new QgsProcessingParameterDistance( QStringLiteral( "PIXEL_SIZE" ), QObject::tr( "Pixel size" ), 10, QStringLiteral( "INPUT" ), false ) );

  // backwards compatibility parameter
  // TODO QGIS 4: remove parameter and related logic
  auto createOptsParam = std::make_unique<QgsProcessingParameterString>( QStringLiteral( "CREATE_OPTIONS" ), QObject::tr( "Creation options" ), QVariant(), false, true );
  createOptsParam->setMetadata( QVariantMap( { { QStringLiteral( "widget_wrapper" ), QVariantMap( { { QStringLiteral( "widget_type" ), QStringLiteral( "rasteroptions" ) } } ) } } ) );
  createOptsParam->setFlags( createOptsParam->flags() | Qgis::ProcessingParameterFlag::Hidden );
  addParameter( createOptsParam.release() );

  auto creationOptsParam = std::make_unique<QgsProcessingParameterString>( QStringLiteral( "CREATION_OPTIONS" ), QObject::tr( "Creation options" ), QVariant(), false, true );
  creationOptsParam->setMetadata( QVariantMap( { { QStringLiteral( "widget_wrapper" ), QVariantMap( { { QStringLiteral( "widget_type" ), QStringLiteral( "rasteroptions" ) } } ) } } ) );
  creationOptsParam->setFlags( creationOptsParam->flags() | Qgis::ProcessingParameterFlag::Advanced );
  addParameter( creationOptsParam.release() );

  addParameter( new QgsProcessingParameterRasterDestination( QStringLiteral( "OUTPUT" ), QObject::tr( "Line density raster" ) ) );
}

QString QgsLineDensityAlgorithm::shortHelpString() const
{
  return QObject::tr( "This algorithm calculates a density measure of linear features "
                      "which is obtained in a circular neighborhood within each raster cell. "
                      "First, the length of the segment of each line that is intersected by the circular neighborhood "
                      "is multiplied with the lines weight factor. In a second step, all length values are summed and "
                      "divided by the area of the circular neighborhood. This process is repeated for all raster cells."
  );
}

Qgis::ProcessingAlgorithmDocumentationFlags QgsLineDensityAlgorithm::documentationFlags() const
{
  return Qgis::ProcessingAlgorithmDocumentationFlag::RespectsEllipsoid;
}

QString QgsLineDensityAlgorithm::shortDescription() const
{
  return QObject::tr( "Calculates a density measure of linear features "
                      "which is obtained in a circular neighborhood within each raster cell." );
}

QgsLineDensityAlgorithm *QgsLineDensityAlgorithm::createInstance() const
{
  return new QgsLineDensityAlgorithm();
}

bool QgsLineDensityAlgorithm::prepareAlgorithm( const QVariantMap &parameters, QgsProcessingContext &context, QgsProcessingFeedback *feedback )
{
  Q_UNUSED( feedback );
  mSource.reset( parameterAsSource( parameters, QStringLiteral( "INPUT" ), context ) );
  if ( !mSource )
    throw QgsProcessingException( invalidSourceError( parameters, QStringLiteral( "INPUT" ) ) );

  mWeightField = parameterAsString( parameters, QStringLiteral( "WEIGHT" ), context );

  mPixelSize = parameterAsDouble( parameters, QStringLiteral( "PIXEL_SIZE" ), context );

  mSearchRadius = parameterAsDouble( parameters, QStringLiteral( "RADIUS" ), context );
  if ( mSearchRadius < 0.5 * mPixelSize * std::sqrt( 2 ) )
    throw QgsProcessingException( QObject::tr( "Raster cells must be fully contained by the search circle. Therefore, "
                                               "the search radius must not be smaller than half of the pixel diagonal." ) );

  mExtent = mSource->sourceExtent();
  mCrs = mSource->sourceCrs();
  mDa = QgsDistanceArea();
  mDa.setEllipsoid( context.ellipsoid() );
  mDa.setSourceCrs( mCrs, context.transformContext() );

  //get cell midpoint from top left cell
  const QgsPoint firstCellMidpoint = QgsPoint( mExtent.xMinimum() + ( mPixelSize / 2 ), mExtent.yMaximum() - ( mPixelSize / 2 ) );
  const QgsCircle searchCircle = QgsCircle( firstCellMidpoint, mSearchRadius );
  mSearchGeometry = QgsGeometry( searchCircle.toPolygon() );

  return true;
}

QVariantMap QgsLineDensityAlgorithm::processAlgorithm( const QVariantMap &parameters, QgsProcessingContext &context, QgsProcessingFeedback *feedback )
{
  mIndex = QgsSpatialIndex( QgsSpatialIndex::FlagStoreFeatureGeometries );

  const QStringList weightName = QStringList( mWeightField );
  const QgsFields attrFields = mSource->fields();

  QgsFeatureRequest r = QgsFeatureRequest();
  r.setSubsetOfAttributes( weightName, attrFields );
  QgsFeatureIterator fit = mSource->getFeatures( r );
  QgsFeature f;

  while ( fit.nextFeature( f ) )
  {
    mIndex.addFeature( f, QgsFeatureSink::FastInsert );

    //only populate hash if weight field is given
    if ( !mWeightField.isEmpty() )
    {
      const double analysisWeight = f.attribute( mWeightField ).toDouble();
      mFeatureWeights.insert( f.id(), analysisWeight );
    }
  }

  QString creationOptions = parameterAsString( parameters, QStringLiteral( "CREATION_OPTIONS" ), context ).trimmed();
  // handle backwards compatibility parameter CREATE_OPTIONS
  const QString optionsString = parameterAsString( parameters, QStringLiteral( "CREATE_OPTIONS" ), context );
  if ( !optionsString.isEmpty() )
    creationOptions = optionsString;

  const QString outputFile = parameterAsOutputLayer( parameters, QStringLiteral( "OUTPUT" ), context );
  const QFileInfo fi( outputFile );
  const QString outputFormat = QgsRasterFileWriter::driverForExtension( fi.suffix() );

  // round up width and height to the nearest integer as GDAL does (e.g. in gdal_rasterize)
  // see https://github.com/qgis/QGIS/issues/43547
  const int rows = static_cast<int>( 0.5 + mExtent.height() / mPixelSize );
  const int cols = static_cast<int>( 0.5 + mExtent.width() / mPixelSize );

  //build new raster extent based on number of columns and cellsize
  //this prevents output cellsize being calculated too small
  const QgsRectangle rasterExtent = QgsRectangle( mExtent.xMinimum(), mExtent.yMaximum() - ( rows * mPixelSize ), mExtent.xMinimum() + ( cols * mPixelSize ), mExtent.yMaximum() );

  QgsRasterFileWriter writer = QgsRasterFileWriter( outputFile );
  writer.setOutputProviderKey( QStringLiteral( "gdal" ) );
  writer.setOutputFormat( outputFormat );
  if ( !creationOptions.isEmpty() )
  {
    writer.setCreationOptions( creationOptions.split( '|' ) );
  }

  std::unique_ptr<QgsRasterDataProvider> provider( writer.createOneBandRaster( Qgis::DataType::Float32, cols, rows, rasterExtent, mCrs ) );
  if ( !provider )
    throw QgsProcessingException( QObject::tr( "Could not create raster output: %1" ).arg( outputFile ) );
  if ( !provider->isValid() )
    throw QgsProcessingException( QObject::tr( "Could not create raster output %1: %2" ).arg( outputFile, provider->error().message( QgsErrorMessage::Text ) ) );

  provider->setNoDataValue( 1, -9999 );

  const qgssize totalCellcnt = static_cast<qgssize>( rows ) * cols;
  int cellcnt = 0;

  auto rasterDataLine = std::make_unique<QgsRasterBlock>( Qgis::DataType::Float32, cols, 1 );

  for ( int row = 0; row < rows; row++ )
  {
    for ( int col = 0; col < cols; col++ )
    {
      if ( feedback->isCanceled() )
      {
        break;
      }

      if ( col > 0 )
        mSearchGeometry.translate( mPixelSize, 0 );

      const QList<QgsFeatureId> fids = mIndex.intersects( mSearchGeometry.boundingBox() );

      if ( !fids.isEmpty() )
      {
        std::unique_ptr<QgsGeometryEngine> engine( QgsGeometry::createGeometryEngine( mSearchGeometry.constGet() ) );
        engine->prepareGeometry();

        double absDensity = 0;
        for ( const QgsFeatureId id : fids )
        {
          const QgsGeometry lineGeom = mIndex.geometry( id );

          if ( engine->intersects( lineGeom.constGet() ) )
          {
            double analysisLineLength = 0;
            try
            {
              analysisLineLength = mDa.measureLength( QgsGeometry( engine->intersection( mIndex.geometry( id ).constGet() ) ) );
            }
            catch ( QgsCsException & )
            {
              throw QgsProcessingException( QObject::tr( "An error occurred while calculating feature length" ) );
            }

            double weight = 1;

            if ( !mWeightField.isEmpty() )
            {
              weight = mFeatureWeights.value( id );
            }

            absDensity += ( analysisLineLength * weight );
          }
        }

        double lineDensity = 0;
        if ( absDensity > 0 )
        {
          //only calculate ellipsoidal area if abs density is greater 0
          double analysisSearchGeometryArea = 0;
          try
          {
            analysisSearchGeometryArea = mDa.measureArea( mSearchGeometry );
          }
          catch ( QgsCsException & )
          {
            throw QgsProcessingException( QObject::tr( "An error occurred while calculating feature area" ) );
          }

          lineDensity = absDensity / analysisSearchGeometryArea;
        }
        rasterDataLine->setValue( 0, col, lineDensity );
      }
      else
      {
        //no lines found in search radius
        rasterDataLine->setValue( 0, col, 0.0 );
      }

      feedback->setProgress( static_cast<double>( cellcnt ) / static_cast<double>( totalCellcnt ) * 100 );
      cellcnt++;
    }
    if ( !provider->writeBlock( rasterDataLine.get(), 1, 0, row ) )
    {
      throw QgsProcessingException( QObject::tr( "Could not write raster block: %1" ).arg( provider->error().summary() ) );
    }

    //'carriage return and newline' for search geometry
    mSearchGeometry.translate( ( cols - 1 ) * -mPixelSize, -mPixelSize );
  }

  QVariantMap outputs;
  outputs.insert( QStringLiteral( "OUTPUT" ), outputFile );
  return outputs;
}


///@endcond
