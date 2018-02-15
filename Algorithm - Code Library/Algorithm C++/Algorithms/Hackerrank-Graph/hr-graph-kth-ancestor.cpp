/*
Problem Statement

A tree of P nodes is an un-directed connected graph having P-1 edges. Let us denote R as the root node. If A is a node such that it is at a distance of L from R, and B is a node such that it is at at distance of L+1 from R and A is connected to B, then we call A as the parent of B.

Similarly, if A is at a distance of L from R and B is at a distance of L+K from R and there is a path of length K from A to B, then we call A as the Kth parent of B.

Susan likes to play with graphs and Tree data structure is one of her favorites. She has designed a problem and wants to know if anyone can solve it. Sometimes she adds or removes a leaf node. Your task is to figure out the K-th parent of a node at any instant.

Input Format
The first line contain an integer T denoting the number of test-cases. T test cases follow. First line of each test case contains an integer P, the number of nodes in the tree. P lines follows each containing two integers X and Y separated by a single space denoting Y as the parent of X. if Y is 0, then X is the root node of the tree. (0 is for namesake and is not in the tree).
The next line contains an integer Q, the number of queries.
Q lines follow each containing a query.

 0 Y X : X is added as a new leaf node whose parent is Y
 1 X : This tells that leaf node X is removed from the tree
 2 X K : In this query output the Kth parent of X
 Note
 
 Each node index is any number between 1 and 105 i.e., a tree with a single node can have its root indexed as 105
 
 Output Format
 For each query of type 2, output the Kth parent of X. If Kth parent doesn't exist, output 0 and if the node doesn't exist, output 0.
 
 Constraints
 1<=T<=3
 1<=P<=105
 1<=Q<=105
 1<=X<=105
 0<=Y<=105
 1<=K<=105
 
 Sample Input
 
 2
 7
 2 0
 5 2
 3 5
 7 5
 9 8
 8 2
 6 8
 10
 0 5 15
 2 15 2
 1 3
 0 15 20
 0 20 13
 2 13 4
 2 13 3
 2 6 10
 2 11 1
 2 9 1
 1
 10000 0
 3
 0 10000 4
 1 4
 2 4 1
 Sample Output
 
 2
 2
 5
 0
 0
 8
 0
 Explanation
 
 There are 2 test cases. The first test case has 7 nodes with 2 as its root. There are 10 queries
 
 0 5 15 -> 15 is added as a leaf node to 5.
 2 15 2 -> 2nd parent of 15 is 15->5->2 is 2.
 1 3 -> leaf node 3 is removed from the tree.
 0 15 20 -> 20 is added as a leaf node to 15.
 0 20 13 -> 13 is added as a leaf node to 20.
 2 13 4 -> 4th parent of 13 is 2.
 2 13 3 -> 3rd parent of 13 is 5.
 2 6 10 -> there is no 10th parent of 6 and hence 0.
 2 11 1 -> 11 is not a node in the tree, hence 0.
 2 9 1 -> 9's parent is 8.
 the second testcase has a tree with only 1 node (10000).
 
 0 10000 4 -> 4 is added as a leaf node to 10000.
 1 4 -> 4 is removed.
 2 4 1 -> as 4 is already removed, answer is 0.
*/


#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string.h>

struct Node
{
    int value;
    int degree;
    Node * parent;
    Node * farAncestor;
    Node * veryFarAncestor;
};

typedef std::map<int, Node *> map_nodes_t;
typedef map_nodes_t::iterator map_nodes_it;
typedef std::list<int> list_values_t;
typedef list_values_t::iterator list_values_it;

enum Actions
{
    ACT_NONE = -1,
    ACT_ADD_LEAF = 0,
    ACT_DEL_LEAF = 1,
    ACT_QUERY_ANCESTOR = 2,
    ACT_MAX
};

const int MAX_ELEMENTS = 100*1000;

class NodeProcessor
{
public:
    //
    static const int MIN_LOOKUP_BASE_1 = 32;
    //
    static const int MIN_LOOKUP_BASE_2 = 512;
    
    //
    NodeProcessor(int fastLookUpBase_ = 100, int veryFastLookUpBase_ = 1000);
    
    //
    ~NodeProcessor();
    
    //
    void reset();
    
    //
    void setInitCount(int nodeCount);
    
    //
    void setRoot(int nodeValue);
    
    //
    void addPair(int value1, int value2);
    
    //
    void addLeaf(int parentValue, int nodeValue);
    
    //
    void deleteLeaf(int nodeValue);
    
    //
    int queryAncestor(int nodeValue, int k);
private:
    list_values_t * mapUndecidedNodes[MAX_ELEMENTS + 1];
    char visited[MAX_ELEMENTS + 1];
    Node * mapOfNodes[MAX_ELEMENTS + 1];
    Node * pRoot;
    int initCount;
    int fastLookUpBase;
    int veryFastLookUpBase;
};

void process_input(std::istream & istr, std::ostream & ostr)
{
    NodeProcessor nodeProcessor;
    int T;
    
    istr >> T;
    
    for(int treeIdx = 0; treeIdx < T; ++treeIdx)
    {
        int P, Q, value1, value2, X, Y, K, C;
        
        istr >> P;
        
        for(int lineIdx = 0; lineIdx < P; ++lineIdx)
        {
            istr >> value1 >> value2;
            
            if(0 == value1)
            {
                nodeProcessor.setRoot(value2);
            }
            else if(0 == value2)
            {
                nodeProcessor.setRoot(value1);
            }
            else
            {
                nodeProcessor.addPair(value1, value2);
            }
        }
        
        istr >> Q;
        
        for(int queryIdx = 0; queryIdx < Q; ++queryIdx)
        {
            istr >> C;
            switch (C) {
                case ACT_ADD_LEAF:
                    istr >> X >> Y;
                    nodeProcessor.addLeaf(X, Y);
                    break;
                case ACT_DEL_LEAF:
                    istr >> X;
                    nodeProcessor.deleteLeaf(X);
                    break;
                case ACT_QUERY_ANCESTOR:
                    istr >> X >> K;
                    ostr << nodeProcessor.queryAncestor(X, K) << std::endl;
                    break;
                default:
                    break;
            }
        }
        
        nodeProcessor.reset();
    }
}

int main()
{
    process_input(std::cin, std::cout);
    //std::ifstream istr("/Users/vietlq/projects/viet-github-cpp/hacker-rank-2013-08/03-kth-ancestor/test01.txt");
    //process_input(istr, std::cout);
    
    return 0;
}

NodeProcessor::NodeProcessor(int fastLookUpBase_, int veryFastLookUpBase_):
pRoot(NULL), initCount(0),
fastLookUpBase(fastLookUpBase_),
veryFastLookUpBase(veryFastLookUpBase_)
{
    if(fastLookUpBase < MIN_LOOKUP_BASE_1)
    {
        fastLookUpBase = MIN_LOOKUP_BASE_1;
    }
    
    if(veryFastLookUpBase < MIN_LOOKUP_BASE_2)
    {
        veryFastLookUpBase = MIN_LOOKUP_BASE_2;
    }
    
    //
    for(int idx = 0; idx <= MAX_ELEMENTS; ++idx)
    {
        mapUndecidedNodes[idx] = NULL;
        mapOfNodes[idx] = NULL;
    }
    memset(visited, 0, MAX_ELEMENTS + 1);
}

NodeProcessor::~NodeProcessor()
{
    reset();
}

void NodeProcessor::reset()
{
    //
    initCount = 0;
    //
    memset(visited, 0, MAX_ELEMENTS + 1);
    //
    for(int idx = 0; idx <= MAX_ELEMENTS; ++idx)
    {
        //
        if(NULL != mapUndecidedNodes[idx])
        {
            delete mapUndecidedNodes[idx];
            mapUndecidedNodes[idx] = NULL;
        }
        //
        if(NULL != mapOfNodes[idx])
        {
            delete mapOfNodes[idx];
            mapOfNodes[idx] = NULL;
        }
    }
    //
    pRoot = NULL;
}

void NodeProcessor::setInitCount(int nodeCount)
{
    if(nodeCount > 0) initCount = nodeCount;
    
    initCount = nodeCount;
}

void NodeProcessor::setRoot(int nodeValue)
{
    pRoot = new Node;
    pRoot->parent = NULL;
    pRoot->farAncestor = NULL;
    pRoot->veryFarAncestor = NULL;
    pRoot->degree = 0;
    pRoot->value = nodeValue;
    
    mapOfNodes[nodeValue] = pRoot;
}

void NodeProcessor::addPair(int value1, int value2)
{
    Node * pNode1 = mapOfNodes[value1];
    Node * pNode2 = mapOfNodes[value2];
    Node * pNode = NULL;
    
    if((NULL == pNode1) && (NULL == pNode2))
    {
        if(NULL == mapUndecidedNodes[value1])
        {
            mapUndecidedNodes[value1] = new list_values_t;
        }
        if(NULL == mapUndecidedNodes[value2])
        {
            mapUndecidedNodes[value2] = new list_values_t;
        }
        
        mapUndecidedNodes[value1]->push_back(value2);
        mapUndecidedNodes[value2]->push_back(value1);
        return;
    }
    
    // Either value1 or value2 is found and the remaining is not
    int nodeValue;
    if(NULL == pNode1)
    {
        // If value1 is not found
        addLeaf(value2, value1);
        pNode = mapOfNodes[value1];
        nodeValue = value1;
    }
    else
    {
        // If value2 is not found
        addLeaf(value1, value2);
        pNode = mapOfNodes[value2];
        nodeValue = value2;
    }
    
    // Consolidation
    std::list<int> listOfValues;
    listOfValues.push_back(nodeValue);
    
    while(listOfValues.size())
    {
        int currNodeValue = listOfValues.front();
        listOfValues.pop_front();
        
        if(visited[currNodeValue]) return;
        visited[currNodeValue] = 1;
        
        if(NULL == mapUndecidedNodes[nodeValue]) return;
        
        const list_values_t * unMappedNodes = mapUndecidedNodes[nodeValue];
        list_values_t::const_iterator tempIt = unMappedNodes->begin();
        const list_values_t::const_iterator tempEnd = unMappedNodes->end();
        
        for(; tempIt != tempEnd; ++tempIt)
        {
            listOfValues.push_back(*tempIt);
            addLeaf(currNodeValue, *tempIt);
        }
        
        // Remove
        delete mapUndecidedNodes[currNodeValue];
        mapUndecidedNodes[currNodeValue] = NULL;
    }
}

void NodeProcessor::addLeaf(int parentValue, int nodeValue)
{
    Node * pParentNode = mapOfNodes[parentValue];
    if(NULL == pParentNode) return;
    
    Node * pNode = new Node;
    pNode->value = nodeValue;
    pNode->parent = pParentNode;
    pNode->degree = pNode->parent->degree + 1;
    
    //
    if(pNode->degree <= veryFastLookUpBase)
    {
        pNode->veryFarAncestor = pRoot;
    }
    else if(1 == (pNode->degree % veryFastLookUpBase))
    {
        pNode->veryFarAncestor = pNode->parent;
    }
    else
    {
        pNode->veryFarAncestor = pNode->parent->veryFarAncestor;
    }
    
    //
    if(pNode->degree <= fastLookUpBase)
    {
        pNode->farAncestor = pRoot;
    }
    else if(1 == (pNode->degree % fastLookUpBase))
    {
        pNode->farAncestor = pNode->parent;
    }
    else
    {
        pNode->farAncestor = pNode->parent->farAncestor;
    }
    
    mapOfNodes[nodeValue] = pNode;
}

void NodeProcessor::deleteLeaf(int nodeValue)
{
    if(NULL == mapOfNodes[nodeValue]) return;
    
    delete mapOfNodes[nodeValue];
    mapOfNodes[nodeValue] = NULL;
}

int NodeProcessor::queryAncestor(int nodeValue, int k)
{
    // If the node does not exist, return 0
    Node * pNode = mapOfNodes[nodeValue];
    if(NULL == pNode) return 0;
    
    // If the degree of the node is < k, return 0
    if(pNode->degree < k)return 0;
    
    if(pNode->degree == k)
    {
        if(NULL == pRoot) return 0;
        return pRoot->value;
    }
    
    Node * pAncestorNode = pNode->parent;
    --k;
    int temp;
    while(k > 0)
    {
        if(k >= veryFastLookUpBase)
        {
            temp = pAncestorNode->degree % veryFastLookUpBase;
            if(0 != temp)
            {
                k -= temp;
            }
            else
            {
                k -= veryFastLookUpBase;
            }
            pAncestorNode = pAncestorNode->veryFarAncestor;
        }
        else if(k >= fastLookUpBase)
        {
            temp = pAncestorNode->degree % fastLookUpBase;
            if(0 != temp)
            {
                k -= temp;
            }
            else
            {
                k -= fastLookUpBase;
            }
            pAncestorNode = pAncestorNode->farAncestor;
        }
        else
        {
            pAncestorNode = pAncestorNode->parent;
            --k;
        }
    }
    
    return pAncestorNode->value;
}