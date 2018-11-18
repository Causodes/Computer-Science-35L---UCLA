Tian Ye
704931660
Assignment 6

To allow the implementation to be more efficient, we multithreaded the code via linking it with lpthread and modifying main.c such that it uses multiple threads. In the original main.c file, the color values of each pixel was calculated individually. This process can be expedited via breaking it into multiple threads.

This was accomplished via creating another function to accomodate pthread. Difficulties were encountered in passing in variables, but they were surmounted via the usage of global variables. Curtailing the overhead was achieved via parallelizing a single loop as opposed to multiple. The single loop was made to be as encompassing as possible such that overhead is minimized. Any additional parallelization would slow down the program as additional overhead was required an overall resulted in a slower runtime.

Viewing the content of make-log.txt below:

rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu11 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm -lpthread
time ./srt 1-test.ppm >1-test.ppm.tmp

real	0m47.733s
user	0m47.726s
sys	0m0.001s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp

real	0m27.283s
user	0m53.608s
sys	0m0.002s
mv 2-test.ppm.tmp 2-test.ppm
time ./srt 4-test.ppm >4-test.ppm.tmp

real	0m12.608s
user	0m49.940s
sys	0m0.006s
mv 4-test.ppm.tmp 4-test.ppm
time ./srt 8-test.ppm >8-test.ppm.tmp

real	0m7.984s
user	0m56.375s
sys	0m0.016s
mv 8-test.ppm.tmp 8-test.ppm
for file in 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm; do \
  diff -u baseline.ppm $file || exit; \
done

We see that each time the number of threads is doubled, the elapsed time is nearly halved. Hence, we can conclude that the SRT implementation is indeed effective.