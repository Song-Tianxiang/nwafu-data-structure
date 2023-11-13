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

    // 先序遍历
    fn pre_order_traversal(&self) -> Vec<i32> {
        let mut result = Vec::new();
        result.push(self.value);
        if let Some(left) = &self.left {
            result.extend(left.pre_order_traversal());
        }
        if let Some(right) = &self.right {
            result.extend(right.pre_order_traversal());
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

fn build_tree(levelorder: &[i32], inorder: &[i32]) -> Option<Box<TreeNode>> {
    if inorder.is_empty() || levelorder.is_empty() {
        return None;
    }

    let root_value = levelorder[0];
    let root_index = inorder.iter().position(|&x| x == root_value).unwrap();

    let left_inorder = &inorder[..root_index];
    let right_inorder = &inorder[root_index + 1..];

    let left_levelorder: Vec<i32> = levelorder
        .iter()
        .filter(|&x| left_inorder.contains(x))
        .cloned()
        .collect();
    let right_levelorder: Vec<i32> = levelorder
        .iter()
        .filter(|&x| right_inorder.contains(x))
        .cloned()
        .collect();

    Some(Box::new(TreeNode {
        value: root_value,
        left: build_tree(&left_levelorder, left_inorder),
        right: build_tree(&right_levelorder, right_inorder),
    }))
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

    // Read and parse level-order and in-order lines
    let level_order: Vec<i32> = lines
        .next()
        .expect("Failed to read level-order tree")
        .expect("Empty pre-order tree")
        .split_whitespace()
        .map(|s| s.parse().expect("Invalid integer in level-order tree"))
        .collect();

    let inorder: Vec<i32> = lines
        .next()
        .expect("Failed to read in-order tree")
        .expect("Empty in-order tree")
        .split_whitespace()
        .map(|s| s.parse().expect("Invalid integer in in-order tree"))
        .collect();

    // Check if the size matches the length of the arrays
    if size != level_order.len() || size != inorder.len() {
        eprintln!("Size mismatch between specified size and the length of input arrays.");
        return;
    }

    let root = build_tree(&level_order, &inorder).unwrap();
    let pre_order_result = root.pre_order_traversal();
    let post_order_result = root.post_order_traversal();

    println!("{}", IntVecDisplay(&pre_order_result));
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
