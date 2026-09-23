# PA4 – Malloc: Resubmission Due 3/13 at 11:59pm

If you want to resubmit PA4, please read this section carefully. You need to pass all the tests in the original PA4, while also implementing an extra functionality.

## vminfo

In `utils.c`, we have implemented the function vminfo(), which traverses through the heap blocks and prints out the metadata in each block header. Update the function so that at the end of its output, it prints details about the largest available block as follows:

```
The largest free block is #x with size y.
```

where `x` is the blockid starting from 0, and `y` is the size (including header) of the largest available block for allocation. If there are multiple candidates for the largest block, `x` should be the smallest blockid of the candidates. Refer the following updated output of `vminfo` as an example:

```
vminit: heap created at 0x707df3026000 (4096 bytes).
vminit: heap initialization done.
---------------------------------------
 #      stat    offset   size     prev
---------------------------------------
 0      BUSY    8        48       BUSY
 1      FREE    56       32       BUSY
 2      BUSY    88       112      FREE
 3      BUSY    200      96       BUSY
 4      FREE    296      208      BUSY
 5      BUSY    504      64       FREE
 6      BUSY    568      320      BUSY
 7      FREE    888      208      BUSY
 8      BUSY    1096     160      FREE
 9      BUSY    1256     368      BUSY
 10     BUSY    1624     272      BUSY
 11     FREE    1896     672      BUSY
 12     BUSY    2568     128      FREE
 13     BUSY    2696     464      BUSY
 14     FREE    3160     672      BUSY
 15     BUSY    3832     160      FREE
 16     FREE    3992     96       BUSY
 END    N/A     4088     N/A      N/A
---------------------------------------
Total: 4080 bytes, Free: 6, Busy: 11, Total: 17
The largest free block is #11 with size 672
```

Total: 4080 bytes, Free: 6, Busy: 11, Total: 17
The largest free block is #11 with size 672
In this example, there are six `FREE` blocks with the two largest `FREE` blocks being 672 bytes in size: the output line shows the index of the 672 sized block that comes first.

## Updated DESIGN question for the resubmission

If you want to resubmit the design questions, we will be asking this updated design question in a new Gradescope assignment. Please submit a PDF containing your answer to the following question:

In our implementation, when freeing an allocated block, we coalesce it with the previous and next blocks in the heap if they are free - to make one larger free block.

1. Consider an updated implementation where in case of freeing, we only coalesce it with exactly 1 next block in the heap if it is free. That is, we do NOT coalesce backwards. Give an example of a program (in C or pseudocode) where all the allocations succeed in the current design (like in this PA), but some allocations would fail with the updated freeing strategy.

---

In class, quizzes, and PAs we've _used_ `malloc` and `free` to manage memory. These are functions [written in C](https://sourceware.org/git/?p=glibc.git;a=blob;f=malloc/malloc.c)! `glibc` contains one of the [frequently used implementations](https://sourceware.org/glibc/wiki/MallocInternals).

There are a lot of details that go into these implementations – we don't expect that anyone could internalize all the details from the documentation above quickly. However, there are a few key details that are really interesting to study. In this project, we'll explore how to implement a basic version of `malloc` and `free` that would be sufficient for many of the programs we have written.

Specifically, we will practice the following concepts in C:

- bitwise operations,
- pointer arithmetic,
- memory management, and of course,
- using the terminal and vim.
