#include_directories(C:/OpenCV/opencv/build/include)
#add_executable(name_opencv main.cpp)
#target_link_libraries(name_opencv 
#C:/OpenCV/opencv/build/x64/vc16/lib/opencv_world480d.lib)


#新的方法  不用绝对路径 需要配系统环境变量
find_package(OpenCV REQUIRED)
add_executable(name_opencv main.cpp)
target_include_directories(name_opencv PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(name_opencv ${OpenCV_LIBS})

message("===============${OpenCV_INCLUDE_DIRS}")
message("==============${OpenCV_LIBS}")
