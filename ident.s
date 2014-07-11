	.section ".note.netbsd.ident", "a"
	.align 4

	.long	7
	.long	4
	.long	1
	.ascii	"NetBSD\0\0"	/* ELF_NOTE_NETBSD_NAME */
	.long	699002300

	.section ".note.netbsd.pax", "a"
	.align 4

	.long	4
	.long	4
	.long	3
	.ascii	"PaX\0"		/* ELF_NOTE_PAX_NAME */
	.long	0
