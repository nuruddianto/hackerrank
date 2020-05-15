package code;

/**
 * Created by SRIN on 1/16/2018.
 */
public class SelfOrganizingList {

    class Node {
        int value;
        int count;
        Node next;

        Node(int number) {
            value = number;
        }
    }

    Node mHead;
    Node mTail;

    void insert(int number) {
        Node tmp = new Node(number);
        if (mHead == null) {
            mHead = tmp;
            mTail = tmp;
        } else {
            mTail.next = tmp;
            mTail = tmp;
        }
    }

    Node search(int number) {
        Node start = mHead;
        Node prev = null;

        //find node that contain value
        while (start.value != number) {
            prev = start;
            start = start.next;
        }
        //increase count on node
        start.count++;


        if (prev == null) {
            return start;
        }
        //remove node
        prev.next = start.next;

        //rearrange node
        Node current = start;
        Node head = mHead;
        Node prevData = null;
        while (current.count < head.count) {
            prevData = head;
            head = head.next;
        }

        if (head == mHead || prevData == null) {
            start.next = mHead;
            mHead = start;
        } else {
            prevData.next = start;
            start.next = head;
        }


        return start;
    }

    void printList() {
        Node tmp = mHead;
        while (tmp != null) {
            System.out.print(tmp.value + " ");
            tmp = tmp.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        SelfOrganizingList s = new SelfOrganizingList();
        for (int i = 1; i < 6; i++) {
            s.insert(i);
        }

        s.printList();

        s.search(3);
        s.search(5);
        s.search(5);
        s.search(4);
        s.search(4);
        s.search(4);
        s.printList();
        String d = "";
    }
}
