	.text
	.global _start

_start:
	sub	$32,%rsp	# create space on stack (don't mess up alignment!)
	leaq	25(%rsp,1),%rbp	# create pointer to our 'string' buffer
	movb	$10,(%rbp)	# drop a CR at the end
	dec	%rbp		# and save initial location for number builder
	mov	$0x04,%rcx	# show 4 lines
mainloop:
	push	%rcx		# save our counter
	rdtscp			# read timestamp counter
	shl	$32,%rdx	# it's returned as TWO 32bit values in RDX:RAX
	or	%rax,%rdx	# full 64 bit of RDTSC

	mov	%r14,%r13	# save prev value
	mov	%rdx,%r14	# save current value
	sub	%r13,%rdx	# find difference
	xchg	%rdx,%rax
	mov	$1,%rcx		# set counter to include trailing CR
	mov	%rbp,%rdi	# argv[0] msg
	mov	$10,%rbx	# divisor (÷10)
divloop:
	xor	%rdx,%rdx	# convert binary value to ascii decimal
	div	%rbx		# not going to explain it
	or	$0x30,%dl
	mov	%dl,(%rdi)
	inc	%rcx
	dec	%rdi
	or	%rax,%rax
	jnz	divloop

	inc	%rdi		# bump to point at new number built
	mov	%rcx,%rdx	# length=rcx
	mov	%rdi,%rsi	# buff=(rdi)
	mov	$1,%rdi		# fd=1
	mov	$1,%rax		# WRITE syscall
	syscall

	pop	%rcx		# restore our counter
	loop	mainloop	# and do it again!

	mov	%rbp,%rsp	# restore stack pointer

	xor	%rdi,%rdi	# exit status = 0
	mov	$60,%rax	# exit syscall
	syscall

