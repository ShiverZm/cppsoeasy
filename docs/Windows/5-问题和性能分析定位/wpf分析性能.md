[TOC]

# 前言

wpa下载: 微软商店搜索 windows performance analyzer （preview）版本，微软官网下载的版本可能会有崩溃问题。

# Windows 性能问题分析实例

（1）windows中使用WPR（windows performance record）生成性能数据，WPR记录的是整个系统的运行情况，而不只是我们的业务的

（2）操作功能

（3）在WPR界面上点击start开始记录，实际业务运行一段时间后，点击save保存性能数据

（3）生成的性能数据（etl文件）使用WPA（windows performance analyzer）打开，WPA打开文件后，需要在Trace菜单中配置符号路径，并加载符号

（4）在WPA界面上左侧Computation视图中双击打开CPU Usage (Precise)，然后选择查看Utilization by Process, Thread，找到实际业务的进程

（5）将CPU Usage较高的线程栈一级级展开，就可以分析各个函数的cpu占用情况

WPR界面：