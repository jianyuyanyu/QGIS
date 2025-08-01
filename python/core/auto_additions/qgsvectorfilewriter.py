# The following has been generated automatically from src/core/qgsvectorfilewriter.h
try:
    QgsVectorFileWriter.MetaData.__attribute_docs__ = {'compulsoryEncoding': 'Some formats require a compulsory encoding, typically UTF-8. If no compulsory encoding, empty string'}
    QgsVectorFileWriter.MetaData.__annotations__ = {'compulsoryEncoding': str}
except (NameError, AttributeError):
    pass
try:
    QgsVectorFileWriter.SaveVectorOptions.__attribute_docs__ = {'driverName': 'OGR driver to use', 'layerName': 'Layer name. If let empty, it will be derived from the filename', 'actionOnExistingFile': 'Action on existing file', 'fileEncoding': 'Encoding to use', 'ct': 'Transform to reproject exported geometries with, or invalid transform\nfor no transformation', 'onlySelectedFeatures': 'Write only selected features of layer', 'datasourceOptions': 'List of OGR data source creation options', 'layerOptions': 'List of OGR layer creation options', 'skipAttributeCreation': 'Only write geometries', 'attributes': 'Attributes to export (empty means all unless skipAttributeCreation is set)', 'attributesExportNames': 'Attributes export names', 'symbologyExport': 'Symbology to export', 'symbologyScale': 'Scale of symbology', 'filterExtent': "If not empty, only features intersecting the extent will be saved.\n\nThe filter extent should be in the destination CRS (if transforming), or the layer's\nCRS if no valid transform is set.", 'overrideGeometryType': 'Set to a valid geometry type to override the default geometry type for the layer. This parameter\nallows for conversion of geometryless tables to null geometries, etc.', 'forceMulti': 'Sets to ``True`` to force creation of multipart geometries', 'includeZ': 'Sets to ``True`` to include z dimension in output. This option is only valid if overrideGeometryType is set', 'fieldValueConverter': 'Field value converter.\n\nOwnership is not transferred and callers must ensure that the lifetime of fieldValueConverter\nexceeds the lifetime of the :py:class:`QgsVectorFileWriter` object.', 'feedback': 'Optional feedback object allowing cancellation of layer save', 'fieldNameSource': 'Source for exported field names.\n\n.. versionadded:: 3.18', 'saveMetadata': 'Set to ``True`` to save layer metadata for the exported vector file.\n\n.. seealso:: :py:func:`layerMetadata`\n\n.. versionadded:: 3.20', 'layerMetadata': 'Layer metadata to save for the exported vector file. This will only be used if saveMetadata is ``True``.\n\n.. seealso:: :py:func:`saveMetadata`\n\n.. versionadded:: 3.20', 'includeConstraints': 'Set to ``True`` to transfer field constraints to the exported vector file.\n\nSupport for field constraints depends on the output file format.\n\n.. versionadded:: 3.34', 'setFieldDomains': 'Set to ``True`` to transfer field domains to the exported vector file.\n\nSupport for field domains depends on the output file format.\n\n.. note::\n\n   Only available in builds based on GDAL 3.5 or later\n\n.. versionadded:: 3.36', 'sourceDatabaseProviderConnection': 'Source database provider connection, for field domains.\n\nOwnership is not transferred and callers must ensure that the lifetime of sourceDatabaseProviderConnection\nexceeds the lifetime of the :py:class:`QgsVectorFileWriter` object.\n\n.. versionadded:: 3.36'}
    QgsVectorFileWriter.SaveVectorOptions.__annotations__ = {'driverName': str, 'layerName': str, 'actionOnExistingFile': 'QgsVectorFileWriter.ActionOnExistingFile', 'fileEncoding': str, 'ct': 'QgsCoordinateTransform', 'onlySelectedFeatures': bool, 'datasourceOptions': 'List[str]', 'layerOptions': 'List[str]', 'skipAttributeCreation': bool, 'attributes': 'QgsAttributeList', 'attributesExportNames': 'List[str]', 'symbologyExport': 'Qgis.FeatureSymbologyExport', 'symbologyScale': float, 'filterExtent': 'QgsRectangle', 'overrideGeometryType': 'Qgis.WkbType', 'forceMulti': bool, 'includeZ': bool, 'fieldValueConverter': 'QgsVectorFileWriter.FieldValueConverter', 'feedback': 'QgsFeedback', 'fieldNameSource': 'QgsVectorFileWriter.FieldNameSource', 'saveMetadata': bool, 'layerMetadata': 'QgsLayerMetadata', 'includeConstraints': bool, 'setFieldDomains': bool, 'sourceDatabaseProviderConnection': 'QgsAbstractDatabaseProviderConnection'}
except (NameError, AttributeError):
    pass
try:
    QgsVectorFileWriter.FilterFormatDetails.__attribute_docs__ = {'driverName': 'Unique driver name', 'filterString': 'Filter string for file picker dialogs', 'globs': 'Matching glob patterns for format, e.g. ``*.shp``.\n\n.. versionadded:: 3.2'}
    QgsVectorFileWriter.FilterFormatDetails.__annotations__ = {'driverName': str, 'filterString': str, 'globs': 'List[str]'}
    QgsVectorFileWriter.FilterFormatDetails.__doc__ = """Details of available filters and formats."""
except (NameError, AttributeError):
    pass
try:
    QgsVectorFileWriter.DriverDetails.__attribute_docs__ = {'longName': 'Descriptive, user friendly name for the driver', 'driverName': 'Unique driver name'}
    QgsVectorFileWriter.DriverDetails.__annotations__ = {'longName': str, 'driverName': str}
    QgsVectorFileWriter.DriverDetails.__doc__ = """Details of available driver formats."""
except (NameError, AttributeError):
    pass
try:
    QgsVectorFileWriter.create = staticmethod(QgsVectorFileWriter.create)
    QgsVectorFileWriter.writeAsVectorFormatV2 = staticmethod(QgsVectorFileWriter.writeAsVectorFormatV2)
    QgsVectorFileWriter.writeAsVectorFormatV3 = staticmethod(QgsVectorFileWriter.writeAsVectorFormatV3)
    QgsVectorFileWriter.supportedFiltersAndFormats = staticmethod(QgsVectorFileWriter.supportedFiltersAndFormats)
    QgsVectorFileWriter.supportedFormatExtensions = staticmethod(QgsVectorFileWriter.supportedFormatExtensions)
    QgsVectorFileWriter.supportsFeatureStyles = staticmethod(QgsVectorFileWriter.supportsFeatureStyles)
    QgsVectorFileWriter.ogrDriverList = staticmethod(QgsVectorFileWriter.ogrDriverList)
    QgsVectorFileWriter.driverForExtension = staticmethod(QgsVectorFileWriter.driverForExtension)
    QgsVectorFileWriter.fileFilterString = staticmethod(QgsVectorFileWriter.fileFilterString)
    QgsVectorFileWriter.filterForDriver = staticmethod(QgsVectorFileWriter.filterForDriver)
    QgsVectorFileWriter.convertCodecNameForEncodingOption = staticmethod(QgsVectorFileWriter.convertCodecNameForEncodingOption)
    QgsVectorFileWriter.deleteShapeFile = staticmethod(QgsVectorFileWriter.deleteShapeFile)
    QgsVectorFileWriter.driverMetadata = staticmethod(QgsVectorFileWriter.driverMetadata)
    QgsVectorFileWriter.defaultDatasetOptions = staticmethod(QgsVectorFileWriter.defaultDatasetOptions)
    QgsVectorFileWriter.defaultLayerOptions = staticmethod(QgsVectorFileWriter.defaultLayerOptions)
    QgsVectorFileWriter.editionCapabilities = staticmethod(QgsVectorFileWriter.editionCapabilities)
    QgsVectorFileWriter.targetLayerExists = staticmethod(QgsVectorFileWriter.targetLayerExists)
    QgsVectorFileWriter.areThereNewFieldsToCreate = staticmethod(QgsVectorFileWriter.areThereNewFieldsToCreate)
    QgsVectorFileWriter.__overridden_methods__ = ['addFeature', 'addFeatures', 'lastError']
except (NameError, AttributeError):
    pass
try:
    QgsVectorFileWriter.FieldValueConverter.__virtual_methods__ = ['fieldDefinition', 'convert', 'clone']
except (NameError, AttributeError):
    pass
