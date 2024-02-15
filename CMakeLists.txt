cmake_minimum_required(VERSION 3.5)

project(G7TrucoGame VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES G7TrucoGame_pt_BR.ts)

set(PROJECT_SOURCES
        View/mainview.cpp
        View/mainview.h
        View/mainview.ui
        main.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(G7TrucoGame
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        Model/cardmodel.h Model/cardmodel.cpp
        Model/playermodel.h Model/playermodel.cpp
        Model/gamemodel.h Model/gamemodel.cpp
        Model/tablemodel.h Model/tablemodel.cpp
        Model/deckmodel.h Model/deckmodel.cpp
        Model/gamerulesmodel.h Model/gamerulesmodel.cpp
        View/helpview.h View/helpview.cpp View/helpview.ui
        View/nicknameview.h View/nicknameview.cpp View/nicknameview.ui
        View/gameview.h View/gameview.cpp View/gameview.ui
        View/actionview.h View/actionview.cpp View/actionview.ui
        View/cardview.h View/cardview.cpp View/cardview.ui
        Controller/playtrucocontroller.h Controller/playtrucocontroller.cpp
        Controller/rulescontroller.h Controller/rulescontroller.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET G7TrucoGame APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(G7TrucoGame SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(G7TrucoGame
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(G7TrucoGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.G7TrucoGame)
endif()
set_target_properties(G7TrucoGame PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS G7TrucoGame
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(G7TrucoGame)
endif()
