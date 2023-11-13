use std::io::{self, BufRead};

type Tree = Vec<Node>;

#[derive(Debug, Eq)]
struct Node {
    alpha: char,
    weight: i32,
    parent: usize,
    lelf_child: usize,
    right_child: usize,
}

impl PartialEq for Node {
    fn eq(&self, other: &Self) -> bool {
        self.weight == other.weight
    }
}

impl Ord for Node {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        self.weight.cmp(&other.weight)
    }
}

impl PartialOrd for Node {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl Default for Node {
    fn default() -> Self {
        Node {
            alpha: char::default(),
            weight: 0,
            parent: usize::MAX,
            lelf_child: usize::MAX,
            right_child: usize::MAX,
        }
    }
}

fn create_tree() -> Tree {
    let lines = io::stdin().lock().lines();
    let mut input = lines
        .skip(1)
        .next()
        .expect("at least two lines")
        .expect("read line error");
    input.retain(|c| !c.is_whitespace());

    let mut tree: Tree = vec![];

    for c in input.chars() {
        if let Some(node) = tree.iter_mut().find(|node| c == node.alpha) {
            node.weight += 1;
        } else {
            tree.push(Node {
                alpha: c,
                weight: 1,
                ..Default::default()
            })
        }
    }
    tree
}

fn huffman_code(tree: &Tree, node: &Node) -> String {
    let mut code = String::new();

    if node.parent == usize::MAX {
        return code;
    }
    let parent = &tree[node.parent];

    if &tree[parent.lelf_child] == node {
        code.push('1');
    } else {
        code.push('0');
    }

    huffman_code(tree, parent) + &code
}

fn build_tree(tree: &mut Vec<Node>, num_node: usize) {
    while tree.len() != num_node {
        let min = tree
            .iter()
            .filter(|x| x.parent == usize::MAX)
            .min()
            .unwrap();
        let min_index = tree.iter().position(|x| x == min).unwrap();

        let min_second = tree
            .iter()
            .filter(|&x| x.parent == usize::MAX && x != min)
            .min()
            .unwrap();
        let min_second_index = tree.iter().position(|x| x == min_second).unwrap();

        tree.push(Node {
            weight: min.weight + min_second.weight,
            lelf_child: min_second_index,
            right_child: min_index,
            ..Default::default()
        });

        tree[min_index].parent = tree.len() - 1;
        tree[min_second_index].parent = tree.len() - 1;
    }
}

fn main() {
    let mut tree = create_tree();

    tree.sort_by(|a, b| b.cmp(a));

    let num_char = tree.len();
    let num_node = tree.len() * 2 - 1;

    // build the tree
    build_tree(&mut tree, num_node);

    for node in &tree[..num_char] {
        println!(
            "{} {} {}",
            node.alpha,
            node.weight,
            huffman_code(&tree, node)
        )
    }
}
