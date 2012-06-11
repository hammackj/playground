SET(FENGINE_SOURCE flog.cpp fengine.cpp flog.h flogtype.h fengine.h fender.h)
add_library(fengine STATIC ${FENGINE_SOURCE})

target_link_libraries(fengine ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
