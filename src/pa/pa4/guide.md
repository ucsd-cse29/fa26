# Implementation Guide

As with all previous PAs, refer back to PSet4 to create helper functions for this PA. Here are more implementation details to keep in mind:

## Implementing `vmalloc`

### Allocation Policy

Many allocation _policies_ are possible – choosing the first block that fits, choosing the last block that fits, choosing the most-recently-freed block that fits, and so on. The one you **must** implement for this PA is the best-fit policy.

That is, once you have determined the size requirement of the desired heap block, you need to traverse the entire heap to find the best-fitting block – the smallest block that is large enough to fit the allocation. If there are multiple candidates of the same size, then you should use the first one you find.

### Splitting Large Blocks

If the best-fitting block you find is larger than what we need, then we need to split that block into two. For example, if we are looking for a 16-byte block for vmalloc(4), and the best fitting candidate is a 64-byte block, then we will split it into a 16-byte block and a 48-byte block. The former is allocated and returned to the caller, the latter remains free.

### Updating Block Header(s)

If a new block was created as a result of a split, you need to create a new header for it, and

- set the correct size.
- set the correct status bits.

And for the block that was allocated, you need to

- update the size (if splitting happened).
- set the correct statuses for the current block header and the next block header.

### Returning the Address

After updating all the relevant metadata, vmalloc should return a pointer to the start of the payload. Do not return the address of the block header!

## Implementing vmfree

The simplest version of `vmfree` just finds the header for the given block and resets the block status bit to 0.

### Coalescing freed blocks

Just freeing a block is not necessarily enough, since this may leave us with many small free blocks that can't hold a large allocation. When freeing, we also want to check if the next / previous block in the heap are free, and coalesce with them to make one large free block.

If you are coalescing two blocks, remember to update both the header and the footer!

### Block footers / Previous Bit

You will need to update both your `vmalloc` and your `vmfree` implementation to add code for creating/updating accurate footers, and making sure the "previous block busy"  bit is correct.
