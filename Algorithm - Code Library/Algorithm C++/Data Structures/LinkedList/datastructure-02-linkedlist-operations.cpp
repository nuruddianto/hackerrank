// Important Operations on Single Linkedlist - Mainly about pointer operator
//===========================================================================

/* Reverses alternate k nodes and returns the pointer to the new head node */
struct node *kAltReverse(struct node *head, int k)
{
    struct node* current = head;
    struct node* next;
    struct node* prev = NULL;
    int count = 0;   
 
    /*1) reverse first k nodes of the linked list */
    while (current != NULL && count < k)
    {
       next  = current->next;
       current->next = prev;
       prev = current;
       current = next;
       count++;
    }
   
    /* 2) Now head points to the kth node.  
    So change next of head to (k+1)th node*/
    if(head != NULL)
      head->next = current;   
 
    /* 3) We do not want to reverse next k nodes. So move the current 
    pointer to skip next k nodes */
    count = 0;
    while(count < k-1 && current != NULL )
    {
      current = current->next;
      count++;
    }
 
    /* 4) Recursively call for the list starting from current->next.
       And make rest of the list as next of first node */
    if(current !=  NULL)
       current->next = kAltReverse(current->next, k); 
 
    /* 5) prev is new head of the input list */
    return prev;
}

// This function rotates a linked list counter-clockwise and updates the head.
// The function assumes that k is smaller than size of linked list. It doesn't
// modify the list if k is greater than or equal to size
void rotate (struct node **head_ref, int k)
{
     if (k == 0)
       return;
 
    // Let us understand the below code for example k = 4 and
    // list = 10->20->30->40->50->60.
    struct node* current = *head_ref;
 
    // current will either point to kth or NULL after this loop.
    //  current will point to node 40 in the above example
    int count = 1;
    while (count < k && current != NULL)
    {
        current = current->next;
        count++;
    }
 
    // If current is NULL, k is greater than or equal to count
    // of nodes in linked list. Don't change the list in this case
    if (current == NULL)
        return;
 
    // current points to kth node. Store it in a variable.
    // kthNode points to node 40 in the above example
    struct node *kthNode = current;
 
    // current will point to last node after this loop
    // current will point to node 60 in the above example
    while (current->next != NULL)
        current = current->next;
 
    // Change next of last node to previous head
    // Next of 60 is now changed to node 10
    current->next = *head_ref;
 
    // Change head to (k+1)th node
    // head is now changed to node 50
    *head_ref = kthNode->next;
 
    // change next of kth node to NULL
    // next of 40 is now NULL
    kthNode->next = NULL;
}

// Function to skip M nodes and then delete N nodes of the linked list.
void skipMdeleteN(struct node  *head, int M, int N)
{
    struct node *curr = head, *t;
    int count;
 
    // The main loop that traverses through the whole list
    while (curr)
    {
        // Skip M nodes
        for (count = 1; count<M && curr!= NULL; count++)
            curr = curr->next;
 
        // If we reached end of list, then return
        if (curr == NULL)
            return;
 
        // Start from next node and delete N nodes
        t = curr->next;
        for (count = 1; count<=N && t!= NULL; count++)
        {
            struct node *temp = t;
            t = t->next;
            free(temp);
        }
        curr->next = t; // Link the previous list with remaining nodes
 
        // Set current pointer for next iteration
        curr = t;
    }
}

// Main function that inserts nodes of linked list q into p at alternate
// positions. Since head of first list never changes and head of second list 
// may change, we need single pointer for first list and double pointer for 
// second list.
void merge(struct node *p, struct node **q)
{
     struct node *p_curr = p, *q_curr = *q;
     struct node *p_next, *q_next;
 
     // While therre are avialable positions in p
     while (p_curr != NULL && q_curr != NULL)
     {
         // Save next pointers
         p_next = p_curr->next;
         q_next = q_curr->next;
 
         // Make q_curr as next of p_curr
         q_curr->next = p_next;  // Change next pointer of q_curr
         p_curr->next = q_curr;  // Change next pointer of p_curr
 
         // Update current pointers for next iteration
         p_curr = p_next;
         q_curr = q_next;
    }
 
    *q = q_curr; // Update head pointer of second list
}

/* Function to pairwise swap elements of a linked list */
void pairWiseSwap(struct node **head)
{
    // If linked list is empty or there is only one node in list
    if (*head == NULL || (*head)->next == NULL)
        return;
 
    // Initialize previous and current pointers
    struct node *prev = *head;
    struct node *curr = (*head)->next;
 
    *head = curr;  // Change head before proceeeding
 
    // Traverse the list
    while (true)
    {
        struct node *next = curr->next;
        curr->next = prev; // Change next of current as previous node
 
        // If next NULL or next is the last node
        if (next == NULL || next->next == NULL)
        {
            prev->next = next;
            break;
        }
 
        // Change next of previous to next next
        prev->next = next->next;
 
        // Update previous and curr
        prev = next;
        curr = prev->next;
    }
}
 

// This function deletes middle nodes in a sequence of horizontal and
// vertical line segments represented by linked list.
struct node* deleteMiddle(struct node *head)
{
    // If only one node or no node...Return back
    if (head==NULL || head->next ==NULL || head->next->next==NULL)
        return head;
 
    struct node* Next = head->next;
    struct node *NextNext = Next->next ;
 
    // Check if this is a vertical line or horizontal line
    if (head->x == Next->x)
    {
        // Find middle nodes with same x value, and delete them
        while (NextNext !=NULL && Next->x==NextNext->x)
        {
            deleteNode(head, Next);
 
            // Update Next and NextNext for next iteration
            Next = NextNext;
            NextNext = NextNext->next;
        }
    }
    else if (head->y==Next->y) // If horizontal line
    {
        // Find middle nodes with same y value, and delete them
        while (NextNext !=NULL && Next->y==NextNext->y)
        {
            deleteNode(head, Next);
 
            // Update Next and NextNext for next iteration
            Next = NextNext;
            NextNext = NextNext->next;
        }
    }
    else  // Adjacent points must have either same x or same y
    {
        puts("Given linked list is not valid");
        return NULL;
    }
 
    // Recur for next segment
    deleteMiddle(head->next);
 
    return head;
}
 

/* returns 1 if linked lists a and b are identical, otherwise 0 */
bool areIdentical(struct node *a, struct node *b)
{ 
  while(1)
  {
    /* base case */
    if(a == NULL && b == NULL)     
    {  return 1; }
    if(a == NULL && b != NULL)  
    {  return 0; }
    if(a != NULL && b == NULL)  
    {  return 0; }
    if(a->data != b->data)
    {  return 0; }
    
    /* If we reach here, then a and b are not NULL and their 
       data is same, so move to next nodes in both lists */
    a = a->next;
    b = b->next; 
  }          
}     
 
/* We are using a double pointer head_ref here because we change    
   head of the linked list inside this function.*/
void moveToFront(struct node **head_ref)
{
  /* If linked list is empty, or it contains only one node, 
    then nothing needs to be done, simply return */  
  if(*head_ref == NULL || (*head_ref)->next == NULL)
    return;
     
  /* Initialize second last and last pointers */ 
  struct node *secLast = NULL;
  struct node *last = *head_ref;
   
  /*After this loop secLast contains address of second last
  node and last contains address of last node in Linked List */
  while(last->next != NULL)  
  {
    secLast = last;
    last = last->next; 
  }                 
   
  /* Set the next of second last as NULL */
  secLast->next = NULL;
   
  /* Set next of last as head node */
  last->next = *head_ref;
   
  /* Change the head pointer to point to last node now */
  *head_ref = last;    
}     
 

/* Function to reverse the linked list */
void printReverse(struct node* head)
{
  // Base case  
  if(head == NULL)
    return;

  // print the list after head node
  printReverse(head->next);

  // After everything else is printed, print head
  printf("%d  ", head->data);
}

/* function to insert a new_node in a list. Note that this
  function expects a pointer to head_ref as this can modify the
  head of the input linked list (similar to push())*/
void sortedInsert(struct node** head_ref, struct node* new_node)
{
    struct node* current;
    /* Special case for the head end */
    if (*head_ref == NULL || (*head_ref)->data >= new_node->data)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *head_ref;
        while (current->next!=NULL &&
               current->next->data < new_node->data)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}


// Write a C function to detect loop in a linked list
int detectloop(struct node *list)
{
  struct node  *slow_p = list, *fast_p = list;
 
  while(slow_p && fast_p &&
          fast_p->next )
  {
    slow_p = slow_p->next;
    fast_p  = fast_p->next->next;
    if (slow_p == fast_p)
    {
       printf("Found Loop");
       return 1;
    }
  }
  return 0;
}
 
/* Function to reverse the linked list */
static void reverse(struct node** head_ref)
{
    struct node* prev   = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL)
    {
        next  = current->next;  
        current->next = prev;   
        prev = current;
        current = next;
    }
    *head_ref = prev;
}
 
 /* Function to print linked list */
void printList(struct node *head)
{
    struct node *temp = head;
    while(temp != NULL)
    {
        printf("%d  ", temp->data);    
        temp = temp->next;  
    }
}    
 
/* Counts no. of nodes in linked list */
int getCount(struct node* head)
{
    int count = 0;  // Initialize count
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

/* Search nodes in linked list */
bool search(struct node* head, int x)
{
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
        if (current->key == x)
            return true;
        current = current->next;
    }
    return false;
}


/* Takes head pointer of the linked list and index
    as arguments and return data at index*/
int GetNth(struct node* head, int index)
{
    struct node* current = head;
    int count = 0; /* the index of the node we're currently
                  looking at */
    while (current != NULL)
    {
       if (count == index)
          return(current->data);
       count++;
       current = current->next;
    }
   
    /* if we get to this line, the caller was asking
       for a non-existent element so we assert fail */
    assert(0);              
}
 
/* Function to get the middle of the linked list*/
void printMiddle(struct node *head)
{
    struct node *slow_ptr = head;
    struct node *fast_ptr = head;
 
    if (head!=NULL)
    {
        while (fast_ptr != NULL && fast_ptr->next != NULL)
        {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }
        printf("The middle element is [%d]\n\n", slow_ptr->data);
    }
}

/* Function to get the nth node from the last of a linked list*/
void printNthFromLast(struct node* head, int n)
{
    int len = 0, i;
    struct node *temp = head;
 
    // 1) count the number of nodes in Linked List
    while (temp != NULL)
    {
        temp = temp->next;
        len++;
    }
 
    // check if value of n is not more than length of the linked list
    if (len < n)
      return;
 
    temp = head;
 
    // 2) get the (n-len+1)th node from the begining
    for (i = 1; i < len-n+1; i++)
       temp = temp->next;
 
    printf ("%d", temp->data);
 
    return;
}


 /* Function to delete the entire linked list */
void deleteList(struct node** head_ref)
{
   /* deref head_ref to get the real head */
   struct node* current = *head_ref;
   struct node* next;
 
   while (current != NULL) 
   {
       next = current->next;
       free(current);
       current = next;
   }
   
   /* deref head_ref to affect the real head back
      in the caller. */
   *head_ref = NULL;
} 

/* Counts the no. of occurences of a node 
   (search_for) in a linked list (head)*/
int count(struct node* head, int search_for) 
{
    struct node* current = head;
    int count = 0;
    while (current != NULL) 
    {
        if (current->data == search_for)
           count++;
        current = current->next;
    }
    return count;
}

/* Function to check if given linked list is
  palindrome or not */
bool isPalindrome(struct node *head)
{
    struct node *slow_ptr = head, *fast_ptr = head;
    struct node *second_half, *prev_of_slow_ptr = head;
    struct node *midnode = NULL;  // To handle odd size list
    bool res = true; // initialize result
 
    if (head!=NULL && head->next!=NULL)
    {
        /* Get the middle of the list. Move slow_ptr by 1
          and fast_ptrr by 2, slow_ptr will have the middle
          node */
        while (fast_ptr != NULL && fast_ptr->next != NULL)
        {
            fast_ptr = fast_ptr->next->next;
 
            /*We need previous of the slow_ptr for
             linked lists  with odd elements */
            prev_of_slow_ptr = slow_ptr;
            slow_ptr = slow_ptr->next;
        }
 
 
        /* fast_ptr would become NULL when there are even elements in list. 
           And not NULL for odd elements. We need to skip the middle node 
           for odd case and store it somewhere so that we can restore the
           original list*/
        if (fast_ptr != NULL)
        {
            midnode = slow_ptr;
            slow_ptr = slow_ptr->next;
        }
 
        // Now reverse the second half and compare it with first half
        second_half = slow_ptr;
        prev_of_slow_ptr->next = NULL; // NULL terminate first half
        reverse(&second_half);  // Reverse the second half
        res = compareLists(head, second_half); // compare
 
        /* Construct the original list back */
         reverse(&second_half); // Reverse the second half again
         if (midnode != NULL)  // If there was a mid node (odd size case) which                                                         
                               // was not part of either first half or second half.
         {
            prev_of_slow_ptr->next = midnode;
            midnode->next = second_half;
         }
         else  prev_of_slow_ptr->next = second_half;
    }
    return res;


    /* The function removes duplicates from a sorted list */
void removeDuplicates(struct node* head)
{
  /* Pointer to traverse the linked list */
  struct node* current = head;
 
  /* Pointer to store the next pointer of a node to be deleted*/
  struct node* next_next; 
   
  /* do nothing if the list is empty */
  if(current == NULL) 
     return; 
 
  /* Traverse the list till last node */
  while(current->next != NULL) 
  {
   /* Compare current node with next node */
    if(current->data == current->next->data) 
    {
       /*The sequence of steps is important*/              
      next_next = current->next->next;
      free(current->next);
      current->next = next_next;  
    }
    else /* This is tricky: only advance if no deletion */
    {
      current = current->next; 
    }
  }
}
 /* Function to remove duplicates from a unsorted linked list */
void removeDuplicates(struct node *start)
{
  struct node *ptr1, *ptr2, *dup;
  ptr1 = start;
 
  /* Pick elements one by one */
  while(ptr1 != NULL && ptr1->next != NULL)
  {
     ptr2 = ptr1;
 
     /* Compare the picked element with rest of the elements */
     while(ptr2->next != NULL)
     {
       /* If duplicate then delete it */
       if(ptr1->data == ptr2->next->data)
       {
          /* sequence of steps is important here */
          dup = ptr2->next;
          ptr2->next = ptr2->next->next;
          free(dup);
       }
       else /* This is tricky */
       {
          ptr2 = ptr2->next;
       }
     }
     ptr1 = ptr1->next;
  }
}
}


/* Intersection two linkedlist: This solution uses the temporary dummy to build up the result list */
struct node* sortedIntersect(struct node* a, struct node* b)
{
  struct node dummy;
  struct node* tail = &dummy;
  dummy.next = NULL;
  
  /* Once one or the other list runs out -- we're done */
  while (a != NULL && b != NULL)
  {
    if (a->data == b->data)
    {
       push((&tail->next), a->data);
       tail = tail->next;
       a = a->next;
       b = b->next;
    }
    else if (a->data < b->data) /* advance the smaller list */     
       a = a->next;
    else
       b = b->next;
  }
  return(dummy.next);
}


/* Takes two lists sorted in increasing order, and splices their nodes together to make one big sorted list which is returned.  */
struct node* SortedMerge(struct node* a, struct node* b) 
{
   /* a dummy first node to hang the result on */   
   struct node dummy;      
    
   /* tail points to the last result node  */
   struct node* tail = &dummy;  
 
   /* so tail->next is the place to add new nodes 
     to the result. */
   dummy.next = NULL;
   while(1) 
   {
      if(a == NULL) 
      { 
         /* if either list runs out, use the other list */
         tail->next = b;
         break;
      }
      else if (b == NULL) 
      {
         tail->next = a;
         break;
      }
      if (a->data <= b->data) 
      {
         MoveNode(&(tail->next), &a);
      }
      else
     {
        MoveNode(&(tail->next), &b);
     }
     tail = tail->next;
  }
  return(dummy.next);
}  
 
 
/* UTILITY FUNCTIONS */
/*MoveNode() function takes the node from the front of the source, and move it to the front of the dest.
   It is an error to call this with the source list empty. 
 
   Before calling MoveNode():
   source == {1, 2, 3}
   dest == {1, 2, 3}
 
   Affter calling MoveNode():
   source == {2, 3}
   dest == {1, 1, 2, 3}
*/
void MoveNode(struct node** destRef, struct node** sourceRef)
{
  /* the front source node  */
  struct node* newNode = *sourceRef;
  assert(newNode != NULL);
 
  /* Advance the source pointer */
  *sourceRef = newNode->next;
 
  /* Link the old dest off the new node */
  newNode->next = *destRef; 
 
  /* Move dest to point to the new node */
  *destRef = newNode;
}
 
 

 // Method that adjusts the pointers and prints the final list
void finalMaxSumList(Node *a, Node *b)
{
    Node *result = NULL;
 
    // Assigning pre and cur to the head of the
    // linked list.
    Node *pre1 = a, *curr1 = a;
    Node *pre2 = b, *curr2 = b;
 
    // Till either of the current pointers is not
    // NULL execute the loop
    while (curr1 != NULL || curr2 != NULL)
    {
        // Keeping 2 local variables at the start of every
        // loop run to keep track of the sum between pre
        // and cur pointer elements.
        int sum1 = 0, sum2 = 0;
 
        // Calculating sum by traversing the nodes of linked
        // list as the merging of two linked list.  The loop
        // stops at a common node
        while (curr1!=NULL && curr2!=NULL && curr1->data!=curr2->data)
        {
            if (curr1->data < curr2->data)
            {
                sum1 += curr1->data;
                curr1 = curr1->next;
            }
            else // (curr2->data < curr1->data)
            {
                sum2 += curr2->data;
                curr2 = curr2->next;
            }
        }
 
        // If either of current pointers becomes NULL
        // carry on the sum calculation for other one.
        if (curr1 == NULL)
        {
            while (curr2 != NULL)
            {
                sum2 += curr2->data;
                curr2 = curr2->next;
            }
        }
        if (curr2 == NULL)
        {
            while (curr1 != NULL)
            {
                sum1 += curr1->data;
                curr1 = curr1->next;
            }
        }
 
        // First time adjustment of resultant head based on
        // the maximum sum.
        if (pre1 == a && pre2 == b)
            result = (sum1 > sum2)? pre1 : pre2;
 
        // If pre1 and pre2 don't contain the head pointers of
        // lists adjust the next pointers of previous pointers.
        else
        {
            if (sum1 > sum2)
                pre2->next = pre1->next;
            else
                pre1->next = pre2->next;
        }
 
        // Adjusting previous pointers
        pre1 = curr1, pre2 = curr2;
 
        // If curr1 is not NULL move to the next.
        if (curr1)
            curr1 = curr1->next;
        // If curr2 is not NULL move to the next.
        if (curr2)
            curr2 = curr2->next;
    }
 
    // Print the resultant list.
    while (result != NULL)
    {
        cout << result->data << " ";
        result = result->next;
    }
}


// The main function that adds two linked lists represented by head1 and head2.
// The sum of two lists is stored in a list referred by result
void addList(node* head1, node* head2, node** result)
{
    node *cur;
 
    // first list is empty
    if (head1 == NULL)
    {
        *result = head2;
        return;
    }
 
    // second list is empty
    else if (head2 == NULL)
    {
        *result = head1;
        return;
    }
 
    int size1 = getSize(head1);
    int size2 = getSize(head2) ;
 
    int carry = 0;
 
    // Add same size lists
    if (size1 == size2)
        *result = addSameSize(head1, head2, &carry);
 
    else
    {
        int diff = abs(size1 - size2);
 
        // First list should always be larger than second list.
        // If not, swap pointers
        if (size1 < size2)
            swapPointer(&head1, &head2);
 
        // move diff. number of nodes in first list
        for (cur = head1; diff--; cur = cur->next);
 
        // get addition of same size lists
        *result = addSameSize(cur, head2, &carry);
 
        // get addition of remaining first list and carry
        addCarryToRemaining(head1, cur, &carry, result);
    }
 
    // if some carry is still there, add a new node to the fron of
    // the result list. e.g. 999 and 87
    if (carry)
        push(result, carry);
}


/* Function to get union of two linked lists head1 and head2 */
struct node *getUnion (struct node *head1, struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1, *t2 = head2;
 
    // Insert all elements of list1 to the result list
    while (t1 != NULL)
    {
        push(&result, t1->data);
        t1 = t1->next;
    }
 
    // Insert those elements of list2 which are not present in result list
    while (t2 != NULL)
    {
        if (!isPresent(result, t2->data))
            push(&result, t2->data);
        t2 = t2->next;
    }
 
    return result;
}
 
/* Function to get intersection of two linked lists head1 and head2 */
struct node *getIntersection (struct node *head1, struct node *head2)
{
    struct node *result = NULL;
    struct node *t1 = head1;
 
    // Traverse list1 and search each element of it in list2. If the element
    // is present in list 2, then insert the element to result
    while (t1 != NULL)
    {
        if (isPresent(head2, t1->data))
            push (&result, t1->data);
        t1 = t1->next;
    }
 
    return result;
}

 