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
        /*Ta Soba = new Ta("Soba", 2, new ArrayList<>(Arrays.asList(1, 3)));
        Ta Udon = new Ta("Udon", 1, new ArrayList<>(Arrays.asList(3, 4)));
        Ta Ramen = new Ta("Ramen", 1, new ArrayList<>(Arrays.asList(2)));

        mListTa.add(Udon);
        mListTa.add(Soba);
        mListTa.add(Ramen);*/


        Ta Erika = new Ta("Erika", 1, new ArrayList<>(Arrays.asList(1, 3, 7, 9)));
        Ta Ryan = new Ta("Ryan", 1, new ArrayList<>(Arrays.asList(1, 8, 10)));
        Ta Reece = new Ta("Reece", 1, new ArrayList<>(Arrays.asList(5, 6)));
        Ta Gordon = new Ta("Gordon", 2, new ArrayList<>(Arrays.asList(2, 3, 9)));
        Ta David = new Ta("David", 2, new ArrayList<>(Arrays.asList(2, 8, 9)));
        Ta Katie = new Ta("Katie", 1, new ArrayList<>(Arrays.asList(4, 6)));
        Ta Aashish = new Ta("Aashish", 2, new ArrayList<>(Arrays.asList(1, 10)));
        Ta Grant = new Ta("Grant", 2, new ArrayList<>(Arrays.asList(1, 11)));
        Ta Raeanne = new Ta("Raeanne", 2, new ArrayList<>(Arrays.asList(1, 11, 12)));

        Ta Alex = new Ta("Alex", 1, new ArrayList<>(Arrays.asList(4)));
        Ta Erin = new Ta("Erin", 1, new ArrayList<>(Arrays.asList(4)));


        mListTa.add(Erika);
        mListTa.add(Ryan);
        mListTa.add(Reece);
        mListTa.add(Gordon);
        mListTa.add(David);
        mListTa.add(Katie);
        mListTa.add(Aashish);
        mListTa.add(Grant);
        mListTa.add(Raeanne);
        mListTa.add(Alex);

        int totalSubject = sc.nextInt();
        mVisited = new boolean[mListTa.size()][100];

        for (int i = 0; i < totalSubject; i++) {
            subjects.add(sc.nextInt());
        }
        Queue<Ta> answer = new LinkedList<>();


        findSubject(0, subjects, cloneList(mListTa), answer);
        String s = "";
    }

    public static void findSubject(int index, List<Integer> subjects, List<Ta> listTa, Queue<Ta> answer) {
        if (answer.size() == subjects.size()) {
            Queue<Ta> cloneAnswer = cloneQueue(answer);
            print(answer);
            if (isAnswerValid(cloneAnswer)) {
                mAnswer = answer;
                return;
            }
        }

        if (mAnswer.size() > 0) {
            return;
        }

        if (index >= subjects.size() || index < 0) {
            return;
        }

        int subject = subjects.get(index);
        for (int i = 0; i < listTa.size() && mAnswer.size() == 0; i++) {
            Ta current = listTa.get(i);
            if (isValid(subject, current) && !mVisited[i][subject]) {

                mVisited[i][subject] = true;
                findSubject(index, subjects, listTa, answer);

                mVisited[i][subject] = false;
                answer.add(mListTa.get(i));
                findSubject(index += 1, subjects, listTa, answer);
            }
        }

    }

    public static List<Ta> cloneList(List<Ta> listToClone) {
        List<Ta> clone = new ArrayList<>(listToClone.size());
        for (Ta item : listToClone) {
            clone.add(new Ta(item.mName, item.mMax, item.mAvail));
        }
        return clone;
    }

    public static void print(Queue<Ta> tas){
        for (Ta ta: tas){
            System.out.print(ta.getmName()+" ");
        }
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

    private static boolean isAnswerValid(Queue<Ta> answers) {
        List<Ta> cloneTa = cloneList(mListTa);
        for (Ta answer : answers) {
            for (Ta ta : cloneTa) {
                if (ta.getmName() == answer.getmName()) {
                    if (ta.getmMax() <= 0) {
                        return false;
                    }

                    ta.setmMax(ta.getmMax() - 1);
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


/*
12
        1 2 3 4 5 6 7 8 9 10 11 12
        */

/*
4
1 2 3 4
*/
