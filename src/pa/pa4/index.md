# PA4 – Malloc

_This assignment is thanks to the [staff of CSE29 spring 2024](https://cse29sp24.github.io/docs/instructors.html), especially [Gerald Soosairaj](https://geraldsoosairaj.github.io) and Jerry Yu._

- **Due Thursday, February 26th, 11:59pm**
- GitHub Classroom: [https://classroom.github.com/a/5PI5i7dZ](https://classroom.github.com/a/5PI5i7dZ)

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

## Task Specification

You will implement and test two functions. As with all PAs, you can use all your code from PSet 4 for helper functions and to help you understand the task.

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

Your implementation of `vmalloc` must:

- Use a “best fit” allocation policy
- Always return an address that is a multiple of **16**
- Always allocate space on **16-byte** boundaries
- Ensure that all blocks, either free or allocated, have correct block headers and footers

#### Best Fit Allocation Policy

Many allocation _policies_ are possible – choosing the first block that fits, choosing the last block that fits, choosing the most-recently-freed block that fits, and so on. The one you **must** implement for this PA is the best-fit policy.

That is, once you have determined the size requirement of the desired heap block, you need to traverse the entire heap to find the best-fitting block – the smallest block that is large enough to fit the allocation. If there are multiple candidates of the same size, then you should use the first one you find.

If the best-fitting block you find is larger than what we need, then we need to **split** that block into two. For example, if we are looking for a 16-byte block for vmalloc(4), and the best fitting candidate is a 64-byte block, then we will split it into a 16-byte block and a 48-byte block. The former is allocated and returned to the caller, the latter remains free. Make sure to create a block header for any new blocks, and update block headers of modified blocks.

#### Returning the Address

After updating all the relevant metadata, vmalloc should return a pointer to the start of the payload. Do not return the address of the block header!

### `vmfree`

```c
void vmfree(void* ptr)
```

The `vmfree` function expects a **16-byte** aligned address obtained by a previous call to `vmalloc`. If the address ptr is `NULL`, then vmfree does not perform any action and returns directly. If the block appears to be a free block, then `vmfree` does not perform any action and returns.

For allocated blocks, `vmfree` updates the block metadata to indicate that it is free, and _coalesces_ with adjacent (previous and next) blocks if they are also free.

#### Coalescing freed blocks

Just freeing a block is not necessarily enough, since this may leave us with many small free blocks that can't hold a large allocation. When freeing, we also want to check if the next / previous block in the heap are free, and coalesce with them to make one large free block.

If you are coalescing two blocks, remember to update both the header and the footer!

### Block footers / Previous Bit

You will need to update both your `vmalloc` and your `vmfree` implementation to add code for creating/updating accurate footers, and making sure the "previous block busy" bit is correct.

## Design Questions

_Heap fragmentation_ occurs when there are many available blocks that are
small-sized and not adjacent (so they cannot be coalesced).

1. Give an example of a program (in C or pseudocode) that sets up a situation
   where a 20-byte `vmalloc` call **fails** to allocate despite the heap having (in
   total) over 200 bytes free across many blocks. Assume all the policies and
   layout of the allocator from the PA are used (best fit, alignment, coalescing
   rules, and so on)

2. Write a short C program that uses the built-in `malloc` and `free`
   that triggers an error when run with `valgrind` for attempting to read or
   write in a block of memory that has been malloc'd and then freed. Submit the
   program and the output.

   Then, in the context of this assignment and your `vmalloc` and `vmfree`,
   describe how you would implement a function `uint8_t safe_readwrite(void*
   p)` that takes a pointer and returns whether it is within the payload of a
   live region on the heap.



## Submission

You'll submit your code Gradescope as usual and submit a **PDF** with your Design Question Answers on Gradescope. Refer to the [policies on collaboration](https://ucsd-cse29.github.io/wi26/#policies-and-perspective) if you need to
refresh your memory.

**Important:** We will compile your program using the provided `Makefile`s, which you should
not change.

To get started, read through the next few sections about the PA:

- [Starter Code](./starter-code.md)
- [Testing](./testing.md)
