#define WRITE_SYSCALL_NUM	"4"

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

int main(void)
{
	int error;
	error = write(0, "hello, world!\n", 14);
	return 0;
}
