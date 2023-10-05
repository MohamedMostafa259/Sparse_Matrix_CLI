# Sparse Matrix CLI
**This is a C++ console application that implements a sparse matrix, optimized for scenarios where most of the elements are zeros. The program utilizes linked lists to efficiently store and manipulate the sparse matrix data.**

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Implementation Details](#implementation-details)
- [Example](#example)

## Introduction
Sparse matrices, commonly found in applications with predominantly zero values, are optimized using linked lists for efficient memory usage and operations. These applications include Natural Language Processing, Finite Element Analysis, Image Processing, Recommendation Systems, Network and Graph Analysis, Computational Fluid Dynamics, Circuit Simulation, Sparse Linear Systems, Web Page Ranking, Optimization Problems, Sparse Solvers, and Machine Learning algorithms.

To optimize memory usage and operations on sparse matrices, this program represents them as linked lists of linked lists. The main components include:
- ArrayLinkedList: A singly linked list implementation to handle 1D arrays efficiently.
- SparseMatrix: A representation of the sparse matrix using linked lists, where each row is a linked list of columns.

## Features
- Efficient storage and manipulation of sparse matrices.
- Support for setting and getting values in the matrix.
- Addition of two sparse matrices.
- Printing matrices with and without zero values.

## Implementation Details
### ArrayLinkedList
  - ArrayLinkedList is a singly linked list where each node represents an element in a 1D array.
  - Elements are sorted by their indices.
  - It provides functions to set and get values, add arrays, and print the list with and without zero values.
  - The list is implemented with a dummy head and tail node [to make coding shorter and more robust!](https://en.wikipedia.org/wiki/Sentinel_node)
### SparseMatrix
  - SparseMatrix represents a sparse matrix as a linked list of rows, where each row is an ArrayLinkedList.
  - Rows are sorted by their indices.
  - The program provides functions to set and get values in the matrix, add matrices, and print the matrix with and without zero values
  - Like ArrayLinkedList, dummy head, and tail nodes are used to make coding shorter and more robust!

## Example
The main() function demonstrates the usage of the Sparse Matrix Console Program:
- Creation and modification of sparse matrices.
- Addition of two matrices.
- Retrieval of values from the matrices.
- Printing matrices with and without zero values.

Code:
```
// Example usage in main() function
SparseMatrix mat(10, 10);
mat.set_value(5, 3, 5);
mat.set_value(7, 3, 7);
mat.set_value(2, 3, 2);
mat.set_value(0, 3, 2); // Modify the above line
mat.set_value(6, 5, 6);
mat.set_value(4, 5, 4);
mat.set_value(3, 7, 3);
mat.set_value(1, 7, 1);
mat.print();
mat.print_nonzero();

SparseMatrix mat2(10, 10);
mat2.set_value(5, 1, 9);
mat2.set_value(6, 3, 8);
mat2.set_value(9, 9, 9);
mat.add_matrix(mat2);
mat.print_nonzero();

cout << mat.get_value(1, 9) << "\n";
cout << mat.get_value(3, 5) << "\n";
cout << mat.get_value(7, 7) << "\n";
```

Output:
```
Print Matrix: 10 X 10

0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 5 0 7 0 0  
0 0 0 0 0 0 0 0 0 0  
0 0 0 0 4 0 6 0 0 0  
0 0 0 0 0 0 0 0 0 0
0 1 0 3 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 

Print Matrix: 10 X 10

0 5 7
4 6
1 3

Print Matrix: 10 X 10

5
0 5 7 6
4 6
1 3
9

5
5
0
```
