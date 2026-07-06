cmake_minimum_required(VERSION 3.19)
project(Gladiators LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILES # файлы для компиляции
    main.cpp
    src/MainWindow.cpp
)

set(HEADER_FILES # header'ы для MOC (header'ы, где используется макрос Q_OBJECT)
    headers/MainWindow.hpp
)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets) # Поиск QT и его компонентов

qt_standard_project_setup()

qt_wrap_cpp(MOC_FILES ${HEADER_FILES})

qt_add_executable(${PROJECT_NAME}
    ${SRC_FILES}
    ${MOC_FILES}
    # res/icon.rc # Иконка приложения
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

include(GNUInstallDirs)
include_directories(headers)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)