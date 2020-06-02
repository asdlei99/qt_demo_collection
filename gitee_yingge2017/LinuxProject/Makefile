#编译器
CC=g++
CFLAGS= -std=c++11 -Wl,--no-as-needed -pthread -g -lrt
CFLAGS+=-levent 
INCLUDE+=-I ../bevent-2.0.20-stable/include 
#目标文件
Target=test 
#所有的目录
Dir=./process ./Cpp11 ./Net ./Lab

#存放obj文件的目录
CurFile=$(notdir $(PWD))
ObjPath=../$(CurFile)_Obj
#test -d $(ObjPath) || mkdir -p $(ObjPath)
#$(warning $(ObjPath))
#一次获取目录下所有.c文件
Files=$(foreach dir,$(Dir),$(wildcard $(dir)/*.cpp))
Files+=main.cpp
#$(warning "FILES" $(Files))
#将.c文件替换为.o文件
Objs=$(patsubst %.cpp,%.o,$(Files))
#$(warning "OBJS" $(Objs))


#目标文件声明
all:$(Objs) $(Target)
#$(warning "all")
#根据类型生成依赖.c进而编译生成.o文件，并且存放到OBJPATH目录下
$(Objs):%.o: %.cpp
	test -d $(ObjPath)||mkdir -p $(ObjPath)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $(ObjPath)/$(notdir $@) $<
#$(warning "Objs")
#连接所有的二进制文件生成程序
$(Target):$(ObjPath)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(ObjPath)/*.o
#$(warning "Target")
#如果存放二进制文件的目录不存在，则创建
#$(warning "------" $(ObjPath))
$(ObjPath):
	mkdir -p $(ObjPath)

#清除
clean:
	-rm -f $(ObjPath)/*.o
	-rm -f $(Target)
