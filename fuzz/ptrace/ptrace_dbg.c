#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, const char *argv[])
{
	pid_t pid;
	struct user_regs_struct regs;

	pid = atoi(argv[1]);

	if (ptrace(PT_ATTACH, pid, NULL, NULL))
	{
		perror("Perror");
	}
 
	memset( &regs, 0, sizeof( regs ) );
	ptrace( PTRACE_GETREGS, child, NULL, &regs );
	printf( "RIP before resuming child is %lx\n", regs.rip );

	
	return 0;
}
