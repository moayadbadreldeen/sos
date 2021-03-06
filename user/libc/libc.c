#include <fcntl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

_syscall0(pid_t, getpid);
_syscall0(pid_t, getppid);
_syscall0(pid_t, fork);
_syscall3(int, write, int, fd, const void*, buf, size_t, nbyte);
/*_syscall2(int, creat, const char*, filename, mode_t, mode)*/
/*_syscall2(int, fcntl, int, fildes, int, cmd);*/
_syscall1(int, chdir, const char *, path);
_syscall1(int, fchdir, int, fd);

_syscall3(int, open, const char*, path, int, flags, int, mode);
_syscall1(int, close, int, fd);
_syscall3(int, read, int, fildes, void*, buf, size_t, nbyte);
_syscall3(int, exec, const char*, path, char *const*, argv, char *const*, envp);
_syscall1(int, sleep, int, millisecs);
_syscall1(int, exit, int, status);
_syscall1(pid_t, wait, int *, status);
_syscall3(pid_t, waitpid, pid_t, pid, int *, status, int, options);
_syscall3(int, readdir, unsigned int, fd, struct dirent *, dirp, unsigned int, count);
_syscall1(int, dup, int, fd);
_syscall2(int, dup2, int, fd, int, fd2);
_syscall1(int, pipe, int*, fds); // int fd[2]
_syscall0(int, kdump); 
_syscall1(void*, sbrk, int, inc);
_syscall3(off_t, lseek, int, fd, off_t, offset, int, whence);
_syscall2(int, stat, const char *, pathname, struct stat *, buf);
_syscall2(int, fstat, int, fd, struct stat *, buf);
_syscall2(int, lstat, const char *, pathname, struct stat *, buf);
_syscall2(int, kill, pid_t, pid, int, sig);
_syscall2(int, signal, int, signum, unsigned long, handler);
_syscall1(int, sigpending, sigset_t *, set);
_syscall3(int, sigprocmask, int, how, sigset_t*, set, sigset_t*, oldset);
_syscall1(int, sigsuspend, sigset_t*, sigmask);
_syscall2(char*, getcwd, char *, buf, size_t, size);

int execve(const char *path, char *const argv[], char *const envp[])
{
    return exec(path, argv, envp);
}

extern int main(int argc, char* argv[]);

extern void _init();
extern void _fini();
extern void __cxa_finalize(void * d);

void _start(int argc, char* argv[])
{
    _init();
    int ret = main(argc, argv);
    _fini();
    __cxa_finalize(NULL);
    exit(ret);
}

#ifdef __cplusplus
}
#endif

