# The following has been generated automatically from src/core/qgsmaplayer.h
QgsMapLayer.Style = QgsMapLayer.PropertyType.Style
QgsMapLayer.Metadata = QgsMapLayer.PropertyType.Metadata
QgsMapLayer.Identifiable = QgsMapLayer.LayerFlag.Identifiable
QgsMapLayer.Removable = QgsMapLayer.LayerFlag.Removable
QgsMapLayer.Searchable = QgsMapLayer.LayerFlag.Searchable
QgsMapLayer.Private = QgsMapLayer.LayerFlag.Private
QgsMapLayer.LayerFlag.baseClass = QgsMapLayer
QgsMapLayer.LayerFlags = lambda flags=0: QgsMapLayer.LayerFlag(flags)
QgsMapLayer.LayerFlags.baseClass = QgsMapLayer
LayerFlags = QgsMapLayer  # dirty hack since SIP seems to introduce the flags in module
QgsMapLayer.LayerConfiguration = QgsMapLayer.StyleCategory.LayerConfiguration
QgsMapLayer.Symbology = QgsMapLayer.StyleCategory.Symbology
QgsMapLayer.Symbology3D = QgsMapLayer.StyleCategory.Symbology3D
QgsMapLayer.Labeling = QgsMapLayer.StyleCategory.Labeling
QgsMapLayer.Fields = QgsMapLayer.StyleCategory.Fields
QgsMapLayer.Forms = QgsMapLayer.StyleCategory.Forms
QgsMapLayer.Actions = QgsMapLayer.StyleCategory.Actions
QgsMapLayer.MapTips = QgsMapLayer.StyleCategory.MapTips
QgsMapLayer.Diagrams = QgsMapLayer.StyleCategory.Diagrams
QgsMapLayer.AttributeTable = QgsMapLayer.StyleCategory.AttributeTable
QgsMapLayer.Rendering = QgsMapLayer.StyleCategory.Rendering
QgsMapLayer.CustomProperties = QgsMapLayer.StyleCategory.CustomProperties
QgsMapLayer.GeometryOptions = QgsMapLayer.StyleCategory.GeometryOptions
QgsMapLayer.Relations = QgsMapLayer.StyleCategory.Relations
QgsMapLayer.Temporal = QgsMapLayer.StyleCategory.Temporal
QgsMapLayer.Legend = QgsMapLayer.StyleCategory.Legend
QgsMapLayer.Elevation = QgsMapLayer.StyleCategory.Elevation
QgsMapLayer.Notes = QgsMapLayer.StyleCategory.Notes
QgsMapLayer.AllVisualStyleCategories = QgsMapLayer.StyleCategory.AllVisualStyleCategories
QgsMapLayer.AllAttributeCategories = QgsMapLayer.StyleCategory.AllAttributeCategories
QgsMapLayer.AllStyleCategories = QgsMapLayer.StyleCategory.AllStyleCategories
QgsMapLayer.StyleCategory.baseClass = QgsMapLayer
QgsMapLayer.StyleCategories = lambda flags=0: QgsMapLayer.StyleCategory(flags)
QgsMapLayer.StyleCategories.baseClass = QgsMapLayer
StyleCategories = QgsMapLayer  # dirty hack since SIP seems to introduce the flags in module
QgsMapLayer.FlagDontResolveLayers = QgsMapLayer.ReadFlag.FlagDontResolveLayers
QgsMapLayer.FlagTrustLayerMetadata = QgsMapLayer.ReadFlag.FlagTrustLayerMetadata
QgsMapLayer.FlagReadExtentFromXml = QgsMapLayer.ReadFlag.FlagReadExtentFromXml
QgsMapLayer.FlagForceReadOnly = QgsMapLayer.ReadFlag.FlagForceReadOnly
QgsMapLayer.ReadFlags = lambda flags=0: QgsMapLayer.ReadFlag(flags)
# monkey patching scoped based enum
QgsMapLayer.SaveStyleResult.Success.__doc__ = "Both QML and SLD formats were successfully written to the database."
QgsMapLayer.SaveStyleResult.QmlGenerationFailed.__doc__ = "Generation of the QML failed, and was not written to the database."
QgsMapLayer.SaveStyleResult.SldGenerationFailed.__doc__ = "Generation of the SLD failed, and was not written to the database."
QgsMapLayer.SaveStyleResult.DatabaseWriteFailed.__doc__ = "An error occurred when attempting to write to the database."
QgsMapLayer.SaveStyleResult.__doc__ = """Results of saving styles to database.

.. versionadded:: 4.0

* ``Success``: Both QML and SLD formats were successfully written to the database.
* ``QmlGenerationFailed``: Generation of the QML failed, and was not written to the database.
* ``SldGenerationFailed``: Generation of the SLD failed, and was not written to the database.
* ``DatabaseWriteFailed``: An error occurred when attempting to write to the database.

"""
# --
QgsMapLayer.SaveStyleResult.baseClass = QgsMapLayer
QgsMapLayer.SaveStyleResults = lambda flags=0: QgsMapLayer.SaveStyleResult(flags)
QgsMapLayer.SaveStyleResults.baseClass = QgsMapLayer
SaveStyleResults = QgsMapLayer  # dirty hack since SIP seems to introduce the flags in module
from enum import Enum


def _force_int(v): return int(v.value) if isinstance(v, Enum) else v


QgsMapLayer.LayerFlag.__bool__ = lambda flag: bool(_force_int(flag))
QgsMapLayer.LayerFlag.__eq__ = lambda flag1, flag2: _force_int(flag1) == _force_int(flag2)
QgsMapLayer.LayerFlag.__and__ = lambda flag1, flag2: _force_int(flag1) & _force_int(flag2)
QgsMapLayer.LayerFlag.__or__ = lambda flag1, flag2: QgsMapLayer.LayerFlag(_force_int(flag1) | _force_int(flag2))
QgsMapLayer.StyleCategory.__bool__ = lambda flag: bool(_force_int(flag))
QgsMapLayer.StyleCategory.__eq__ = lambda flag1, flag2: _force_int(flag1) == _force_int(flag2)
QgsMapLayer.StyleCategory.__and__ = lambda flag1, flag2: _force_int(flag1) & _force_int(flag2)
QgsMapLayer.StyleCategory.__or__ = lambda flag1, flag2: QgsMapLayer.StyleCategory(_force_int(flag1) | _force_int(flag2))
QgsMapLayer.ReadFlag.__bool__ = lambda flag: bool(_force_int(flag))
QgsMapLayer.ReadFlag.__eq__ = lambda flag1, flag2: _force_int(flag1) == _force_int(flag2)
QgsMapLayer.ReadFlag.__and__ = lambda flag1, flag2: _force_int(flag1) & _force_int(flag2)
QgsMapLayer.ReadFlag.__or__ = lambda flag1, flag2: QgsMapLayer.ReadFlag(_force_int(flag1) | _force_int(flag2))
try:
    QgsMapLayer.__attribute_docs__ = {'beforeResolveReferences': 'Emitted when all layers are loaded and references can be resolved, just\nbefore the references of this layer are resolved.\n\n.. versionadded:: 3.10\n', 'statusChanged': 'Emit a signal with status (e.g. to be caught by QgisApp and display a\nmsg on status bar)\n', 'idChanged': "Emitted when the layer's ID has been changed.\n\n.. seealso:: :py:func:`id`\n\n.. seealso:: :py:func:`setId`\n\n.. versionadded:: 3.38\n", 'nameChanged': 'Emitted when the name has been changed\n', 'crsChanged': 'Emitted when the :py:func:`~QgsMapLayer.crs` of the layer has changed.\n\n.. seealso:: :py:func:`crs`\n\n.. seealso:: :py:func:`setCrs`\n\n.. seealso:: :py:func:`verticalCrsChanged`\n\n.. seealso:: :py:func:`crs3DChanged`\n', 'crs3DChanged': 'Emitted when the :py:func:`~QgsMapLayer.crs3D` of the layer has changed.\n\n.. seealso:: :py:func:`crs3D`\n\n.. seealso:: :py:func:`crsChanged`\n\n.. seealso:: :py:func:`verticalCrsChanged`\n\n.. versionadded:: 3.38\n', 'verticalCrsChanged': 'Emitted when the :py:func:`~QgsMapLayer.verticalCrs` of the layer has\nchanged.\n\nThis signal will be emitted whenever the vertical CRS of the layer is\nchanged, either as a direct result of a call to\n:py:func:`~QgsMapLayer.setVerticalCrs` or when\n:py:func:`~QgsMapLayer.setCrs` is called with a compound CRS.\n\n.. seealso:: :py:func:`crsChanged`\n\n.. seealso:: :py:func:`crs3DChanged`\n\n.. seealso:: :py:func:`setCrs`\n\n.. seealso:: :py:func:`setVerticalCrs`\n\n.. seealso:: :py:func:`verticalCrs`\n\n.. versionadded:: 3.38\n', 'repaintRequested': 'By emitting this signal the layer tells that either appearance or\ncontent have been changed and any view showing the rendered layer should\nrefresh itself. If ``deferredUpdate`` is ``True`` then the layer will\nonly be repainted when the canvas is next re-rendered, and will not\ntrigger any canvas redraws itself.\n', 'recalculateExtents': 'This is used to send a request that any mapcanvas using this layer\nupdate its extents\n', 'dataChanged': 'Data of layer changed\n', 'blendModeChanged': 'Signal emitted when the blend mode is changed, through\n:py:func:`QgsMapLayer.setBlendMode()`\n', 'opacityChanged': "Emitted when the layer's opacity is changed, where ``opacity`` is a\nvalue between 0 (transparent) and 1 (opaque).\n\n.. seealso:: :py:func:`setOpacity`\n\n.. seealso:: :py:func:`opacity`\n\n.. note::\n\n   Prior to QGIS 3.18, this signal was available for vector layers only\n\n.. versionadded:: 3.18\n", 'rendererChanged': 'Signal emitted when renderer is changed.\n\n.. seealso:: :py:func:`styleChanged`\n', 'styleChanged': "Signal emitted whenever a change affects the layer's style. Ie this may\nbe triggered by renderer changes, label style changes, or other style\nchanges such as blend mode or layer opacity changes.\n\n.. warning::\n\n   This signal should never be manually emitted. Instead call the :py:func:`~QgsMapLayer.emitStyleChanged` method\n   to ensure that the signal is only emitted when appropriate.\n\n.. seealso:: :py:func:`rendererChanged`\n", 'legendChanged': 'Signal emitted when legend of the layer has changed\n', 'renderer3DChanged': 'Signal emitted when 3D renderer associated with the layer has changed.\n', 'request3DUpdate': 'Signal emitted when a layer requires an update in any 3D maps.\n\n.. versionadded:: 3.18\n', 'configChanged': 'Emitted whenever the configuration is changed. The project listens to\nthis signal to be marked as dirty.\n', 'dependenciesChanged': 'Emitted when dependencies are changed.\n', 'willBeDeleted': 'Emitted in the destructor when the layer is about to be deleted, but it\nis still in a perfectly valid state: the last chance for other pieces of\ncode for some cleanup if they use the layer.\n', 'autoRefreshIntervalChanged': 'Emitted when the auto refresh interval changes.\n\n.. seealso:: :py:func:`setAutoRefreshInterval`\n', 'metadataChanged': "Emitted when the layer's metadata is changed.\n\n.. seealso:: :py:func:`setMetadata`\n\n.. seealso:: :py:func:`metadata`\n", 'flagsChanged': "Emitted when layer's flags have been modified.\n\n.. seealso:: :py:func:`setFlags`\n\n.. seealso:: :py:func:`flags`\n\n.. versionadded:: 3.4\n", 'dataSourceChanged': "Emitted whenever the layer's data source has been changed.\n\n.. seealso:: :py:func:`setDataSource`\n\n.. versionadded:: 3.5\n", 'styleLoaded': 'Emitted when a style has been loaded\n\n:param categories: style categories\n\n.. versionadded:: 3.12\n', 'isValidChanged': 'Emitted when the validity of this layer changed.\n\n.. versionadded:: 3.16\n', 'customPropertyChanged': 'Emitted when a custom property of the layer has been changed or removed.\n\n.. versionadded:: 3.18\n', 'editingStarted': 'Emitted when editing on this layer has started.\n\n.. versionadded:: 3.22\n', 'editingStopped': 'Emitted when edited changes have been successfully written to the data\nprovider.\n\n.. versionadded:: 3.22\n', 'layerModified': 'Emitted when modifications has been done on layer\n\n.. versionadded:: 3.22\n', 'mapTipTemplateChanged': 'Emitted when the map tip template changes\n\n.. versionadded:: 3.30\n', 'mapTipsEnabledChanged': 'Emitted when map tips are enabled or disabled for the layer.\n\n.. seealso:: :py:func:`setMapTipsEnabled`\n\n.. versionadded:: 3.32\n'}
    QgsMapLayer.extensionPropertyType = staticmethod(QgsMapLayer.extensionPropertyType)
    QgsMapLayer.formatLayerName = staticmethod(QgsMapLayer.formatLayerName)
    QgsMapLayer.generateId = staticmethod(QgsMapLayer.generateId)
    QgsMapLayer.providerReadFlags = staticmethod(QgsMapLayer.providerReadFlags)
    QgsMapLayer.__virtual_methods__ = ['properties', 'dataProvider', 'setOpacity', 'opacity', 'reload', 'extent', 'extent3D', 'subLayers', 'setLayerOrder', 'setSubLayerVisibility', 'supportsEditing', 'isEditable', 'isModified', 'isSpatial', 'isTemporary', 'resolveReferences', 'listStylesInDatabase', 'getStyleFromDatabase', 'deleteStyleFromDatabase', 'saveStyleToDatabase', 'loadNamedStyle', 'error', 'metadataUri', 'saveDefaultMetadata', 'loadNamedMetadata', 'loadDefaultMetadata', 'styleURI', 'loadDefaultStyle', 'loadNamedStyleFromDatabase', 'importNamedStyle', 'exportNamedStyle', 'exportSldStyle', 'exportSldStyleV2', 'exportSldStyleV3', 'saveDefaultStyle', 'saveNamedStyle', 'saveSldStyle', 'saveSldStyleV2', 'loadSldStyle', 'readSld', 'readSymbology', 'readStyle', 'writeSymbology', 'writeStyle', 'setMetadata', 'htmlMetadata', 'timestamp', 'dependencies', 'accept', 'selectionProperties', 'temporalProperties', 'elevationProperties', 'profileSource', 'hasMapTips', 'setDependencies', 'setExtent', 'setExtent3D', 'readXml', 'writeXml', 'encodedSource', 'decodedSource']
    QgsMapLayer.__abstract_methods__ = ['clone', 'createMapRenderer', 'readSymbology', 'writeSymbology', 'setTransformContext']
    QgsMapLayer.__signal_arguments__ = {'beforeResolveReferences': ['project: QgsProject'], 'statusChanged': ['status: str'], 'idChanged': ['id: str'], 'repaintRequested': ['deferredUpdate: bool = False'], 'blendModeChanged': ['blendMode: QPainter.CompositionMode'], 'opacityChanged': ['opacity: float'], 'autoRefreshIntervalChanged': ['interval: int'], 'styleLoaded': ['categories: QgsMapLayer.StyleCategories'], 'customPropertyChanged': ['key: str']}
except (NameError, AttributeError):
    pass
