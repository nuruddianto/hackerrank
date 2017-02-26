package code.srin;

import java.util.Scanner;

/**
 * Created by SRIN on 2/24/2017.
 */
public class TestApi {

    private static class Name {
        Name right;
        Name left;
        char[] name;
        int indexCounter;
    }

    public static class Number {
        Number right;
        Number left;
        char[] number;
        int indexCounter;
    }

    public static class Birthday {
        Birthday right;
        Birthday left;
        char[] birthday;
        int indexCounter;
    }

    public static class Email {
        Email right;
        Email left;
        char[] email;
        int indexCounter;
    }

    public static class Memo {
        Memo right;
        Memo left;
        char[] memo;
        int indexCounter;
    }

    public static int index;
    public static int count;
    public static String data[][];
    public static Name nameNode;

    private static void InitDB() {
        data = new String[50001][5];
        nameNode = null;
        return;
    }

    /*==============================================insert===================================================================================*/
    private static void Add(char[] name2, char[] number2, char[] birthday2, char[] email2, char[] memo2) {
        Name l = nameNode;
        nameNode = insertName(nameNode, name2);
//        insertNumber(numberNode, number2);
//        insertBirthday(birthdayNode, birthday2);
//        insertEmail(emailNode, email2);
//        insertMemo(memoNode,memo2);

        index++;
    }

    private static Name insertName(Name l, char[] name) {
        if(l == null){
            l = new Name();
            l.name = name;
            return l;
        }

        int compare = isNewBigger(l.name, name);
        if (compare == 1 || compare == 2 ) {
            l.right = insertName(l.right, name);
        } else {
            l.left = insertName(l.left, name);
        }

        return l;
    }

    private static Number insertNumber(Number l, char[] number) {
        if (l == null || index == 0) {
            if (index != 0) {
                l = new Number();
                l.indexCounter = index;
            }
            l.number = number;
            return l;
        }

        int compare = isNewBigger(l.number, number);
        if (compare == 1 || compare == 2 ) {
            l.right = insertNumber(l.right, number);
        } else {
            l.left = insertNumber(l.left, number);
        }

        return l;
    }

    private static Birthday insertBirthday(Birthday l, char[] birthday) {
        if (l == null || index == 0) {
            if (index != 0) {
                l = new Birthday();
                l.indexCounter = index;
            }
            l.birthday = birthday;
            return l;
        }

        int compare = isNewBigger(l.birthday, birthday);
        if (compare == 1 || compare == 2 ) {
            l.right = insertBirthday(l.right, birthday);
        } else {
            l.left = insertBirthday(l.left, birthday);
        }

        return l;
    }

    private static Email insertEmail(Email l, char[] email) {
        if (l == null || index == 0) {
            if (index != 0) {
                l = new Email();
                l.indexCounter = index;
            }
            l.email = email;
            return l;
        }

        int compare = isNewBigger(l.email, email);
        if (compare == 1 || compare == 2 ) {
            l.right = insertEmail(l.right, email);
        } else {
            l.left = insertEmail(l.left, email);
        }

        return l;
    }

    private static Memo insertMemo(Memo l, char[] memo) {
        if (l == null || index == 0) {
            if (index != 0) {
                l = new Memo();
                l.indexCounter = index;
            }
            l.memo = memo;
            return l;
        }

        int compare = isNewBigger(l.memo, memo);
        if (compare == 1 || compare == 2 ) {
            l.right = insertMemo(l.right, memo);
        } else {
            l.left = insertMemo(l.left, memo);
        }

        return l;
    }

    /*===========================================================Search=======================================================*/
    private static RESULT Search(int field, char[] str, int returnfield) {
        RESULT result = new RESULT();
        result.count = 1;
        result.str = "null".toCharArray();

        return result;
    }

    private int searchName(Name l, char[] name, int count) {
        if (l == null) {
            return count;
        }

        int compare = isNewBigger(l.name, name);

        if ( compare == 2) {
            return searchName(l.right, name, count + 1);
        }else if (compare == 1) {
            return searchName(l.right, name, count);
        } else if (compare == 3) {
            return searchName(l.left, name, count);
        }

        return count;
    }
    /*===========================================================MinVal=======================================================*/
    private Name minValueName(Name l){
        Name current = l;
        while(current.left != null){
            current = current.left;
        }
        return current;
    }

    /*===========================================================Delete=======================================================*/
    private static int Delete(int field, char[] str) {

        return 0;
    }

    private Name deleteName(Name l, char[] name){
        if(l == null){
            return l;
        }

        int compare = isNewBigger(l.name, name);
        if(compare == 1){
            l.right = deleteName(l.right, name);
        }else if(compare == 3){
            l.left = deleteName(l.left, name);
        }else{
            count++;
            if(l.left == null){
                l = l.right;
                return deleteName(l,name);
            }else if(l.right == null){
                l =  l.left;
                deleteName(l,name);
                return deleteName(l,name);
            }

            Name tmp = minValueName(l.right);
            l.name = tmp.name;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteName(l.right, tmp.name);
        }
        return l;
    }


    /*===========================================================Change=======================================================*/
    private static int Change(int field, char[] str, int changefield, char[] changestr) {

        return 0;
    }

    private Name changeName(Name l, char[] oldName, char[] newName) {
        l = deleteName(l, oldName);
        for(int i=0; i < count; i++){
            l = insertName(l, newName);
        }
        return l;
    }

    /*
    1 - if new data is bigger
    2 - if new data is equal
    3 - if new data is smaller
    */
    private static int isNewBigger(char[] currentString, char[] newString) {
        int lengthCurr = 0;
        if (currentString != null){
            lengthCurr = currentString.length;
        }
        int lengthNew = 0;
        if(newString != null){
            lengthNew = newString.length;
        }

        int i = min(lengthCurr, lengthNew);
        for (int k = 0; k < i; k++) {
            if (newString[k] > currentString[k]) {
                return 1;
            } else if (newString[k] < currentString[k]) {
                return 3;
            }
        }

        if (lengthCurr == lengthNew) {
            return 2;
        } else if (lengthCurr < lengthNew) {
            return 1;
        }

        return 3;
    }

    private static int min(int a, int b) {
        return (a > b) ? b : a;
    }

    /*=====================================Main program==========================================================================*/
    private static final int CMD_INIT = 0;
    private static final int CMD_ADD = 1;
    private static final int CMD_DELETE = 2;
    private static final int CMD_CHANGE = 3;
    private static final int CMD_SEARCH = 4;

    static Scanner sc = new Scanner(System.in);

    static int [] dummy = new int[100];
    static int Score, ScoreIdx;
    static char[] name = new char[20], number= new char[20], birthday = new char[20], email = new char[20], memo = new char[20];

    static char[][] lastname = { "kim".toCharArray(), "lee".toCharArray(), "park".toCharArray(), "choi".toCharArray(), "jung".toCharArray(), "kang".toCharArray(), "cho".toCharArray(), "oh".toCharArray(), "jang".toCharArray(), "lim".toCharArray() };
    static int[] lastname_length = { 3, 3, 4, 4, 4, 4, 3, 2, 4, 3 };

    public static class RESULT
    {
        public int count;
        public char[] str = new char[20];
    };

    static int mSeed;
    static int mrand(int num)
    {
        mSeed = mSeed * 1103515245 + 37209;
        if (mSeed < 0) mSeed *= -1;
        return ((mSeed >> 8) % num);
    }

    static void make_field(int seed)
    {
        int name_length, email_length, memo_length;
        int idx, num;

        mSeed = (int)seed;

        name_length = 6 + mrand(10);
        email_length = 10 + mrand(10);
        memo_length = 5 + mrand(10);

        int a = 97;
        int zero = 48;
        num = mrand(10);
        for (idx = 0; idx < lastname_length[num]; idx++) name[idx] = lastname[num][idx];
        for (; idx < name_length; idx++) name[idx] = (char)(a + mrand(26));
        name[idx] = 0;

        for (idx = 0; idx < memo_length; idx++) memo[idx] = (char)(a + mrand(26));
        memo[idx] = 0;

        for (idx = 0; idx < email_length - 6; idx++) email[idx] = (char)(a + mrand(26));
        email[idx++] = '@';
        email[idx++] = (char)(a + mrand(26));
        email[idx++] = '.';
        email[idx++] = 'c';
        email[idx++] = 'o';
        email[idx++] = 'm';
        email[idx] = 0;

        idx = 0;
        number[idx++] = '0';
        number[idx++] = '1';
        number[idx++] = '0';
        for (; idx < 11; idx++) number[idx] = (char)(zero + mrand(10));
        number[idx] = 0;

        idx = 0;
        birthday[idx++] = '1';
        birthday[idx++] = '9';
        num = mrand(100);
        birthday[idx++] = (char) ('0' + num / 10);
        birthday[idx++] = (char) ('0' + num % 10);
        num = 1 + mrand(12);
        birthday[idx++] = (char) ('0' + num / 10);
        birthday[idx++] = (char) ('0' + num % 10);
        num = 1 + mrand(30);
        birthday[idx++] = (char) ('0' + num / 10);
        birthday[idx++] = (char) ('0' + num % 10);
        birthday[idx] = 0;
    }

    static void cmd_init()
    {
        ScoreIdx = sc.nextInt();

        InitDB();
    }

    static void cmd_add()
    {
        int seed;
        seed = sc.nextInt();

        make_field(seed);

        Add(name, number, birthday, email, memo);
    }

    static void cmd_delete()
    {
        int field, check, result;
        char[] str = new char[20];
        field  = sc.nextInt();
        str  = sc.next().toCharArray();
        check  = sc.nextInt();

        result = Delete(field, str);
        if (result != check) {
            Score -= ScoreIdx;
        }
    }

    static void cmd_change()
    {
        int field, changefield, check, result;
        char[] str = new char[20], changestr = new char[20];
        field  = sc.nextInt();
        str  = sc.next().toCharArray();
        changefield  = sc.nextInt();
        changestr  = sc.next().toCharArray();
        check  = sc.nextInt();

        result = Change(field, str, changefield, changestr);
        if (result != check) {
            Score -= ScoreIdx;
        }
    }

    static void cmd_search()
    {
        int field, returnfield, check;
        char[] str = new char[20], checkstr = new char[20];
        field  = sc.nextInt();
        str  = sc.next().toCharArray();
        returnfield  = sc.nextInt();
        checkstr  = sc.next().toCharArray();
        check  = sc.nextInt();

        RESULT result = Search(field, str, returnfield);

        if (result.count != check || (result.count == 1 && (checkstr.toString().compareTo(result.toString()) != 0))) {
            Score -= ScoreIdx;
        }
    }

    static void run()
    {
        int N;
        N = sc.nextInt();
        for (int i = 0; i < N; i++)
        {
            int cmd;
            cmd = sc.nextInt();
            switch (cmd)
            {
                case CMD_INIT:   cmd_init();   break;
                case CMD_ADD:    cmd_add();    break;
                case CMD_DELETE: cmd_delete(); break;
                case CMD_CHANGE: cmd_change(); break;
                case CMD_SEARCH: cmd_search(); break;
                default: break;
            }
        }
    }

    static void init()
    {
        Score = 1000;
        ScoreIdx = 1;
    }

    public static void main(String[] args)
    {
        int T;
        T = sc.nextInt();

        int TotalScore = 0;
        for (int tc = 1; tc <= T; tc++)
        {
            init();

            run();

            if (Score < 0)
                Score = 0;

            TotalScore += Score;
            System.out.format("#%d %d%n", tc, Score);
        }
        System.out.format("TotalScore = %d%n", TotalScore);
//        TestApi t = new TestApi();
//        String name1 = "rudi";
//        String name2 = "ahmad";
//        String name3 = "surti";
//        Name name = null;
//        name =  insertName(name, name1.toCharArray());
//        index++;
//        name = insertName(name, name2.toCharArray());
//        index++;
//        name = insertName(name, name3.toCharArray());
//
//        Name s = name;
    }
}
