# The following has been generated automatically from src/core/geometry/qgscircle.h
try:
    QgsCircle.from2Points = staticmethod(QgsCircle.from2Points)
    QgsCircle.from3Points = staticmethod(QgsCircle.from3Points)
    QgsCircle.fromCenterDiameter = staticmethod(QgsCircle.fromCenterDiameter)
    QgsCircle.fromCenterPoint = staticmethod(QgsCircle.fromCenterPoint)
    QgsCircle.from3Tangents = staticmethod(QgsCircle.from3Tangents)
    QgsCircle.from3TangentsMulti = staticmethod(QgsCircle.from3TangentsMulti)
    QgsCircle.fromExtent = staticmethod(QgsCircle.fromExtent)
    QgsCircle.minimalCircleFrom3Points = staticmethod(QgsCircle.minimalCircleFrom3Points)
    QgsCircle.calculateSegments = staticmethod(QgsCircle.calculateSegments)
    QgsCircle.calculateSegmentsStandard = staticmethod(QgsCircle.calculateSegmentsStandard)
    QgsCircle.calculateSegmentsAdaptive = staticmethod(QgsCircle.calculateSegmentsAdaptive)
    QgsCircle.calculateSegmentsByAreaError = staticmethod(QgsCircle.calculateSegmentsByAreaError)
    QgsCircle.calculateSegmentsByConstant = staticmethod(QgsCircle.calculateSegmentsByConstant)
    QgsCircle.__overridden_methods__ = ['area', 'perimeter', 'setSemiMajorAxis', 'setSemiMinorAxis', 'boundingBox', 'toString']
    QgsCircle.__group__ = ['geometry']
except (NameError, AttributeError):
    pass
