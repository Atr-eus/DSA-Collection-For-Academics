function insertionSort(list: number[]): number[] {
  if (list.length === 1) return list;

  for (let i = 1; i < list.length; i++) {
    let key = list[i];
    let j = i - 1;

    while (j >= 0 && list[j] > key) {
      list[j + 1] = list[j];
      j = j - 1;
    }

    list[j + 1] = key;
  }

  return list;
}

console.log(insertionSort([5, 2, 4, 6, 1, 3]));
