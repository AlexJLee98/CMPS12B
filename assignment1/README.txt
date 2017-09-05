The program I wrote calculates the prime, perfect, and composite numbers up to one hundred thousand.The program is within a for loop that starts at 2. If the value of the corresponding bit is 1, the program prints the number and P. If the value of the corresponding bit is 0 and the number is odd, it prints the prime factors. If the value of the corresponding bit is 0 and the number is even, it checks and stores the factors in an array. If the factors add up to the number, it prints the factors. Otherwise, it prints the prime factors of the number.

Files: parfait.c, sieve.c, bv.c.

To run the program, just compile it using "make" and typing ./parfait.