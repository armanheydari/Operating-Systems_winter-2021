#include "types.h"
#include "stat.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"
#include "memlayout.h"
#include "param.h"
#include "proc.h"

int main(int argc, char* argv[]) {
	//int temp = atoi(argv[1]);
	//struct proc_info processes[temp];
	//printf(stdout, "%d\n", temp);
	//int *ptr;
	//uint z;
	//int r = fork();
	//if(r == 0) {
	//	z = 120;
	//	ptr = (int*) malloc(z);
	//	int r1 = fork();
	//	if (r1 == 0) {
	//		z = 500;
	//		ptr = (int*) malloc(z);
	//	}
	//	else {
	//		z = 800;
	//		ptr = (int*) malloc(z);
	//	}
	//}
	//else {
	//	z = 100;
	//	ptr = (int*) malloc(z);
	//	proc_dump();
	//}
	//ptr++;
	//exit();
	int process_number = atoi(argv[1]), len, i;
	int pids[process_number];
	struct proc_info *procs = NULL;
	
	for (i = 0; i<process_number; i++) {
		pids[i] = fork();
		if (pids[i] == 0) {
			char *temp = malloc(sizeof(char) * (i+1) * 45000);
			memset(temp, 10, sizeof(char) * (i+1) * 45000);
			while(1);
			exit();
		}
	}
	
	sleep(100);

	procs = malloc(sizeof(struct proc_info) * NPROC);
	proc_dump(procs, &len);
	
	printf(1, "pid\tmemory size\n");
	for(i=0; i<len; i++){
		printf(1, "%d\t%d\n", procs[i].pid, procs[i].memsize);
	}

	for(i=0; i < process_number; i++){
		wait();
		kill(pids[i]);
	}
	free(procs);
	exit();

}
