#define WRITE_SYSCALL_NUM	"4"
#define OPEN_SYSCALL_NUM	"5"

int write(int fd, char *str, int len)
{
	int error;
	asm volatile("xor r1, r1, r1\n\t"
		     "ori r1, r1, "WRITE_SYSCALL_NUM"\n\t"
		     "mv r2, %[fd]\n\t"
		     "mv r3, %[str]\n\t"
		     "mv r4, %[len]\n\t"
		     "scall\n\t"

		     "mv %[error], r1"
		    : [error] "=&r" (error) : [fd] "r" (fd), [str] "r" (str), [len] "r" (len) : "r1", "r2", "r3", "r4");

	return error;
}

int open(const char *str, int mode)
{
	int fd;
	asm volatile("xor r1, r1, r1\n\t"
		     "ori r1, r1, "OPEN_SYSCALL_NUM"\n\t"
		     "mv r2, %[str]\n\t"
		     "mv r3, %[mode]\n\t"
		     "scall\n\t"

		     "mv %[fd], r1"
		    : [fd] "=&r" (fd) : [str] "r" (str), [mode] "r" (mode) : "r1", "r2", "r3");

	return fd;
}

int main(void)
{
	int error, fd_stdin, fd_stdout, fd_stderr;

	fd_stdin = open("/dev/console", 2);
	fd_stdout = open("/dev/console", 2);
	fd_stderr = open("/dev/console", 2);

	error = write(fd_stdout, "hello, world!\n", 14);
	return 0;
}
