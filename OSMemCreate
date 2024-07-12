OS_MEM *OSMemCreate(void* addr, INT32U nblks, INT32U blksize, INT8U *perr)
{
	OS_MEM *pmem; //定义一个指向OS_MEM结构的指针pmem
	INT8U *pblk; //定义一个指向无符号8位整数的指针pblk
	void **plink; //定义一个指向void指针的指针plink
	INT32U loops; //定义一个32位无符号整数loops
	INT32U i; //定义一个32位无符号整数i

	OS_ENTER_CRITICAL(); //进入临界区，防止中断
	pmem = OSMemFreeList; //将空闲内存控制块链表的头赋给pmem
	OSMemFreeList = (OS_MEM *)OSMemFreeList->OSMemFreeList; //更新空闲内存控制块链表的头
	/*
	假设我们有一个链表，初始状态如下：
	OSMemFreeList --> [OS_MEM] --> [OS_MEM] --> [OS_MEM] --> NULL
	                   (节点A)      (节点B)      (节点C)
	在初始状态下，OSMemFreeList指向节点A。节点A的OSMemFreeList成员指向节点B，依此类推
	在执行这行代码后，OSMemFreeList->OSMemFreeList获取节点A中指向节点B的指针
	OSMemFreeList更新为节点B的指针
	更新后的链表结构：
	OSMemFreeList --> [OS_MEM] --> [OS_MEM] --> NULL
				      (节点B)      (节点C)
	节点A已经从链表中移除，链表的头部现在是节点B
	*/
	OS_EXIT_CRITICAL();//退出临界区

	plink = (void **)addr; //将addr转换为void指针的指针，并赋值给plink
	pblk = (INT8U *)addr; //将addr转换为无符号8位整数的指针，并赋值给pblk
	loops = nblks - 1u; //计算循环次数，nblks减1
	for (i = 0u; i < loops; i++) //循环，将每个块链接到下一个块
	{
		pblk += blksize; //将pblk移动到下一个块的地址
		*plink = (void *)pblk; //将当前块的指针指向下一个块
		plink = (void **)pblk; //将plink更新为下一个块的指针
	}
	*plink = (void *)0; //将最后一个块的指针置为NULL，表示链表的结束
	pmem->OSMemAddr = addr; //设置内存控制块的地址为addr
	pmem->OSMemFreeList = addr; //设置内存控制块的空闲链表为addr
	pmem->OSMemNFree = nblks; //设置内存控制块的空闲块数量为nblks
	pmem->OSMemNBlks = nblks; //设置内存控制块的总数量为nblks
	pmem->OSMemBlkSize = blksize; //设置内存控制块的块大小为blksize
	*perr = OS_ERR_NONE; //将错误代码设置为无错误
	return(pmem); //返回指向新创建的内存控制块的指针
}
