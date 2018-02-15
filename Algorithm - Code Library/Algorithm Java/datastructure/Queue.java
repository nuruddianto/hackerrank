/*
 * Queue implementation based-on linked-list
 * 
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 * 
 */
package datastructure;

public class Queue<E extends Comparable<E>>
{
	private Node<E> front;
	
	private Node<E> back;
	
	private int queueSize;
	
	/**
	 * Construct the queue. Example 
	 * {@code Queue<Integer> queue = new Queue<Integer>(); } 
	 */
	public Queue()
	{
		clear();
	}
	
	/**
	 * Get total elements on the queue
	 * @return total elements on the queue
	 */
	public int size() 
	{
		return queueSize;
	}

	/**
	 * Test if queue is logically empty
	 * @return true if queue is empty
	 */
	public boolean isEmpty() 
	{
		return front == null;
	}

	/**
	 * Make the queue logically empty
	 */
	public void clear() 
	{
		front = null;
		back = null;
		queueSize = 0;
	}

	/**
	 * Insert a new element at the end of the queue
	 * @param element to be inserted to the queue
	 */
	public void enqueue(E element) 
	{
		if (isEmpty())
			back = front = new Node<E>(element); //make queue of one element
		else
			back = back.next = new Node<E>(element); //regular case
		queueSize++;
	}

	/**
	 * Remove and return the least recently inserted element from the queue
	 * @return front element on the queue
	 */
	public E dequeue() 
	{
		if (isEmpty())
			throw new RuntimeException("queue is empty");
		
		E frontElement = front.element;
		front = front.next;
		queueSize--;
		return frontElement;
	}

	/**
	 * Get the least recently inserted element in the queue. Does not alter the queue.
	 * @return front element on the queue
	 */
	public E getFront() 
	{
		if (isEmpty())
			throw new RuntimeException("queue is empty");
		
		return front.element;
	}

	/**
	 * Check specified element is exist or not on the queue
	 * @param element whose presence in this queue is to be tested
	 * @return true if this queue contains the specified element.
	 */
	public boolean contains(E element) 
	{
		if (isEmpty())
			throw new RuntimeException("queue is empty");
		
		Node<E> current = front;
		while(current != null)
		{
			if (current.element.compareTo(element) == 0)
				return true;
			
			current = current.next;
		}
		
		return false;
	}
	
	/**
	 * Returns an array containing all of the elements in this queue in proper sequence (from front to end element)
	 * @param type class or type of array. Example
	 * {@code Integer[] array = queue.toArray(Integer.class); }
	 * @return an array of elements
	 */
	public E[] toArray(Class<E> type) 
	{
		if (isEmpty())
			throw new RuntimeException("queue is empty");
		
		final E[] array = (E[]) java.lang.reflect.Array.newInstance(type, size());
		
		// iterate from top of the stack
		int idx = 0;
		Node<E> current = front;
		while(current != null)
		{
			array[idx++] = current.element;
			current = current.next;
		}
		
		return array;
	}
	
	public void printQueue()
	{
		Node<E> current = front;
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
