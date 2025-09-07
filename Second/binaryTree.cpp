#include <iostream>
#include <queue>
#include <vector>

template<typename T>
class BinaryTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        
        Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };
    
    Node* root;
    
    // Helper function for insertion (BST property)
    Node* insertHelper(Node* node, const T& value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        // If value equals node->data, we don't insert duplicates
        
        return node;
    }
    
    // Helper function for deletion
    Node* deleteHelper(Node* node, const T& value) {
        if (node == nullptr) {
            return node;
        }
        
        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        } else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        } else {
            // Node to be deleted found
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Node with two children
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }
    
    // Find minimum value node
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
    
    // Helper function for search
    bool searchHelper(Node* node, const T& value) {
        if (node == nullptr) {
            return false;
        }
        
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
    
    // Helper functions for traversals
    void inorderHelper(Node* node, std::vector<T>& result) {
        if (node != nullptr) {
            inorderHelper(node->left, result);
            result.push_back(node->data);
            inorderHelper(node->right, result);
        }
    }
    
    void preorderHelper(Node* node, std::vector<T>& result) {
        if (node != nullptr) {
            result.push_back(node->data);
            preorderHelper(node->left, result);
            preorderHelper(node->right, result);
        }
    }
    
    void postorderHelper(Node* node, std::vector<T>& result) {
        if (node != nullptr) {
            postorderHelper(node->left, result);
            postorderHelper(node->right, result);
            result.push_back(node->data);
        }
    }
    
    // Helper function for calculating height
    int heightHelper(Node* node) {
        if (node == nullptr) {
            return -1;
        }
        
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        
        return 1 + std::max(leftHeight, rightHeight);
    }
    
    // Helper function for destroying the tree
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    // Helper function for copying tree
    Node* copyTree(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        
        return newNode;
    }

public:
    // Constructor
    BinaryTree() : root(nullptr) {}
    
    // Copy constructor
    BinaryTree(const BinaryTree& other) : root(copyTree(other.root)) {}
    
    // Assignment operator
    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            destroyTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    // Destructor
    ~BinaryTree() {
        destroyTree(root);
    }
    
    // Insert a value (maintains BST property)
    void insert(const T& value) {
        root = insertHelper(root, value);
    }
    
    // Delete a value
    void remove(const T& value) {
        root = deleteHelper(root, value);
    }
    
    // Search for a value
    bool search(const T& value) {
        return searchHelper(root, value);
    }
    
    // Check if tree is empty
    bool empty() const {
        return root == nullptr;
    }
    
    // Get height of the tree
    int height() {
        return heightHelper(root);
    }
    
    // Traversal methods
    std::vector<T> inorderTraversal() {
        std::vector<T> result;
        inorderHelper(root, result);
        return result;
    }
    
    std::vector<T> preorderTraversal() {
        std::vector<T> result;
        preorderHelper(root, result);
        return result;
    }
    
    std::vector<T> postorderTraversal() {
        std::vector<T> result;
        postorderHelper(root, result);
        return result;
    }
    
    // Level-order traversal (breadth-first)
    std::vector<T> levelorderTraversal() {
        std::vector<T> result;
        if (root == nullptr) {
            return result;
        }
        
        std::queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            
            result.push_back(current->data);
            
            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        
        return result;
    }
    
    // Print tree structure (for visualization)
    void printTree() {
        if (root == nullptr) {
            std::cout << "Tree is empty" << std::endl;
            return;
        }
        
        std::queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                Node* current = q.front();
                q.pop();
                
                if (current != nullptr) {
                    std::cout << current->data << " ";
                    q.push(current->left);
                    q.push(current->right);
                } else {
                    std::cout << "null ";
                }
            }
            std::cout << std::endl;
        }
    }
};

// Example usage and test function
int main() {
    BinaryTree<int> tree;
    
    // Test insertions
    std::cout << "Inserting values: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    std::cout << "Tree structure:" << std::endl;
    tree.printTree();
    
    // Test traversals
    std::cout << "\nTraversals:" << std::endl;
    
    auto inorder = tree.inorderTraversal();
    std::cout << "Inorder: ";
    for (int val : inorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto preorder = tree.preorderTraversal();
    std::cout << "Preorder: ";
    for (int val : preorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto postorder = tree.postorderTraversal();
    std::cout << "Postorder: ";
    for (int val : postorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    auto levelorder = tree.levelorderTraversal();
    std::cout << "Level-order: ";
    for (int val : levelorder) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // Test search
    std::cout << "\nSearch tests:" << std::endl;
    std::cout << "Search 40: " << (tree.search(40) ? "Found" : "Not found") << std::endl;
    std::cout << "Search 90: " << (tree.search(90) ? "Found" : "Not found") << std::endl;
    
    // Test height
    std::cout << "Tree height: " << tree.height() << std::endl;
    
    // Test deletion
    std::cout << "\nDeleting 30..." << std::endl;
    tree.remove(30);
    
    std::cout << "Tree after deletion:" << std::endl;
    auto inorderAfterDel = tree.inorderTraversal();
    std::cout << "Inorder: ";
    for (int val : inorderAfterDel) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}