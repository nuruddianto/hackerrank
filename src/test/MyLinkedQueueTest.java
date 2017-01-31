package test;
import code.MyLinkedQueue;
import org.junit.Test;

import junit.framework.TestCase;

public class MyLinkedQueueTest extends TestCase {
	
	MyLinkedQueue q;
	
	@Override
	protected void setUp() throws Exception
	{
		super.setUp();
		q = new MyLinkedQueue();
	}
	
	@Test
	public void testNewQueueIsEmpty() {
		assertTrue(q.isEmpty());
		assertEquals(q.size(), 0);
	}
	
	@Test
	public void testInsertToEmptyQueue(){
		int numberOfInsertingData = 3;
		for(int i =0; i < numberOfInsertingData; i++){
			q.enqueue("zzzz"+i);
		}
		assertTrue(!q.isEmpty());
		assertEquals(q.size(), numberOfInsertingData);
	}

	@Test
	public void testEnqueueThenDequeue(){
		String message = "hai";
		q.enqueue(message);
		assertEquals(q.dequeue(), message);
	}

	@Test
	public void testPeekFunction(){
		String message = "this is peak ";
		for(int i = 0; i < 3; i++){
			q.enqueue(message + i);
		}

		assertEquals(q.peek(), message+0);

	}
}
