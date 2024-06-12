cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

#CONFIGURE
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
set("BIN" ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# FILES
set(APP_SOURCE_FILES 
	qt_qml.cpp
)

set(APP_HEADER_FILES

)

set(QT_DIR_PATH "D:/libraries/Qt/6.7.1/msvc2019_64")

# PROJECT
project (qt_qml LANGUAGES CXX)

# FINDS PACKAGE
find_package(QT NAMES Qt6 CONFIG REQUIRED COMPONENTS Gui Quick Charts Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Gui Quick Charts Core Widgets)

# Добавьте источник в исполняемый файл этого проекта.
qt_add_executable (${PROJECT_NAME} MANUAL_FINALIZATION ${APP_SOURCE_FILES} ${APP_HEADER_FILES})

qt_add_qml_module(${PROJECT_NAME}
	URI Qtqml
	VERSION 1.0
	RESOURCE_PREFIX "/imports"
	QML_FILES  
		main.qml
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
	set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED TRUE)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Quick
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Widgets
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		Qt${QT_VERSION_MAJOR}::Gui
		Qt${QT_VERSION_MAJOR}::Quick
		Qt${QT_VERSION_MAJOR}::Core
		Qt${QT_VERSION_MAJOR}::Widgets
)

# QT WINDEPLOY
message(STATUS "Deploy ${PROJECT_NAME}")
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND Qt${QT_VERSION_MAJOR}::windeployqt
    ARGS 
		$<TARGET_FILE:${PROJECT_NAME}> 
		--qmldir ${CMAKE_SOURCE_DIR}
)

#DIRS FOR QML
#message(STATUS "Make resources dir")
#file(MAKE_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}/Resources")
#message(STATUS "Copy files into resource dir")
#file(COPY "${CMAKE_SOURCE_DIR}/qml/main.qml" DESTINATION "${BIN}/${CMAKE_BUILD_TYPE}/Resources")