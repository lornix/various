/* ******************************************************************
 ** watchpoint.c
 **
 ** Implements a watchpoint on a supplied memory location. This will
 ** let you know when this address gets overwritten.
 **
 ** usage:
 **
 **
 watchpoing PID 0xaddress
 **
 ** LINUX x86 SPECIFIC VERSION. Other Unix systems will be similar
 **
 ** jdblakey@innovative-as.com
 **
 ** ******************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <sys/signal.h>

#ifdef __x86_64__
#define reg_IP_off (RIP * (__WORDSIZE / 8))
#define reg_SP_off (RSP * (__WORDSIZE / 8))
#else
#define reg_IP_off (EIP * (__WORDSIZE / 8))
#define reg_SP_off (ESP * (__WORDSIZE / 8))
#endif

int main (int argc __attribute__((unused)), char *argv[])
{
    int Tpid, stat, res;
    int signo;
    int ip;
    unsigned int memcontents = 0, startcontents = 0, watchaddr = 0;
    /*
     ** This program is started with the PID of the target process and
     ** the watched address
     */
    if ((argv[1] == NULL) || (argv[2] == NULL)) {
        printf("Need pid of traced process\n");
        printf("Usage: pt pid 0xwatchaddress\n");
        exit(1);
    }
    Tpid = strtoul(argv[1], NULL, 10);
    watchaddr = strtoul(argv[2], NULL, 16);
    printf("Tracing pid %d. checking for change to %x \n",Tpid ,watchaddr);
    /*
     ** Attach to the process. This will cause the target process to become
     ** the child of this process. The target will be sent a SIGSTOP. call
     ** wait(2) after this to detect the child state change. We're expecting
     ** the new child state to be STOPPED
     */
    printf("Attaching to process %d\n",Tpid);
    if ((res = ptrace(PTRACE_ATTACH, Tpid, 0, 0)) != 0) {;
        printf("Attach result %d\n",res);
    }
    res = waitpid(Tpid, &stat, WUNTRACED);
    if ((res != Tpid) || !(WIFSTOPPED(stat)) ) {
        printf("Unexpected wait result res %d stat %x\n",res,stat);
        exit(1);
    }
    printf("Wait result stat %x pid %d\n",stat, res);
    stat = 0;
    signo = 0;
    /*
     ** Get the starting value at the requested watch location. The PTRACE_PEEKEXT
     ** option allows you to reach into the tartet process address space, using
     ** its relocation maps, and read/change values. Nice, huh?
     */
    startcontents = ptrace(PTRACE_PEEKTEXT, Tpid, watchaddr, 0);
    printf("Starting value at %x is %x\n",watchaddr, startcontents);
    /*
     ** Loop now, tracing the child
     */
    while (1) {
        /*
         ** Ok, now we will continue the child, but set the single step bit in
         ** the psw. This will cause the child to exeute just one instruction and
         ** trap us again. The wait(2) catches the trap.
         */
        if ((res = ptrace(PTRACE_SINGLESTEP, Tpid, 0, signo)) < 0) {
            perror("Ptrace singlestep error");
            exit(1);
        }
        res = wait(&stat);
        /*
         ** The previous call to wait(2) returned the child's signal number.
         ** If this is a SIGTRAP, then we set it to zero (this does not get
         ** passed on to the child when we PTRACE_CONT or PTRACE_SINGLESTEP
         ** it). If it is the SIGHUP, then PTRACE_CONT the child and we
         ** can exit.
         */
        if ((signo = WSTOPSIG(stat)) == SIGTRAP) {
            signo = 0;
        }
        if ((signo == SIGHUP) || (signo == SIGINT)) {
            ptrace(PTRACE_CONT, Tpid, 0, signo);
            printf("Child took a SIGHUP or SIGINT. We are done\n");
            break;
        }
        /*
         ** get the current value from the watched address and see if it is
         ** different from the starting value. If so, then get the instruction
         ** pointer from the target's user area, 'cause this is the instruction
         ** that changed the value!
         */
        memcontents = ptrace(PTRACE_PEEKTEXT, Tpid, watchaddr, 0);
        if (memcontents != startcontents) {
            ip = ptrace(PTRACE_PEEKUSER, Tpid, reg_IP_off, 0);
            printf("!!!!! Watchpoint address changed !!!!!\n");
            printf("Instruction that changed it at %x\n",ip);
            printf("New contents of address %x\n",memcontents);
            break;
        }
    }
    printf("Debugging complete\n");
    return(0);
}
