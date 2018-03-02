package code.srin;

import java.util.Scanner;

import org.omg.PortableInterceptor.LOCATION_FORWARD;



public class TimeScheduler {
	interface SEARCH_TYPE{
		public final static int SEARCH_TYPE_TITLE = 0;
		public final static int SEARCH_TYPE_LOCATION = 1;
		public final static int SEARCH_TYPE_DATE = 2;
	}
	
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
		
		//System.out.print(userSolution.deltaDate("200903111114", "200903111113") );
		//System.out.print(userSolution.parseDateTree("200903111113"));
		
		sc.close();
	}
	


static class UserSolution
{	
	final int TABLE_SIZE = 10000;
	final int TITLE = 1;
	final int LOCATION = 2;
	final int START_DATE = 3;
	final int END_DATE = 4;
	
	
	class Node{
		int Id;
		String title;
		String location;
		String start_date;
		String end_date;
		long startDateLong;
		long endDateLong;
		boolean isDeleted;
		Node next;
		Node nextDate;
		
		Node(){
			
		}
		Node(Node newData){
			Id = newData.Id;
			title = newData.title;
			location = newData.location;
			start_date = newData.start_date;
			end_date = newData.end_date;
			startDateLong = newData.startDateLong;
			endDateLong = newData.endDateLong;
		}
	}
	
	Node[] idTable;
	Node[] titleTable;
	Node[] locationTable;
	
	Node mHeadList;
	Node mTailList;
	boolean isMerging;
	
	void insertList(Node newData){
		if(mHeadList == null){
			mTailList = newData;
		}else{
			newData.nextDate = mHeadList;
		}
		
		mHeadList = newData;
	}
	
	
	TimeScheduler.RESULT searchDate(Node tmp, long searchedDate, TimeScheduler.RESULT result){
		int count = 0;
		int[] listId = new int[10000];
		while(tmp != null){
			if( tmp.startDateLong/10000 <= searchedDate && searchedDate <= tmp.endDateLong/10000 && !tmp.isDeleted){
				listId[count] = tmp.Id;
				count++;
			}
			tmp = tmp.nextDate;
		}
		
		result.count = count;
		result.id_list = new int[count];
		for(int i =0; i < count; i++){
			result.id_list[i] = listId[i];
		}
		
		return result;
	}
	
	void put(Node[] table, Node newData, int type){
		int hashVal = 0;
		
		if(type == START_DATE || type == END_DATE){
			return;
		}
		
		switch (type) {
		case TITLE:
			hashVal = hashStr(newData.title.toCharArray());
			break;
		case LOCATION:
			hashVal = hashStr(newData.location.toCharArray());
			break;
		}	
		
		Node tmp = table[hashVal];
		
		if(tmp == null || tmp.isDeleted){
			table[hashVal] = newData;
		}else{
			Node prev = null;
			boolean isEqual = false;
			while(tmp != null){
				switch (type) {
				case TITLE:
					isEqual =  equals(tmp.title, newData.title);
					break;
				case LOCATION:
					isEqual =  equals(tmp.location, newData.location);
					break;
				}
				
				if(isEqual){

					if(mergeNode(type, tmp, newData) == 0){
						isMerging = true;
						return;
					};
					
					if(prev == null){
						newData.next = tmp;
						table[hashVal] = newData;
						return;
					}else{
						newData.next = tmp;
						prev.next = newData;
						return;
					}
				}
				
				prev = tmp;
				tmp = tmp.next;
			}
			prev.next = newData;
		}
	}
	
	Node get(int currentId, String searched, Node[] table, int type){
		int hashVal = hashStr(searched.toCharArray());
		
		Node data = table[hashVal];
		if(data.isDeleted){
			return null;
		}
		while(data != null){
			if(currentId != data.Id){
			switch (type) {
			case TITLE:
				if(equals(searched, data.title)){
					return data;
				}
				break;
			case LOCATION:
				if(equals(searched, data.location)){
					return data;
				}
				break;
			}
			}
			data = data.nextDate;
		}
		
		return null;
	}

	
	boolean equals(String str1, String str2){
		
		if(str1.length() != str2.length()){
			return false;
		}
		
		for(int i=0; i < str1.length(); i++){
			int val = str1.charAt(i) - str2.charAt(i);
			if(val != 0){
				return false;
			}
		}
		
		return true;
	}
	
	boolean equalsDate(String str1, String str2){
		for(int i=0; i < 8; i++){
			int val = str1.charAt(i) - str2.charAt(i);
			if(val != 0){
				return false;
			}
		}
		return true;
	}
	
	boolean isTimeOverlap(Node tmp, Node newData){
		if(tmp.startDateLong > newData.endDateLong || newData.startDateLong > tmp.endDateLong){
			return false;
		}
		return true;
	}
	
	int mergeNode(int type, Node tmp, Node newData){
		if(tmp == null || newData == null || !isTimeOverlap(tmp, newData) || tmp.Id == newData.Id || newData.isDeleted){
			return 1;
		}
		
		if(tmp.Id == newData.Id){
			return 1;
		}
		
		if((type == TITLE && equals(tmp.location, newData.location)) 
				|| (type == LOCATION && equals(tmp.title, newData.title))){
			long startDateTmp = parseDate(tmp.start_date);
			long endDateTmp = parseDate(tmp.end_date);
			
			long startDateNew = parseDate(newData.start_date);
			long endDateNew = parseDate(newData.end_date);
			
			if((startDateTmp - startDateNew)> 0){
				tmp.start_date = newData.start_date;
			} 
			
			if((endDateTmp - endDateNew) < 0){
				tmp.end_date = newData.end_date;
			}
			
			tmp.startDateLong = parseDate(tmp.start_date);
			tmp.endDateLong = parseDate(tmp.end_date);
			
			if(tmp.Id > newData.Id){
				idTable[tmp.Id].isDeleted = true;
			} else {
				
				Node g = idTable[newData.Id];
				if(g != null){
					g.isDeleted = true;
				}
			}
			return 0;
		}
		return 1;
	}
	
	String longToString(long date){
		String.valueOf(date);
		return "";
	}
	
	long parseDate(String date){
		int totalDigit = date.length();
		long firstDate = 0;
		for(int i=0; i < totalDigit; i++){
			long digit = 1;
			for(int j=0; j < totalDigit -1 - i; j++){
				digit *= 10;
			}
			firstDate += (date.charAt(i) - '0') * digit ;
		}
		
		return firstDate;
	}
	
	void Init(){
		idTable = new Node[10000];
		titleTable = new Node[10000];
		locationTable = new Node[10000];
		mHeadList = null;
		mTailList = null;
		isMerging = false;
	}

	void Add(int id, String title, String location, String start_date, String end_date){
		//add to id table
		Node newData = new Node();
		newData.Id = id;
		newData.title = title;
		newData.location = location;
		newData.start_date = start_date;
		newData.end_date = end_date;
		newData.startDateLong = parseDate(start_date);
		newData.endDateLong = parseDate(end_date);
		
		put(titleTable, newData, TITLE);
		put(locationTable, newData, LOCATION);
		if(isMerging){
			isMerging = false;
			return;
		}
		idTable[id] = newData;
		insertList(newData);
		
	}

	int Modify(int id, String title, String location, String start_date, String end_date){
		Node tmp = idTable[id];
		if(tmp == null || tmp.isDeleted){
			return 1;
		}
		
		
		tmp.title = title;
		tmp.location = location;
		tmp.start_date = start_date;
		tmp.end_date = end_date;
		tmp.startDateLong = parseDate(start_date);
		tmp.endDateLong = parseDate(end_date);
		
		int res = 0;
		
		while(res != 1){
			res = mergeNode(TITLE, tmp, get(tmp.Id, title, titleTable, TITLE));	
		}
		
		return 0;
	}

	int Delete(int id){
		Node tmp = idTable[id];
		if(tmp == null || tmp.isDeleted){
			return 1;
		}
		
		tmp.isDeleted = true;

		return 0;
	}

	TimeScheduler.RESULT Search(int type, String str){
		Node tmp = null;
		Node startDate = null;
		Node endDate = null;
		int id[] = new int[10000];
		int count = 0;
		
		int hashVal = hashStr(str.toCharArray());
		
		switch (type) {
		case 0:
			tmp = titleTable[hashVal];
			break;
		case 1:
			tmp = locationTable[hashVal];
			break;
		default:
			break;
		}
		TimeScheduler.RESULT result = new TimeScheduler.RESULT();
		
		if(type == 2){
			result = searchDate(mHeadList, parseDate(str), result);
		} else if(type == 0){
			while(tmp != null){
				if(equals(tmp.title, str) && !tmp.isDeleted){
					id[count] = tmp.Id;
					count++;
				}
				
				tmp = tmp.next;
			}
		} else {
			while(tmp != null){
				if(equals(tmp.location, str) && !tmp.isDeleted){
					id[count] = tmp.Id;
					count++;
				}
				
				tmp = tmp.next;
			}
		}

		
		if(type != 2){
			result.count = count;
			result.id_list = new int[count];
			for(int i=0; i < count; i++){
				result.id_list[i] = id[i];
			}
		}
		
		return result;
	}
	
	int hashStr(char[] str){
		int hashValue = 0;
		int primeNum = 13;
		
		for(int i=0; i < str.length; i++){
			hashValue += (primeNum * (i+1) + str[i]) % TABLE_SIZE;
		}
		return hashValue;
	}
	
	int hashDate(char[] str){
		int hashValue = 0;
		int primeNum = 13;
		
		for(int i=0; i < 8; i++){
			hashValue += (primeNum * (i+1) + str[i]) % TABLE_SIZE;
		}
		return hashValue;
	}
}
}

// -------------------------------

