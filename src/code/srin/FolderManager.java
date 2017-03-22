package code.srin;

/**
 * Created by SRIN on 3/14/2017.
 */

import java.util.Scanner;

class Solution {
    private static final int CMD_ADD = 1;
    private static final int CMD_MOVE = 2;
    private static final int CMD_INFECT = 3;
    private static final int CMD_RECOVER = 4;
    private static final int CMD_REMOVE = 5;

    private static Scanner sc;
    private static FolderManager userSolution = new FolderManager();

    private static int run() {
        int score = 0;
        int N = Integer.parseInt(sc.next());

        for(int i=0; i<N; i++) {
            int cmd = Integer.parseInt(sc.next());
            int ret = 0;

            switch(cmd) {
                case CMD_ADD: {
                    int id = Integer.parseInt(sc.next());
                    int pid = Integer.parseInt(sc.next());
                    int fileSize = Integer.parseInt(sc.next());
                    ret = userSolution.add(id, pid, fileSize);
                    break;
                }
                case CMD_MOVE: {
                    int id = Integer.parseInt(sc.next());
                    int pid = Integer.parseInt(sc.next());
                    ret = userSolution.move(id, pid);
                    break;
                }
                case CMD_INFECT: {
                    int id = Integer.parseInt(sc.next());
                    ret = userSolution.infect(id);
                    break;
                }
                case CMD_RECOVER: {
                    int id = Integer.parseInt(sc.next());
                    ret = userSolution.recover(id);
                    break;
                }
                case CMD_REMOVE: {
                    int id = Integer.parseInt(sc.next());
                    ret = userSolution.remove(id);
                    break;
                }
            }

            int checkSum = Integer.parseInt(sc.next());
            if(ret == checkSum) score++;
        }
        return score;
    }

    public static void main(String arg[]) throws Exception {
        //System.setIn(new java.io.FileInputStream("res/sample_input.txt"));
        sc = new Scanner(System.in);

        int totalScore = 0;

        int T = sc.nextInt();
        for(int t=1; t<=T; t++) {
            userSolution.init();
            int score = run();
            System.out.println("#" + t + " " + score);
            totalScore += score;
        }
        sc.close();
        System.out.println("Total Score : " + totalScore);
    }
}

public class FolderManager {

    private class File {
        int id;
        int pid;
        File parent;
        Child child;
        int totalFileChild;
        int totalSize;
        int size;
        int infectedSize;
        int totalFileChildFromRoot;

        public File(int id, int pid, int size) {
            this.id = id;
            this.pid = pid;
            this.size = size;
            totalFileChild = 0;
        }

        public void setInfectedSize(int infectedSize) {
            this.infectedSize = infectedSize;
        }

        public int getFileSize(){
            return totalSize+infectedSize;
        }
    }

    private class Child {
        Child next;
        Child previous;
        File file;

        public Child(File file) {
            this.file = file;
        }
    }

    private class Bst {
        Bst right;
        Bst left;
        File file;

        public Bst(File file) {
            this.file = file;
        }
    }

    Bst bst;

    private Bst insertBst(Bst bst, File file) {
        if (bst == null) {
            bst = new Bst(file);
            return bst;
        }

        if (file.id > bst.file.id) {
            bst.right = insertBst(bst.right, file);
        } else {
            bst.left = insertBst(bst.left, file);
        }

        return bst;
    }

    private File searchBst(Bst bst, int id) {
        if (bst == null) {
            return null;
        }

        if (bst.file.id < id) {
            return searchBst(bst.right, id);
        } else if (bst.file.id > id) {
            return searchBst(bst.left, id);
        }

        return bst.file;
    }

    private Child addChildList(Child head, File newFile) {
        Child newChild = new Child(newFile);
        newChild.previous = null;

        newChild.next = head;
        if (head != null) {
            head.previous = newChild;
        }
        head = newChild;
        return head;
    }

    private void removeChildFromList(Child child, File fileToDelete) {
        if (child == null || fileToDelete == null) {
            return;
        }

        Child tmpLeft = child;
        Child tmpRight = child;

        Child childToDelete = null;
        while (tmpLeft != null) {
            if (tmpLeft.file.id == fileToDelete.id) {
                childToDelete = tmpLeft;
                break;
            }
            tmpLeft = tmpLeft.previous;
        }

        if(childToDelete != null){
            while (tmpRight != null) {
                if (tmpRight.file.id == fileToDelete.id) {
                    childToDelete = tmpRight;
                    break;
                }
                tmpRight = tmpRight.next;
            }
        }

        if (childToDelete.previous != null) {
            childToDelete.previous.next = childToDelete.next;
        }

        if (childToDelete.next != null) {
            childToDelete.next.previous = child.previous;
        }

        childToDelete = null;
    }

    public void init() {
        bst = null;
    }

    /*
    File or directory corresponding to id is newling added to the pid directory.
    The id value is not overlapping with other id.

    Parameters
    id  : id of file or directory that is newly added.
    pid : pid of parent directory.
    fileSize : Size of the file that is newly added (greater than 0). If 0 then is a directory.

    Returns
    After file or directory is added, return the size of the corresponding pid
            (return the total size of pid's subordinate directories and files)
    */
    public int add(int id, int pid, int fileSize) {
        File newFile = new File(id, pid, fileSize);
        bst = insertBst(bst, newFile);

        File parent = searchBst(bst, pid);
        if(parent == null){
            parent = new File(0,0,0);
            newFile.parent = parent;
            return fileSize;
        }

        if(newFile.size != 0){
            File parentTmp = parent;
            while (parentTmp.id != 0){
                parentTmp.totalFileChildFromRoot += 1;
                parentTmp = parent.parent;
            }
            parent.totalFileChild += 1;
        }

        newFile.parent = parent;


        addChildList(parent.child, newFile);
        int totalSize = parent.totalSize + fileSize;
        parent.totalSize = totalSize;
        return totalSize;
    }

    /*
    File or directory corresponding to id is moved below the pid directory.
    In the move command, a pid that is the subordinate directory of the id will not be given.

    Parameters
    id  : id of file or directory that is to be moved.
    pid : id of becoming parent directory.

    Returns
    After file or directory is moved, return the size of the corresponding pid
            (return the total size of pid's subordinate directories and files)
    */
    public int move(int id, int pid) {
        File fileToMove = searchBst(bst, id);
        File parent = searchBst(bst, pid);

        File tmp = fileToMove;
        removeChildFromList(fileToMove.parent.child, fileToMove);
        addChildList(parent.child, tmp);

        return add(id, parent.id, fileToMove.totalSize);
    }

    public int infect(int id) {
        File fileToInfect = searchBst(bst, id);
        File tmp = fileToInfect;

        int totalFileToInfect = fileToInfect.parent.totalFileChild;
        int infectedSize = fileToInfect.totalSize / totalFileToInfect / fileToInfect.parent.totalFileChildFromRoot;

        Child tmpInfected = fileToInfect.parent.child;
        while(tmpInfected != null){
            if(tmp.size != 0){
                tmp.setInfectedSize(infectedSize);
            }
            tmpInfected = tmpInfected.next;
        }

        return fileToInfect.getFileSize();
    }

    public int recover(int id) {
        return -1;
    }

    public int remove(int id) {
        return -1;
    }
}
