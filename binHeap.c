//      binHeap.c
//      
//      Copyright 2011 Simon Wrafter <simon.wrafter@gmail.com>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.

#include "binHeap.h"
#include <stdlib.h>

struct HeapEntry {
	int index;
	void *entry;
};

struct HeapStruct {
	QueueObject binheap;
	int (*cmp)();
	int size;
	int limit;
};


PriorityQueue makeHeap(int startSize, int (*comparator)()) {
	PriorityQueue PQ = malloc(sizeof(struct HeapStruct));
	
	if (startSize < INITIAL_SIZE) {
		startSize = INITIAL_SIZE;
	}
	
	PQ->binheap = malloc(sizeof(struct HeapEntry) * startSize);
	PQ->size = 0;
	PQ->limit = INITIAL_SIZE;
	
	return PQ;
}

int getSize(PriorityQueue PQ) {
	return PQ->size;
}

int offer(PriorityQueue PQ, void *newEntry) {
	QueueObject QO = malloc(sizeof(struct HeapEntry));
	
	if (PQ->size == PQ->limit-1){
		PQ->limit = PQ->size * 2;
		PQ->binheap = realloc(PQ->binheap, sizeof( struct HeapEntry ) * PQ->limit);
	}
	
	QO->index = PQ->size;
	QO->entry = newEntry;
	
	PQ->binheap[PQ->size] = *QO;
	//moveUp(PQ->size);
	PQ->size++;
	return 1;
}

void *peek(PriorityQueue PQ) {
	return PQ->binheap[PQ->size - 1].entry;
}

void *poll(PriorityQueue PQ) {
	QueueObject QO = PQ->binheap[PQ->size - 1].entry;
	return QO;
}

int isEmpty(PriorityQueue PQ) {
	return (PQ->size == 0);
}
