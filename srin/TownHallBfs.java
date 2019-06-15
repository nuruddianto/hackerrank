package code.srin;

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

    private  Node head;
    private  Node tail;

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
        if (x < N && x >= 0 && y < N && y >= 0 /*&& map[x][y] == 1  */ && !visited[x][y]) {
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
        TownHallBfs th = new TownHallBfs();
        N = sc.nextInt();
        totalHall = sc.nextInt();
        Point hall[] = new Point[totalHall];
        map = new int[N][N];
        visited = new boolean[N][N];

        for (int k = 0; k < totalHall; k++) {
            hall[k] = new Point(sc.nextInt() - 1, sc.nextInt() - 1);
        }

        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                map[i][j] = sc.nextInt();
            }
        }
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                if (map[j][i] == 1) {
                    Point start = new Point(i, j);
                    int newHall[] = th.doBfs(start, hall);
                    int distance = maxValueFromDistance(newHall);
                    if (distance < minDistance) {
                        minDistance = distance;
                    }
                }
            }
        }

        System.out.print(minDistance);
    }

    private int[] doBfs(Point start, Point[] hall) {
        int distHall[] = new int[totalHall];
        TownHallBfs q = new TownHallBfs();
        int d=0;
        while(d < totalHall){
            clearVisisted();
            visited[start.x][start.y] = true;
            int dist=0;
            int minDist = 10000;
            q.enqueue(start, dist);

            while (!q.isEmpty()) {
                Node data = q.dequeue();
                Point pt = data.point;

                if (pt.x == hall[d].x && pt.y == hall[d].y) {
                    if(data.dist == 0){
                        distHall[d] = 1000;
                        continue;
                    }
                    if(data.dist < minDist){
                        distHall[d] = data.dist;
                        continue;
                    }
                }

                if(dist > minDist){
                    continue;
                }

                for (int k = 0; k < 4; k++) {
                    if (isValid(pt.x + xNum[k], pt.y + yNum[k])) {
                        Point newPoint = new Point(pt.x + xNum[k], pt.y + yNum[k]);
                        q.enqueue(newPoint, data.dist+1);
                        visited[newPoint.x][newPoint.y] = true;
                    }
                }
            }

            d++;
        }

        return distHall;
    }

    private static int maxValueFromDistance(int[] distHall) {
        int max = 0;
        for (int i = 0; i < distHall.length; i++) {
            if (distHall[i] > max) {
                max = distHall[i];
            }
        }
        return max;
    }

    private static void clearVisisted(){
        for(int j = 0; j < N; j++){
            for(int i =0; i < N; i++){
                visited[i][j] = false;
            }
        }
    }
}
