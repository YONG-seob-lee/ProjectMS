// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreTypes.h"
#include "Templates/UnrealTemplate.h"
#include "HAL/PlatformAtomics.h"
#include "HAL/PlatformMisc.h"

/**
 * 
 */
template<typename T>
class TMS_PriorityQueue
{
public:
	using FElementType = T;

	/** Default constructor. */
	TMS_PriorityQueue()
	{
		Head = Tail = new TPriorityNode();
	}

	/** Destructor. */
	~TMS_PriorityQueue()
	{
		while (Tail != nullptr)
		{
			TPriorityNode* Node = Tail;
			Tail = Tail->NexTPriorityNode;

			delete Node;
		}
	}

	/**
	 * Removes and returns the item from the tail of the queue.
	 *
	 * @param OutValue Will hold the returned value.
	 * @return true if a value was returned, false if the queue was empty.
	 * @note To be called only from consumer thread.
	 * @see Empty, Enqueue, IsEmpty, Peek, Pop
	 */
	bool Dequeue(FElementType& OutItem)
	{
		TPriorityNode* Popped = Tail->NexTPriorityNode;

		if (Popped == nullptr)
		{
			return false;
		}
		
		TSAN_AFTER(&Tail->NexTPriorityNode);
		OutItem = MoveTemp(Popped->Item);

		TPriorityNode* OldTail = Tail;
		Tail = Popped;
		Tail->Item = FElementType();
		delete OldTail;

		return true;
	}

	/**
	 * Empty the queue, discarding all items.
	 *
	 * @note To be called only from consumer thread.
	 * @see Dequeue, IsEmpty, Peek, Pop
	 */
	void Empty()
	{
		while (Pop());
	}

	/**
	 * Adds an item to the head of the queue.
	 *
	 * @param Item The item to add.
	 * @return true if the item was added, false otherwise.
	 * @note To be called only from producer thread(s).
	 * @see Dequeue, Pop
	 */
	bool Enqueue(const FElementType& Item, int32 Priority)
	{
		TPriorityNode* NewNode = new TPriorityNode(Item, Priority);

		if (NewNode == nullptr)
		{
			return false;
		}

		TPriorityNode* PreviousNode = Head;
		
		while ( PreviousNode->Priority > NewNode->Priority && PreviousNode != Tail)
		{
			PreviousNode = PreviousNode->NexTPriorityNode;
		}

		if (PreviousNode == Head)
		{
			Head = NewNode;
			TSAN_BEFORE(&OldHead->NexTPriorityNode);
			FPlatformMisc::MemoryBarrier();
			PreviousNode->NexTPriorityNode = NewNode;
		}
		else
		{
			TSAN_BEFORE(&OldHead->NexTPriorityNode);
			FPlatformMisc::MemoryBarrier();
			NewNode->NexTPriorityNode = PreviousNode->NexTPriorityNode;
			PreviousNode->NexTPriorityNode = NewNode;
		}

		return true;
	}

	/**
	 * Adds an item to the head of the queue.
	 *
	 * @param Item The item to add.
	 * @return true if the item was added, false otherwise.
	 * @note To be called only from producer thread(s).
	 * @see Dequeue, Pop
	 */
	bool Enqueue(FElementType&& Item, int32 Priority)
	{
		TPriorityNode* NewNode = new TPriorityNode(MoveTemp(Item), Priority);

		if (NewNode == nullptr)
		{
			return false;
		}

		TPriorityNode* PreviousNode = Head;
		
		while ( PreviousNode->Priority > NewNode->Priority && PreviousNode != Tail)
		{
			PreviousNode = PreviousNode->NexTPriorityNode;
		}

		if (PreviousNode == Head)
		{
			Head = NewNode;
			TSAN_BEFORE(&OldHead->NexTPriorityNode);
			FPlatformMisc::MemoryBarrier();
			PreviousNode->NexTPriorityNode = NewNode;
		}
		else
		{
			TSAN_BEFORE(&OldHead->NexTPriorityNode);
			FPlatformMisc::MemoryBarrier();
			NewNode->NexTPriorityNode = PreviousNode->NexTPriorityNode;
			PreviousNode->NexTPriorityNode = NewNode;
		}

		return true;
	}

	/**
	 * Checks whether the queue is empty.
	 *
	 * @return true if the queue is empty, false otherwise.
	 * @note To be called only from consumer thread.
	 * @see Dequeue, Empty, Peek, Pop
	 */
	bool IsEmpty() const
	{
		return (Tail->NexTPriorityNode == nullptr);
	}

	/**
	 * Peeks at the queue's tail item without removing it.
	 *
	 * @param OutItem Will hold the peeked at item.
	 * @return true if an item was returned, false if the queue was empty.
	 * @note To be called only from consumer thread.
	 * @see Dequeue, Empty, IsEmpty, Pop
	 */
	bool Peek(FElementType& OutItem) const
	{
		if (Tail->NexTPriorityNode == nullptr)
		{
			return false;
		}

		OutItem = Tail->NexTPriorityNode->Item;

		return true;
	}

	/**
	 * Peek at the queue's tail item without removing it.
	 *
	 * This version of Peek allows peeking at a queue of items that do not allow
	 * copying, such as TUniquePtr.
	 *
	 * @return Pointer to the item, or nullptr if queue is empty
	 */
	FElementType* Peek()
	{
		if (Tail->NexTPriorityNode == nullptr)
		{
			return nullptr;
		}

		return &Tail->NexTPriorityNode->Item;
	}

	FORCEINLINE const FElementType* Peek() const
	{
		return const_cast<TMS_PriorityQueue*>(this)->Peek();
	}

	/**
	 * Removes the item from the tail of the queue.
	 *
	 * @return true if a value was removed, false if the queue was empty.
	 * @note To be called only from consumer thread.
	 * @see Dequeue, Empty, Enqueue, IsEmpty, Peek
	 */
	bool Pop()
	{
		TPriorityNode* Popped = Tail->NexTPriorityNode;

		if (Popped == nullptr)
		{
			return false;
		}
		
		TSAN_AFTER(&Tail->NexTPriorityNode);

		TPriorityNode* OldTail = Tail;
		Tail = Popped;
		Tail->Item = FElementType();
		delete OldTail;

		return true;
	}

private:

	/** Structure for the internal linked list. */
	struct TPriorityNode
	{
		/** Holds a pointer to the next node in the list. */
		TPriorityNode* volatile NexTPriorityNode;

		/** Holds the node's item. */
		FElementType Item;

		int32 Priority;

		/** Default constructor. */
		TPriorityNode()
			: NexTPriorityNode(nullptr)
		{ }

		/** Creates and initializes a new node. */
		explicit TPriorityNode(const FElementType& InItem, int32 InPriority)
			: NexTPriorityNode(nullptr)
			, Item(InItem)
			, Priority(InPriority)
		{ }

		/** Creates and initializes a new node. */
		explicit TPriorityNode(FElementType&& InItem, int32 InPriority)
			: NexTPriorityNode(nullptr)
			, Item(MoveTemp(InItem))
			, Priority(InPriority)
		{ }
	};

	/** Holds a pointer to the head of the list. */
	MS_ALIGN(16) TPriorityNode* volatile Head GCC_ALIGN(16);

	/** Holds a pointer to the tail of the list. */
	TPriorityNode* Tail;
};
