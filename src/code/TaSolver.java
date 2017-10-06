package code;

import java.util.*;

/**
 * Created by SRIN on 10/5/2017.
 */
public class TaSolver {

    private static List<Ta> mListTa;
    private static Queue<Ta> mAnswer;
    private static boolean[][] mVisited;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        mListTa = new LinkedList<>();
        mAnswer = new LinkedList<>();

        List<Integer> subjects = new ArrayList<>();

        //Initiate Ta
        Ta Soba = new Ta("Soba", 2, new ArrayList<>(Arrays.asList(1, 3)));
        Ta Udon = new Ta("Udon", 1, new ArrayList<>(Arrays.asList(3, 4)));
        Ta Ramen = new Ta("Ramen", 1, new ArrayList<>(Arrays.asList(2)));

        mListTa.add(Udon);
        mListTa.add(Soba);
        mListTa.add(Ramen);

        int totalSubject = sc.nextInt();
        mVisited = new boolean[mListTa.size()][100];

        for (int i = 0; i < totalSubject; i++) {
            subjects.add(sc.nextInt());
        }
        Queue<Ta> answer = new LinkedList<>();
        findSubject(0, subjects, cloneList(mListTa), answer);
        String s = "";
    }

    public static void findSubject(int index, List<Integer> subjects, List<Ta> listTa, Queue<Ta> answer){
        if(answer.size() == subjects.size()){
            Queue<Ta> cloneAnswer = cloneQueue(answer);
            if(isAnswerValid(cloneAnswer)){
                mAnswer = answer;
                return;
            }
        }

        if(index >= subjects.size() || index < 0){
            return;
        }
        Ta current = null;
        int subject = subjects.get(index);
        for(int i=0 ; i < listTa.size(); i++){
            current = listTa.get(i);
            if(isValid(subject, current ) && !mVisited[i][subject]){
                mVisited[i][subject] = true;
                answer.add(mListTa.get(i));
                findSubject(index += 1, subjects, listTa, answer);
            }
            mVisited[i][subject] = false;
        }
        if(answer.size() > 0){
            answer.poll();
        }
        findSubject(index-1, subjects, listTa, answer);
    }

    public static List<Ta> cloneList(List<Ta> listToClone) {
        List<Ta> clone = new ArrayList<>(listToClone.size());
        for (Ta item : listToClone) {
            clone.add(new Ta(item.mName, item.mMax, item.mAvail));
        }
        return clone;
    }

    public static Queue<Ta> cloneQueue(Queue<Ta> listToClone) {
        Queue<Ta> clone = new LinkedList<>();
        for (Ta item : listToClone) {
            clone.add(new Ta(item.mName, item.mMax, item.mAvail));
        }
        return clone;
    }

    private static boolean isValid(int subject, Ta ta) {
        return ta.getmAvail().contains(subject) && ta.getmMax() > 0;
    }

    private static boolean isAnswerValid(Queue<Ta> answers){
        List<Ta> cloneTa = cloneList(mListTa);
        for(Ta answer : answers){
            for(Ta ta : cloneTa){
                if(ta.getmName() == answer.getmName()){
                    if(ta.getmMax() <= 0){
                        return false;
                    }

                    ta.setmMax(ta.getmMax()-1);
                }
            }
        }
        return true;
    }

    private static class Ta {
        String mName;
        int mMax;
        List<Integer> mAvail;

        public Ta(String mName, int mMax, List<Integer> mAvail) {
            this.mName = mName;
            this.mMax = mMax;
            this.mAvail = mAvail;
        }

        public String getmName() {
            return mName;
        }

        public void setmName(String mName) {
            this.mName = mName;
        }

        public int getmMax() {
            return mMax;
        }

        public void setmMax(int mMax) {
            this.mMax = mMax;
        }

        public List<Integer> getmAvail() {
            return mAvail;
        }

        public void setmAvail(List<Integer> mAvail) {
            this.mAvail = mAvail;
        }
    }
}
