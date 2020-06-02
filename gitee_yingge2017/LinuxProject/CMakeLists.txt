#设置最低版本
cmake_minimum_required(VERSION 2.8)
project(LinuxProject)
#支持c++11
SET(CMAKE_CXX_COMPILER g++)

add_compile_options(-std=c++11)
#set(CMAKE_CXX_FLAGS "-g")

#set (CMAKE_C_FLAG "${CMAKE_C_FLAG} -pthread -rt")
#set (CMAKE_CXX_FLAG "${CMAKE_CXX_FLAG} -pthread -rt")
########################################################
#宏定义
#add_definitions("-DDb")
#add_definitions("-DPractise")
add_definitions("-DLog")
########################################################
#常用变量
message(-----------------------------------)
MESSAGE(STATUS "HOME dir: $ENV{HOME}")
message(STATUS "CMAKE_VERSION:" ${CMAKE_VERSION})
message(STATUS "CMAKE_SYSTEM:" ${CMAKE_SYSTEM})
message(STATUS "CMAKE_SYSTEM_NAME:" ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_SYSTEM_PROCESSOR:" ${CMAKE_SYSTEM_PROCESSOR})

message(STATUS "UNIX?" ${UNIX})
message(STATUS "WIN32?" ${WIN32})

message(STATUS "CMAKE_VERSION:" ${CMAKE_VERSION})
message("CMAKE_CXX_FLAG" ${CMAKE_CXX_FLAG})
message(-----------------------------------)

#ADD_DEFINITIONS(-DENABLE_DEBUG -DABC)，参数之间用空格分割。
#如果你的代码中定义了#ifdef ENABLE_DEBUG #endif，这个代码块就会生效。
#ADD_DEFINITIONS(-DRUN)
#############################################################
#递归查找文件,但当目录下的文件增减时，
#而CMakelists.txt文件没有修改时，cmake不能识别这些文件
#file(GLOB  src_list "src/*" ".")

#set(src_list
#    main.cpp
#    src/addfun.h
#    src/subfun.h
#    src/subfun.cpp)

#向变量中添加文件
#list(APPEND src_list
#    src/addfun.cpp)

#向文件列表中添加文件目录，添加目录中的文件到目录列表中
AUX_SOURCE_DIRECTORY(Cpp11 src_list)
AUX_SOURCE_DIRECTORY(Lab src_list)
AUX_SOURCE_DIRECTORY(Net src_list)
AUX_SOURCE_DIRECTORY(process src_list)
AUX_SOURCE_DIRECTORY(sql src_list)
AUX_SOURCE_DIRECTORY(practise src_list)
aux_source_directory(log src_list)

#头文件的搜索路径,这样添加文件资源的时候可以不用添加头文件了 src/addfun.h、 src/subfun.h
#INCLUDE_DIRECTORIES(src librun)

#######################################################
#编译动态库

#EXCLUDE_FROM_ALL 参数的意思是这个库不会被默认构建，除非有其他的组件依赖或者手工构建。
#ADD_LIBRARY(libname [SHARED|STATIC|MODULE][EXCLUDE_FROM_ALL]source1 source2 ... sourceN)

#ADD_LIBRARY(run SHARED  ${librun_list} )
###############################################################
#库文件存放目录（将库与工程文件放到同一目录，便于工程文件执行时搜索，减少错误产生）
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
###############################################################
#引用动态库
#include_directories(libSrc)
#include_directories("${PROJECT_SOURCE_DIR_DIR}/lib")

#link_directories(${PROJECT_SOURCE_DIR_DIR}/bin)
#link_directories("D:/gitFile/cmake_demo/lib")
#message(STATUS "link_directories:" ${PROJECT_SOURCE_DIR_DIR}/lib)

#引用hpsocket库
#include_directories(HPSocket4C) #头文件
#link_directories(${PROJECT_SOURCE_DIR}/HPSocket4C/x86)

#引用mysq-connect-c++库
include_directories(${PROJECT_SOURCE_DIR}/lib/mysql-cppconn-1.1.12/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/mysql-cppconn-1.1.12/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib/mysql-connector-c/lib)
#查找动库,系统环境变量中的
find_library(Pd pthread)
find_library(Rt rt)
###############################################################
#编译工程文件
#PROJECT_BINARY_DIR表示编译目录
#MESSAGE(STATUS “This is BINARY dir” ${PROJECT_BINARY_DIR})
#PROJECT_SOURCE_DIR 表示源文件所在目录
#MESSAGE(STATUS “This is SOURCES dir” ${PROJECT_SOURCE_DIR})

#第一项参数为可执行文件的名称
ADD_EXECUTABLE(${PROJECT_NAME}  main.cpp ${src_list})
#可执行文件存放目录
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

#可执行程序与库连接
target_link_libraries(${PROJECT_NAME} libmysqlcppconn.so)
target_link_libraries(${PROJECT_NAME} libmysqlclient.so)
target_link_libraries(${PROJECT_NAME} ${Pd})
target_link_libraries(${PROJECT_NAME} ${Rt})

#target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
#连接hpsocket库
#target_link_libraries(${PROJECT_NAME} HPSocket4C_UD)






