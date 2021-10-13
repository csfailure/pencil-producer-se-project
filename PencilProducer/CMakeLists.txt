cmake_minimum_required(VERSION 3.1.0)



# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Multimedia REQUIRED)


# Populate a CMake variable with the forms, headers and sources
set(project_sources
    mainwindow.cpp
    main.cpp
    APM.cpp
    wallet.cpp
    inventory.cpp
    scoreboard.cpp
)

set(project_headers
    mainwindow.h
    APM.h
    wallet.h
    inventory.h
    scoreboard.h
)

set(project_ui
    mainwindow.ui
)


#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
# Tell CMake to create the helloworld executable
add_executable(pencilproducer 
    ${project_sources} 
    ${project_headers}
    ${project_ui} imagesss.qrc)

include_directories(${CURL_INCLUDE_DIR})

# Use the Widgets module from Qt 5
target_link_libraries(pencilproducer Qt5::Widgets Qt5::Multimedia ${CURL_LIBRARIES})


