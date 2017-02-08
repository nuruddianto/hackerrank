package code;

import java.util.Scanner;

/**
 * Created by SRIN on 2/8/2017.
 */
public class InterstellarCargo {

    private static class Point {
        int x;
        int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private static int totalHole;
    private static int minDistance = 100000000;
    private static Point start;
    private static Point finish;
    private static Point[] inHole;
    private static Point[] outHole;
    private static boolean[] visitedHole;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        start = new Point(sc.nextInt(), sc.nextInt());
        finish = new Point(sc.nextInt(), sc.nextInt());

        totalHole = sc.nextInt();
        visitedHole = new boolean[totalHole * 2];
        inHole = new Point[totalHole * 2];
        outHole = new Point[totalHole * 2];
        for (int i = 0; i < totalHole * 2; i += 2) {
            inHole[i] = new Point(sc.nextInt(), sc.nextInt());
            outHole[i] = new Point(sc.nextInt(), sc.nextInt());
            inHole[i + 1] = outHole[i];
            outHole[i + 1] = inHole[i];
        }

//        for(int j=0 ; j < inHole.length; j++){
//            System.out.print(inHole[j].x+" ");
//        }
        if (totalHole == 0) {
            System.out.print(abs(start.x, finish.x) + abs(start.y, finish.y));
        } else {
            for (int i = 0; i < totalHole * 2; i++) {
                searchMinDistance(start, finish, i, 0);
                clearVisited();
            }
//            searchMinDistance(start,finish, 0, 0);
            System.out.print(minDistance);
        }
    }

    private static void searchMinDistance(Point starts, Point finish, int indexHole, int dist) {
        if (indexHole >= totalHole * 2 || indexHole < 0) {
            return;
        }

        if (visitedHole[indexHole]) {
            return;
        }

        visitedHole[indexHole] = true;

        int distToNextHole = abs(starts.x, inHole[indexHole].x) + abs(starts.y, inHole[indexHole].y);
        int distToFinish = abs(starts.x, finish.x) + abs(starts.y, finish.y);

        if (dist + distToFinish < minDistance) {
            minDistance = dist + distToFinish;
        }

        for(int i=0; i < totalHole*2; i++){
            if(!visitedHole[i]){
                if (distToFinish > distToNextHole && distToNextHole!=0) {
                    Point newStart = new Point(outHole[indexHole].x, outHole[indexHole].y);
                    searchMinDistance(newStart, finish, i, dist + distToNextHole);
                }else{
                    searchMinDistance(starts, finish, i, dist + distToNextHole);
                }
            }
        }

        visitedHole[indexHole] = false;
    }

    private static void clearVisited(){
        for(int i=0; i < visitedHole.length; i++){
            visitedHole[i] = false;
        }
    }
    private static int abs(int one, int two) {
        int distance = two - one;
        if (two - one < 0) {
            return distance * -1;
        }
        return distance;
    }
}
