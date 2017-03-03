package code.srin;

import java.util.Scanner;

/**
 * Created by SRIN on 2/24/2017.
 */
public class TestApi {

    private static class IndexData{
        int data;
        IndexData next;
    }

    private static class Name {
        Name right;
        Name left;
        char[] name;
        int indexCounter;

        public Name(char[] name, int indexCounter) {
            this.name = name.clone();
            this.indexCounter = indexCounter;
        }
    }

    public static class Number {
        Number right;
        Number left;
        char[] number;
        int indexCounter;

        public Number(char[] number, int indexCounter) {
            this.number = number.clone();
            this.indexCounter = indexCounter;
        }
    }

    public static class Birthday {
        Birthday right;
        Birthday left;
        char[] birthday;
        int indexCounter;

        public Birthday(char[] birthday, int indexCounter) {
            this.birthday = birthday.clone();
            this.indexCounter = indexCounter;
        }
    }

    public static class Email {
        Email right;
        Email left;
        char[] email;
        int indexCounter;

        public Email(char[] email, int indexCounter) {
            this.email = email.clone();
            this.indexCounter = indexCounter;
        }
    }

    public static class Memo {
        Memo right;
        Memo left;
        char[] memo;
        int indexCounter;

        public Memo(char[] memo, int indexCounter) {
            this.memo = memo.clone();
            this.indexCounter = indexCounter;
        }
    }

    public static int index;
    public static int count;
    public static String data[][];
    public static Name nameNode;
    public static Number numberNode;
    public static Birthday birthdayNode;
    public static Email emailNode;
    public static Memo memoNode;
    public static IndexData indexData;

    private static void InitDB() {
        index = 0;
        nameNode = null;
        numberNode = null;
        birthdayNode = null;
        emailNode = null;
        memoNode = null;
        indexData = null;
        data = new String[50001][5];
        return;
    }

    /*==============================================insert===================================================================================*/
    private static void Add(char[] name2, char[] number2, char[] birthday2, char[] email2, char[] memo2) {
        nameNode = insertName(nameNode,reformatChar(name2));
        numberNode = insertNumber(numberNode, reformatChar(number2));
        birthdayNode = insertBirthday(birthdayNode, reformatChar(birthday2));
        emailNode = insertEmail(emailNode, reformatChar(email2));
        memoNode = insertMemo(memoNode, reformatChar(memo2));
        index++;
    }

    private static Name insertName(Name l, char[] name) {
        if (l == null) {
            l = new Name(name, index);
            data[index][0] = new String(l.name);
            return l;
        }

        int compare = isNewBigger(l.name, name);
        if (compare == 1 || compare == 2) {
            l.right = insertName(l.right, name);
        } else {
            l.left = insertName(l.left, name);
        }

        return l;
    }

    private static Number insertNumber(Number l, char[] number) {
        if (l == null) {
            l = new Number(number, index);
            data[index][1] = new String(number);
            return l;
        }

        int compare = isNewBigger(l.number, number);
        if (compare == 1 || compare == 2) {
            l.right = insertNumber(l.right, number);
        } else {
            l.left = insertNumber(l.left, number);
        }

        return l;
    }

    private static Birthday insertBirthday(Birthday l, char[] birthday) {
        if (l == null) {
            l = new Birthday(birthday, index);
            data[index][2] = new String(birthday);
            return l;
        }

        int compare = isNewBigger(l.birthday, birthday);
        if (compare == 1 || compare == 2) {
            l.right = insertBirthday(l.right, birthday);
        } else {
            l.left = insertBirthday(l.left, birthday);
        }

        return l;
    }

    private static Email insertEmail(Email l, char[] email) {
        if (l == null) {
            l = new Email(email, index);
            data[index][3] = new String(email);
            return l;
        }

        int compare = isNewBigger(l.email, email);
        if (compare == 1 || compare == 2) {
            l.right = insertEmail(l.right, email);
        } else {
            l.left = insertEmail(l.left, email);
        }

        return l;
    }

    private static Memo insertMemo(Memo l, char[] memo) {
        if (l == null) {
            l = new Memo(memo, index);
            data[index][4] = new String(memo);
            return l;
        }

        int compare = isNewBigger(l.memo, memo);
        if (compare == 1 || compare == 2) {
            l.right = insertMemo(l.right, memo);
        } else {
            l.left = insertMemo(l.left, memo);
        }

        return l;
    }

    /*===========================================================Search=======================================================*/
    private static RESULT Search(int field, char[] str, int returnfield) {
        RESULT result = new RESULT();
        indexData = new IndexData();
        count = 0;
        switch (field) {
            case 0:
                return searchName(nameNode, str, 0, 0, result, returnfield);
            case 1:
                return searchNumber(numberNode, str, 0,0, result, returnfield);
            case 2:
                return searchBirthday(birthdayNode, str, 0,0,result,returnfield);
            case 3:
                return searchEmail(emailNode, str, 0, 0, result, returnfield);
            case 4:
                return searchMemo(memoNode, str, 0,0, result, returnfield);
        }
        return result;
    }

    private static String convertToString(char[] c){
        String s = "";
        for(int i=0; i <c.length; i++){
            if(c[i] == 0){
                break;
            }
            s += c[i];
        }
        return s;
    }

    private static void setIndexData(int index){
        IndexData newData = new IndexData();
        newData.data = index;
        if(indexData == null){
            indexData = new IndexData();
            indexData.data = index;
        }else{
            IndexData tmp = indexData;
            while(tmp.next != null){
                tmp = tmp.next;
            }
            tmp.next = newData;
        }
    }

    private static RESULT searchName(Name l, char[] name, int count, int index, RESULT result, int returnfield) {
        if (l == null) {
            if(count == 1){
                result.count = 1;
                result.str = convertToString(data[index][returnfield].toCharArray()).toCharArray();
            }else{
                result.count = count;
                result.str = "null".toCharArray();
            }
            return result;
        }
        int compare = isNewBigger(l.name, name);

        if (compare == 2) {
            return searchName(l.right, name, count + 1, l.indexCounter, result, returnfield);
        } else if (compare == 1) {
            return searchName(l.right, name, count, index, result, returnfield);
        }
        setIndexData(l.indexCounter);
        return searchName(l.left, name, count, index, result,returnfield);
    }

    private static RESULT searchNumber(Number l, char[] number, int count, int index, RESULT result, int returnfield) {
        if (l == null) {
            if(count == 1){
                result.count = 1;
                result.str = convertToString(data[index][returnfield].toCharArray()).toCharArray();
            }else{
                result.count = count;
                result.str = "null".toCharArray();
            }
            return result;
        }
        int compare = isNewBigger(l.number, number);

        if (compare == 2) {
            return searchNumber(l.right, number, count + 1, l.indexCounter, result, returnfield);
        } else if (compare == 1) {
            return searchNumber(l.right, number, count, index, result, returnfield);
        }
        setIndexData(l.indexCounter);
        return searchNumber(l.left, number, count, index, result,returnfield);
    }

    private static RESULT searchBirthday(Birthday l, char[] birthday, int count, int index, RESULT result, int returnfield) {
        if (l == null) {
            if(count == 1){
                result.count = 1;
                result.str = convertToString(data[index][returnfield].toCharArray()).toCharArray();
            }else{
                result.count = count;
                result.str = "null".toCharArray();
            }
            return result;
        }
        int compare = isNewBigger(l.birthday, birthday);

        if (compare == 2) {
            return searchBirthday(l.right, birthday, count + 1, l.indexCounter, result, returnfield);
        } else if (compare == 1) {
            return searchBirthday(l.right, birthday, count, index, result, returnfield);
        }
        setIndexData(l.indexCounter);
        return searchBirthday(l.left, birthday, count, index, result,returnfield);
    }

    private static RESULT searchEmail(Email l, char[] email, int count, int index, RESULT result, int returnfield) {
        if (l == null) {
            if(count == 1){
                result.count = 1;
                result.str = convertToString(data[index][returnfield].toCharArray()).toCharArray();
            }else{
                result.count = count;
                result.str = "null".toCharArray();
            }
            return result;
        }
        int compare = isNewBigger(l.email, email);

        if (compare == 2) {
            return searchEmail(l.right, email, count + 1, l.indexCounter, result, returnfield);
        } else if (compare == 1) {
            return searchEmail(l.right, email, count, index, result, returnfield);
        }
        setIndexData(l.indexCounter);
        return searchEmail(l.left, email, count, index, result,returnfield);
    }

    private static RESULT searchMemo(Memo l, char[] memo, int count, int index, RESULT result, int returnfield) {
        if (l == null) {
            if(count == 1){
                result.count = 1;
                result.str = convertToString(data[index][returnfield].toCharArray()).toCharArray();
            }else{
                result.count = count;
                result.str = "null".toCharArray();
            }
            return result;
        }
        int compare = isNewBigger(l.memo, memo);

        if (compare == 2) {
            return searchMemo(l.right, memo, count + 1, l.indexCounter, result, returnfield);
        } else if (compare == 1) {
            return searchMemo(l.right, memo, count, index, result, returnfield);
        }
        setIndexData(l.indexCounter);
        return searchMemo(l.left, memo, count, index, result,returnfield);
    }

    /*===========================================================MinVal=======================================================*/
    private static Name minValueName(Name l) {
        Name current = l;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    private static Number minValueNumber(Number l) {
        Number current = l;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    private static Birthday minValueBirthday(Birthday l) {
        Birthday current = l;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    private static Email minValueEmail(Email l) {
        Email current = l;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    private static Memo minValueMemo(Memo l) {
        Memo current = l;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    /*===========================================================Delete=======================================================*/
    private static int Delete(int field, char[] str) {
        count = 0;
        switch (field){
            case 0 :
                deleteName(nameNode, str);
                return count;
            case 1:
                Number n = numberNode;
                deleteNumber(numberNode, str);
                return count;
            case 2:
                deleteBirthday(birthdayNode, str);
                return count;
            case 3:
                deleteEmail(emailNode, str);
                return count;
            case 4:
                deleteMemo(memoNode, str);
                return count;
        }
        return count;
    }

    private static Name deleteName(Name l, char[] name) {
        if (l == null) {
            return l;
        }

        int compare = isNewBigger(l.name, name);
        if (compare == 1) {
            l.right = deleteName(l.right, name);
        } else if (compare == 3) {
            l.left = deleteName(l.left, name);
        } else {
            count++;
            if (l.left == null) {
                l = l.right;
                return deleteName(l, name);
            } else if (l.right == null) {
                l = l.left;
                deleteName(l, name);
                return deleteName(l, name);
            }

            Name tmp = minValueName(l.right);
            l.name = tmp.name;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteName(l.right, tmp.name);
        }
        return l;
    }

    private static Number deleteNumber(Number l, char[] number) {
        if (l == null) {
            return l;
        }

        int compare = isNewBigger(l.number, number);
        if (compare == 1) {
            l.right = deleteNumber(l.right, number);
        } else if (compare == 3) {
            l.left = deleteNumber(l.left, number);
        } else {
            count++;
            if (l.left == null) {
                l = l.right;
                return deleteNumber(l, name);
            } else if (l.right == null) {
                l = l.left;
                deleteNumber(l, name);
                return deleteNumber(l, name);
            }

            Number tmp = minValueNumber(l.right);
            l.number = tmp.number;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteNumber(l.right, tmp.number);
        }
        return l;
    }

    private static Birthday deleteBirthday(Birthday l, char[] birthday) {
        if (l == null) {
            return l;
        }

        int compare = isNewBigger(l.birthday, birthday);
        if (compare == 1) {
            l.right = deleteBirthday(l.right, birthday);
        } else if (compare == 3) {
            l.left = deleteBirthday(l.left, birthday);
        } else {
            count++;
            if (l.left == null) {
                l = l.right;
                return deleteBirthday(l, birthday);
            } else if (l.right == null) {
                l = l.left;
                deleteBirthday(l, birthday);
                return deleteBirthday(l, birthday);
            }

            Birthday tmp = minValueBirthday(l.right);
            l.birthday = tmp.birthday;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteBirthday(l.right, tmp.birthday);
        }
        return l;
    }

    private static Email deleteEmail(Email l, char[] email) {
        if (l == null) {
            return l;
        }

        int compare = isNewBigger(l.email, email);
        if (compare == 1) {
            l.right = deleteEmail(l.right, email);
        } else if (compare == 3) {
            l.left = deleteEmail(l.left, email);
        } else {
            count++;
            if (l.left == null) {
                l = l.right;
                return deleteEmail(l, email);
            } else if (l.right == null) {
                l = l.left;
                deleteEmail(l, email);
                return deleteEmail(l, email);
            }

            Email tmp = minValueEmail(l.right);
            l.email = tmp.email;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteEmail(l.right, tmp.email);
        }
        return l;
    }

    private static Memo deleteMemo(Memo l, char[] memo) {
        if (l == null) {
            return l;
        }

        int compare = isNewBigger(l.memo, memo);
        if (compare == 1) {
            l.right = deleteMemo(l.right, memo);
        } else if (compare == 3) {
            l.left = deleteMemo(l.left, memo);
        } else {
            count++;
            if (l.left == null) {
                l = l.right;
                return deleteMemo(l, memo);
            } else if (l.right == null) {
                l = l.left;
                deleteMemo(l, memo);
                return deleteMemo(l, memo);
            }

            Memo tmp = minValueMemo(l.right);
            l.memo = tmp.memo;
            l.indexCounter = tmp.indexCounter;
            l.right = deleteMemo(l.right, tmp.memo);
        }
        return l;
    }


    /*===========================================================Change=======================================================*/
    private static int Change(int field, char[] str, int changefield, char[] changestr) {
        RESULT result = Search(field, str, field);
        IndexData dex = indexData;
        count = 0;
        while (dex != null){
            char[] search = data[dex.data][changefield].toCharArray();
            switch (changefield){
                case 0 :
                    changeName(nameNode, search, changestr);
                    break;
                case 1:
                    changeNumber(numberNode, search, changestr);
                    break;
                case 2:
                    changeBirthday(birthdayNode, search, changestr);
                    break;
                case 3:
                    changeEmail(emailNode, search, changestr);
                    break;
                case 4:
                    changeMemo(memoNode, search, changestr);
                    break;
            }
            dex = dex.next;
        }

        return result.count;
    }

    private static Name changeName(Name l, char[] oldName, char[] newName) {
        l = deleteName(l, oldName);
        for (int i = 0; i < count; i++) {
            l = insertName(l, newName);
        }
        return l;
    }

    private static Number changeNumber(Number l, char[] oldNumber, char[] newNumber) {
        l = deleteNumber(l, oldNumber);
        for (int i = 0; i < count; i++) {
            l = insertNumber(l, newNumber);
        }
        return l;
    }

    private static Birthday changeBirthday(Birthday l, char[] oldBirthday, char[] newBirthday) {
        l = deleteBirthday(l, oldBirthday);
        for (int i = 0; i < count; i++) {
            l = insertBirthday(l, newBirthday);
        }
        return l;
    }

    private static Email changeEmail(Email l, char[] oldEmail, char[] newEmail) {
        l = deleteEmail(l, oldEmail);
        for (int i = 0; i < count; i++) {
            l = insertEmail(l, newEmail);
        }
        return l;
    }

    private static Memo changeMemo(Memo l, char[] oldMemo, char[] newMemo) {
        l = deleteMemo(l, oldMemo);
        for (int i = 0; i < count; i++) {
            l = insertMemo(l, newMemo);
        }
        return l;
    }

    private static char[] reformatChar(char[] c){
        String s = "";
        for(int i=0; i < c.length; i++){
            if(c[i] == 0){
                break;
            }
            s += c[i];
        }
        return s.toCharArray();
    }
    /*
    1 - if new data is bigger
    2 - if new data is equal
    3 - if new data is smaller
    */
    private static int isNewBigger(char[] currentString, char[] newString) {
        int lengthCurr = 0;
        if (currentString != null) {
            lengthCurr = currentString.length;
        }
        int lengthNew = 0;
        if (newString != null) {
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

        if(lengthCurr == lengthNew){
            return 2;
        }else if(lengthCurr > lengthNew){
            return 3;
        }

        return 1;
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

    static int[] dummy = new int[100];
    static int Score, ScoreIdx;
    static char[] name = new char[20], number = new char[20], birthday = new char[20], email = new char[20], memo = new char[20];

    static char[][] lastname = {"kim".toCharArray(), "lee".toCharArray(), "park".toCharArray(), "choi".toCharArray(), "jung".toCharArray(), "kang".toCharArray(), "cho".toCharArray(), "oh".toCharArray(), "jang".toCharArray(), "lim".toCharArray()};
    static int[] lastname_length = {3, 3, 4, 4, 4, 4, 3, 2, 4, 3};

    public static class RESULT {
        public int count;
        public char[] str = new char[20];
    }

    ;

    static int mSeed;

    static int mrand(int num) {
        mSeed = mSeed * 1103515245 + 37209;
        if (mSeed < 0) mSeed *= -1;
        return ((mSeed >> 8) % num);
    }

    static void make_field(int seed) {
        int name_length, email_length, memo_length;
        int idx, num;

        mSeed = (int) seed;

        name_length = 6 + mrand(10);
        email_length = 10 + mrand(10);
        memo_length = 5 + mrand(10);

        int a = 97;
        int zero = 48;
        num = mrand(10);
        for (idx = 0; idx < lastname_length[num]; idx++) name[idx] = lastname[num][idx];
        for (; idx < name_length; idx++) name[idx] = (char) (a + mrand(26));
        name[idx] = 0;

        for (idx = 0; idx < memo_length; idx++) memo[idx] = (char) (a + mrand(26));
        memo[idx] = 0;

        for (idx = 0; idx < email_length - 6; idx++) email[idx] = (char) (a + mrand(26));
        email[idx++] = '@';
        email[idx++] = (char) (a + mrand(26));
        email[idx++] = '.';
        email[idx++] = 'c';
        email[idx++] = 'o';
        email[idx++] = 'm';
        email[idx] = 0;

        idx = 0;
        number[idx++] = '0';
        number[idx++] = '1';
        number[idx++] = '0';
        for (; idx < 11; idx++) number[idx] = (char) (zero + mrand(10));
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

    static void cmd_init() {
        ScoreIdx = sc.nextInt();

        InitDB();
    }

    static void cmd_add() {
        int seed;
        seed = sc.nextInt();

        make_field(seed);

        Add(name, number, birthday, email, memo);
    }

    static void cmd_delete() {
        int field, check, result;
        char[] str = new char[20];
        field = sc.nextInt();
        str = sc.next().toCharArray();
        check = sc.nextInt();

        result = Delete(field, str);
        if (result != check) {
            System.out.println("Fail to delete :"+ new String(str)+" at field :"+field+" result :"+result+" !="+check);
            Score -= ScoreIdx;
        }
    }

    static void cmd_change() {
        int field, changefield, check, result;
        char[] str = new char[20], changestr = new char[20];
        field = sc.nextInt();
        str = sc.next().toCharArray();
        changefield = sc.nextInt();
        changestr = sc.next().toCharArray();
        check = sc.nextInt();

        result = Change(field, str, changefield, changestr);
        if (result != check) {
            System.out.println("Fail to change :"+ new String(str)+" at field :"+field+" Result check :"+result +"!="+check);
            Score -= ScoreIdx;
        }
    }

    static void cmd_search() {
        int field, returnfield, check;
        char[] str = new char[20], checkstr = new char[20];
        field = sc.nextInt();
        str = sc.next().toCharArray();
        returnfield = sc.nextInt();
        checkstr = sc.next().toCharArray();
        check = sc.nextInt();
        RESULT result = Search(field, str, returnfield);

        if (result.count != check || (result.count == 1 && (new String(checkstr).compareTo(new String(result.str)) != 0))) {
            System.out.println("Fail to search :"+ new String(str)+" at field :"+field+" result :"+result+" !="+check);
            Score -= ScoreIdx;
        }
    }

    static void run() {
        int N;
        N = sc.nextInt();
        for (int i = 0; i < N; i++) {
            int cmd;
            cmd = sc.nextInt();
            switch (cmd) {
                case CMD_INIT:
                    cmd_init();
                    break;
                case CMD_ADD:
                    cmd_add();
                    break;
                case CMD_DELETE:
                    cmd_delete();
                    break;
                case CMD_CHANGE:
                    cmd_change();
                    break;
                case CMD_SEARCH:
                    cmd_search();
                    break;
                default:
                    break;
            }
        }
    }

    static void init() {
        Score = 1000;
        ScoreIdx = 1;
    }

    public static void main(String[] args) {
        int T;
        T = sc.nextInt();
        int TotalScore = 0;
        for (int tc = 1; tc <= T; tc++) {
            init();

            run();

            if (Score < 0)
                Score = 0;

            TotalScore += Score;
            System.out.format("#%d %d%n", tc, Score);
            traverse(numberNode);
        }
        System.out.format("TotalScore = %d%n", TotalScore);
    }

    private static void traverse(Number name){
        if(name != null){
            System.out.println(new String(name.number));
            traverse(name.left);
            traverse(name.right);
        }

    }
}

        /*
        2
        10
        0 200
        1 757148
        1 851001
        1 413357
        1 971125
        4 0 kimgysrtpnjzbp 1 01072086371 1
        4 0 leefgujjze 2 19260414 1
        4 4 cwjpxrzpsof 2 19260414 1
        4 1 01086024865 3 NULL 0
        4 3 jqtwx@e.com 4 ccxzhdzymdjpt 1
30
                0 84
                1 73109
                1 574081
                1 435177
                1 764301
                1 846734
                1 496026
                1 633605
                1 544848
                1 415473
                1 312137
                1 595209
                1 502521
                1 563001
                1 818981
                1 768385
                3 0 parkyylueyoeqe 3 mayvudj@l.com 1
        3 0 leecsk 3 zudl@t.com 1
        4 4 nmwbfty 0 limgcufqjp 1
        4 0 parkyzupol 1 01020452508 1
        3 2 19760921 4 owkbjzwucwl 1
        3 0 choiekaaogozxl 0 ohtoohonagn 1
        1 579871
        4 2 19860414 0 ohtoohonagn 1
        4 3 uhuhrsmiiva@a.com 2 19490309 1
        1 970536
        4 2 19981002 3 chjdwnujhr@d.com 1
        4 3 kbcltfnijs@c.com 4 ooursvtxz 1
        3 3 kbcltfnijs@c.com 0 chootzgkubmjrm 1
        4 1 01052910135 2 19570912 1
     */


        /*
        1
        50
                0 44
                1 918711
                1 581907
                1 376363
                1 686977
                1 60625
                1 386939
                1 568501
                1 551266
                1 385256
                1 59921
                1 869822
                1 542056
                1 996142
                1 965957
                1 752958
                1 580455
                1 239000
                1 595881
                1 599193
                1 554428
                1 579329
                1 311431
                1 810236
                1 250279
                4 0 jangwudbo 4 ruoavwi 1
                3 1 01014405687 0 kangmb 1
                3 2 19700409 2 19940822 1
                4 1 01064131716 0 kangbhxbbrszkp 1
                4 0 leegpfx 1 01087479896 1
                4 0 choiadohmlo 3 qrytkf@e.com 1
        4 3 dxwfiuwjc@a.com 4 ltntpdk 1
        4 3 lfvftidfo@z.com 4 wfzmzffycil 1
        3 4 ophwu 3 gkjisuxh@a.com 1
        2 1 01046140822 1
        4 3 uclanjbw@z.com 4 porkarme 1
        2 1 01046140822 0
        3 3 xsxljdvwbexml@g.com 2 19380720 1
        2 4 xlcwjxr 1
        1 552041
        4 0 kangsdwhf 4 pkngwlqwql 1
        2 2 19870722 0
        4 1 01082270556 0 jangvqgibfx 1
        4 0 jungbjtee 2 19290828 1
        3 0 kangmb 4 jsaevteqcsk 1
        3 3 dxwfiuwjc@a.com 3 kntarjkpxin@o.com 1
        3 3 xpvve@h.com 0 leehkw 1
        4 4 yyxrupuvo 0 parkaakqc 1
        4 4 omnzwjspx 2 19330507 1
        1 61039
        */
