/*
 * DoublyNode represent a node for LinkedList
 * 
 * Author: Gilang Kusuma Jati (gilang.k@samsung.com), SRIN.
 * 
 */
package datastructure;

public class DoublyNode<E extends Comparable<E>> 
{
	DoublyNode<E> prev;
	E element;
	DoublyNode<E> next;
	
	public DoublyNode(DoublyNode<E> prev, E element, DoublyNode<E> next)
	{
		this.prev = prev;
		this.element = element;
		this.next = next;
	}
	
	public DoublyNode(E element)
	{
		this(null, element, null);
	}
	
	public DoublyNode()
	{
		this(null);
	}
}
