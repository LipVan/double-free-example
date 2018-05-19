#include <unistd.h>

int main(int argc, char const *argv[])
{
	char *arg[] = {"./time","123",NULL};

	execve("./time",arg,NULL);

	return 0;
}