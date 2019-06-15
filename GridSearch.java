package code;

import java.util.Scanner;

/**
 * Created by SRIN on 4/26/2017.
 */
public class GridSearch {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int t = 0; t < T; t++) {
            int rowGrid = sc.nextInt();
            int colGrid = sc.nextInt();

            String[] rowG = new String[rowGrid + 1];

            for (int i = 1; i <= rowGrid; i++) {
                rowG[i] = sc.next();
            }

            int rowPattern = sc.nextInt();
            int colPattern = sc.nextInt();

            String rowP[] = new String[rowPattern + 1];

            for (int j = 1; j <= rowPattern; j++) {
                rowP[j] = sc.next();
            }

            boolean firstCharFound = false;
            boolean isContain = false;

            for (int k = 1; k <= rowGrid; k++) {
                for(int i = 0; i < colGrid; i++){
                    if(k == 2 && i == 4){
                        String s = "";
                    }
                    int firstCol = getFirstCol(rowG[k], i, rowP[1], 0, firstCharFound);
                    if(firstCol != 0 && colGrid - firstCol >= rowPattern-1){
                        int rG = k + 1;
                        int rP = 2;
                        isContain = true;
                        while (rG <= rowGrid && rP <= rowPattern) {
                            boolean bol = true;
                            int getCol = getFirstCol(rowG[rG], firstCol - 1, rowP[rP], 0, bol);
                            if (getCol == 0 ) {
                                isContain = false;
                                break;
                            }
                            rG++;
                            rP++;
                        }

                        if (isContain) {
                            break;
                        }
                    }
                }

                if (isContain) {
                    break;
                }

            }

            if (isContain) {
                System.out.println("YES");
            } else {
                System.out.println("NO");
            }
        }
    }

    private static int getFirstCol(String rowGrid, int offsetGrid, String rowPattern, int offsetPattern, boolean firstCharFound) {
        int gridLength = rowGrid.length();
        int patLength = rowPattern.length();

        if (offsetPattern == patLength) {
            return offsetGrid - patLength + 1;
        }

        if (offsetGrid >= gridLength) {
            return 0;
        }

        if (rowGrid.charAt(offsetGrid) - rowPattern.charAt(offsetPattern) != 0) {
            if (firstCharFound) {
                return 0;
            }
            return getFirstCol(rowGrid, offsetGrid + 1, rowPattern, offsetPattern, firstCharFound);
        }

        if (!firstCharFound) {
            firstCharFound = true;
        }
        return getFirstCol(rowGrid, offsetGrid + 1, rowPattern, offsetPattern + 1, firstCharFound);
    }
}

/*
1
        10 10
        7283455864
        6731158619
        8988242643
        3830589324
        2229505813
        5633845374
        6473530293
        7053106601
        0834282956
        4607924137
        3 4
        9505
        3845
        3530

        1
        20 20
34889246430321978567
58957542800420926643
35502505614464308821
14858224623252492823
72509980920257761017
22842014894387119401
01112950562348692493
16417403478999610594
79426411112116726706
65175742483779283052
89078730337964397201
13765228547239925167
26113704444636815161
25993216162800952044
88796416233981756034
14416627212117283516
15248825304941012863
88460496662793369385
59727291023618867708
19755940017808628326
7 4
1641
7942
6517
8907
1376
2691
2599

NO

1
7 15
111111111111111
111111111111111
111111111111111
111111011111111
111111111111111
111111111111111
101010101010101
4 5
11111
11111
11111
11110

YES

1
4 4
1234
4321
9999
9999
2 2
12
21

*/
