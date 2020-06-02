# 项目说明
## QMLPluginOnlyQml  是基于QML文件的扩展方式

- [基于QML文件的扩展方式](https://www.cnblogs.com/senior-engineer/p/5596976.html)

## QMLPluginCplus    用C++ 编写的Qt插件

- [基于C++的插件扩展](https://www.cnblogs.com/senior-engineer/p/5596988.html)

	
## textedit    Qt example 中的文本编辑器  widgets/richtext/textedit/

## tetrix  俄罗斯方块 widgets/tetrix 
	看看官方的项目如何排版

## LazyWidgetPlugin  自己收集和编写的控件, 有如何封装designer插件，如何使用等
	examples  例子集合
	tests     unitest
	lazywidgetplugin  designer插件封装
	lazywidgets  自定义widget集合
	
## LazyQtDemos  自己验证一些Qt功能的演示
- common 是通用功能
	
- examples  例子集合
		backEnd 是最简单的 qml 和 C++ 交互的软件
		echowindow  使用 echoplugin的例子
		ExcelDemo  测试通用功能 common/excel 功能的
		opengl2ddemo  2d画图测试，使用的painter
		
- LazyQt   主程序
	
- views  自定义的视图例子
		model_view  模型视图的例子，主要是参考 《Qt Creator快速入门》
		stardelegate  Qt 官方自定义 delegate 的例子
	
 **大的功能模块**
- plugins 插件， E:\src_works\qt\build_msvc2015\*
		echoplugin 简单的qt插件

## qtquick qtquick学习的项目
	
	callQml    演示了 C++ 如何操作Qml定义的对象
	DynamicList  演示 ListView 中如何设置一个 C++ 写的 model
	FileViewer   几乎是一个从Qml程序， 可以设置窗口icon， 然后如何用Qml组件显示文本，图像，媒体文件
	PaintedItem  如何用 qmlRegisterType 注册一个Qml组件， PaintedItem 继承 QQuickPaintedItem 实现画图功能
	VideoListDemo  两种方式显示视频列表， qml的 ListModel 和 c++ model， 里面涉及到了dialog
	contactlist   官方qml 例子，使用的 control2， Dialog控件不能移动
	
	

