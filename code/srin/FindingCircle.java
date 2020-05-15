package code.srin;

import java.util.Scanner;

/**
 * Created by nurud on 11/02/2017.
 */
public class FindingCircle {
    private static class Node {
        Node next;
        int city;

        public Node(int city) {
            this.city = city;
        }

        public void setNext(Node node) {
            next = node;
        }

        public Node getNext() {
            return next;
        }
    }

    static Node head;
    static Node tail;
    static boolean visited[];

    private static void enqueue(int data) {
        Node newData = new Node(data);
        if (head == null) {
            head = newData;
        } else {
            tail.setNext(newData);
        }
        tail = newData;
    }

    private static int dequeue() {
        int data = head.city;
        if (head == tail) {
            tail = null;
        }
        head = head.getNext();
        return data;
    }

    private static boolean isEmpty() {
        return head == null;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int p = sc.nextInt();

        if(p == 0 || n == 0){
            System.out.print("No");
        }

        FindingCircle[] cities = new FindingCircle[n + 1];
        visited = new boolean[n + 1];
        int startCity = 0;
        for (int i = 0; i < p; i++) {
            int firstCity = sc.nextInt();
            int secondCity = sc.nextInt();
            cities[firstCity].enqueue(secondCity);
            if (i == 0) {
                startCity = firstCity;
            }
        }

        System.out.print(isCircle(cities, startCity));
    }

    private static String isCircle(FindingCircle[] cities, int startCity) {
        if (visited[startCity]) {
            return "Yes";
        }

        visited[startCity] = true;
        while (!cities[startCity].isEmpty()) {
            int nextCity = cities[startCity].dequeue();
            return isCircle(cities, nextCity);
        }
        return "No";
    }
}
