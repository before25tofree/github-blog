## exec进程的继承属性
    执行exec的进程，其个性虽然叛逆，与过去做了决裂，但是也继承了过去的一些属性。exec运行后，与进程相关的ID保持不变。如果进程在执行exec之前，设置了告警
    那么告警时间到时，它仍然会产生一个信号。在执行exec之后，挂起信号依然保留。创建文件时，掩码umask和执行exec之前一样。
    通过fork创建的子进程继承的属性和执行exec之后进程保持的属性，两比较，差异不小。对于fork而言：
    - 告警剩余时间：不仅仅是告警剩余时间，还有其他定时器，fork创建的子进程都不继承。
    - 进程挂起信号：子进程会将挂起信号初始化为空
    - 信号量调整semadj：子进程不继承父进程的该值
    - 记录锁：子进程 不继承父进程的记录锁。比较有意思的地方是文件锁flock子进程是继承的
    - 已用时间times：子进程将该值初始化为0
