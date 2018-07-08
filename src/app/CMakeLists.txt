add_executable(attpcfe_app
  src/attpcfe_app.cpp)

target_link_libraries(attpcfe_app
  PUBLIC attpcfelib)


add_executable(attpcgui_app
  src/attpcgui_app.cpp)

target_link_libraries(attpcgui_app
  PUBLIC attpcguilib attpcfelib)
