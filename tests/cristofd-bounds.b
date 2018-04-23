These next two test the array bounds checking. Bounds checking is not
essential, and in a high-level implementation it is likely to introduce
extra overhead. In a low-level implementation you can get bounds checking
for free by using the OS's own memory protections; this is the best
solution, which may require making the array size a multiple of the page
size.
Anyway. These two programs measure the "real" size of the array, in some
sense, in cells left and right of the initial cell respectively. They
output the result in unary; the easiest thing is to direct them to a file
and measure its size, or (on Unix) pipe the output to wc. If bounds
checking is present and working, the left should measure 0 and the right
should be the array size minus one.
+[<+++++++++++++++++++++++++++++++++.]

+[>+++++++++++++++++++++++++++++++++.]
