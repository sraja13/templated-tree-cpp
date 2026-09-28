# Templated Tree Library (C++)

A generic ordered n-ary tree in C++11, plus a character-specialized version (`CTree`).

## Design
- **Left-child, right-sibling representation:** each node stores a pointer to its first child and its next sibling, so nodes can have any number of children
- **Templates:** `Tree<T>` works with any comparable type; the implementation lives in `Tree.inc`, included by `Tree.h`
- **Memory safety:** `CTree` follows the Rule of Three; `Tree<T>` follows the Rule of Five, with deep-copy constructor and assignment plus `noexcept` move constructor and move assignment
- **Operator overloading:** `==` compares trees node by node; `<<` prints a tree
- **Recursive algorithms:** deep copy, structural comparison, and pre-order traversal for string output

## Files
| File | Contents |
|---|---|
| `CTree.h`, `CTree.cpp` | Character tree |
| `Tree.h`, `Tree.inc` | Templated tree |

## Build
```bash
make   # compiles CTree and compile-checks the templated Tree
```
Include `Tree.h` in your own code to use `Tree<T>`.
