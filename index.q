\d .threads
if["l"<>(*)($).z.o;'`NIX_ONLY];
dll:`$string[.z.o],"/threads"
init:dll 2:(`threads_init;1)
async:dll 2:(`threads_async;2)
init[];
\d .