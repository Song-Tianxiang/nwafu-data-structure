use std::collections::VecDeque;
use std::io::{self, BufRead};

type Tree = Vec<Node>;

#[derive(Debug, Default, Clone)]
struct Node {
    alpha: char,
    next: Edge,
}

impl Node {
    fn new(ch: char) -> Self {
        Node {
            alpha: ch,
            ..Default::default()
        }
    }

    fn append(&mut self, index: usize) {
        let new_node = Some(Box::new(CSNode {
            index,
            ..Default::default()
        }));

        if let Some(mut child) = self.next.as_mut() {
            while let Some(ref mut x) = child.next {
                child = x;
            }
            child.next = new_node;
        } else {
            self.next = new_node
        }
    }
}

impl Iterator for Node {
    type Item = CSNode;

    fn next(&mut self) -> Option<Self::Item> {
        match self.next.take() {
            Some(first_child) => {
                self.next = first_child.next.clone();
                Some(*first_child)
            }
            None => None,
        }
    }
}

type Edge = Option<Box<CSNode>>;

#[derive(Debug, Default, Clone)]
struct CSNode {
    index: usize,
    next: Edge,
}

fn main() {
    let mut lock = io::stdin().lock();
    let mut input = String::new();
    lock.read_line(&mut input).expect("at least 1 input line.");

    let mut tree: Tree = input
        .chars()
        .filter(char::is_ascii_alphabetic)
        .map(|x| Node::new(x))
        .collect();

    if let Some(root) = input.chars().skip(1).next() {
        build_tree(&mut tree, &input[2..input.len() - 2], root);
    }
    println!("{}",level_travelsal(&mut tree));
}

fn build_tree(tree: &mut Tree, subtree: &str, root: char) {
    if subtree.len() == 0 {
        return;
    }
    let node_list = tree
        .iter()
        .position(|x| x.alpha == root)
        .expect("can not find root in tree");
    let mut stack = vec![];
    for (index, alpha) in subtree.chars().enumerate() {
        match alpha {
            ch if ch.is_ascii_alphabetic() => {
                if stack.len() == 1 {
                    let inn = tree
                        .iter()
                        .position(|x| x.alpha == ch)
                        .expect("can not find root in tree");
                    tree[node_list].append(inn);
                }
            }
            '(' => {
                stack.push(index);
            }
            ')' => {
                let first = stack.pop().expect("Parentheses should be paired");
                if stack.len() == 1 {
                    build_tree(
                        tree,
                        &subtree[first..=index],
                        subtree
                            .chars()
                            .nth(first - 1)
                            .expect(") index can not find"),
                    );
                }
            }
            _ => {}
        }
    }
}

fn level_travelsal(tree: &mut Tree) -> String {
    let mut tree_nodes = String::new();

    if tree.is_empty() {
        return tree_nodes;
    }

    let mut queue: VecDeque<usize> = VecDeque::new();
    queue.push_back(0);
    while !queue.is_empty() {
        let index = queue.pop_front().expect("tree should not be empty");
        let node = &mut tree[index];
        tree_nodes.push(node.alpha);
        for child in node {
            queue.push_back(child.index);
        }
    }
    tree_nodes
}
