# AP1400-2-HW3 二叉搜索树 (BST) 总结

## 1. 项目概览
本项目使用 C++ 实现了二叉搜索树 (BST)。它展示了高级 C++ 特性，包括内存管理（五法则）、运算符重载、Lambda 表达式以及用于树遍历的函数式编程接口。

## 2. 关键 C++ 概念

### 2.1 双重指针 (`Node**`)
本项目广泛使用双重指针 (`Node**`) 来简化树的操作。通过持有指向当前节点指针的指针（例如指向 `root` 指针，或父节点的 `left`/`right` 子节点指针），我们可以轻松修改树的结构，而无需单独跟踪父节点。

```cpp
bool BST::add_node(int value) {
    Node** current = &root;
    while (*current) {
        // 遍历逻辑...
        if (value < (*current)->value) current = &((*current)->left);
        else current = &((*current)->right);
    }
    // 直接将新节点插入到正确的链接指针中
    *current = new Node(value, nullptr, nullptr);
    return true;
}
```

### 2.2 五法则 (Rule of Five)
由于该类管理动态内存（原始 `Node*`），它实现了五法则以确保资源安全：
*   **析构函数**：使用 BFS 遍历并 `delete` 所有节点。
*   **拷贝构造函数**：深拷贝树结构。
*   **移动构造函数**：转移 `root` 指针的所有权，基本无开销 (O(1))。
*   **拷贝赋值运算符**：使用拷贝并交换 (copy-and-swap) 或手动清除 + 重建。
*   **移动赋值运算符**：交换资源。

### 2.3 函数式遍历 (BFS)
`bfs` 函数接受一个 `std::function`（或 Lambda），允许用户定义对树节点的自定义操作，而无需暴露迭代逻辑。

```cpp
void BST::bfs(std::function<void(Node*& node)> func) const {
    // 基于队列的层序遍历
    // 对每个节点调用 func(node)
}

// 使用示例（计算长度）：
bfs([&count](Node*& node) { count++; });
```

## 3. 关键实现细节

### 3.1 后继节点与前驱节点 (重要修正)
本次作业的一个关键发现是“后继节点 (Successor)”的定义。单元测试 (`TEST15`, `TEST29`) 期望 `find_successor` 返回 **中序前驱 (Predecessor)**（左子树中的最大节点），而不是标准的后继节点（右子树中的最小节点）。

经过验证的实现：
```cpp
BST::Node** BST::find_successor(int value) {
    // ... 基础检查 ...
    if ((*target_ptr)->left) {
        // 寻找左子树中的最大节点
        auto succ_ptr = &(*target_ptr)->left;
        while ((*succ_ptr)->right)
            succ_ptr = &(*succ_ptr)->right;
        return succ_ptr;
    }
    // ... 祖先回溯逻辑 ...
}
```

### 3.2 节点删除
`delete_node` 函数处理三种情况：
1.  **叶子节点**：直接移除。
2.  **单子节点**：将父节点链接到唯一的子节点。
3.  **双子节点**：
    *   找到 **前驱节点**（使用修改后的 `find_successor`）。
    *   交换值。
    *   删除前驱节点。注意前驱节点（左子树最大值）最多只有一个左孩子，从而简化了删除过程。

## 4. 构建与测试系统
本项目使用 **CMake** 和 **Google Test**。
*   **FetchContent**：在 `CMakeLists.txt` 中用于包含 Google Test 源码（本配置中使用本地目录）。
*   **GTest/GMock**：链接到主可执行文件以运行 `unit_test.cpp` 中定义的单元测试。
