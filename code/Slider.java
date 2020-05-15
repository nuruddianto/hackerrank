package code;

import java.util.*;

public class Slider {

    final int LEFT = 0;
    final int UP = 1;
    final int RIGHT = 2;
    final int DOWN = 3;

    static char[][] s;
    static char[][] t;
    static Stack<String> moveList;
    static Map<String, Integer> sumMap;

    static boolean[][] visited;

    static long minLength = Long.MAX_VALUE;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        Slider slider = new Slider();
        s = new char[n][n];
        t = new char[n][n];
        visited = new boolean[n][n];
        moveList = new Stack<>();

        // init sum map
        sumMap = new HashMap<>();
        sumMap.put("L", 82);
        sumMap.put("U", 68);
        sumMap.put("R", 76);
        sumMap.put("D", 85);

        int rW = 0;
        int cW = 0;
        for (int r = 0; r < n; r++) {
            String row = sc.next();
            for (int c = 0; c < n; c++) {
                if (row.charAt(c) == 'W') {
                    rW = r;
                    cW = c;
                }
                s[r][c] = row.charAt(c);
            }
        }

        for (int r = 0; r < n; r++) {
            String row = sc.next();
            for (int c = 0; c < n; c++) {
                t[r][c] = row.charAt(c);
            }
        }

        slider.backtrack(rW, cW);
        System.out.println(minLength);
        sc.close();
    }

    void backtrack(int r, int c) {
        if (isAchieveTarget())
            return;

        if (r < 0 || c < 0 || r >= s.length || c >= s.length || visited[r][c])
            return;

        System.out.println("== " + moveList.toString() + " ==");
        print();

        visited[r][c] = true;
        for (int i = 0; i < 4; i++) {
            switch (i) {
            case LEFT:
                if (c - 1 < 0 || visited[r][c - 1])
                    continue;

                swap(r, c, LEFT);
                moveList.push("L");

                backtrack(r, c - 1);

                moveList.pop();
                swap(r, c, RIGHT);
                break;
            case UP:
                if (r - 1 < 0 || visited[r - 1][c])
                    continue;

                swap(r, c, UP);
                moveList.push("U");

                backtrack(r - 1, c);

                moveList.pop();
                swap(r, c, DOWN);
                break;
            case RIGHT:
                if (c + 1 >= s.length || visited[r][c + 1])
                    continue;

                swap(r, c, RIGHT);
                moveList.push("R");

                backtrack(r, c + 1);

                moveList.pop();
                swap(r, c, LEFT);
                break;
            default:
                if (r + 1 >= s.length || visited[r + 1][c])
                    continue;

                swap(r, c, DOWN);
                moveList.push("D");

                backtrack(r + 1, c);

                moveList.pop();
                swap(r, c, UP);
            }
        }
        visited[r][c] = false;
    }

    public boolean isAchieveTarget() {
        // print();
        for (int r = 0; r < s.length; r++) {
            for (int c = 0; c < s.length; c++) {
                if (s[r][c] != t[r][c])
                    return false;
            }
        }
        long currSum = checkSum();
        minLength = currSum < minLength ? currSum : minLength;
        return true;
    }

    void swap(int r, int c, int move) {
        char tmp;
        switch (move) {
        case LEFT:
            if (c - 1 < 0)
                return;

            tmp = s[r][c];
            s[r][c] = s[r][c - 1];
            s[r][c - 1] = tmp;
            break;
        case UP:
            if (r - 1 < 0)
                return;

            tmp = s[r][c];
            s[r][c] = s[r - 1][c];
            s[r - 1][c] = tmp;
            break;
        case RIGHT:
            if (c + 1 >= s.length)
                return;

            tmp = s[r][c];
            s[r][c] = s[r][c + 1];
            s[r][c + 1] = tmp;
            break;
        default:
            if (r + 1 >= s.length)
                return;

            tmp = s[r][c];
            s[r][c] = s[r + 1][c];
            s[r + 1][c] = tmp;
        }
    }

    void print() {
        for (int r = 0; r < s.length; r++) {
            System.out.println(Arrays.toString(s[r]));
        }
        System.out.println();
    }

    long checkSum() {
        long sum = 0;

        Iterator value = moveList.iterator();
        while (value.hasNext()) {
            String move = String.valueOf(value.next());
            sum = ((sum * 243) + sumMap.get(move)) % 100000007;
        }

        return sum;
    }
}

/**
 * 2 WR BB RB BW
 **/

/**
 * 3 BBB BWR RRR RBR BWB RBR
 * 
 */

/**
 * 4 WRBB RRBB RRBB RRBB RRBB RBBB RWRB RRBB
 */
