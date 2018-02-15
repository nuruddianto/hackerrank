import java.util.Scanner;

interface SEARCH_TYPE{
	public final static int SEARCH_TYPE_TITLE = 0;
	public final static int SEARCH_TYPE_LOCATION = 1;
	public final static int SEARCH_TYPE_DATE = 2;
}

class Solution {
	private static Scanner sc;
	private static UserSolution userSolution = new UserSolution();

	static class RESULT{
		int count;
		int id_list[];
	}

	private static final int CMD_INIT = 0;
	private static final int CMD_ADD = 1;
	private static final int CMD_MODIFY = 2;
	private static final int CMD_DELETE = 3;
	private static final int CMD_SEARCH = 4;

	private static int Score, ScoreIdx;

	private static void cmd_init(){
		Score = 1000;
		ScoreIdx = Integer.parseInt(sc.next());
		userSolution.Init();
	}

	private static void cmd_add(){
		int newid = Integer.parseInt(sc.next());
		String newTitle = sc.next();
		String newLocation = sc.next();
		String newStartDate = sc.next();
		String newEndDate = sc.next();
		userSolution.Add(newid, newTitle, newLocation, newStartDate, newEndDate);
	}

	private static void cmd_modify(){
		int modifyid = Integer.parseInt(sc.next());
		String newTitle = sc.next();
		String newLocation = sc.next();
		String newStartDate = sc.next();
		String newEndDate = sc.next();
		int check = Integer.parseInt(sc.next());

		int result = userSolution.Modify(modifyid, newTitle, newLocation, newStartDate, newEndDate);
		if (result != check)
			Score -= ScoreIdx;
	}

	private static void cmd_delete(){
		int modifyid = Integer.parseInt(sc.next());
		int check = Integer.parseInt(sc.next());

		int result = userSolution.Delete(modifyid);
		if (result != check)
			Score -= ScoreIdx;
	}

	private static void cmd_search(){
		int searchType = Integer.parseInt(sc.next());
		String str = sc.next();
		int checkCnt = Integer.parseInt(sc.next());
		int check = Integer.parseInt(sc.next());

		RESULT result = userSolution.Search(searchType, str);

		if (result.count != checkCnt || result.id_list == null || result.count > result.id_list.length)
			Score -= ScoreIdx;
		else{
			int checkSum = 0;
			for (int i = 0; i < result.count; ++i)
				checkSum += result.id_list[i];
			if (checkSum != check)
				Score -= ScoreIdx;
		}
	}

	private static void run(){
		int N = Integer.parseInt(sc.next());
		for (int i = 0; i < N; ++i){
			int cmd = Integer.parseInt(sc.next());
			switch (cmd){
			case CMD_INIT:   cmd_init();   break;
			case CMD_ADD:    cmd_add();    break;
			case CMD_MODIFY: cmd_modify(); break;
			case CMD_DELETE: cmd_delete(); break;
			case CMD_SEARCH: cmd_search(); break;
			default: break;
			}
		}
	}

	public static void main(String arg[]) throws Exception{
		//System.setIn(new java.io.FileInputStream("sample_input.txt"));		
		sc = new Scanner(System.in);

		int T = sc.nextInt();
		int TotalScore = 0;

		for (int tc = 1; tc <= T; ++tc){
			run();
			if (Score < 0)	Score = 0;

			TotalScore += Score;
			System.out.println("#" + tc + " " + Score);
		}
		System.out.println("Total Score = " + TotalScore);
		sc.close();
	}
}

// -------------------------------


class UserSolution
{
	void Init(){

	}

	void Add(int id, String title, String location, String start_date, String end_date){

	}

	int Modify(int id, String title, String location, String start_date, String end_date){

		return -1;
	}

	int Delete(int id){

		return -1;
	}

	Solution.RESULT Search(int type, String str){
		Solution.RESULT result = new Solution.RESULT();
		result.count = -1;

		return result;
	}
}