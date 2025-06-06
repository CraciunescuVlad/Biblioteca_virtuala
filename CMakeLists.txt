#cmake_minimum_required(VERSION 3.20)
#project(Biblioteca_virtuala)
#
#set(CMAKE_CXX_STANDARD 17)
#
## Executabil pentru administrator
#add_executable(administrator_biblioteca
#        administrator/main_administrator.cpp
#        administrator/Carte.cpp
#        administrator/Administrator.cpp
#        fisiere/GestionareFisiere.cpp
#)
#
#target_include_directories(administrator_biblioteca PRIVATE
#        administrator
#        fisiere
#)
#
## Executabil pentru utilizator
#add_executable(utilizator_biblioteca
#        utilizator/main_utilizator.cpp
#        utilizator/Cos.cpp
#        utilizator/Imprumut.cpp
#        utilizator/Data.cpp
#        utilizator/Utilizator.cpp
#        fisiere/GestionareFisiere.cpp
#        administrator/Carte.cpp
#)
#
#target_include_directories(utilizator_biblioteca PRIVATE
#        utilizator
#        fisiere
#)
#

#=========================================================================================

#cmake_minimum_required(VERSION 3.10)
#project(BibliotecaVirtuala)
#
#set(CMAKE_CXX_STANDARD 17)
#
## Include directoarele pentru fișiere header
#include_directories(
#        ${CMAKE_SOURCE_DIR}/administrator
#        ${CMAKE_SOURCE_DIR}/utilizator
#        ${CMAKE_SOURCE_DIR}/fisiere
#)
#
## === Executabil pentru administrator ===
#add_executable(admin_biblioteca
#        main_administrator.cpp
#        administrator/Administrator.cpp
#        administrator/Carte.cpp
#)
#
## === Executabil pentru utilizator ===
#add_executable(utilizator_biblioteca
#        main_utilizator.cpp
#        utilizator/Utilizator.cpp
#        utilizator/Cos.cpp
#        utilizator/Data.cpp
#        utilizator/Imprumut.cpp
#        fisiere/GestionareFisiere.cpp
#        administrator/Carte.cpp  # reutilizezi clasa Carte
#)
#
#
#
#
## Adaugă calea către fișierele ImGui
#include_directories(
#        external/imgui
#        external/imgui/backends
#        external/glfw/include
#)
#
#set(IMGUI_SRC
#        external/imgui/imgui.cpp
#        external/imgui/imgui_draw.cpp
#        external/imgui/imgui_widgets.cpp
#        external/imgui/imgui_tables.cpp
#        external/imgui/backends/imgui_impl_glfw.cpp
#        external/imgui/backends/imgui_impl_opengl3.cpp
#)
#
#add_executable(Biblioteca_virtuala
#        main.cpp
#        ${IMGUI_SRC}
#)
#
#target_link_libraries(Biblioteca_virtuala glfw3 opengl32)
#
#include_directories(${PROJECT_SOURCE_DIR}/external/glfw/include)
#
#link_directories(${PROJECT_SOURCE_DIR}/external/glfw/lib-mingw-w64)
#
#add_executable(Biblioteca_virtuala
#        main.cpp
#        # alte fișiere sursă
#)
#
#target_link_libraries(Biblioteca_virtuala
#        glfw3
#        opengl32
#)


#==============================================================================


cmake_minimum_required(VERSION 3.10)
project(BibliotecaVirtuala)

set(CMAKE_CXX_STANDARD 17)

# Include directoarele interne
include_directories(
        ${CMAKE_SOURCE_DIR}/administrator
        ${CMAKE_SOURCE_DIR}/utilizator
        ${CMAKE_SOURCE_DIR}/fisiere
)

# ================= Executabile originale =================

add_executable(admin_biblioteca
        main_administrator.cpp
        shared/classes/administrator/Administrator.cpp
        shared/classes/administrator/Carte.cpp
)

add_executable(utilizator_biblioteca
        main_utilizator.cpp
        shared/classes/utilizator/Utilizator.cpp
        shared/classes/utilizator/Cos.cpp
        shared/classes/utilizator/Data.cpp
        shared/classes/utilizator/Imprumut.cpp
        shared/classes/gestionareFisiere/GestionareFisiere.cpp
        shared/classes/administrator/Carte.cpp
)

# ================= Interfață grafică =================

# Include ImGui și GLFW
include_directories(
        external/imgui
        external/imgui/backends
        external/glfw/include
)

# Link către biblioteca compilată GLFW
link_directories(${PROJECT_SOURCE_DIR}/external/glfw/lib-mingw-w64)

# Fișierele ImGui
set(IMGUI_SRC
        external/imgui/imgui.cpp
        external/imgui/imgui_draw.cpp
        external/imgui/imgui_widgets.cpp
        external/imgui/imgui_tables.cpp
        external/imgui/backends/imgui_impl_glfw.cpp
        external/imgui/backends/imgui_impl_opengl3.cpp
)

# Executabil pentru interfața grafică
add_executable(Biblioteca_virtuala
        main.cpp
        ${IMGUI_SRC}
        shared/classes/administrator/Administrator.cpp
        shared/classes/administrator/Carte.cpp
        shared/classes/utilizator/Utilizator.cpp
        shared/classes/utilizator/Cos.cpp
        shared/classes/utilizator/Data.cpp
        shared/classes/utilizator/Imprumut.cpp
        shared/classes/gestionareFisiere/GestionareFisiere.cpp
)

target_link_libraries(Biblioteca_virtuala
        glfw3
        opengl32
)
