import java.util.Scanner;

public class Solution {
	private static Scanner sc;
	private static UserSolution userSolution = new UserSolution();
	
	private static int mSeed;
	private static int mrand(int num)
	{
		mSeed = mSeed * 1103515245 + 37209;
		if (mSeed < 0) mSeed *= -1;
		return ((mSeed >> 8) % num);
	}
	private static final int CMD_REQUEST = 0;
	private static final int CMD_FCFS = 1;
	private static final int CMD_SSTF = 2;
	private static final int CMD_LOOK = 3;
	private static final int CMD_CLOOK = 4;

	private static final int MAX = 100000;
	private static final int SAMPLE_SIZE = 200;
	
	private static int track_size;
	private static int track_head;
	private static int answer[] = new int[MAX];
	private static int answer_size;
	private static int answer_idx;
	private static int req_q[] = new int[MAX];
	private static int req_size;
	private static int req_idx;
	private static int cmd_q[] = new int[MAX*2];
	private static int cmd_size;
	private static int cmd_idx;

	private static boolean flag[] = new boolean[MAX];
	
	private static void load_data(int tc){
		track_size = sc.nextInt();
		track_head = sc.nextInt();
		
		if(tc <= 4){
			req_size = sc.nextInt();
			for(int i = 0; i < req_size; ++i) req_q[i] = sc.nextInt();
			cmd_size = sc.nextInt();
			for(int i = 0; i < cmd_size; ++i) cmd_q[i] = sc.nextInt();
			answer_size = sc.nextInt();
			for(int i = 0; i < answer_size; ++i) answer[i] = sc.nextInt();						
		}
		else{		
			req_size = sc.nextInt();
			answer_size = sc.nextInt();
			for(int i = 0; i < answer_size; ++i) answer[i] = sc.nextInt();
			mSeed = sc.nextInt();			
			cmd_size = req_size + answer_size;
		}	
	}


	private static int run(int tc){
		answer_idx = req_idx = cmd_idx = 0;
		int correct = 0;
		int cmd = 0;
		int user_answer = 0;	
		int new_track = 0;
		int req_cnt = 0;
		
		for(int i = 0; i < track_size; ++i) flag[i] = false;
	
		while(req_size != req_cnt || (tc <= 4 && cmd_size != cmd_idx)){
			if(tc <= 4)	cmd = cmd_q[cmd_idx++];
			else cmd = mrand(9);
	
			user_answer = -1;
	
			if(CMD_FCFS <= cmd && CMD_CLOOK >= cmd && (req_cnt - answer_idx) > 0){
				if(cmd == CMD_FCFS) user_answer = userSolution.fcfs();
				else if(cmd == CMD_SSTF) user_answer = userSolution.sstf();
				else if(cmd == CMD_LOOK) user_answer = userSolution.look();
				else user_answer = userSolution.clook();		
	
				if(answer[answer_idx++] == user_answer)	++correct;
			}
			else{			
				if(tc <= 4) new_track = req_q[req_idx++];
				else{
					new_track = mrand(track_size);
					while(flag[new_track]) { 
						++new_track;
						if(new_track == track_size) new_track = 0; 
					} 
				}
			
				userSolution.request(new_track);
				flag[new_track] = true;
				++req_cnt;
			}
		}
		
		return correct;
	}
	
	public static void main(String arg[]) throws Exception {
		System.setIn(new java.io.FileInputStream("sample_input.txt"));		
		sc = new Scanner(System.in);
		
		int total_score = 0;
		int T = sc.nextInt();
			
		for(int tc = 1; tc <= T; ++tc){
			load_data(tc);
			userSolution.init(track_size, track_head);
			int score = run(tc);	
            System.out.println("#" + tc + " " + score);
            total_score += score;
        }
        System.out.println("Total Score: " + total_score);
		sc.close();
	}
}
