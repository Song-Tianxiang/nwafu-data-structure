use std::io::{self, BufRead};

#[derive(Default)]
pub struct BinaryTree {
    root: Edge,
}

type Edge = Option<Box<TreeNode>>;

struct TreeNode {
    alpha: char,
    lchild: Edge,
    rchild: Edge,
}

impl BinaryTree {
    fn new() -> Self {
        Default::default()
    }
}


impl Drop for BinaryTree {
    fn drop(&mut self) {
        let mut stack = vec![];
        if let Some(whole_tree_root) = self.root.take() {
            stack.push(whole_tree_root);
        }
        while let Some(mut cur_root) = stack.pop() {
            if let Some(lchild) = cur_root.lchild.take() {
                stack.push(lchild);
            }
            if let Some(rchild) = cur_root.rchild.take() {
                stack.push(rchild);
            }
        }
    }
}

fn main() {
    let mut lock = io::stdin().lock();
    let mut input = String::new();

    lock.read_line(&mut input)
        .expect("there should be input, can't get");
    dbg!(&input);
}

fn build_tree(input: &str) -> BinaryTree {
    Default::default()
}
