cmake_minimum_required(VERSION 3.9)

project(Energo VERSION 2.0.0 DESCRIPTION "Resources consumption monitoring system.")

#Externals
add_subdirectory(External/GoogleTest)
add_subdirectory(External/fmtlib)

# Core
add_subdirectory(SDK)
add_subdirectory(SDK_Tests)
add_subdirectory(SDK_Gui)
add_subdirectory(Configurator)
add_subdirectory(DataServer)

# Tools
add_subdirectory(Tools/HashGen)
add_subdirectory(Tools/UuidParser)

# Plugins
add_subdirectory(Plugins/TestPlugin)