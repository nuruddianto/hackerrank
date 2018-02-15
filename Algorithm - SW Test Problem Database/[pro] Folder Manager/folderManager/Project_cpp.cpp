#include <stdio.h>
using namespace std;

enum COMMAND {
	CMD_ADD = 1,
	CMD_MOVE,
	CMD_INFECT,
	CMD_RECOVER,
	CMD_REMOVE
};

extern void init();
extern int add(int id, int pid, int fileSize);
extern int move(int id, int pid);
extern int infect(int id);
extern int recover(int id);
extern int remove(int id);

int run() {
	int score = 0;
	int N;
	scanf("%d", &N);

	for (int i=0; i<N; i++) {
		int cmd;
		int ret;

		int id, pid, fileSize;

		scanf("%d", &cmd);

		switch (cmd) {
			case CMD_ADD: {
				
				scanf("%d%d%d", &id, &pid, &fileSize);
				ret = add(id, pid, fileSize);
				break;
			}
			case CMD_MOVE: {
				scanf("%d%d", &id, &pid);
				ret = move(id, pid);
				break;
			}
			case CMD_INFECT: {
				scanf("%d", &id);
				ret = infect(id);
				break;
			}
			case CMD_RECOVER: {
				scanf("%d", &id);
				ret = recover(id);
				break;
			}
			case CMD_REMOVE: {
				scanf("%d", &id);
				ret = remove(id);
				break;
			}
		}

		int checkSum;
		scanf("%d", &checkSum);
		if (ret == checkSum) score++;
		else {
			switch (cmd) {
			case CMD_ADD: {
				printf("  error on CMD_ADD : %d %d %d\n",  id, pid, fileSize);
				break;
			}
			case CMD_MOVE: {
				printf("  error on CMD_MOVE : %d %d\n",  id, pid);
				break;
			}
			case CMD_INFECT: {
				printf("  error on CMD_INFECT : %d \n",  id);
				break;
			}
			case CMD_RECOVER: {
				printf("  error on CMD_RECOVER : %d \n",  id);
				break;
			}
			case CMD_REMOVE: {
				printf("  error on CMD_REMOVE : %d \n",  id);
				break;
			}
		}

		}
	}
	return score;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int totalScore = 0;

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		init();
		int score = run();
		printf("#%d %d\n", t, score);
		totalScore += score;
	}
	printf("Total Score : %d\n", totalScore);
	return 0;
}














// --------------------------------------------------------------------------------------------------------------------------------------------------------
#define maxID 1000000001

const bool isDebug = true;

struct t_data {
	int ID;
	int parentID;
	int originalSize;
	int currentSize;
	int totalFileCount;
	t_data *parent;
	t_data *childHead;
	t_data *childTail;
	t_data *next;
	t_data *prev;
};

// simple BST
typedef struct t_index {
    int id;
	t_data *data;
    t_index *parent;
    t_index *left;
    t_index *right;
};


struct t_properties {
	int filesize;
	int filecount;
};

t_index *indexTree;
t_data  *fileTree;


// --------------------------------------------------------------------------------------------------------------------------------------------------------



void deleteIndexTree(t_index *point){
    if (point != NULL) {
        deleteIndexTree(point->left);
        deleteIndexTree(point->right);
		
		//printf("deleting [%d] from index tree\n", point->data->ID);
		delete point;
    }
}

t_index *searchBST(t_index *l, int id){
    if (l == NULL) return(NULL);
    
    if (l->id == id) return(l);
    
    if (id < l->id)
        return( searchBST(l->left, id) );
    else
        return( searchBST(l->right, id) );
}

t_data *findIndex(int id) {
	//if (id == 10000) return NULL;

	t_data *point = NULL;
	t_index *index = searchBST(indexTree, id);
	
	if (id != NULL) return index->data;
	else return NULL;
}

t_properties findMyProperties(t_data *point) {
	t_properties currentProperties;
	currentProperties.filecount = point->totalFileCount;
	currentProperties.filesize = point->currentSize;

	return currentProperties;

	//if (point != NULL) {
	//	// handle if is file
	//	if (point->originalSize != 0) {
	//		currentProperties.filecount++;
	//		currentProperties.filesize += point->currentSize;
	//	} else {
	//		// is a folder and we must iterate trough it's childs
	//		t_data *children = point->childHead;
	//		while (children != NULL) {
	//			if (children->originalSize != 0) {
	//				currentProperties.filecount++;
	//				currentProperties.filesize += point->currentSize;
	//			} else {
	//				t_properties 
	//			}
	//	} 
	//		}
	//	}
	//}
}

void updatePropertiesOfMyParents(t_data *parent, t_properties properties) {
	if (parent != NULL) {
		parent->totalFileCount += properties.filecount;
		parent->currentSize += properties.filesize;
		updatePropertiesOfMyParents(parent->parent, properties);
	}
}

int addToFileTree (t_data *pChild, t_data *pParent) {
	if (pChild->ID == 10000) return 0;

	int totalFileSize = 0;

	// if parent is still empty
	if (pParent->childHead == NULL) {
		pParent->childHead = pChild;
		pParent->childTail = pChild;	
	} else { // add to it's tail
		pChild->prev = pParent->childTail;
		pParent->childTail->next = pChild;
		pParent->childTail = pChild;
	}

	t_properties newProperties = findMyProperties(pChild);
	updatePropertiesOfMyParents(pParent, newProperties);

	//pParent->currentSize += pChild->currentSize;
	//if (pChild->originalSize != 0) pParent->totalFileCount++;

	return pParent->currentSize;
}

void insertBST(t_index **l, int id, t_data *pData, t_index *parent){
    t_index *p;            /* temporary pointer */
    
    if (*l == NULL) {
        p = new t_index();
        p->id = id;
		p->data = pData;
        p->left = p->right = NULL;
        p->parent = parent;
        *l = p;
        return;
    }
    
    if (id < (*l)->id)
        insertBST(&((*l)->left), id, pData, *l);
    else
        insertBST(&((*l)->right), id, pData, *l);
}

void addToIndexTree(int id, t_data *pData) {
	insertBST(&indexTree, id, pData, NULL);
}

int dataAdd(int id, int pid, int fileSize) {
	t_data *parentPointer;
	if (id == 10000) parentPointer = NULL;
	else parentPointer = findIndex(pid);
	
	t_data *newData = new t_data();
	newData->ID = id;
	newData->parentID = pid;
	newData->originalSize = fileSize;
	newData->currentSize = fileSize;
	if (fileSize == 0) newData->totalFileCount = 0;
	else newData->totalFileCount = 1;
	newData->parent = parentPointer;
	newData->childHead = NULL;
	newData->childTail = NULL;
	newData->next = NULL;
	newData->prev = NULL;

	int totalFileSize = addToFileTree(newData, parentPointer);
	addToIndexTree(id, newData);

	printf ("adding [%d/%d] to parent [%d] resulting in total size of [%d]\n", id, fileSize, pid, totalFileSize); 

	return totalFileSize;
}



void moveData(t_data *point, t_data *newParent) {
	t_data *oldParent = point->parent;

	// handle on the old parent 
	if ((oldParent->childHead == point) && (oldParent->childTail == point)) {
		oldParent->childHead = NULL;
		oldParent->childTail = NULL;
	}
	if (oldParent->childHead == point) {
		oldParent->childHead = point->next;
	} else if (oldParent->childTail == point) {
		oldParent->childTail = point->prev;
		oldParent->childTail->next = NULL;
	} else {
		point->prev->next = point->next;
		point->next->prev = point->prev;
	}

	// handle on new parent
	// if parent is still empty
	if (newParent->childHead == NULL) {
		newParent->childHead = point;
		newParent->childTail = point;	
		point->next = NULL;
		point->prev = NULL;
	} else { // add to it's tail
		point->next = NULL;
		point->prev = newParent->childTail;
		newParent->childTail->next = point;
		newParent->childTail = point;
	}
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------


void init() {
	// purge the file stack
	// remove(10000)

	// purge the file index
	deleteIndexTree(indexTree);

	// add the root to both filestack and index
	dataAdd(10000, 10000, 0);
	
}

int add(int id, int pid, int fileSize) {
	return dataAdd(id, pid, fileSize);
}

int move(int id, int pid) {
	t_data *pointData, *pointNewParent;

	pointData = findIndex(id);
	pointNewParent = findIndex(pid);

	t_properties totalProperties = findMyProperties(pointData);
	t_properties totalPropertiesNegative;

	totalPropertiesNegative.filesize = -1 * totalProperties.filesize;
	totalPropertiesNegative.filecount = -1 * totalProperties.filecount;	

	updatePropertiesOfMyParents(pointData->parent, totalPropertiesNegative);
	updatePropertiesOfMyParents(pointNewParent, totalProperties);

	int totalSize = pointNewParent->currentSize;

	moveData(pointData, pointNewParent);

	return totalSize;
}

int infectID(t_data *pointData, int virusSize) {
	if (pointData->originalSize != 0) {
		pointData->currentSize += virusSize;

		t_properties newProperties;
		newProperties.filecount = 0;
		newProperties.filesize = virusSize;
		updatePropertiesOfMyParents(pointData->parent, newProperties);		
	} else {
		t_properties oldProperties;
		oldProperties.filecount = pointData->totalFileCount;
		oldProperties.filesize = pointData->currentSize;

		t_data *children = pointData->childHead;
		while (children != NULL) {
			infectID(children, virusSize);			
			children = children->next;
		}

		t_properties newProperties;
		newProperties.filecount = pointData->totalFileCount;
		newProperties.filesize = pointData->currentSize - oldProperties.filesize;

		updatePropertiesOfMyParents(pointData->parent, newProperties);
	}

	return pointData->currentSize;
}

int infect(int id) {
	t_data *root = findIndex(10000);
	int virusSize = root->currentSize / root->totalFileCount;
	
	t_data *pointData = findIndex(id);	
	int totalDamage = infectID(pointData, virusSize);
	
	printf("infecting : [%d] returns [%d]\n", id, totalDamage);

	return totalDamage;
}

int recover(int id) {
	return -1;
}

int remove(int id) {
	return -1;
}
