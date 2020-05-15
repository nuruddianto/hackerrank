package code;

/**
 * Created by SRIN on 11/21/2017.
 */
public class MyMaxHeap {
    private int[] mHeap;
    private int mSize;
    private int mMaxSize;

    private static final int HEAD = 1;

    public MyMaxHeap(int maxSize) {
        mMaxSize = maxSize;
        maxSize = 0;
        mHeap = new int[mMaxSize + 1];
        mHeap[0] = Integer.MAX_VALUE;
    }

    private int parent(int pos) {
        return pos / 2;
    }

    private int leftChild(int pos) {
        return 2 * pos;
    }

    private int rightChild(int pos) {
        return (2 * pos) + 1;
    }

    private boolean isLeaf(int pos) {
        if (pos >= (mSize / 2) && pos <= mSize) {
            return true;
        }
        return false;
    }

    private void swap(int from, int to) {
        int tmp;
        tmp = mHeap[from];
        mHeap[from] = mHeap[to];
        mHeap[to] = tmp;
    }

    private void maxHeapify(int pos) {
        if (!isLeaf(pos)) {
            if (mHeap[pos] < mHeap[leftChild(pos)] || mHeap[pos] < mHeap[rightChild(pos)]) {
                if (mHeap[leftChild(pos)] > mHeap[rightChild(pos)]) {
                    swap(pos, leftChild(pos));
                    maxHeapify(leftChild(pos));
                } else {
                    swap(pos, rightChild(pos));
                    maxHeapify(rightChild(pos));
                }
            }
        }
    }

    public void insert(int value) {
        mHeap[++mSize] = value;
        int current = mSize;

        while (mHeap[current] > mHeap[parent(current)]) {
            swap(current, parent(current));
            current = parent(parent(current));
        }
    }

    public void maxHeap() {
        for (int pos = (mMaxSize / 2); pos >= 1; pos--) {
            maxHeapify(pos);
        }
    }

    public int remove() {
        int pop = mHeap[HEAD];
        mHeap[HEAD] = mHeap[mSize--];
        maxHeapify(HEAD);
        return pop;
    }

    public void print()

    {
        for (int i = 1; i <= mSize / 2; i++) {
            System.out.print(" PARENT : " + mHeap[i] + " LEFT CHILD : " + mHeap[2 * i]
                    + " RIGHT CHILD :" + mHeap[2 * i + 1]);
            System.out.println();
        }

    }

    public static void main(String[] args) {
        MyMaxHeap maxHeap = new MyMaxHeap(15);
        maxHeap.insert(5);
        maxHeap.insert(3);
        maxHeap.insert(17);
        maxHeap.insert(10);
        maxHeap.insert(84);
        maxHeap.insert(19);
        maxHeap.insert(6);
        maxHeap.insert(22);
        maxHeap.insert(9);
        maxHeap.maxHeap();
        maxHeap.print();
        System.out.println("The max val is " + maxHeap.remove());
    }
}
