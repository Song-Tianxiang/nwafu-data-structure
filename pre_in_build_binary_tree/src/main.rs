use std::collections::VecDeque;
use std::fmt;
use std::io::{self, BufRead};

// 定义二叉树结构
#[derive(Debug)]
struct TreeNode {
    value: i32,
    left: Option<Box<TreeNode>>,
    right: Option<Box<TreeNode>>,
}

impl TreeNode {
    fn new(value: i32) -> Self {
        TreeNode {
            value,
            left: None,
            right: None,
        }
    }

    // 层序遍历
    fn level_order_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        let mut queue = VecDeque::new();
        queue.push_back(self);

        while !queue.is_empty() {
            if let Some(node) = queue.pop_front() {
                result.push(node.value);
                if let Some(left) = &node.left {
                    queue.push_back(left);
                }
                if let Some(right) = &node.right {
                    queue.push_back(right);
                }
            }
        }

        result
    }

    // 后序遍历
    fn post_order_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        if let Some(left) = &self.left {
            result.extend(left.post_order_traversal());
        }
        if let Some(right) = &self.right {
            result.extend(right.post_order_traversal());
        }
        result.push(self.value);
        result
    }
}

fn build_tree(preorder: &[i32], inorder: &[i32]) -> Option<Box<TreeNode>> {
    if preorder.is_empty() || inorder.is_empty() {
        return None;
    }

    let root_value = preorder[0];
    let root_index = inorder.iter().position(|&x| x == root_value).unwrap();
    let mut root = TreeNode::new(root_value);

    root.left = build_tree(&preorder[1..1 + root_index], &inorder[..root_index]);
    root.right = build_tree(&preorder[1 + root_index..], &inorder[root_index + 1..]);

    Some(Box::new(root))
}

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();

    // Read the size
    let size: usize = lines
        .next()
        .expect("Failed to read the first line")
        .expect("Empty first line")
        .trim()
        .parse()
        .expect("First line should be an integer");

    // Read and parse pre-order and in-order lines
    let preorder: Vec<i32> = lines
        .next()
        .expect("Failed to read pre-order tree")
        .expect("Empty pre-order tree")
        .split_whitespace()
        .map(|s| s.parse().expect("Invalid integer in pre-order tree"))
        .collect();

    let inorder: Vec<i32> = lines
        .next()
        .expect("Failed to read in-order tree")
        .expect("Empty in-order tree")
        .split_whitespace()
        .map(|s| s.parse().expect("Invalid integer in in-order tree"))
        .collect();

    // Check if the size matches the length of the arrays
    if size != preorder.len() || size != inorder.len() {
        eprintln!("Size mismatch between specified size and the length of input arrays.");
        return;
    }

    let root = build_tree(&preorder, &inorder).unwrap();
    let level_order_result = root.level_order_traversal();
    let post_order_result = root.post_order_traversal();

    println!("{}", IntVecDisplay(&level_order_result));
    println!("{}", IntVecDisplay(&post_order_result));
}

struct IntVecDisplay<'a>(&'a Vec<i32>);

impl<'a> fmt::Display for IntVecDisplay<'a> {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let vec = self.0;
        for (i, value) in vec.iter().enumerate() {
            write!(f, "{}", value)?;
            if i < vec.len() - 1 {
                write!(f, " ")?;
            }
        }
        Ok(())
    }
}
