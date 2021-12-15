This demonstrates a bug in Rust with thread local variables.

To reproduce:

1. Run on CentOS 7, or another system with glibc 2.17
2. `cargo build`
3. `gcc test.c -ldl -pthread`
4. `./a.out`
5. Observe segfault

