/*
 * LinkedList implementation. An alternative of java.util.ArrayList
 * 
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 * 
 */
package datastructure;

public class LinkedList<E extends Comparable<E>>
{
	private int listSize;
	private DoublyNode<E> header;
	private DoublyNode<E> tail;
	
	public LinkedList()
	{
		clear();
	}
	
	public int size() 
	{
		return listSize;
	}

	public boolean isEmpty() 
	{
		return listSize == 0;
	}

	public void clear() 
	{
		header = new DoublyNode<E>();
		tail = new DoublyNode<E>();
		header.next = tail;
		tail.prev = header;
		listSize = 0;
	}
	
	private DoublyNode<E> findPosition(E element)
	{
		for(DoublyNode<E> pointer = header.next; pointer != null; pointer = pointer.next)
		{
			if (pointer.element.compareTo(element) == 0)
				return pointer;
		}
		return null;
	}

	public boolean contains(E element) 
	{
		return findPosition(element) != null;
	}
	
	private DoublyNode<E> getNode(int index, int low, int high)
	{
		DoublyNode<E> pointer = null;
		
		if (index < low || index > high)
			throw new IndexOutOfBoundsException("Index: " + index + " out of bounds");
		
		if (index < listSize / 2)
		{
			pointer = header.next;
			for(int i = 0; i < index; i++)
				pointer = pointer.next;
		}
		else
		{
			pointer = tail;
			for(int i = listSize; i > index; i--)
				pointer = pointer.prev;
		}
		return pointer;
	}
	
	private DoublyNode<E> getNode(int index)
	{
		return getNode(index, 0, listSize-1);
	}

	public E get(int index) 
	{
		return getNode(index).element;
	}
	
	public E getFirst()
	{
		if (isEmpty())
			throw new RuntimeException("Linked-list is empty");
		
		return header.next.element;
	}
	
	public E getLast()
	{
		if (isEmpty())
			throw new RuntimeException("Linked-list is empty");
		
		return tail.prev.element;
	}

	public E set(int index, E element) 
	{
		DoublyNode<E> node = getNode(index);
		E oldElement = node.element;
		node.element = element;
		return oldElement;
	}

	public void add(int index, E element) 
	{
		DoublyNode<E> node = getNode(index, 0, listSize);
		DoublyNode<E> newNode = new DoublyNode<E>(node.prev, element, node);
		newNode.prev.next = newNode;
		node.prev = newNode;
		listSize++;
	}
	
	public void addFirst(E element)
	{
		add(0, element);
	}
	
	public void addLast(E element)
	{
		add(listSize, element);
	}
	
	public void add(E element) 
	{
		addLast(element);
	}

	private E remove(DoublyNode<E> node)
	{
		node.next.prev = node.prev;
		node.prev.next = node.next;
		listSize--;
		return node.element;
	}
	
	public boolean remove(E element)
	{
		DoublyNode<E> node = findPosition(element);
		if (node != null)
		{
			remove(node);
			return true;
		}
		else
			return false;
	}
	
	public E removeAt(int index) 
	{
		return remove(getNode(index));
	}
	
	public E removeFirst()
	{
		if (isEmpty())
			throw new RuntimeException("Linked-list is empty");
		
		return remove(header.next);
	}
	
	public E removeLast()
	{
		if (isEmpty())
			throw new RuntimeException("Linked-list is empty");
		
		return remove(tail.prev);
	}

	/**
	 * Returns an array containing all of the elements in this linked-list in proper sequence (from front to end element)
	 * @param type class or type of array. Example
	 * {@code Integer[] array = list.toArray(Integer.class); }
	 * @return an array of elements
	 */
	public E[] toArray(Class<E> type) 
	{
		if (isEmpty())
			throw new RuntimeException("Linked-list is empty");
		
		final E[] array = (E[]) java.lang.reflect.Array.newInstance(type, size());
		
		// iterate from top of the stack
		int idx = 0;
		DoublyNode<E> current = header.next;
		while(current != tail)
		{
			array[idx++] = current.element;
			current = current.next;
		}
		
		return array;
	}
	
	public void printList()
	{
		DoublyNode<E> current = header.next;
		while(current != tail)
		{
			if (current == tail.prev)
				System.out.print(current.element);
			else
				System.out.print(current.element + ", ");
			current = current.next;
		}
		System.out.println();
	}

}
