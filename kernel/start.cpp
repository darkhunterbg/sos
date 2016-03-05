
int test();

int start()
{
	//return (int)&test;
	//asm("hlt");
	int a = test();
	return a;
}

int test()
{
	return 3;
}
/*int start()
{
	asm("hlt");
	return 0;
}*/
