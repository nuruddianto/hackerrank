package code.srin;

import java.util.Scanner;

class WidgetRenderer {
	private final static int MAX_ID = 100;
	private final static int MAX_STR_LENGTH = 3000;
	private final static int MAX_IMAGE_HEIGHT = 50;
	private final static int MAX_IMAGE_WIDTH = 50;
	private final static int MAX_SCREEN_HEIGHT = 1000;
	private final static int MAX_SCREEN_WIDTH = 1000;
	private final static int THRESHOLD = 0x07FFFFFF;
	private final static int INIT = 0;
	private final static int CREATE = 1;
	private final static int ADD = 2;
	private final static int SHOW = 3;
	private final static int VWIDGET = 0;
	private final static int HWIDGET = 1;
	private final static int TEXT = 2;
	private final static int IMAGE = 3;

	static class Element {
		public int type;

		Element(int type) {
			this.type = type;
		}
	}

	static class VWidget extends Element {
		public int width;

		VWidget() {
			super(VWIDGET);
		}
	}

	static class HWidget extends Element {
		public int height;

		HWidget() {
			super(HWIDGET);
		}
	}

	static class Text extends Element {
		public char strPtr[];

		Text() {
			super(TEXT);
		}
	}

	static class Image extends Element {
		public int height, width;
		public char imagePtr[];

		Image() {
			super(IMAGE);
		}
	}

	private static int id[] = new int[MAX_ID + 1];
	private static int point, expected;
	private static char baseStr[] = new char[MAX_STR_LENGTH];
	private static char baseImage[][] = new char[MAX_IMAGE_HEIGHT][MAX_IMAGE_WIDTH];
	private static char bufStr[] = new char[MAX_STR_LENGTH];
	private static char bufImage[] = new char[MAX_IMAGE_HEIGHT
			* MAX_IMAGE_WIDTH];
	private static char screen[][] = new char[MAX_SCREEN_HEIGHT][MAX_SCREEN_WIDTH];
	private static UserSolution usersolution = new UserSolution();

	private static void loadBase(Scanner sc) {
		int N, H, W;
		String line;
		N = sc.nextInt();
		sc.nextLine();
		do {
			line = sc.nextLine();
		} while (line.length() != N);
		for (int idx = 0; idx < N; ++idx)
			baseStr[idx] = line.charAt(idx);
		baseStr[N] = '\0';
		H = sc.nextInt();
		W = sc.nextInt();
		for (int y = 0; y < H; ++y) {
			do {
				line = sc.nextLine();
			} while (line.length() != W);
			for (int x = 0; x < W; ++x)
				baseImage[y][x] = line.charAt(x);
		}
	}

	private static VWidget vwidget = new VWidget();
	private static HWidget hwidget = new HWidget();
	private static Text text = new Text();
	private static Image image = new Image();

	private static Element readElement(Scanner sc, int type) {
		int x1, y1, x2, y2, idx;
		int height, width;
		switch (type) {
		case VWIDGET:
			vwidget.width = sc.nextInt();
			return vwidget;
		case HWIDGET:
			hwidget.height = sc.nextInt();
			return hwidget;
		case TEXT:
			x1 = sc.nextInt();
			x2 = sc.nextInt();
			idx = 0;
			for (int x = x1; x <= x2; ++x)
				bufStr[idx++] = baseStr[x];
			bufStr[idx] = '\0';
			text.strPtr = bufStr;
			return text;
		case IMAGE:
			x1 = sc.nextInt();
			y1 = sc.nextInt();
			x2 = sc.nextInt();
			y2 = sc.nextInt();
			idx = 0;
			for (int y = y1; y <= y2; ++y)
				for (int x = x1; x <= x2; ++x)
					bufImage[idx++] = baseImage[y][x];
			image.height = y2 - y1 + 1;
			image.width = x2 - x1 + 1;
			image.imagePtr = bufImage;
			return image;
		default:
			return null; // never executed
		}
	}

	private static int calcHash(char[][] screen, int height, int width) {
		int ret = 0, count = 1;
		for (int y = 0; y < height; ++y)
			for (int x = 0; x < width; ++x) {
				ret += screen[y][x] * count++;
				ret &= THRESHOLD;
			}
		return ret;
	}

	private static void init_m() {
		for (int idx = 0; idx <= MAX_ID; ++idx)
			id[idx] = -1;
		point = 0;
	}

	private static void run(Scanner sc) {
		int lineN = sc.nextInt();
		for (int line = 0; line < lineN; ++line) {
			int command, type;
			int parentId, childId, elementId;
			int height, width;
			int hash, resultHash;
			Element element;
			command = sc.nextInt();
			switch (command) {
			case INIT:
				expected = sc.nextInt();
				usersolution.init();
				break;
			case CREATE:
				elementId = sc.nextInt();
				type = sc.nextInt();
				element = readElement(sc, type);
				id[elementId] = usersolution.create(element);
				break;
			case ADD:
				parentId = sc.nextInt();
				childId = sc.nextInt();
				usersolution.add(id[parentId], id[childId]);
				break;
			case SHOW:
				elementId = sc.nextInt();
				height = sc.nextInt();
				width = sc.nextInt();
				hash = sc.nextInt();
				usersolution.show(id[elementId], screen);
				resultHash = calcHash(screen, height, width);
				if (resultHash == hash)
					point++;
				break;
			}
		}
	}

	public static void main(String[] args) throws Exception {
		int T, total_score;
		// System.setIn(new java.io.FileInputStream("sample_input.txt"));
		Scanner sc = new Scanner(System.in);
		T = sc.nextInt();
		loadBase(sc);
		total_score = 0;
		for (int testcase = 1; testcase <= T; ++testcase) {
			init_m();
			run(sc);
			System.out.println("#" + testcase + " " + point);
			if (point == expected)
				total_score++;
		}
		System.out.println("total score = " + total_score * 100 / T);
		sc.close();
	}

	// -----------------------------------------------------------------------
	// write your code here :

	static class UserSolution {
		public final static int MAX_SCREEN_HEIGHT = 1000;
		public final static int MAX_SCREEN_WIDTH = 1000;
		public final static int VWIDGET = 0;
		public final static int HWIDGET = 1;
		public final static int TEXT = 2;
		public final static int IMAGE = 3;
		public final static byte BORDER = '+';
		public final static byte SPACE = ' ';

		int itemID = 0;
		Item head;
		Item[] listItem;

		public class Item {
			int id;
			int type;
			int startRow;
			int startCol;
			int height;
			int width;
			char[] strChr;
			char[] imageChr;
			Item child;
			Item parent;
			Item contain;
		}

		public void init() {
			itemID = 0;
			head = null;
			listItem = new Item[101];
		}

		public int create(WidgetRenderer.Element element) {
			Item newItem = new Item();
			switch (element.type) {
			case VWIDGET:
				VWidget vw = (VWidget)element;
				newItem.id = itemID;
				newItem.type = VWIDGET;
				newItem.width = vw.width;
				break;
			case HWIDGET:
				HWidget hw = (HWidget)element;
				newItem.id = itemID;
				newItem.type = HWIDGET;
				newItem.height = hw.height;
				break;
			case TEXT:
				Text text = (Text)element;
				newItem.id = itemID;
				newItem.type = TEXT;
				newItem.strChr = text.strPtr;
				break;
			default:
				Image image = (Image)element;
				newItem.id = itemID;
				newItem.type = IMAGE;
				newItem.imageChr = image.imagePtr;
				break;
			}
			return itemID++; // return id
		}

		public void add(int parentId, int childId) {
			addContain(listItem[parentId], listItem[childId]);
		}

		public void show(int elementId, char[][] screen) {
			
		}

		void inserChild(Item newItem) {
			if (head == null) {
				head = newItem;
				return;
			}

			Item tmp = head;

			while (tmp.child != null) {
				tmp = tmp.child;
			}

			tmp.child = newItem;
			newItem.parent = tmp;
		}
		
		void addContain(Item parent, Item contain) {
			if (parent == null) {
				parent = contain;
				return;
			}

			Item tmp = parent;

			while (tmp.contain != null) {
				tmp = tmp.contain;
			}

			tmp.contain = contain;
		}
	}
}
