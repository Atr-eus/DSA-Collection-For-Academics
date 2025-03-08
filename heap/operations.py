class MinHeap:
    def __init__(self, init=None):
        self.heap = init[:] if init else []

        if self.heap:
            self.heapify_up(0)

    def heapify_up(self, i):
        h = self.heap

        while i > 0:
            pi = (i - 1) // 2
            if h[i] < h[pi]:
                h[i], h[pi] = h[pi], h[i]
                i = pi
            else:
                break

    def insert_node(self, val):
        h = self.heap

        h.append(val)
        self.heapify_up(len(h) - 1)

    def heapify_down(self, i):
        h = self.heap
        n = len(h)

        while True:
            l = i * 2 + 1
            r = i * 2 + 2
            sm = i

            if l < n and h[l] < h[sm]:
                sm = l
            if r < n and h[r] < h[sm]:
                sm = r
            if sm == i:
                break
            else:
                h[i], h[sm] = h[sm], h[i]
                i = sm

    def delete_node(self):
        h = self.heap
        if not h:
            print("Cannot delete, heap is empty.")
            return

        h[0], h[-1] = h[-1], h[0]
        h.pop()
        if h:
            self.heapify_down(0)


class MaxHeap:
    def __init__(self, init=None):
        self.heap = init[:] if init else []

        if self.heap:
            self.heapify_up(0)

    def heapify_up(self, i):
        h = self.heap

        while i > 0:
            pi = (i - 1) // 2
            if h[i] > h[pi]:
                h[i], h[pi] = h[pi], h[i]
                i = pi
            else:
                break

    def insert_node(self, val):
        h = self.heap

        h.append(val)
        self.heapify_up(len(h) - 1)

    def heapify_down(self, i):
        h = self.heap
        n = len(h)

        while True:
            l = i * 2 + 1
            r = i * 2 + 2
            lg = i

            if l < n and h[l] > h[lg]:
                lg = l
            if r < n and h[r] > h[lg]:
                lg = r
            if lg == i:
                break
            else:
                h[i], h[lg] = h[lg], h[i]
                i = lg

    def delete_node(self):
        h = self.heap
        if not h:
            print("Cannot delete, heap is empty.")
            return

        h[0], h[-1] = h[-1], h[0]
        h.pop()
        if h:
            self.heapify_down(0)

    def get_max(self):
        return self.heap[0] if self.heap else None
