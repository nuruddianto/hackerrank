package code.srin;//-- do not alter these code, you must start writing your code -------------------
//-- from line 200 ---------------------------------------------------------------

import java.util.Scanner;

interface Constants {
    public static final int MAX_REG = 32;
    public static final int HAF_REG = MAX_REG / 2;
    public static final int MAX_CMD = 4096;
    public static final int MAX_STR = MAX_CMD * 2;
    public static final int MAX_MOV = MAX_CMD * 500;
}

class Core {
    class Memory {
        public int c;  // cmd
        public int i;  // Ri
        public int j;  // Rj or Num
        public int k;  // Rk

        Memory() {
            c = i = j = k = 0;
        }
    }

    private int[] R;  // Register
    private Memory[] M;  // Memory
    private int I;  // Instruction Pointer

    class Result {
        public int c;  // count of command
        public boolean r;  // valid or invalid
        public boolean s;  // start command exist
        public boolean e;  // end command exist

        Result() {
            c = 0;
            r = true;
            s = false;
            e = false;
        }
    }

    private Result rst;

    Core(int[] reg) {
        R = new int[Constants.MAX_REG];
        for (int r = 0; r < Constants.HAF_REG; ++r) {
            R[r] = reg[r];
            R[Constants.HAF_REG + r] = 0;
        }
        M = new Memory[Constants.MAX_CMD];
        for (int c = 0; c < Constants.MAX_CMD; ++c)
            M[c] = new Memory();
        I = 0;
        rst = new Result();
    }

    public boolean save(int cmd, int line) {
        if (!rst.r)
            return false;
        ++rst.c;
        if (line < 0 || Constants.MAX_CMD <= line)
            return (rst.r = false);
        if (line == 0) {
            if (cmd != -2147483648)
                return (rst.r = false);
            M[0].c = 0;
            return (rst.s = true);
        }
        if (0 < line && cmd == -2147483648)
            return (rst.r = false);
        M[line].c = cmd >> 23;
        if (M[line].c == 128 || M[line].c == 64 || M[line].c == 32) {  // (LOAD, Ri, Num) or (ADD, Ri, Num) or (SUB, Ri, Num)
            M[line].i = cmd >> 18 & 31;
            M[line].j = cmd & 262143;
        } else if (M[line].c == 16 || M[line].c == 8) {  // (ADD Ri, Rj) or (SUB Ri, Rj)
            if (0 < (cmd & 8191))
                return (rst.r = false);
            M[line].i = cmd >> 18 & 31;
            M[line].j = cmd >> 13 & 31;
        } else if (M[line].c == 4) {  // JMP Rk
            if (0 < (cmd & 8380671))
                return (rst.r = false);
            M[line].k = cmd >> 8 & 31;
        } else if (M[line].c == 2) {  // CJMP Ri, Rj, Rk
            if (0 < (cmd & 255))
                return (rst.r = false);
            M[line].i = cmd >> 18 & 31;
            M[line].j = cmd >> 13 & 31;
            M[line].k = cmd >> 8 & 31;
        } else if (M[line].c == 1) {  // END Ri
            if (0 < (cmd & 262143))
                return (rst.r = false);
            M[line].i = cmd >> 18 & 31;
            rst.e = true;
        } else {
            return (rst.r = false);
        }
        return true;
    }

    public int execute(int ans) {
        if (!rst.r || !rst.s || !rst.e)
            return 1000000;
        int mov = 0;
        while (++mov < Constants.MAX_MOV && ++I < Constants.MAX_CMD) {
            if (I < 1)
                break;
            switch (M[I].c) {
                case 1:  // END Ri
                    if (ans == R[M[I].i])
                        return rst.c;
                    return 1000000;
                case 2:  // CJMP Ri, Rj, Rk
                    if (R[M[I].i] == R[M[I].j]) {
                        I = R[M[I].k] - 1;
                        if (I < 0 || Constants.MAX_CMD - 1 <= I)
                            return 1000000;
                    }
                    break;
                case 4:  // JMP Rk
                    I = R[M[I].k] - 1;
                    if (I < 0 || Constants.MAX_CMD - 1 <= I)
                        return 1000000;
                    break;
                case 8:  // SUB Ri, Rj
                    R[M[I].i] -= R[M[I].j];
                    break;
                case 16:  // ADD Ri, Rj
                    R[M[I].i] += R[M[I].j];
                    break;
                case 32:  // SUB Ri, Num
                    R[M[I].i] -= M[I].j;
                    break;
                case 64:  // ADD Ri, Num
                    R[M[I].i] += M[I].j;
                    break;
                case 128:  // LOAD Ri, Num
                    R[M[I].i] = M[I].j;
                    break;
            }
        }
        return 1000000;
    }
}

class Cpu {
    private Core core;

    Cpu(Core c) {
        core = c;
    }

    public boolean save(int cmd, int line) {
        return core.save(cmd, line);
    }
}

public class MiniCompiler {
    public static void main(String arg[]) throws Exception {
        //System.setIn(new java.io.FileInputStream("sample_input.txt"));
        Scanner sc = new Scanner(System.in);

        System.out.println("---- user output ----");

        int total = 0;
        int testcase = sc.nextInt();
        for (int t = 1; t <= testcase; ++t)
        {
            // input
            int[] reg = new int[Constants.HAF_REG];
            for (int r = 0; r < Constants.HAF_REG; ++r)
                reg[r] = sc.nextInt();
            String str = sc.next();
            int ans = sc.nextInt();

            // ...
            Core core = new Core(reg);
            Cpu cpu = new Cpu(core);
            UserSolution user = new UserSolution(cpu);

            // implement run() function
            user.run(str);

            // execute
            int count = core.execute(ans);
            total += count;

            // print result
            System.out.println("#" + t + " " + count);
        }

        // print total score
        System.out.println("total : " + total);
    }


}

// -- user code ------------------------------------------------------------------

class UserSolution {
    private Cpu cpu;
    private int currentLine;

    UserSolution(Cpu c) {
        cpu = c;
        currentLine = 0;
    }

    public void run(String str) {
        cpu.save(1 << 31, currentLine++);
        //process
        parseString(str);
        cpu.save(1 << 23 | 21 << 18, currentLine++);
        // TO DO
    }

    void parseString(String str) {
        int startIndex = 0;

        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == '+' || str.charAt(i) == '-' || str.charAt(i) == '*') {
                if (str.charAt(startIndex) == 'R') {
                    enqueue(new Node(0, stringToInteger(str.substring(startIndex + 1, i - startIndex)), Node.Type.Register, Node.TypeOperator.Addition));
                } else {
                    enqueue(new Node(stringToInteger(str.substring(startIndex, i - startIndex)), 0, Node.Type.Number, Node.TypeOperator.Addition));
                }
                startIndex = i + 1;
            }

            switch (str.charAt(i)) {
                case '+':
                    enqueue(new Node(0, 0, Node.Type.Operator, Node.TypeOperator.Addition));
                    break;
                case '-':
                    enqueue(new Node(0, 0, Node.Type.Operator, Node.TypeOperator.Substraction));
                    break;
                case '*':
                    enqueue(new Node(0, 0, Node.Type.Operator, Node.TypeOperator.Multiplication));
                    break;
            }
        }
    }

    void processQueue(){
        Node initial = dequeue();
        addRN(21, initial.mValue, currentLine++);

        while(head != null){
            Node current = dequeue();
            if(current.mType == Node.Type.Operator){

            }
        }
    }

    private static int stringToInteger(String str) {
        int length = str.length();
        int ans = 0;

        for (int i = 0; i < length; i++) {
            int current = str.charAt(i) - '0';
            ans += current * Math.pow(10, length - i - 1);
        }
        return ans;
    }


    private static class Node {
        public enum Type {Number, Operator, Register}

        public enum TypeOperator {Multiplication, Addition, Substraction}

        public static int mValue;
        public static int mRegister;
        public static Type mType;
        public static TypeOperator mTypeOperator;
        public static Node next;

        public Node(int value, int register, Type type, TypeOperator typeOperator) {
            mValue = value;
            mRegister = register;
            mType = type;
            mTypeOperator = typeOperator;
        }
    }

    //Queue function
    Node head;
    Node tail;

    private void enqueue(Node newNode) {
        if (head == null) {
            head = newNode;
        } else {
            tail.next = newNode;
        }
        tail = newNode;
    }

    private Node dequeue() {
        if (head == null) {
            return null;
        }
        Node data = head;
        if (head == tail) {
            tail = null;
        }
        head = head.next;
        return data;
    }

    private void load(int ri, int n, int line) {
        cpu.save(1 << 30 | ri << 18 | n, line);
    }

    private void addRN(int ri, int n, int line) {
        cpu.save(1 << 29 | ri << 18 | n, line);
    }

    private void subRN(int ri, int n, int line) {
        cpu.save(1 << 28 | ri << 18 | n, line);
    }

    private void addRR(int ri, int rj, int line) {
        cpu.save(1 << 27 | ri << 18 | rj << 13, line);
    }

    private void subRR(int ri, int rj, int line) {
        cpu.save(1 << 26 | ri << 18 | rj << 14, line);
    }

    private void jmpRk(int rk, int line) {
        cpu.save(1 << 25 | rk << 8, line);
    }

    private void cjmp(int ri, int rj, int rk, int line) {
        cpu.save(1 << 24 | ri << 18 | rj << 13 | rk << 8, line);
    }

}
