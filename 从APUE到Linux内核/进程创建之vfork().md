## vfork()
    所需头文件：

    #include <sys/types.h>

    #include <unistd.h>



pid_t vfork(void);

功能：

    vfork() 函数和 fork() 函数（fork()如何使用，请点此链接）一样都是在已有的进程中创建一个新的进程，但它们创建的子进程是有区别的。

参数：

    无

返回值：

    成功：子进程中返回 0，父进程中返回子进程 ID。pid_t，为无符号整型。

    失败：返回 -1。




fork() 与 vfock() 都是创建一个进程，那它们有什么区别呢？

    1）fork()： 父子进程的执行次序不确定。

       vfork()：保证子进程先运行,在它调用 exec（进程替换） 或 exit（退出进程）之后父进程才可能被调度运行。

    2）fork()： 子进程拷贝父进程的地址空间，子进程是父进程的一个复制品。

       vfork()：子进程共享父进程的地址空间（准确来说，在调用 exec（进程替换） 或 exit（退出进程） 之前与父进程数据是共享的）
![image](https://github.com/before25tofree/Images/raw/master/vfork.png)
