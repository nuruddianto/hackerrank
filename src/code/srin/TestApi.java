package code.srin;

/**
 * Created by SRIN on 2/24/2017.
 */
public class TestApi {

    public static class Name {
        Name right;
        Name left;
        char[] name;
        int indexCounter;
    }

    public class Number {
        Number right;
        Number left;
        char[] number;
        int index;
    }

    public class Birthday {
        Birthday right;
        Birthday left;
        char[] birthday;
        int index;
    }

    public class Email {
        Email right;
        Email left;
        char[] email;
        int index;
    }

    public class Memo {
        Memo right;
        Memo left;
        char[] memo;
        int index;
    }

    public static int index;
    public Name rootName = new Name();

    /*insert*/
    private static void Add(char[] name2, char[] number2, char[] birthday2, char[] email2, char[] memo2) {
    }

    private Name insertName(Name l, char[] name) {
        if(l == null || index == 0){
            if(index != 0){
                l = new Name();
                l.indexCounter = index;
            }
            l.name = name;
            return l;
        }

        if(isNewBigger(l.name, name) ){
            l.right = insertName(l.right, name);
        }else{
            l.left = insertName(l.left, name);
        }

        return l;
    }

    /*Change*/
    private static int Change(int field, char[] str, int changefield, char[] changestr) {

        return 0;
    }

/*    private Name changeName(Name l,char[] oldName, char[] newName ){
        if(l == null){
            return null;
        }

        if(isNewBigger(l.name, oldName)){}
    }*/

    private static boolean isNewBigger(char[] currentString, char[] newString) {
        int lengthCurr = currentString.length;
        int lengthNew = newString.length;
        int i = min(lengthCurr, lengthNew);
        for(int k=0; k < i; k++){
            if(newString[k] > currentString[k]){
                return true;
            }else if(newString[k] < currentString[k]){
                return false;
            }
        }

       if(lengthCurr < lengthNew){
            return false;
       }

       return true;
    }

    private static int min(int a, int b) {
        return (a > b) ? b : a;
    }

    public static void main(String[] args) {
        TestApi t = new TestApi();
        String name1 = "rudi";
        String name2 = "ahmad";
        Name name = new Name();
        t.insertName(name, name1.toCharArray());
        index++;
        t.insertName(name, name2.toCharArray());

        Name s = name;
    }


}
