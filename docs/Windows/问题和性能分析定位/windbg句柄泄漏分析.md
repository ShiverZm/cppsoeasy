# Windbg定位句柄泄漏

对应用程序进行不同的操作，对比两个操作的句柄数，可以初步判定该程序是否存在句柄泄漏。

当通过任务管理器确认程序存在句柄泄漏后，我们就需要定位到具体的代码处，Windbg可以帮助我们完成这个任务。

 首先简单介绍一下!htrace命令，该命令用于显示一个或多个句柄的堆栈回溯信息。在Windbg中输入!htrace ? 查看该命令的参数：
 ```cpp
0:000> !htrace ?
!htrace [handle [max_traces]]
!htrace -enable [max_traces]
!htrace -disable
!htrace -snapshot
!htrace -diff
 ```

handle
指定要显示堆栈回溯的句柄。如果Handle 为0 或者省略，则显示进程中所有句柄 的堆栈回溯
Max_Traces
指定要显示的堆栈回溯的最大层数。用户模式下如果省略该参数，则显示目标进程中的所有堆栈回溯。
-enable
(仅用户模式) 启用句柄跟踪，并且为-diff 选项使用的初始状态产生第一次句柄信息的快照。
-snapshot
(仅用户模式) 抓取当前的句柄信息的快照用作-diff 选项的初始状态。.
-diff
(仅用户模式) 将当前的句柄信息和上一次句柄快照的信息进行对比。显示所有仍然打开的句柄。
-disable
(仅用户模式；仅Windows Server 2003和之后的系统) 禁止句柄跟踪。在Windows XP中，只有结束目标进程才能禁用句柄跟踪。


`下面开始使用Windbg调试`:

1，启动存在句柄泄漏的程序后，先使用Windbg附加到该进程上，设置好符号路径：
File -> Attach to a process 附加进程
File -> Symbol File Path 设置PDB符号文件路径

2，输入!htrace –enable开启句柄栈回溯跟踪，该命令同时默认产生第一次句柄信息的快照，后面也可以再输入!htrace –snapshot产生新的句柄初始快照
```cpp
0:027> !htrace -enable
Handle tracing enabled.
Handle tracing information snapshot successfully taken.
0:027> !htrace -snapshot
Handle tracing information snapshot successfully taken.
```

3，F5让程序继续运行，进行会导致句柄泄漏或增长的操作，然后在Debug菜单下选择Break中断操）， 输入!htrace –diff命令来查看没有删除操作的句柄栈回溯信息，截取其中一个来进行分析：


记录下来的栈回溯都包含了一个头和栈回溯信息，在头中包含了以下信息：

（1）句柄的值，格式为Handle = <value>，比如上面的0x0000000000000678；

（2）紧跟在句柄值后的是执行的操作类型，可以是OPEN或CLOSE，这里的是OPEN，表示这是打开句柄的栈回溯；

（3）线程ID和进程ID的表现形式为T和read ID = <value>和Process iD = <value>，这些值给出了这个栈回溯属于哪个线程和进程。

         句柄我们都知道是相对于进程的，因此进程ID一定是当前运行进程的ID，但是也存在其它进程将句柄注入到当前进程中的情况。



4，通过上述栈回溯，可以发现在实际业务的plugin_msg_post_message函数中，调用了boost::unique_lock，内部又是通过win api CreateEvent实现的，由于流程没走完，所以当前Event的句柄处于打开状态。

      当然也可以通过lsa命令查看具体的代码行号：