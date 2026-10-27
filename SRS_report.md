# Mini Project Report: Student Record Search System Using Trees

## 1. Aim
To implement a student record system using a Binary Search Tree, where enrolment ID is the unique key. The application supports insertion, search, deletion, and tree traversals.

## 2. Data structure
Each `Student` contains an enrolment ID, name, and department/programme. Each BST node stores one student and pointers to left and right children. For each node, IDs in the left subtree are smaller and IDs in the right subtree are larger. Duplicate IDs are rejected.

Ten sample student records are inserted when the program starts. These are fictional sample records and can be replaced with suitable test data.

## 3. Operations
- **Insertion:** follows the BST ordering property to place a new record; rejects duplicate IDs.
- **Search:** compares the requested ID with the current node and follows the left or right subtree.
- **Deletion:** handles a leaf by removing it; a node with one child is replaced by its child; a node with two children is replaced with its inorder successor (the minimum node in its right subtree).
- **Inorder traversal:** left, root, right; prints IDs in ascending order.
- **Preorder traversal:** root, left, right.
- **Postorder traversal:** left, right, root.
- **Insertion-order comparison:** compares key comparisons and height for balanced-looking and sorted insertion sequences.

## 4. Complexity analysis
Let n be the number of records and h the height of the tree.

| Operation | Average case | Worst case |
|---|---|---|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Traversal | O(n) | O(n) |

The average-case figures assume a reasonably balanced tree. If IDs are inserted in sorted order, each new node can become the right child of the previous node, creating a skewed tree with height n. Operations then degrade to O(n). An AVL tree uses rotations to maintain height O(log n), keeping insert/search/delete O(log n).

## 5. Test cases
| Test | Action | Expected result |
|---|---|---|
| Successful search | Search ID 105 | Student details for Aarav Sharma are displayed |
| Missing search | Search ID 999 | “No student found” message |
| Duplicate key | Insert another record with ID 105 | Duplicate enrolment ID rejected |
| Leaf deletion | Delete leaf ID 101 from initial tree | Record removed; traversal no longer includes 101 |
| One-child deletion | Create a node with one child, then delete that node | Its child takes its place |
| Two-child deletion | Delete ID 105 from initial tree | Inorder successor replaces the deleted node; ordering remains valid |
| Sorted display | Inorder traversal | Enrolment IDs appear in ascending order |

## 6. Conclusion
The project demonstrates the BST ordering property, recursive operations, deletion edge cases, traversals, and the impact of tree shape on performance. The comparison option illustrates why sorted insertion can make an ordinary BST inefficient.

