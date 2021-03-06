# 文件IO
## 背景介绍
  文件I/O是操作系统不可或缺的部分，也是实现数据持久化的手段。对于Linux来说，“其一切皆是文件”的思想，更是突出了文件在Linux内核中的重要地位。讲述，Linux文件I/O部分的系统调用。
## 文件、文件描述符和文件表
  Linux内核将一切视为文件，那么Linux的文件时什么呢？其既可以是事实上的真正的物理文件，也可以是设备、管道，甚至还可以是一块内存。狭义文件是指文件系统中的物理文件，而广义的文件则可以是Linux管理的所有对象。这些广义的文件利用VFS机制，以文件系统的形式挂载在Linux内核中，对外提供一致的文件系统操作接口。
  从数值上看，文件描述符就是一个非负整数，其本质就是一个句柄，所以也可以认为文件描述符就是一个文件句柄。那么何为句柄呢？一切对于用户透明的返回值，即可视为句柄。用户空间利用文件描述符与内核进行交互；而内核拿到文件描述符后，可以通过它得到用于管理文件的真正数据结构。
  使用文件描述符即句柄，有两个好处：一是增加了安全性，句柄类型对用户完全透明，用户无法通过hacking的方式更改句柄对应的内部结果，比如Linux内核的文件描述符，只有内核才能通过盖子得到对应的文件结构；二是增加了可扩展性，用户的代码最依赖与句柄的值，这样实际结构的类型就可以随时发生变化，与句柄的映射关系也可以随时改变，这些变化不会影响任何现有的用户代码。
  Linux的每个进程都会维护一个文件表，以便维护该进程打开文件的信息，包括打开的文件个数、每个打开文件的偏移量等信息。
## 内核文件表的实现
  内核中进程对应的结构是task_struct，进程的文件保存在task_struct->files中。其结构：struct files_struct
## read读取文件
  Linux中读取文件操作时，最常用的就是read函数。ssize_t read(int fd, void *buf, size_t count); read尝试从fd中读取count个字节到buf中，并返回成功读取的字节数，同时将文件意向相同的字节数。返回零的时候则表示已经到了“文件尾”。read还有可能读取比count小的字节数。
  使用read进行数据读取时，要注意正确地处理错误，也是说read返回-1时，
