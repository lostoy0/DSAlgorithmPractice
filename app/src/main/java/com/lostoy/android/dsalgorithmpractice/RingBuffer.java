package com.lostoy.android.dsalgorithmpractice;

public class RingBuffer {
	
	private static final int DEFAULT_CAPACITY = 10;
	private int capacity = DEFAULT_CAPACITY;
	private byte[] buffer;
	private int size = 0;
	private int head = 0;
	private int tail = 0;
	
	public RingBuffer() {}
	
	public RingBuffer(int capacity) {
		if(capacity > 0) {
			this.capacity = capacity;
		}
		buffer = new byte[this.capacity];
	}
	
	public int size() {
		return size;
	}
	
	public boolean isEmpty() {
		return size == 0;
	}
	
	public boolean isFull() {
		return size == capacity;
	}
	
	public void clear() {
		size = 0;
		head = tail = 0;
	}
	
	public boolean write(byte b) {
		if(isFull()) {
			try {
				throw new Exception("The buffer is full!");
			} catch (Exception e) {
				e.printStackTrace();
			}
			return false;
		}
		
		if(tail < capacity-1) {
			tail ++;
		} else {
			tail = 0;
		}
		buffer[tail] = b;
		size ++;
		
		return true;
	}
	
	public byte read() {
		if(isEmpty()) {
			
			return -1;
		}
		
		byte value = buffer[head ++];
		if(head == capacity) head = 0;
		size --;
		
		return value;
	}
	
}
