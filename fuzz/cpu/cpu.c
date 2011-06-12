#include <sys/sysctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/machine.h>

int main(int argc, char **argv)
{
		int result = -1;
    int mib[CTL_MAXNAME];
    static size_t miblen = 0;
		cpu_type_t cpu;
    
    miblen = CTL_MAXNAME;
		cpu = 0;

    result = sysctlnametomib("sysctl.proc_cputype", mib, &miblen);

		//printf("miblen => %lu\n", miblen);

		mib[miblen] = atoi(argv[1]);
    size_t len = sizeof(&cpu);

    if (sysctl(mib, miblen + 1, &cpu, &len, NULL, 0) == -1)
        perror("sysctl");

		//printf("size => %lu\n", sizeof(&cpu));

		//printf("cpu => %d\n", cpu);
		
		printf("pid => %d | 0x%x | ", atoi(argv[1]), cpu);
		
		switch(cpu)
		{
			case CPU_TYPE_ARM:
				printf("cpu => arm\n");
			case CPU_TYPE_POWERPC:
				printf("cpu => ppc\n");			
			case CPU_TYPE_POWERPC64:
				printf("cpu => ppc64\n");
			case CPU_TYPE_I386:
				printf("cpu => 32\n");
			case CPU_TYPE_X86_64:
				printf("cpu => 64\n");
			default:					
				return 0;
		}
		
		
    
    exit(0xff);
}
