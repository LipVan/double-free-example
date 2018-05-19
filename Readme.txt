#attack必须和time在同一个路径下才能攻击成功
#利用的是在time留下的一个简单后门。


#如果重新编译使得plt表free地址发生更改，可以
	objdump -R ./time
#查看更改后free的表项地址

#然后在time.c，将
	chunk2[3] = 0x602018
#修改为对应的地址，再次编译

#或者将
	// printf("free at GOT(use ):");
	// unsigned int free_addr;
	// scanf("%x",&free_addr);

	chunk2[3] = 0x602018;
#的注释取消，修改
	chunk2[3] = free_addr
#然后在执行attack时，手动输入free@plt