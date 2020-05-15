package code;

import java.io.*;
import java.math.*;
import java.security.*;
import java.text.*;
import java.util.*;
import java.util.concurrent.*;
import java.util.regex.*;

public class CrosswordPuzzle {

    static class Loc {
        int row;
        int col;
        int length;
        String word;

        public Loc(int r, int c, int l) {
            row = r;
            col = c;
            length = l;
        }
    }

    static List<Loc> horizontal;
    static List<Loc> vertical;
    static String[] result;

    static final int size = 10;
    static char[][] map;
    static boolean isPlus;

    static String[] crosswordPuzzle(String[] crossword, String words) {
        List<String> wordList = new LinkedList<String>();
        horizontal = new LinkedList<Loc>();
        vertical = new LinkedList<Loc>();

        map = new char[size][size];
        initMap(crossword);
        findLocation();
        Collections.addAll(wordList, words.split(";"));
        backtrack(wordList);
        return result;
    }

    static void findLocation() {
        // find horizontal
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (r == 6 && c == 4) {
                    String s = "";
                }
                if (map[r][c] == '+' || map[r][c] == '1')
                    continue;

                if (map[r][c] != '1' && c < size - 1 && map[r][c + 1] != '+') {
                    int horizontalLeng = 0;
                    int col = c;
                    while (col < size && map[r][col] != '+') {
                        horizontalLeng++;
                        map[r][col] = '1';
                        col++;
                    }

                    horizontal.add(new Loc(r, c, horizontalLeng));
                }
            }
        }

        // find vertical
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (map[r][c] == '+' || map[r][c] == '2')
                    continue;

                if (map[r][c] != '2' && r < size - 1 && map[r + 1][c] != '+') {
                    int verticalLength = 0;
                    int row = r;
                    while (row < size && map[row][c] != '+') {
                        verticalLength++;
                        map[row][c] = '2';
                        row++;
                    }

                    vertical.add(new Loc(r, c, verticalLength));
                }
            }
        }

    }

    static void backtrack(List<String> wordList) {
        if (wordList.size() == 0) {
            String[] res = fillTheMap(wordList);
            if (res != null) {
                result = res;
            }
            return;
        }

        for (int i = 0; i < wordList.size(); i++) {
            String word = wordList.get(i);
            wordList.remove(i);

            // findVertical solution
            for (int v = 0; v < vertical.size(); v++) {
                Loc curr = vertical.get(v);
                if (word.length() != curr.length || curr.word != null)
                    continue;

                curr.word = word;
                backtrack(wordList);
                curr.word = null;
            }

            if (word.equals("YANGON")) {
                String s = "s";
            }
            // findHorizontal solution
            for (int h = 0; h < horizontal.size(); h++) {
                Loc curr = horizontal.get(h);
                if (word.length() != curr.length || curr.word != null)
                    continue;

                curr.word = word;
                backtrack(wordList);
                curr.word = null;
            }

            wordList.add(word);
        }
    }

    static String[] fillTheMap(List<String> wordList) {
        String[] result = new String[size];
        char[][] board = copyMap();

        for (int h = 0; h < horizontal.size(); h++) {
            Loc curr = horizontal.get(h);
            int col = curr.col;
            for (int i = 0; i < curr.length; i++) {
                if (curr.word == null)
                    continue;

                char c = curr.word.charAt(i);
                if (board[curr.row][col] != '-' && board[curr.row][col] != c) {
                    return null;
                }

                board[curr.row][col] = c;
                col++;
            }

        }

        for (int v = 0; v < vertical.size(); v++) {
            Loc curr = vertical.get(v);
            int row = curr.row;
            for (int i = 0; i < curr.length; i++) {
                char c = curr.word.charAt(i);
                if (board[row][curr.col] != '-' && board[row][curr.col] != c) {
                    return null;
                }

                board[row][curr.col] = c;
                row++;
            }
        }

        if (!isPlus) {
            for (int r = 0; r < size; r++) {
                for (int c = 0; c < size; c++) {
                    if (board[r][c] == '+')
                        board[r][c] = 'X';
                }
            }
        }
        for (int r = 0; r < size; r++) {
            String s = new String(board[r]);
            result[r] = s;
        }
        return result;
    }

    static void initMap(String[] crossword) {
        for (int row = 0; row < size; row++) {
            for (int col = 0; col < size; col++) {
                if (crossword[row].charAt(col) == '+') {
                    isPlus = true;
                }
                char c = crossword[row].charAt(col) == 'X' || crossword[row].charAt(col) == '+' ? '+' : '-';
                map[row][col] = c;
            }
        }
    }

    static char[][] copyMap() {
        char[][] newMap = new char[size][size];
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                if (map[r][c] == '+') {
                    newMap[r][c] = '+';
                    continue;
                }

                newMap[r][c] = '-';
            }
        }
        return newMap;
    }

    private static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) throws IOException {

        String[] crossword = new String[10];

        for (int i = 0; i < 10; i++) {
            String crosswordItem = scanner.nextLine();
            crossword[i] = crosswordItem;
        }

        String words = scanner.nextLine();

        String[] result = crosswordPuzzle(crossword, words);

        for (int i = 0; i < result.length; i++) {
            System.out.println(result[i]);
        }

        scanner.close();
    }

    static void print(char[][] m) {
        System.out.println();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(m[i][j] + " ");
            }
            System.out.println();
        }
    }
}

// +M++++++++
// +ANDAMAN++
// +N++L+++++
// +ICELAND++
// +P++E++++P
// +U++P++++U
// +R++YANGON
// +++++++++E
// ++++++++++
// ++++++++++
