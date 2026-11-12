# Implementation Guide

As with all previous PAs, refer back to PSet4 to create helper functions for this PA. Here are more implementation details to keep in mind:

## Implementing `vmalloc`

### Returning the Address

After updating all the relevant metadata, vmalloc should return a pointer to the start of the payload. Do not return the address of the block header!

## Implementing vmfree

If you use the starter code's block format, the simplest version of `vmfree` finds the header for the given block and resets the block status bit to 0. Remember the two error cases from the specification: `NULL`, and a block that is already free.
