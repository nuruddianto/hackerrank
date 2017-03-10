package code.srin;

import code.LinkedListed;

import java.util.Scanner;

/**
 * Created by SRIN on 3/6/2017.
 */
public class DatabaseSimulator {
    private static class Data {
        Data next;
        String string_data;
        int arrayIndex;

        public Data(int arrayIndex, String stringData) {
            this.arrayIndex = arrayIndex;
            this.string_data = stringData;
        }
    }

    private static class Field {
        Field right;
        Field left;
        Data data;
    }

    private static class DeleteRecord {
        DeleteRecord next;
        int record;

        public DeleteRecord(int record) {
            this.record = record;
        }
    }

    private static void enqueueDeleteRecord(int record) {
        if (deleteRecord == null) {
            deleteRecord = new DeleteRecord(record);
            return;
        }

        DeleteRecord tmp = deleteRecord;
        DeleteRecord newRecord = new DeleteRecord(record);
        while (tmp.next != null) {
            tmp = tmp.next;
        }
        tmp.next = newRecord;
    }

    private static int dequeueRecord() {
        if (deleteRecord == null) {
            return 0;
        }

        int record = deleteRecord.record;
        deleteRecord = deleteRecord.next;
        return record;
    }

    private static Data addDataList(Data data, String stringContain, int indexArray) {
        int index = (indexArray == 0) ? mIndexArray : indexArray;
        Data new_data = new Data(index, stringContain);
        if (data == null) {
            data = new_data;
            return data;
        }

        Data tmp = data;
        while (tmp.next != null) {
            tmp = tmp.next;
        }
        tmp.next = new_data;
        return tmp;
    }

    private static int getTotalData(Field l) {
        if (l == null) {
            return 0;
        }
        Data tmp = l.data;
        int count = 1;
        while (tmp.next != null) {
            tmp = tmp.next;
            count++;
        }
        return count;
    }

    private static Field insert(Field l, String string_contain, int indexArray) {
        if (l == null ) {
            l = new Field();
            Data data = null;
            l.data = addDataList(data, string_contain, indexArray);
            return l;
        }

        int compare = l.data.string_data.compareTo(string_contain);
        if (compare > 0) {
            l.right = insert(l.right, string_contain, indexArray);
        } else if (compare < 0) {
            l.left = insert(l.left, string_contain, indexArray);
        } else {
            l.data = addDataList(l.data, string_contain, indexArray);
        }

        return l;
    }

    private static Field search(Field l, String string_contain) {
        if (l == null) {
            return null;
        }

        int compare = l.data.string_data.compareTo(string_contain);
        if (compare > 0) {
            return search(l.right, string_contain);
        } else if (compare < 0) {
            return search(l.left, string_contain);
        }
        return l;
    }

    private static Field minValue(Field l) {
        if (l == null) {
            return null;
        }
        Field tmp = l;
        while (tmp.left != null) {
            tmp = tmp.left;
        }

        return tmp;
    }


    private static Field delete(Field l, String stringData) {
        if (l == null) {
            return null;
        }

        int compare = l.data.string_data.compareTo(stringData);
        if (compare > 0) {
            l.right = delete(l.right, stringData);
        } else if (compare < 0) {
            l.left = delete(l.left, stringData);
        } else {
            totalDeleted = getTotalData(l);
            Data tmpData = l.data;
            while (tmpData != null) {
                enqueueDeleteRecord(tmpData.arrayIndex);
                tmpData = tmpData.next;
            }

            if (l.left == null) {
                l = l.right;
                return l;
            } else if (l.right == null) {
                l = l.left;
                return l;
            }

            Field tmp = minValue(l.right);
            l.data = tmp.data;
            l.right = delete(l.right, tmp.data.string_data);
        }
        return l;
    }

    private static Field deleteByIndex(Field l ,int indexArray, String stringData){
        if (l == null) {
            return null;
        }

        int compare = l.data.string_data.compareTo(stringData);
        if (compare > 0) {
            l.right = deleteByIndex(l.right,indexArray, stringData);
        } else if (compare < 0) {
            l.left = deleteByIndex(l.left,indexArray, stringData);
        } else {
            totalDeleted = getTotalData(l);
            if(totalDeleted > 1){
                Data currData = l.data;
                while (currData.next != null) {
                    if(currData.arrayIndex == indexArray){
                        break;
                    }
                    currData = currData.next;
                }
                l.data = currData;
            }else{
                if (l.left == null) {
                    l = l.right;
                    return l;
                } else if (l.right == null) {
                    l = l.left;
                    return l;
                }

                Field tmp = minValue(l.right);
                l.data = tmp.data;
                l.right = deleteByIndex(l.right, tmp.data.arrayIndex, tmp.data.string_data);
            }

        }
        return l;
    }

    private static String charToString(char[] chars) {
        String s = "";
        for (int i = 0; i < chars.length; i++) {
            if (chars[i] == 0) {
                break;
            }
            s += chars[i];
        }
        return s;
    }

    private static Field nameField;
    private static Field numberField;
    private static Field birthdayField;
    private static Field emailField;
    private static Field memoField;

    private static String data[][];

    private static int mIndexArray;
    private static DeleteRecord deleteRecord;
    private static int totalDeleted;


    private static void InitDB() {
        nameField = null;
        numberField = null;
        birthdayField = null;
        emailField = null;
        memoField = null;
        data = null;
        data = new String[50001][5];
        mIndexArray = 1;
        totalDeleted = 0;
        deleteRecord = null;
        return;
    }

    private static void Add(char[] name2, char[] number2, char[] birthday2, char[] email2, char[] memo2) {
        String name = name2 != null ? charToString(name2): "";
        String number = number2 != null ? charToString(number2): "";
        String birthday = birthday2 != null ? charToString(birthday2): "";
        String email = email2 != null ?charToString(email2): "";
        String memo = memo2 != null ? charToString(memo2): "";

        nameField = insert(nameField, name, 0);
        numberField = insert(numberField, number, 0);
        birthdayField = insert(birthdayField, birthday, 0);
        emailField = insert(emailField, email, 0);
        memoField = insert(memoField, memo, 0);


        data[mIndexArray][0] = name;
        data[mIndexArray][1] = number;
        data[mIndexArray][2] = birthday;
        data[mIndexArray][3] = email;
        data[mIndexArray][4] = memo;

        mIndexArray++;
    }

    private static int Delete(int field, char[] str) {
        totalDeleted = 0;
        switch (field){
            case 0:
                delete(nameField, charToString(str));
                break;
            case 1:
                delete(numberField, charToString(str));
                break;
            case 2:
                delete(birthdayField, charToString(str));
                break;
            case 3:
                delete(emailField, charToString(str));
                break;
            case 4:
                delete(memoField, charToString(str));
                break;
        }

        while (deleteRecord != null){
            int indexArrayToDelete = dequeueRecord();
            for(int i=0; i < 5 ; i++){
                if(i == field){
                    continue;
                }
                String stringToDelete = data[indexArrayToDelete][i];
                switch (i){
                    case 0:
                        deleteByIndex(nameField, indexArrayToDelete, stringToDelete);
                        break;
                    case 1:
                        deleteByIndex(numberField,indexArrayToDelete, stringToDelete);
                        break;
                    case 2:
                        deleteByIndex(birthdayField,indexArrayToDelete, stringToDelete);
                        break;
                    case 3:
                        deleteByIndex(emailField,indexArrayToDelete, stringToDelete);
                        break;
                    case 4:
                        deleteByIndex(memoField,indexArrayToDelete, stringToDelete);
                        break;
                }
            }

        }
        return totalDeleted;
    }

    private static int Change(int field, char[] str, int changefield, char[] changestr) {
        Field searchResult = null;
        switch (field) {
            case 0:
                searchResult = search(nameField, new String(str));
                break;
            case 1:
                searchResult = search(numberField, new String(str));
                break;
            case 2:
                searchResult = search(birthdayField, new String(str));
                break;
            case 3:
                searchResult = search(emailField, new String(str));
                break;
            case 4:
                searchResult = search(memoField, new String(str));
                break;
        }
        int totalChangeData =  getTotalData(searchResult);
        if(searchResult != null){
            Data tmp = searchResult.data;
            while (tmp != null){
                int indexFieldToChange = tmp.arrayIndex;
                String stringToDelete = data[indexFieldToChange][changefield];
                data[indexFieldToChange][changefield] = charToString(changestr);
                switch (changefield) {
                    case 0:
                        deleteByIndex(nameField, indexFieldToChange, stringToDelete);
                        insert(nameField, charToString(changestr), indexFieldToChange);
                        break;
                    case 1:
                        deleteByIndex(numberField, indexFieldToChange, stringToDelete);
                        insert(numberField, charToString(changestr), indexFieldToChange);
                        break;
                    case 2:
                        deleteByIndex(birthdayField, indexFieldToChange, stringToDelete);
                        insert(birthdayField, charToString(changestr), indexFieldToChange);
                        break;
                    case 3:
                        deleteByIndex(emailField, indexFieldToChange, stringToDelete);
                        insert(emailField, charToString(changestr), indexFieldToChange);
                        break;
                    case 4:
                        deleteByIndex(memoField, indexFieldToChange, stringToDelete);
                        insert(memoField, charToString(changestr), indexFieldToChange);
                        break;
                }
                tmp = tmp.next;
            }
        }

        return totalChangeData;
    }

    private static RESULT Search(int field, char[] str, int returnfield) {
        RESULT result = new RESULT();
        Field searchResult = null;
        switch (field) {
            case 0:
                searchResult = search(nameField, new String(str));
                break;
            case 1:
                searchResult = search(numberField, new String(str));
                break;
            case 2:
                searchResult = search(birthdayField, new String(str));
                break;
            case 3:
                searchResult = search(emailField, new String(str));
                break;
            case 4:
                searchResult = search(memoField, new String(str));
                break;
        }

        int totaldata = getTotalData(searchResult);
        if (totaldata == 1) {
            int indexArray = searchResult.data.arrayIndex;
            result.count = 1;
            result.str = data[indexArray][returnfield].toCharArray();
        } else {
            result.count = totaldata;
            result.str = "NULL".toCharArray();
        }

        return result;
    }

    private static void traverse(Field f){
        if(f!=null){
            System.out.println(f.data.string_data);
            traverse(f.left);
            traverse(f.right);
        }
    }

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
            System.out.println("Fail to delete :" + new String(str) + " at field :" + field + " result :" + result + " !=" + check);
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
            System.out.println("Fail to change :" + new String(str) + " at field :" + field + " Result check :" + result + "!=" + check);
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
            System.out.println("Fail to search :" + new String(str) + " at field :" + field + " result :" + result.count + " !=" + check + ":Your string is"+ new String(result.str));
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
        }
        System.out.format("TotalScore = %d%n", TotalScore);
        //traverse(numberField);
    }
}

//    public static void main(String[] args){
//        cont = true;
//        DatabaseSimulator d = new DatabaseSimulator();
//        f = null;
//        String s1 = "d";
//        String s2 = "d";
//        String s3 = "b";
//        String s4 = "e";
//        String s5 = "a";
//        String s6 = "c";
//
//
//        f = d.insert(f, s1);
//        mIndexArray++;
//        f = d.insert(f, s2);
//        mIndexArray++;
//        f = d.insert(f, s3);
//        mIndexArray++;
//        f = d.insert(f, s4);
//        mIndexArray++;
//        f = d.insert(f, s5);
//        mIndexArray++;
//        f = d.insert(f, s6);
//        mIndexArray++;
//
//
////        f = d.search(f, "e");
////        System.out.println(d.getTotalData(f));
//
//        f = d.delete(f, "b");
//        System.out.print(getTotalData(d.search(f,"d")));
//        //System.out.println(d.minValue(f).data.string_data);
//        String s = "";
////        System.out.print("a".compareTo("b"));
//    }


/*
Test case #4
        1
        100
        0 24
        1 746211
        1 74001
        1 690726
        1 385751
        1 221761
        1 796484
        1 665817
        1 864833
        1 595816
        1 896467
        1 811623
        1 335937
        1 583105
        1 190204
        1 177321
        1 779617
        1 713623
        1 262016
        1 832563
        1 581076
        1 607880
        1 570601
        1 101871
        1 861098
        1 14041
        1 470723
        1 390086
        1 576091
        1 447216
        1 81656
        1 476006
        1 185857
        1 51081
        1 685793
        1 553321
        1 17569
        1 323885
        1 125481
        1 929045
        1 53457
        1 616737
        1 477188
        1 98491
        1 435929
        1 118309
        1 349091
        1 855681
        1 497721
        1 707519
        4 2 19971223 3 osldtv@g.com 1
        2 0 chotjgowk 1
        3 2 19280801 3 osldtv@g.com 1
        1 119291
        4 2 19770616 3 qgamfx@m.com 1
        4 0 jangdhtphoa 3 jzvrqtproyftf@n.com 1
        4 4 tccjyplry 2 19910520 1
        4 0 jungtd 4 kotncp 1
        2 3 qponnnawysbn@o.com 1
        1 115046
        3 3 xzzazmjydyd@y.com 0 ohexggfozhothih 1
        3 3 osldtv@g.com 3 rjbfrjpcgdjdr@w.com 2
        2 3 fgjjj@b.com 1
        3 4 kotncp 2 19441013 0
        3 0 kimpqicgr 2 19910520 1
        4 2 19251113 1 01064602569 1
        1 648391
        1 779068
        4 3 jkprruyuw@g.com 4 bprwyxxehl 1
        4 4 suiqwprqn 0 choxlfic 1
        4 4 sondruiajnur 1 NULL 0
        3 2 19910520 0 ohsrtuixrcv 2
        3 2 19330108 3 jzvrqtproyftf@n.com 1
        4 0 kimqcctkbt 3 bsinwvantrwjj@y.com 1
        1 502317
        1 277478
        4 3 fgjjj@b.com 2 NULL 0
        3 0 jangefwu 3 qghosyvg@m.com 1
        3 4 whubcx 4 kyadxdgzlzkxmu 1
        4 2 19311226 1 01061086162 1
        1 587841
        4 4 deiyeg 1 01087783961 1
        4 1 01010707184 0 jungvfzbrthzs 1
        4 0 ohsrtuixrcv 4 fgcxjk 3
        4 4 svfmjsguc 0 kimziidzs 1
        4 4 kotncp 1 NULL 0
        3 2 19110321 4 hlvbypec 1
        4 2 19060718 4 kyadxdgzlzkxmu 1
        3 2 19910520 0 kangdqsvmte 2
        4 2 19340607 4 zcdff 1
        4 3 zrtr@s.com 4 opyaajz 1
        4 2 19940420 3 aojyrd@c.com 1
        4 3 xzzazmjydyd@y.com 2 19360722 1
        3 4 uvnymsbolqe 4 egkmqltbc 1
        2 2 19731017 1
        2 1 01069396922 1
        4 1 01098909693 2 19030428 1
        4 0 chombsijhkl 1 NULL 0
        4 1 01044601341 3 wxlhsgkwnelj@q.com 1
        4 3 khlrbxbluzcpo@n.com 4 zcdff 1
        */


       /*
       1
                13
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
        3 0 jungyyevu 0 abi 1
        3 0 leefgujjze 0 abi 1
        4 0 abi 0 abi 2
        */