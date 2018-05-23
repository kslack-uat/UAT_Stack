#pragma once
#include "stdafx.h"
#include <memory>
#include <iostream>

using namespace std;

// Node class that stores data of type generic_type along with a smart pointer to the next node (structural information)
template <typename generic_type>
class StackNode
{
private:
	generic_type data;						// Data to be stored in the node
	shared_ptr<StackNode> next_node;		// Smart pointer to the next node in the stack (nullptr if empty)

public:
	// Default constructor
	StackNode()
	{
		data = NULL;
		next_node = nullptr;
	}

	// Constructor used if data is passed in
	StackNode(const generic_type data_to_add)
	{
		data = data_to_add;
		next_node = nullptr;
	}

	// Destructor, instructions for destroying a StackNode object.
	~StackNode()
	{
		data = NULL;
		next_node = nullptr;		// decrements this next_node reference counter. When this counter becomes 0, it will be garbage collected (finally removed)
	}

	generic_type GetData()
	{
		return data;
	}

	shared_ptr<StackNode> GetNext()
	{
		return next_node;
	}

	void SetNext(const shared_ptr<StackNode> node_to_set)
	{
		next_node = node_to_set;
	}
};

// Class to implement the constraints of a Stack. Stores and manages StackNodes.
template <typename generic_type>
class CSC382_Stack
{
private:
	shared_ptr<StackNode<generic_type>> top;
	int size;

public:
	// Default Constructor
	CSC382_Stack()
	{
		init();
	}

	// Constructs an empty stack object and then adds the specified initial value
	CSC382_Stack(const generic_type initial_stack_value)
	{
		init();
		Push(initial_stack_value);
	}

	// Initialize the stack object variables
	void init()
	{
		this->top = nullptr;
		this->size = 0;
	}

	// Instructions for destorying a stack
	~CSC382_Stack()
	{
		// Iterate through all nodes in the Stack and delete them
		while (top != nullptr)
		{
			shared_ptr<StackNode<generic_type>> next_stack_node = top->GetNext();
			top.reset();
			top = next_stack_node;
			size--;
		}
	}

	// Push a node object onto the top of the stack
	bool PushNode(shared_ptr<StackNode<generic_type>> new_stack_node)
	{
		// Add a new node to the top of the stack
		if (top != nullptr)
		{
			new_stack_node->SetNext(top);		// Establish link between the new top node and the old top node
			top = new_stack_node;				// Move the top pointer to the new node on top of the stack
		}
		else
		{
			top = new_stack_node;				// Stack is empty, so simply point top to the new node
		}
		size++;
		return true;
	}

	// Creates a new StackNode and pushes it onto the top of the stack
	void Push(const generic_type insert_value)
	{
		auto new_stack_node = make_shared<StackNode<generic_type>>(insert_value);
		PushNode(new_stack_node);
	}

	// Pops a node off the stack and returns a smart pointer to the node
	shared_ptr<StackNode<generic_type>> Pop()
	{
		auto old_top = top;
		top = top->GetNext();
		size--;
		return old_top;
	}

	// Pops a node off the stack and returns the value stored in the node
	generic_type PopValue()
	{
		if (top != nullptr)
		{
			auto popped_node = Pop();
			return popped_node->GetData();
		}
		else
		{
			cout << "Cannot Pop. Stack is empty." << endl;
			return NULL;
		}
	}

	// Peek at the top node on the stack without removing it.
	shared_ptr<StackNode<generic_type>> PeekNode()
	{
		return top;
	}

	// Peek at the value of the top node on the stack without removing it.
	generic_type PeekValue()
	{
		if (top != nullptr)
		{
			return top->GetData();
		}
		else
		{
			cout << "Stack is empty." << endl;
			return NULL;
		}
	}

	// Peek at the top node without removing it.
	shared_ptr<StackNode<generic_type>> Peek()
	{
		return top;
	}

	// Returns the size of the stack (number of nodes in it)
	int GetSize()
	{
		return size;
	}

	// Prints the value stored in the stack to the screen
	void PrintStack()
	{
		auto current_node = top;
		// Iterates over the stack and prints the data stored in each node of the stack
		while (current_node != nullptr)
		{
			cout << current_node->GetData() << endl;
			current_node = current_node->GetNext();
		}
		// Message to display if the stack is empty
		if (size == 0)
		{
			cout << "The stack is empty." << endl;
		}
	}

};