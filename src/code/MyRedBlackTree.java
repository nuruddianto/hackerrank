package code;

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
            this.color = "red";
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
        if(h != null && isDoubleRedProblem(h)){
            if(isRed(getParent(h)) && isRed(getSibling(getParent(h)))){
                recolor(h);
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
            if(h == h.parent.left){
                Node sibling = h.parent.right;
                if(isRed(sibling)){
                    sibling.color = BLACK;
                    h.parent.color = RED;
                    rotateLeft(h.parent);
                    sibling = rightOf(h.parent);
                }

                if(!isRed(sibling.left) && !isRed(sibling.right)){
                    sibling.color = RED;
                    h = h.parent;
                }else{
                    if(!isRed(sibling.right)){
                        sibling.left.color = BLACK;
                        sibling.color = RED;
                        rotateRight(sibling);
                        sibling = h.parent.left;
                        h = (Node) root;
                    }
                }
            }else{
                Node sibling = h.parent.left;
                if(isRed(sibling)){
                    sibling.color = BLACK;
                    h.parent.color = RED;
                    rotateRight(h.parent);
                    sibling = leftOf(h.parent);
                }

                if(!isRed(sibling.left) && !isRed(sibling.right)){
                    sibling.color = RED;
                    h = h.parent;
                }else{
                    if(!isRed(h.left)){
                        sibling.right.color = BLACK;
                        sibling.color = RED;
                        rotateLeft(sibling);
                        sibling = h.parent.right;
                        h = (Node) root;
                    }
                }
            }
        }
        h.color = BLACK;
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
        } else {
            c.parent.right = oldRight;
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
        } else {
            c.parent.right = oldLeft;
        }
        oldLeft.right = c;
        c.parent = oldLeft;
    }


    private void recolor(Node h) {
        h.parent.color = BLACK;
        getSibling(h.parent).color = BLACK;
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
        MyRedBlackTree m = new MyRedBlackTree();
        m.insert(10);
        m.insert(20);
        m.insert(30);
        m.insert(15);
        m.insert(40);
        m.insert(50);

        Node s = m.root;
        String b = "";
    }
}
