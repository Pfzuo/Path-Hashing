## Path Hashing

Storage cells in the path hashing are logically organized as an inverted complete binary tree. The last level of the inverted binary tree, i.e., all leaf nodes, is considered as the hash table. All nodes in the remaining levels are considered as the shared positions to deal with hash collisions. Path hashing leverages three techniques, i.e., position sharing, double-path hashing and path shortening, allowing insertion and deletion requests to incur no extra writes to NVMs, while maintaining high performance of hash table in terms of space utilization and request latency.

## Purpose

> *Write-friendly.* Path hashing causes no extra writes to non-volatile memories. Insertion and deletion requests in path hashing only need to read the nodes in a path for finding an empty position or the target item, thus causing no extra writes.

> *Memory-efficient.* Path hashing has high space utilization which is as high as 95%, since position sharing and double-path hashing provide multiple standby positions for conflicting items.

> *Low request latency.* Path hashing incurs low latency for insertion, deletion, and query requests, due to only probing the nodes in several levels. The flat-addressed storage structure in path hashing allows all nodes in a read path to be read in parallel from NVMs, which has the time complexity of O(1).

## Implementation

The physical storage structure of path hashing is simple and efficient without pointers. Path hashing is implemented in a flat-addressed one-dimensional structure. The leaf nodes in the level *L* are stored in the first *2^L* positions in the one-dimensional structure. The level *L-1* is stored in the following *2^{L-1}* positions, and so on.

## Usage 

> The code of path hashing can be run in GEM5 with NVMain to evaluate the performance in the context of NVMs, and can also be run in real-world systems with DRAMs to evaluate the performance in DRAMs.

> We use the xxHash as an example of the hash function in the implementation code. After cloning the repository, the hash function can be modified to fit your needs.


## The Path Hashing Paper

Pengfei Zuo and Yu Hua, "A Write-friendly Hashing Scheme for Non-volatile Memory Systems", in Proceedings of the 33st International Conference on Massive Storage Systems and Technology (MSST), 2017.


