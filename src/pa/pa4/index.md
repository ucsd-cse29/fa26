# PA4 – Malloc Due Friday 11/20 10:00pm

_This assignment is thanks to the [staff of CSE29 spring 2024](https://cse29sp24.github.io/docs/instructors.html), especially [Gerald Soosairaj](https://geraldsoosairaj.github.io), [Aaron Schulman](https://cseweb.ucsd.edu/~schulman/), and Jerry Yu._

- **Due Friday, November 20th 10:00pm**
- Classroom50: [https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa4/accept](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa4/accept)

In class, quizzes, and PAs we've _used_ `malloc` and `free` to manage memory.
These are functions [written in
C](https://sourceware.org/git/?p=glibc.git;a=blob;f=malloc/malloc.c)! `glibc`
contains one of the [frequently used
implementations](https://sourceware.org/glibc/wiki/MallocInternals).

There are a lot of details that go into these implementations – we don't expect
that anyone could internalize all the details from the documentation above
quickly. However, there are a few key details that are really interesting to
study. In this project, we'll explore how to implement a basic version of
`malloc` and `free` that would be sufficient for many of the programs we have
written.

Specifically, we will practice the following concepts in C:

- bitwise operations,
- pointer arithmetic,
- memory management, and of course,
- using the terminal and vim.

## Getting Started

The starter code for this assignment is hosted on Classroom50:
[https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa4/accept](https://classroom50.org/ucsd-cse29-fall2026/cse29-fa26/assignments/pa4/accept).
Just like on previous PAs, clone the repository to the ieng6 server.

The starter code is deliberately small. It gives you a heap to work in; the design of the allocator itself is up to you.

- `vminit.c` implements `vminit()`, which creates the heap, and `vmdestroy()`, which releases it. In every program, `vminit` is called exactly once, before any call to `vmalloc` or `vmfree`, so there is only ever one heap. Just like production allocators, the heap is one large chunk of memory obtained with `mmap`, and every allocation and free happens inside that region. The autograder uses its own versions of these two functions, so any changes you make to them won't be used.
- `vmlib.h` is the public interface. It declares `vminit`, `vmdestroy`, `vmalloc`, and `vmfree`, and it's what your test programs include.
- `vm.h` is the private header for your allocator's source files. It declares two global variables that `vminit` sets and your allocator can read:
  - `heap_start`: the address of the first byte of the heap.
  - `heap_size`: the heap's size in bytes (`vminit` may round the requested size up).

  `vm.h` also redefines `malloc`, `calloc`, and `realloc` as `NULL` inside your library, to guard against using the standard allocator by accident. Add your own data structures, constants, and helper declarations here.
- `vmalloc.c` and `vmfree.c` are where you implement `vmalloc` and `vmfree`.
- The `Makefile` builds every `.c` file in the root of the repository into your allocator library (`libvm.so`), with `-O2` optimization and `-fno-strict-aliasing` (which keeps the optimizer from miscompiling code that reads the same bytes as different types). It also builds every test program in `tests/` (see [Testing](#testing)). Run `make` from the root of the repository to compile.

## Task Specification

You will implement and test two functions. As with all PAs, you can use all your code from PSet 4 for helper functions and to help you understand the task.

This PA does not prescribe how your allocator works. You choose the allocation policy, the block format (headers, footers, size classes, or something else), the alignment of the addresses you return, and whether and when to combine free blocks. What is required is the behavior described below.

All memory your allocator hands out must come from the heap that the provided `vminit` creates. Don't call `mmap`, `malloc`, or `sbrk` yourself. You can look at `vm.h` for the variables that describe the heap.

You can split your allocator across more `.c` files in the root of the repository: the `Makefile` compiles every one of them. A global variable that more than one file uses is defined in one `.c` file and declared with `extern` in `vm.h`, the same way `heap_start` and `heap_size` are.

### `vmalloc`

```c
void *vmalloc(size_t size);
```

The `size_t size` parameter specifies the number of bytes the caller wants.
This has the same meaning as the usual `malloc` we have been using: the returned
pointer is to the start of `size` bytes of memory that is now exclusively
available to the caller.

Note the `void *` return type, which is the same as the usual `malloc`. `void *`
is not associated with any concrete data type. It is used as a generic pointer,
and can be implicitly assigned to any other type of pointer.

This is how `malloc` (and our `vmalloc`) allow assigning the result to any pointer type:

```c
int *p = malloc(sizeof(int) * 10);
char *c = malloc(sizeof(char) * 64);
```

If `size` is not greater than `0`, or if the allocator could not find a heap
block that is large enough for the allocation, then `vmalloc` should return
`NULL` to indicate no allocation was made.

If `vmalloc(size)` returns `p`, the `size` bytes starting at `p` belong to the caller until `vmfree(p)`. Your allocator must never change those bytes, so its own bookkeeping has to live outside every allocated block. Also, don't assume the heap starts out zeroed: a heap byte can hold any value until your code writes to it.

#### Returning the Address

After updating all the relevant metadata, vmalloc should return a pointer to the start of the payload.

### `vmfree`

```c
void vmfree(void* ptr)
```

The `vmfree` function expects an address obtained by a previous call to `vmalloc`. If the address ptr is `NULL`, then `vmfree` prints `free: invalid pointer` (followed by a newline) to `stderr` and returns without performing any other action. If the block appears to be a free block, then `vmfree` prints `free: double free detected` (followed by a newline) to `stderr` and returns without performing any other action.

For allocated blocks, `vmfree` updates the block metadata to indicate that it is free.

Freed memory must be reusable for a request of the same size: if a block returned by `vmalloc(a)` is freed, a later `vmalloc(a)` must succeed, even if the rest of the heap is full. It does not have to return the same address.

## Design Questions

_Heap fragmentation_ occurs when there are many available blocks that are
small-sized and not adjacent (so they cannot be coalesced).

1. Describe policy choices you've made for allocating/freeing dynamic memory (e.g. header size, placement policy, etc) in your implementation. 

    Given this set up you just described, give an example of a program (in C or pseudocode) that sets up a situation where a 20-byte `vmalloc` call fails to allocate despite the heap having (in total) over 200 bytes free across many blocks. Depending on your choice of policies, this may not result in an issue, if that is the case for your implementation, please explain why it isn't an issue.


2. Write a short C program that uses the built-in `malloc` and `free`
   that triggers an error when run with `valgrind` for attempting to read or
   write in a block of memory that has been malloc'd and then freed. Paste the
   program and the output.

   Then, in the context of this assignment and your `vmalloc` and `vmfree`,
   describe how you would implement a function `uint8_t safe_readwrite(void*
   p)` that takes a pointer and returns whether it is within the payload of a
   live region on the heap.



## Grading

Half of the PA's points come from the Gradescope leaderboard. The rest come from the correctness tests and the design questions.

- **Correctness tests** check only behavior: return values, the `vmfree` error messages, that your allocator never changes data in allocated blocks, and same-size reuse. They don't check your block format, alignment, or allocation policy.
- **The leaderboard** runs your allocator on a set of `vmalloc`/`vmfree` workloads. Its points are split evenly between:
  - **Speed**: how quickly your allocator runs the workloads.
  - **Heap efficiency**: how much of the heap your allocator uses, including its own bookkeeping, compared with the amount of data allocated at once.

The leaderboard runs only when a submission passes every correctness test. You get at most one leaderboard run every 2 hours. Submissions in between still run the correctness tests and keep your most recent leaderboard results. 

## Testing

No tests are provided. You should write your own. A test is a small C program that includes `vmlib.h` and has a `main()` that calls `vminit()` once, makes `vmalloc` and `vmfree` calls, checks the results, and calls `vmdestroy()` at the end. Put each test in the `tests/` directory: `make` builds every `tests/NAME.c` into `tests/bin/NAME`, linked with your allocator.

Test the behavior the autograder checks (see [Grading](#grading)): the return values of `vmalloc`, the `vmfree` error messages, that data you write into allocated blocks is never changed by later `vmalloc`/`vmfree` calls, and that freed memory can be reused.

The autograder can create heaps of any size, with no upper bound, so test your allocator with heaps of many sizes, from small to very large.

To measure speed, write test programs that make many `vmalloc` and `vmfree` calls (lots of small blocks, mixed sizes, blocks that grow) and time them with `time`:

```
$ time ./tests/bin/mytest
```

`user` is the time your program spent running on the CPU. Run each program several times, since the numbers vary from run to run, and build your tests with `make` so you measure the same build the autograder uses.

Do note that your local testing is not reflective of the autograder's runtime. It will likely be very different. Use local timing to compare your own designs against each other, not to predict your leaderboard score.

## Submission

You'll submit your code to Gradescope as usual and submit your Design Question Answers on Gradescope. Refer to the [policies on collaboration](https://ucsd-cse29.github.io/fa26/#policies-and-perspective) if you need to
refresh your memory.

Fill in `CREDITS.txt` with attributions for the sources you used, such as people you discussed the PA with, websites, and AI tools.

**Important:** We will compile your program using the provided `Makefile`, which if you do change will not be used by the grader. 
