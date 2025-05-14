cmake_minimum_required(VERSION 3.16)

project(planewar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt核心模块（自动包含Core和Gui）
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui Multimedia)  # 添加Multimedia模块
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Multimedia)  # 同步添加

set(PROJECT_SOURCES
    main.cpp
    mainscene.cpp
    mainscene.h
    config.h
    map.h map.cpp
    heroplane.h heroplane.cpp
    bullet.h bullet.cpp
    enemyplane.h enemyplane.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(planewar
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(planewar SHARED ${PROJECT_SOURCES})
    else()
        add_executable(planewar ${PROJECT_SOURCES})
    endif()
endif()

# 链接所有需要的Qt模块
target_link_libraries(planewar PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core      # 显式添加Core模块
    Qt${QT_VERSION_MAJOR}::Gui       # 显式添加Gui模块
    Qt${QT_VERSION_MAJOR}::Multimedia # 添加Multimedia模块
)

# 其他配置保持不变...
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.planewar)
endif()

set_target_properties(planewar PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS planewar
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(planewar)
endif()
