use std::io::{self, BufRead};

fn main() {
    let mut tree = vec![0];
    tree.extend(
        io::stdin()
            .lock()
            .lines()
            .skip(1)
            .next()
            .expect("at least two line input")
            .unwrap()
            .split_whitespace()
            .map(|x| x.parse::<i32>().expect("input should be a int")),
    );

    let mut out = String::new();
    pre_traverse(&tree, 1, &mut out);
    out.pop();
    out.push('\n');

    in_traverse(&tree, 1, &mut out);
    out.pop();
    out.push('\n');

    post_traverse(&tree, 1, &mut out);
    out.pop();
    out.push('\n');

    print!("{}", out);
}

fn pre_traverse(tree: &Vec<i32>, index: usize, out: &mut String) {
    if index >= tree.len() {
        return;
    }

    if tree[index] > 0 {
        out.push_str(&format!("{} ", tree[index]));

        let left_index = index * 2;
        let right_index = index * 2 + 1;
        pre_traverse(tree, left_index, out);
        pre_traverse(tree, right_index, out);
    }
}

fn in_traverse(tree: &Vec<i32>, index: usize, out: &mut String) {
    if index >= tree.len() {
        return;
    }
    if tree[index] > 0 {
        let left_index = index * 2;
        in_traverse(tree, left_index, out);

        out.push_str(&format!("{} ", tree[index]));

        let right_index = index * 2 + 1;
        in_traverse(tree, right_index, out);
    }
}

fn post_traverse(tree: &Vec<i32>, index: usize, out: &mut String) {
    if index >= tree.len() {
        return;
    }
    if tree[index] > 0 {
        let left_index = index * 2;
        post_traverse(tree, left_index, out);
        let right_index = index * 2 + 1;
        post_traverse(tree, right_index, out);

        out.push_str(&format!("{} ", tree[index]));
    }
}
