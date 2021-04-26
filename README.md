# Its a Race… Prim and Kruskal MST

CS 3353 Spring 2021

By Nick Wall and Elias Mann

## Analysis

Kruskal’s algorithm is an efficient method of determining the minimum spanning tree in a sparse graph. However, with a time complexity of `O(ElgE)`, the design of the algorithm requires iterating through every edge in a graph. Prim’s algorithm only needs to traverse to the next least costly edge from a given vertex and has a time complexity of `O(E+lgV)`. Therefore, Prim’s algorithm is more efficient as graph density increases. This difference can be circumvented by optimizing Kruskal’s algorithm to end as soon as the minimum spanning tree is completed. By definition of a minimum spanning tree, the tree must contain `V - 1` edges . The optimization of Kruskal’s algorithm stops attempting to add edges to the tree when `V -1` edges have been added. This optimization has a time complexity of `O((V-1)lgE)`.

As the density of the graphs increase, there is no significant change in performance. In fact, Kruskal’s algorithm was faster for larger densities in small graphs. As graph size increased, both algorithms slowed down. As the size increased, the density had less effect on the performance of both algorithms. Optimized Kruskal’s algorithm performed faster than Prim’s Algorithm in every test.

![graph](/artifacts/all_data_lines.png)

## Building

To build the project run the following commands:

```bash
$ git clone https://github.com/smu-cs-3353/s21-pa04-wall_mann.git
$ cd s21-pa04-wall_mann
$ mkdir build
$ cmake -Bbuild -H.
$ cmake --build build/
```

## Running

To run the binary, navigate to the root directory after building the binary and execute the following command:

```bash
$ cd build
$ ./MinTree -b <insert_file_path_for_data_here>
```

Using the -b flag for perfomance mode with no extra analytics. The -f flag can also be substituted to log statistics about the run. This output will be added to the `Data_Analysis.txt` file.
