/*
 * Stack implementation based-on linked-list
 * 
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 * 
 */
package datastructure;

public class Stack<E extends Comparable<E>>
{
	// top of the stack (TOS)
	private Node<E> top;
	
	// size of stack
	private int stackSize;
	
	/**
	 * Construct the stack. Example 
	 * {@code Stack<Integer> stack = new Stack<Integer>(); } 
	 */
	public Stack()
	{
		clear();
	}
	
	/**
	 * Total elements on the stack
	 * @return the size of the stack
	 */
	public int size() 
	{
		return stackSize;
	}

	/**
	 * Test if stack is logically empty
	 * @return true if stack is empty
	 */
	public boolean isEmpty() 
	{
		return stackSize == 0;
	}

	/**
	 * Make the stack logically empty
	 */
	public void clear() 
	{
		top = null;
		stackSize = 0;
	}

	/**
	 * Insert a new element into the stack
	 * @param element to be inserted to stack
	 */
	public void push(E element) 
	{
		top = new Node<E>(element, top);
		stackSize++;
	}

	/**
	 * Get the most recently inserted element in the stack (top of the stack). Does not alter the stack.
	 * @return element of top of the stack
	 */
	public E peek() 
	{
		if (isEmpty())
			throw new RuntimeException("stack is empty");
		
		return top.element;
	}

	/**
	 * Remove the most recently inserted element in the stack (top of the stack) and return the element
	 * @return element of top of the stack
	 */
	public E pop() 
	{
		if (isEmpty())
			throw new RuntimeException("stack is empty");
		
		E element = top.element;
		top = top.next;
		stackSize--;
		
		return element;
	}
	
	/**
	 * Check specified element is exist or not on the stack
	 * @param element whose presence in this stack is to be tested
	 * @return true if this stack contains the specified element.
	 */
	public boolean contains(E element)
	{
		if (isEmpty())
			throw new RuntimeException("stack is empty");
		
		// iterate from top of the stack (TOS)
		Node<E> current = top;
		while(current != null)
		{
			if (current.element.compareTo(element) == 0)
				return true;
			
			current = current.next;
		}
		
		return false;
	}
	
	/**
	 * Returns an array containing all of the elements in this stack in proper sequence (from top to last element)
	 * @param type class or type of array. Example
	 * {@code Integer[] array = stack.toArray(Integer.class); }
	 * @return toArray
	 */
	public E[] toArray(Class<E> type)
	{
		if (isEmpty())
			throw new RuntimeException("stack is empty");
		
		final E[] array = (E[]) java.lang.reflect.Array.newInstance(type, size());
		
		// iterate from top of the stack
		int idx = 0;
		Node<E> current = top;
		while(current != null)
		{
			array[idx++] = current.element;
			current = current.next;
		}
		
		return array;
	}
	
	/**
	 * Print all of the elements in this stack in proper sequence (from top to last element)
	 */
	public void printStack()
	{
		if (isEmpty())
			throw new RuntimeException("stack is empty");
		
		System.out.println("Print stack from the top:");
		// iterate from top of the stack (TOS)
		Node<E> current = top;
		while(current != null)
		{
			if (current.next == null)
				System.out.print(current.element);
			else
				System.out.print(current.element + ", ");
			current = current.next;
		}
		System.out.println();
	}
}
