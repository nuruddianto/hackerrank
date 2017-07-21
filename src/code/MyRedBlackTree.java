package code;

import com.sun.org.apache.regexp.internal.RE;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Created by Nuruddianto on 4/6/2017.
 */
public class MyRedBlackTree {
    private class Node{
        Node left,right, parent;
        int value;
        String color;

        public Node(int value) {
            this.value = value;
            this.color = RED;
        }
    }

    final private String RED = "red";
    final private String BLACK = "black";

    Node root;

    /*Search*/
    private Node search(Node node, int value){
        if(node == null){
            return node;
        }
        int comparison = value - node.value;

        if(comparison > 0){
            return search(node.right, value);
        }else if(comparison < 0){
            return search(node.left, value);
        }
        return node;
    }

    /*Insert*/
    private void insert(int newValue){
        if(root == null){
            root = new Node(newValue);
            return;
        }

        Node h = root;
        while (true){
            int comparison = newValue - h.value;
            if(comparison == 0){
                h.value = newValue;
            }else if(comparison < 0){
                if(h.left == null){
                    h.left = new Node(newValue);
                    h.left.parent = h;
                    letsBalancing(h.left);
                    break;
                }
                h = h.left;
            }else if(comparison > 0){
                if(h.right == null){
                    h.right = new Node(newValue);
                    h.right.parent = h;
                    letsBalancing(h.right);
                    break;
                }
                h = h.right;
            }
        }
    }

    /*Delete*/
    private void delete(int deletedValue){
        Node node = search(root, deletedValue);
        if(node == null){
            return;
        }else if(node.left != null && node.right != null){
            //Node has two children
            Node predecessor = predecessor(node);
            node.value = predecessor.value;
            node = (Node) predecessor;
        }

        //if node only has one child
        Node upNode = node.left == null? node.right : node.left;
        if(upNode != null){
            //check if there is double black problem
            if(node == root){
                root = upNode;
            }else if(node.parent.left == node){
                node.parent.left = upNode;
            }else{
                node.parent.right = upNode;
            }
        }else if(node == root){
            root = null;
        }else{
            if(!isRed(node)){
                letsBalancingDelete(node);
            }
            removeParentNode(node);
        }
    }


    private Node predecessor(Node n){
        Node leftNode = n.left;
        if(n != null){
            while(n.right != null){
                n = n.right;
            }
        }
        return n;
    }

    private void letsBalancing(Node h) {
        if(h != null && h != root && isDoubleRedProblem(h)){
            if( isRed(getSibling(getParent(h)))){
                recolor(h);
                letsBalancing(getGrandParent(h));
            }else if(getParent(h) == rightOf(getGrandParent(h))){
                if(h == leftOf(getParent(h))){
                    rotateRight(h = getParent(h));
                }
                getParent(h).color = BLACK;
                getGrandParent(h).color = RED;
                rotateLeft(getGrandParent(h));
            }else if(getParent(h) == leftOf(getGrandParent(h))){
                if(h == rightOf(getParent(h))){
                    rotateLeft(h = getParent(h));
                }
                getParent(h).color = BLACK;
                getGrandParent(h).color = RED;
                rotateRight(getGrandParent(h));
            }
        }
        root.color = BLACK;
    }

    private void letsBalancingDelete(Node h){
        while (h != root && !isRed(h)){
            if(h == leftOf(h.parent)){
                Node sibling = rightOf(h.parent);

                if(isRed(sibling)){
                    setColor(sibling, BLACK);
                    setColor(h.parent, RED);
                    rotateLeft(h.parent);
                    sibling = rightOf(h.parent);
                }

                if(!isRed(leftOf(sibling)) && !isRed(rightOf(sibling))){
                    setColor(sibling, RED);
                    h = h.parent;
                }else{
                    if(!isRed(rightOf(sibling))){
                        setColor(leftOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateRight(sibling);
                        sibling = rightOf(h.parent);
                    }
                    setColor(sibling, h.parent.color);
                    setColor(h.parent, BLACK);
                    setColor(rightOf(sibling), BLACK);
                    rotateLeft(h.parent);
                    h = (Node) root;
                }
            }else{
                Node sibling = leftOf(h.parent);
                if(isRed(sibling)){
                    setColor(sibling, BLACK);
                    setColor(h.parent, RED);
                    rotateRight(h.parent);
                    sibling = leftOf(h.parent);
                }

                if(!isRed( leftOf(sibling)) && !isRed( rightOf(sibling))){
                    setColor(sibling, RED);
                    h = h.parent;
                }else{
                    if(!isRed(leftOf(h))){
                        setColor(rightOf(sibling), BLACK);
                        setColor(sibling, RED);
                        rotateLeft(sibling);
                        sibling = leftOf(h.parent);
                    }
                    setColor(sibling, h.parent.color);
                    setColor(h.parent, BLACK);
                    setColor(leftOf(sibling), BLACK);
                    rotateRight(h.parent);
                    h = (Node) root;
                }
            }
        }
        setColor(h, BLACK);
    }

    private void removeParentNode(Node n){
        if( n != null){
            if(n.parent.left == n){
                n.parent.left = null;
            }else if(n.parent.right == n){
                n.parent.right = null;
            }
            n.parent = null;
        }
    }

    protected void rotateLeft(Node c) {
        if (c.right == null) {
            return;
        }
        Node oldRight = c.right;
        c.right = oldRight.left;
        if (c.parent == null) {
            root = oldRight;
            oldRight.parent = null;
        } else if (c.parent.left == c) {
            c.parent.left = oldRight;
            oldRight.parent = c.parent;
        } else {
            c.parent.right = oldRight;
            oldRight.parent = c.parent;
        }
        oldRight.left = c;
        c.parent = oldRight;
    }


    protected void rotateRight(Node c) {
        if (c.left == null) {
            return;
        }
        Node oldLeft = c.left;
        c.left = oldLeft.right;
        if (c.parent == null) {
            root = oldLeft;
            oldLeft.parent = null;
        } else if (c.parent.left == c) {
            c.parent.left = oldLeft;
            oldLeft.parent = c.parent;
        } else {
            c.parent.right = oldLeft;
            oldLeft.parent = c.parent;
        }
        oldLeft.right = c;
        c.parent = oldLeft;
    }


    private void recolor(Node h) {
        h.parent.color = BLACK;
        getSibling(h.parent).color = BLACK;
        getGrandParent(h).color = RED;
    }

    private boolean isDoubleRedProblem(Node h){
        return h.color == RED && h.parent.color == RED;
    }

    private Node getSibling(Node h){
        return h == null || h.parent == null ? null : h == h.parent.left ? h.parent.right : h.parent.left;
    }

    private Node getGrandParent(Node h){
        return h.parent == null ? null : h.parent.parent == null ? null : h.parent.parent;
    }

    private void setColor(Node n, String c) {
        if (n != null)
            n.color = c;
    }

    private Node getParent(Node h){
        return h.parent == null ? null : h.parent;
    }

    private boolean isRed(Node h){
        return h != null && h.color == "red";
    }
    
    private Node rightOf(Node h){
        return h == null ? null : h.right;
    }
    
    private Node leftOf(Node h){
        return h == null ? null : h.left;
    }

    public static void main(String[] args){
        MyRedBlackTree tree = new MyRedBlackTree();

        /*Insert Test Case*/
        tree.insert(20);
        tree.insert(15);
        tree.insert(25);
        tree.insert(10);
        tree.insert(17);
        tree.insert(8);
        tree.insert(9);
        tree.delete(15);
        tree.delete(20);

        Node s = tree.root;
        String b = "";
    }

    @Test
    public void testCase() {
        MyRedBlackTree tree = new MyRedBlackTree();

        /*Test Insert*/
        tree.insert(20);
        tree.insert(15);
        tree.insert(25);
        tree.insert(10); // re color 15 and 25 to black on this insert
        assertEquals((tree.root).color, tree.BLACK);
        assertEquals( (tree.search(tree.root, 15)).color, tree.BLACK);
        assertEquals((tree.search(tree.root, 25)).color, tree.BLACK);
        tree.insert(17);
        tree.insert(8);
        assertEquals((tree.search(tree.root,15)).color, tree.RED);
        assertEquals((tree.search(tree.root,10)).color, tree.BLACK);
        assertEquals((tree.search(tree.root,17)).color, tree.BLACK);
        assertEquals((tree.search(tree.root,8)).color, tree.RED);
        tree.insert(9); // case 2/3 - rotation right, then left
        assertEquals((tree.search(tree.root,10)).color, tree.RED);
        assertEquals((tree.search(tree.root,8)).color, tree.RED);
        assertEquals( tree.search(tree.root,9).left.value, 8);

        /*Test Delete*/
        tree.delete(15);
        assertEquals(tree.search(tree.root,10).left.value, 9);
        assertEquals(tree.search(tree.root,10).left.color, BLACK);
        assertEquals(tree.search(tree.root,10).color, RED);

        tree.delete(10);
        assertEquals(tree.search(tree.root,9).color, tree.RED);
        assertEquals(tree.search(tree.root,9).left.color, tree.BLACK);
    }
}
