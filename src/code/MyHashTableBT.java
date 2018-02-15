package code;

/**
 * Created by SRIN on 11/22/2017.
 */
public class MyHashTableBT {

    class TreeNode{
        TreeNode left, right;
        int data;

        public TreeNode(int value){
            data = value;
            left = null;
            right = null;
        }
    }

    private TreeNode[] mTable;
    private int mSize;

    public MyHashTableBT(int tableSize) {
        mSize = 0;
        mTable = new TreeNode[tableSize];
    }

    boolean isEmpty(){
        return mSize == 0;
    }

    private int myHash(Integer x){
        return x.hashCode();
    }

    public void insert(int val){
        mSize++;

    }
}
