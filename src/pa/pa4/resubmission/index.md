# PA4 – Malloc: Resubmission Due 12/4 10PM

If you want to resubmit the PA4 code section, please read this section carefully. You need to pass all the tests in the original PA4, while also implementing an extra functionality. You also need to meet the leaderboard performance boundaries for heap efficiency and speed.

## Implement Segregated Free List Design

For your resubmission, you must implement a segregated free list(seglist) design for your `vmalloc`. At minimum, it must keep two separate size classes: one free list for small blocks and one for large blocks. You may add more size classes if you want finer-grained segregation, and you're encouraged to, but it is not strictly required.

__**What you need to do depends on how your original submission went:**__
- If your original allocator did not use segregated free lists: 
    - Restructure vmalloc and vmfree around a seglist design with at least the two size classes described above
    - Your new implementation must pass all correctness tests and meet the required heap efficiency and speed bounds.
- If your original allocator already used segregated free lists: 
    - You don't need to redesign it. Instead, refine your implementation until it meets the required heap efficiency and speed bounds from the leaderboard.
- If your original allocator failed one or more correctness tests: 
    - First fix every correctness issue. Your allocator must pass the full correctness suite before it will be evaluated on the leaderboard workloads. 
    - Once it's correct, it must meet the same heap efficiency and speed bounds as above.

In every case, your allocator must keep the behavior required by the original PA4 writeup. That includes the NULL return conditions, the error messages, and reuse of freed memory.

## Updated DESIGN question for the resubmission

If you want to resubmit the design questions, we will be asking this updated design question in a new Gradescope assignment. Please add your answers to all questions to your resubmission, even the ones you got full points on.

Study the design of the GNU C Library (glibc) implementation of malloc (often called ptmalloc). In a written response, compare it with your own allocator. Your response should:

- Summarize the key design features of glibc's malloc. Cover how it organizes free blocks, its chunk header layout, its placement policy, and when and how it coalesces adjacent free chunks.
- Compare those choices with your allocator's design. Address at least these dimensions: block header and footer format, free-block organization (your size classes compared with glibc's bins), block selection policy, splitting, and coalescing.
- Analyze the trade-offs. For each significant difference, explain how it is likely to affect heap efficiency (fragmentation and metadata overhead) and speed. Explain why glibc's design choices might make sense for a general-purpose, production allocator, and whether they would help or hurt in the setting of this assignment.

Be specific, and justify your claims with reference to both glibc's design and your own code.