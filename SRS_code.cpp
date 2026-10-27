#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

struct Student {
    int enrolmentId;
    string name;
    string department;
};

struct Node {
    Student data;
    Node* left;
    Node* right;
    explicit Node(const Student& s) : data(s), left(nullptr), right(nullptr) {}
};

class StudentBST {
private:
    Node* root = nullptr;
    int comparisons = 0;

    Node* insertNode(Node* node, const Student& student, bool& inserted) {
        if (!node) {
            inserted = true;
            return new Node(student);
        }
        ++comparisons;
        if (student.enrolmentId < node->data.enrolmentId)
            node->left = insertNode(node->left, student, inserted);
        else if (student.enrolmentId > node->data.enrolmentId)
            node->right = insertNode(node->right, student, inserted);
        else
            inserted = false;
        return node;
    }

    Node* searchNode(Node* node, int id) {
        if (!node) return nullptr;
        ++comparisons;
        if (id == node->data.enrolmentId) return node;
        if (id < node->data.enrolmentId) return searchNode(node->left, id);
        return searchNode(node->right, id);
    }

    Node* minimumNode(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int id, bool& deleted) {
        if (!node) return nullptr;
        ++comparisons;
        if (id < node->data.enrolmentId) {
            node->left = deleteNode(node->left, id, deleted);
        } else if (id > node->data.enrolmentId) {
            node->right = deleteNode(node->right, id, deleted);
        } else {
            deleted = true;
            if (!node->left) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }
            if (!node->right) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }
            Node* successor = minimumNode(node->right);
            node->data = successor->data;
            bool ignored = false;
            node->right = deleteNode(node->right, successor->data.enrolmentId, ignored);
        }
        return node;
    }

    void inorderNode(Node* node) const {
        if (!node) return;
        inorderNode(node->left);
        printStudent(node->data);
        inorderNode(node->right);
    }

    void preorderNode(Node* node) const {
        if (!node) return;
        printStudent(node->data);
        preorderNode(node->left);
        preorderNode(node->right);
    }

    void postorderNode(Node* node) const {
        if (!node) return;
        postorderNode(node->left);
        postorderNode(node->right);
        printStudent(node->data);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    ~StudentBST() { destroy(root); }

    static void printStudent(const Student& s) {
        cout << "ID: " << s.enrolmentId << " | Name: " << s.name
             << " | Department: " << s.department << '\n';
    }

    bool insert(const Student& student) {
        bool inserted = false;
        root = insertNode(root, student, inserted);
        return inserted;
    }

    bool search(int id, Student& found) {
        Node* result = searchNode(root, id);
        if (!result) return false;
        found = result->data;
        return true;
    }

    bool remove(int id) {
        bool deleted = false;
        root = deleteNode(root, id, deleted);
        return deleted;
    }

    void inorder() const { inorderNode(root); }
    void preorder() const { preorderNode(root); }
    void postorder() const { postorderNode(root); }

    void resetComparisons() { comparisons = 0; }
    int getComparisons() const { return comparisons; }

    int height() const { return heightNode(root); }

private:
    int heightNode(Node* node) const {
        if (!node) return 0;
        return 1 + max(heightNode(node->left), heightNode(node->right));
    }
};

Student readStudent() {
    Student s{};
    cout << "Enrolment ID (integer): ";
    cin >> s.enrolmentId;
    cin.ignore(10000, '\n');
    cout << "Student name: ";
    getline(cin, s.name);
    cout << "Department/programme: ";
    getline(cin, s.department);
    return s;
}

int main() {
    StudentBST bst;

    // Ten sample records, inserted in a mixed order to avoid a fully skewed tree.
    vector<Student> sample = {
        {105, "Aarav Sharma", "CSE"},
        {102, "Diya Verma", "IT"},
        {108, "Kabir Singh", "ECE"},
        {101, "Meera Patel", "CSE"},
        {104, "Rohan Gupta", "Mechanical"},
        {107, "Ananya Das", "IT"},
        {110, "Ishaan Rao", "Civil"},
        {103, "Sara Khan", "CSE"},
        {106, "Vivaan Joshi", "ECE"},
        {109, "Nisha Roy", "IT"}
    };
    for (const auto& s : sample) bst.insert(s);

    int choice;
    do {
        cout << "\n=== Student Record Search System (BST) ===\n"
             << "1. Insert student\n"
             << "2. Search by enrolment ID\n"
             << "3. Delete by enrolment ID\n"
             << "4. Inorder traversal (sorted by ID)\n"
             << "5. Preorder traversal\n"
             << "6. Postorder traversal\n"
             << "7. Compare insertion orders (comparisons and height)\n"
             << "8. Exit\n"
             << "Enter choice: ";
        if (!(cin >> choice)) return 0;

        if (choice == 1) {
            Student s = readStudent();
            if (bst.insert(s)) cout << "Student inserted successfully.\n";
            else cout << "Duplicate enrolment ID rejected.\n";
        } else if (choice == 2) {
            int id;
            cout << "Enter enrolment ID to search: ";
            cin >> id;
            bst.resetComparisons();
            Student found{};
            if (bst.search(id, found)) {
                cout << "Student found:\n";
                StudentBST::printStudent(found);
            } else {
                cout << "No student found with ID " << id << ".\n";
            }
            cout << "Comparisons: " << bst.getComparisons() << '\n';
        } else if (choice == 3) {
            int id;
            cout << "Enter enrolment ID to delete: ";
            cin >> id;
            if (bst.remove(id)) cout << "Student deleted successfully.\n";
            else cout << "No student found with ID " << id << ".\n";
        } else if (choice == 4) {
            cout << "Inorder traversal:\n";
            bst.inorder();
        } else if (choice == 5) {
            cout << "Preorder traversal:\n";
            bst.preorder();
        } else if (choice == 6) {
            cout << "Postorder traversal:\n";
            bst.postorder();
        } else if (choice == 7) {
            vector<int> balancedOrder = {50, 30, 70, 20, 40, 60, 80};
            vector<int> sortedOrder = {20, 30, 40, 50, 60, 70, 80};
            // A small local BST experiment counts key comparisons during insertion.
            auto measure = [](const vector<int>& order) {
                struct TNode { int key; TNode* left; TNode* right; TNode(int k):key(k),left(nullptr),right(nullptr){} };
                TNode* r = nullptr;
                int comps = 0;
                for (int key : order) {
                    TNode** link = &r;
                    while (*link) {
                        ++comps;
                        if (key < (*link)->key) link = &((*link)->left);
                        else link = &((*link)->right);
                    }
                    *link = new TNode(key);
                }
                int h = 0;
                auto height = [&](auto&& self, TNode* n) -> int {
                    if (!n) return 0;
                    return 1 + max(self(self, n->left), self(self, n->right));
                };
                h = height(height, r);
                auto freeTree = [&](auto&& self, TNode* n) -> void {
                    if (!n) return;
                    self(self, n->left); self(self, n->right); delete n;
                };
                freeTree(freeTree, r);
                return pair<int,int>{comps, h};
            };
            auto a = measure(balancedOrder);
            auto b = measure(sortedOrder);
            cout << "Balanced-looking order: comparisons=" << a.first << ", height=" << a.second << '\n';
            cout << "Sorted order:            comparisons=" << b.first << ", height=" << b.second << '\n';
        } else if (choice == 8) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}
