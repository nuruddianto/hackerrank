package code.srin;

/**
 * Created by SRIN on 3/14/2017.
 */

import java.util.Scanner;

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
            return totalSize+infectedSize+size;
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

    private Bst bst;

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

        Child tmp = child;
        File parentTmp = fileToDelete.parent;
        int sizeToRemove = fileToDelete.totalSize == 0 ? fileToDelete.size : fileToDelete.totalSize;
        while(parentTmp.id != 10000){
        	parentTmp.totalSize -= sizeToRemove;
        	parentTmp.totalFileChildFromRoot -= 1;
        	parentTmp = parentTmp.parent;
        }
        
        parentTmp.totalSize -= sizeToRemove;
    	parentTmp.totalFileChildFromRoot -= 1;
    	
    	if(fileToDelete.size != 0){
    		fileToDelete.parent.totalFileChild -= 1;
    	}
    	

        while (tmp != null && tmp.file.id != fileToDelete.id) {
            tmp = tmp.next;
        }
        
        if(tmp.previous == null && tmp.next == null){
        	tmp = null;
        	return;
        }
        if(tmp.previous == null){
        	tmp = tmp.next;
        	tmp.previous = null;
        }else if(tmp.next == null){
        	tmp = tmp.previous;
        	tmp.next = null;
        }else{
        	tmp.next.previous = tmp.previous;
        	tmp.previous.next = tmp.next;
        }
    }

    public void init() {
    	File parent = new File(10000, 0, 0);
        bst = insertBst(bst, parent);
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
        if(newFile.size != 0){
            File parentTmp = parent;
            while (parentTmp.id != 10000){
                parentTmp.totalFileChildFromRoot += 1;
                parentTmp.totalSize += fileSize;
                parentTmp = parentTmp.parent;
            }
            parentTmp.totalSize += fileSize;
            parentTmp.totalFileChildFromRoot += 1;
            parent.totalFileChild += 1;
        }

        newFile.parent = parent;

        parent.child = addChildList(parent.child, newFile);
        int totalSize = parent.totalSize;
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
        int realSizeToMove = fileToMove.totalSize == 0 ? fileToMove.size : fileToMove.totalSize;
        int realTotalFileChild = fileToMove.totalFileChild == 0 ? 1 : fileToMove.totalFileChild ;
        int realTotalFileChildFromRoot = fileToMove.totalFileChildFromRoot == 0 ? 1 : fileToMove.totalFileChildFromRoot;

        File parentFile = fileToMove.parent;
        fileToMove.parent.child = removeObjectForMove(fileToMove.parent.child, fileToMove);
        while(parentFile != null){
            //remove all type size, totalChild && totalChildFromRRoot from parent
            parentFile.totalFileChild -= realTotalFileChild;
            parentFile.totalFileChildFromRoot -= realTotalFileChildFromRoot;
            parentFile.totalSize -= realSizeToMove;
            parentFile.infectedSize -= fileToMove.infectedSize;
            parentFile = parentFile.parent;
        }

        addObjectForMOve(fileToMove, parent);
        fileToMove.parent = parent;

        File newParentFile = parent;

        while(newParentFile != null){
            //add all type size, totalChild && totalChildFromRoot to new parent
            newParentFile.totalFileChild += realTotalFileChild;
            newParentFile.totalFileChildFromRoot += realTotalFileChildFromRoot;
            newParentFile.totalSize += realSizeToMove;
            newParentFile.infectedSize += fileToMove.infectedSize;
            newParentFile = newParentFile.parent;
        }

        return parent.getFileSize();
    }

    public void addObjectForMOve(File fileToMove, File parent) {
        fileToMove.parent = parent;
        parent.child = addChildList(parent.child, fileToMove);
    }

    private Child removeObjectForMove(Child child, File fileToDelete) {
        if (child == null || fileToDelete == null) {
            return null;
        }

        Child tmp = child;

        while (tmp != null && tmp.file.id != fileToDelete.id) {
            tmp = tmp.next;
        }


        if(tmp.previous == null){
            child = tmp.next;
            child.previous = null;
        }else if(tmp.next == null){
            tmp = tmp.previous;
            tmp.next = null;
        }else{
            tmp.next.previous = tmp.previous;
            tmp.previous.next = tmp.next;
        }
        return child;
    }


    public int infect(int id) {
        File fileToInfect = searchBst(bst, id);

        int totalFileToInfect = fileToInfect.parent.totalFileChild;
        int totalFileFromRoot = fileToInfect.parent.totalFileChildFromRoot;
        
        int infectedSize = fileToInfect.parent.getFileSize() / totalFileToInfect / totalFileFromRoot;
        
        /*add infected size to parent*/
        File tmpParent = fileToInfect.parent;
        int infextedSizeForParent = fileToInfect.totalFileChildFromRoot == 0 ? infectedSize :fileToInfect.totalFileChildFromRoot * infectedSize;
        while(tmpParent != null){
        	tmpParent.infectedSize += infextedSizeForParent;
        	tmpParent = tmpParent.parent;
        }
        
        /*add infected size to child*/
        traverseFile(fileToInfect, infectedSize);
        
        return fileToInfect.getFileSize();
    }
    
    private void traverseFile(File fileToInfected, int infectedSize){
    	if(fileToInfected != null){
    		//infected for directory
    		if(fileToInfected.totalFileChildFromRoot != 0){
    			int totalInfectedSize = fileToInfected.totalFileChildFromRoot * infectedSize;
    			fileToInfected.setInfectedSize(totalInfectedSize);
    			
    			/*loop child*/
    			Child tmpChild = fileToInfected.child;
    			while(tmpChild.next != null){
    				traverseFile(tmpChild.next.file, infectedSize);
    				tmpChild = tmpChild.next;
    			}   			
    		}else{
    			fileToInfected.setInfectedSize(infectedSize);
    		}
    	}
    }

    public int recover(int id) {
    	File fileToRecover = searchBst(bst, id);
    	int recoverFileSize = fileToRecover.infectedSize;
    	
    	File tmpFileParent = fileToRecover;
    	while(tmpFileParent != null){
    		tmpFileParent.infectedSize -= recoverFileSize;
    		tmpFileParent = tmpFileParent.parent;
    	}
    	
    	traverseFile(fileToRecover, 0);
        return fileToRecover.getFileSize();
    }

    public int remove(int id) {
    	File fileToRemove = searchBst(bst, id);
    	removeChildFromList(fileToRemove.parent.child, fileToRemove);
        return fileToRemove.getFileSize();
    }
    
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
            if(ret == checkSum){ 
            	score++;
            }else{
            	System.out.println("failed in command :" + cmd);
            }
        }
        return score;
    }

    public static void main(String arg[]) {
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

/*
Sample Test Case
1
15
1 10001 10000 0 0
1 10002 10000 300 300
1 10003 10000 0 300
1 20001 10001 200 200
1 20002 10001 100 300
1 30001 10003 0 0
1 40001 30001 240 240
2 20002 30001 340
2 10001 10003 540
3 10002 510
3 10003 1326
4 10001 200
4 20002 100
5 10002 510
5 10001 200

Only add Test Case
1
9
1 10001 10000 0 0
1 10002 10000 300 300
1 10003 10000 0 300
1 20001 10001 200 200
1 20002 10001 100 300
1 30001 10003 0 0
1 40001 30001 240 240
2 20002 30001 340
2 10001 10003 540
*/

