# The following has been generated automatically from src/core/geometry/qgsgeometryengine.h
QgsGeometryEngine.Success = QgsGeometryEngine.EngineOperationResult.Success
QgsGeometryEngine.NothingHappened = QgsGeometryEngine.EngineOperationResult.NothingHappened
QgsGeometryEngine.MethodNotImplemented = QgsGeometryEngine.EngineOperationResult.MethodNotImplemented
QgsGeometryEngine.EngineError = QgsGeometryEngine.EngineOperationResult.EngineError
QgsGeometryEngine.NodedGeometryError = QgsGeometryEngine.EngineOperationResult.NodedGeometryError
QgsGeometryEngine.InvalidBaseGeometry = QgsGeometryEngine.EngineOperationResult.InvalidBaseGeometry
QgsGeometryEngine.InvalidInput = QgsGeometryEngine.EngineOperationResult.InvalidInput
QgsGeometryEngine.SplitCannotSplitPoint = QgsGeometryEngine.EngineOperationResult.SplitCannotSplitPoint
try:
    QgsGeometryEngine.__virtual_methods__ = ['splitGeometry']
    QgsGeometryEngine.__abstract_methods__ = ['geometryChanged', 'prepareGeometry', 'intersection', 'difference', 'combine', 'symDifference', 'buffer', 'simplify', 'interpolate', 'envelope', 'centroid', 'pointOnSurface', 'convexHull', 'distance', 'distanceWithin', 'intersects', 'touches', 'crosses', 'within', 'overlaps', 'contains', 'disjoint', 'relate', 'relatePattern', 'area', 'length', 'isValid', 'isEqual', 'isEmpty', 'isSimple', 'offsetCurve']
    QgsGeometryEngine.__group__ = ['geometry']
except (NameError, AttributeError):
    pass
