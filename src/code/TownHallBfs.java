package code;

import java.util.Scanner;

/**
 * Created by SRIN on 2/3/2017.
 */
public class TownHallBfs {
    private static class Point {
        int x;
        int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private class Node {
        Point point;
        Node next;
        int dist;

        public Node(Point point, int dist) {
            this.point = point;
            this.dist = dist;
        }

        public Node getNext() {
            return next;
        }

        public void setNext(Node next) {
            this.next = next;
        }
    }

    private static Node head;
    private static Node tail;

    private void enqueue(Point point, int dist) {
        Node newNode = new Node(point, dist);
        if (isEmpty()) {
            head = newNode;
        } else {
            tail.setNext(newNode);
        }

        tail = newNode;
    }

    private Node dequeue() {
        Node data = head;
        if (head == tail) {
            tail = null;
        }
        head = head.getNext();
        return data;
    }

    private boolean isEmpty() {
        return head == null;
    }

    private static boolean isValid(int x, int y) {
        if (x < N && x >= 0 && y < N && y >= 0 && map[x][y] == 1  /* && !visited[x][y]*/) {
            return true;
        }
        return false;
    }

    private static int map[][];
    private static boolean visited[][];
    private static int N;
    private static int totalHall;
    private static int minDistance = 100000;

    private static int yNum[] = {-1, 1, 0, 0};
    private static int xNum[] = {0, 0, -1, 1};

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        N = sc.nextInt();
        totalHall = sc.nextInt();
        Point hall[] = new Point[totalHall];
        map = new int[N][N];
        visited = new boolean[N][N];

        for (int k = 0; k < totalHall; k++) {
            hall[k] = new Point(sc.nextInt(), sc.nextInt());
        }

        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                map[i][j] = sc.nextInt();
            }
        }
        int bestPoint[] = new int[totalHall];
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                if(map[i][j] == 1){
                    Point start = new Point(i,j);
                    int newHall[] = doBfs(start, hall);
                    int distance =  getTotalDistance(newHall);
                    if(distance < minDistance){
                        minDistance = distance;
                        bestPoint = newHall;
                    }
                }
            }
        }

        System.out.print(maxValueFromDistance(bestPoint));

        /*TownHallBfs q = new TownHallBfs();
        for(int o =0; o < 5; o++ ){
            Point point = new Point(o,o);
            q.enqueue(point);
        }

        for(int o =0; o < 5; o++ ){
            Node data = q.dequeue();
            System.out.println("X: "+ data.point.x);
        }*/
    }

    private static int[] doBfs(Point start, Point[] hall) {
        TownHallBfs q = new TownHallBfs();
        int dist = 0;
        q.enqueue(start, dist);
        int distHall[] = new int[totalHall];
        visited[start.x][start.y] = true;
        int count = 0;
        while (!q.isEmpty() && count <= totalHall){
            Node data = q.dequeue();
            Point pt = data.point;

            for(int i=0; i < totalHall; i++){
                if(pt.x == hall[i].x && pt.y == hall[i].y){
                    distHall[i] = data.dist;
                    count++;
                }
            }

            for(int k =0; k < 4 ; k++){
                if(isValid(pt.x + xNum[k], pt.y + yNum[k])){
                    Point newPoint = new Point(pt.x + xNum[k], pt.y + yNum[k]);
                    q.enqueue(newPoint, dist+1);
                    visited[newPoint.x][newPoint.y] = true;
                }
            }

        }

        return distHall;
    }

    private static int getTotalDistance(int[] distHall){
        int totalDistance = 0;
        for(int i =0; i < distHall.length; i++){
            totalDistance += distHall[i];
        }
        return totalDistance;
    }

    private static int maxValueFromDistance(int[] distHall){
        int max =0;
        for(int i=0; i < distHall.length; i++){
            if(distHall[i]>max){
                max = distHall[i];
            }
        }
        return max;
    }
}
