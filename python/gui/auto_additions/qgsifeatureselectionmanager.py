# The following has been generated automatically from src/gui/attributetable/qgsifeatureselectionmanager.h
try:
    QgsIFeatureSelectionManager.__attribute_docs__ = {'selectionChanged': 'Emitted when selection was changed.\n\n:param selected: Newly selected feature ids\n:param deselected: Ids of all features which have previously been\n                   selected but are not any more\n:param clearAndSelect: In case this is set to ``True``, the old\n                       selection was dismissed and the new selection\n                       corresponds to selected\n'}
    QgsIFeatureSelectionManager.__abstract_methods__ = ['selectedFeatureCount', 'select', 'deselect', 'setSelectedFeatures']
    QgsIFeatureSelectionManager.__signal_arguments__ = {'selectionChanged': ['selected: QgsFeatureIds', 'deselected: QgsFeatureIds', 'clearAndSelect: bool']}
    QgsIFeatureSelectionManager.__group__ = ['attributetable']
except (NameError, AttributeError):
    pass
