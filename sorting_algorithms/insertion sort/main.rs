fn main() {
    println!("{:?}", insertion_sort(&mut vec![5, 2, 4, 6, 1, 3]));
}

fn insertion_sort(list: &mut Vec<i32>) -> &mut Vec<i32>{
    let mut i: usize = 1;

    while i < list.len() {
        let key = list[i];
        let mut j = i - 1;

        while j >= 0 && list[j] > key {
            list[j + 1] = list[j];
            j = j - 1;
        }
        list[j + 1] = key;

        i = i + 1;
    }
    list
}
