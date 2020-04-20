void _start()
{
   const char text[] = "Hello World\n";

   long rv = 0;
   long exit_code = 0;

   // write system call to standard output
   asm volatile ("push %%ebx ; movl %2,%%ebx ; int $0x80 ; pop %%ebx"
      : "=a" (rv) \
      : "0" (4), "ri" ((long)1), "c" ((long)text), "d" ((long)(12))
      : "memory");

   // exit system call -  exit with exit code 0
   rv = 0;
   asm volatile ("push %%ebx ; movl %2,%%ebx ; int $0x80 ; pop %%ebx"
      : "=a" (rv)
      : "0" (1), "ri" (exit_code)
      : "memory");
}