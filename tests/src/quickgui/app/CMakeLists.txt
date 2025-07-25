set(QGIS_QUICK_APP_MOC_HDRS
)

set(QGIS_QUICK_APP_SRCS
  main.cpp
)

set(QGIS_QUICK_APP_QMLS
  main.qml
)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}

  ${CMAKE_SOURCE_DIR}/src/native
  ${CMAKE_SOURCE_DIR}/src/quickgui

  ${CMAKE_BINARY_DIR}/src/native
  ${CMAKE_BINARY_DIR}/src/quickgui
)

include_directories(SYSTEM
  ${LIBZIP_INCLUDE_DIRS}
  ${SPATIALINDEX_INCLUDE_DIR}
  ${QCA_INCLUDE_DIR}
  ${QTKEYCHAIN_INCLUDE_DIR}
)

qt_wrap_cpp(QGIS_QUICK_APP_MOC_SRCS ${QGIS_QUICK_APP_MOC_HDRS})

set(QGIS_QUICK_APP_RCCS qml.qrc)
set(QGIS_QUICK_APP_NAME qgis_quickapp)
add_executable(${QGIS_QUICK_APP_NAME}
    ${QGIS_QUICK_APP_RCCS}
    ${QGIS_QUICK_APP_QMLS}
    ${QGIS_QUICK_APP_SRCS}
    ${QGIS_QUICK_APP_MOC_SRCS}
)
if (QGISPOSTFIX)
  set_target_properties(qgis_quickapp PROPERTIES RUNTIME_OUTPUT_NAME qgis_quickapp${QGISPOSTFIX})
endif()

target_compile_features(${QGIS_QUICK_APP_NAME} PRIVATE cxx_std_17)

target_link_libraries(${QGIS_QUICK_APP_NAME}
    ${QT_VERSION_BASE}::Gui
    ${QT_VERSION_BASE}::Qml
    ${QT_VERSION_BASE}::Quick
    ${QT_VERSION_BASE}::Xml
    qgis_core
    qgis_quick)
set_target_properties(${QGIS_QUICK_APP_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
target_compile_definitions(${QGIS_QUICK_APP_NAME} PRIVATE "-DQT_NO_FOREACH")
add_dependencies(${QGIS_QUICK_APP_NAME}
    qgis_quick_plugin
    provider_spatialite
    provider_virtuallayer)

install(TARGETS ${QGIS_QUICK_APP_NAME}
  RUNTIME DESTINATION ${QGIS_BIN_DIR}
  LIBRARY DESTINATION ${QGIS_LIB_DIR}
  ARCHIVE DESTINATION ${QGIS_LIB_DIR}
  FRAMEWORK DESTINATION ${QGIS_FW_SUBDIR}
  PUBLIC_HEADER DESTINATION ${QGIS_INCLUDE_DIR})

