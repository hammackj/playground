#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <mach/mach.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int pid;
	kern_return_t kret;
	mach_port_t task;
	thread_act_port_array_t threadList;
	mach_msg_type_number_t threadCount;
	x86_thread_state64_t state;

	pid = atoi(argv[1]);

	kret = task_for_pid(mach_task_self(), pid, &task);

	if (kret != KERN_SUCCESS)
	{
		printf("task_for_pid() failed with message %s!\n", mach_error_string(kret));
	}

	kret = task_threads(task, &threadList, &threadCount);

	if (kret!=KERN_SUCCESS)
	{
		printf("task_threads() failed with message %s!\n", mach_error_string(kret));
		exit(0);
	}

	mach_msg_type_number_t stateCount = x86_THREAD_STATE64_COUNT;
	
	printf("stateCount => %d\n", stateCount);
	

	kret = thread_get_state(threadList[0], x86_THREAD_STATE64, (thread_state_t)&state, &stateCount);

	if (kret!=KERN_SUCCESS)
	{
		printf("thread_get_state() failed with message %s!\n", mach_error_string(kret));
		exit(0);
	}

	printf("Thread %d has %d threads. Thread 0 state: \n", pid, threadCount);
	//printf("EIP: %lx\nEAX: %lx\nEBX: %lx\nECX: %lx\nEDX: %lx\nSS: %lx\n",state.__eip,state.__eax,state.__ebx,state.__ecx,state.__edx,state.__ss);

	printf("RIP 0x%llx\n", state.__rip);
	printf("RBX 0x%llx\n", state.__rbx);
	printf("RCX 0x%llx\n", state.__rcx);
	printf("RDX 0x%llx\n", state.__rdx);
	printf("RDI 0x%llx\n", state.__rdi);
	printf("RSI 0x%llx\n", state.__rsi);
	printf("RBP 0x%llx\n", state.__rbp);
	printf("RSP 0x%llx\n", state.__rsp);

	return 0;
}
