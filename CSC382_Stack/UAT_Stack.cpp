// UAT_Stack - Example Stack implementation for UAT
// Coded by: Kent Slack
#include "stdafx.h"
#include "Stack.h"
#include <memory>
#include <iostream>

using namespace std;

bool StackTestingSuite()
{
	bool test_success = true;
	//**************************************
	//****** Stack Constructor Tests *******
	//****** Default Stack Constructor Tests
	auto stack_default_constructor = make_shared<CSC382_Stack<int>>();		// Creates a new stack
	int stack_size = stack_default_constructor->GetSize();
	if (stack_size == 0)
	{
		cout << "Success - Size correctly reported of new stack using default constructor." << endl;
	}
	else
	{
		cout << "FAIL - Size incorrectly reported of new stack using default constructor. Size reported as " << stack_size << endl;
		test_success = false;
	}

	int default_top_value = stack_default_constructor->PeekValue();
	if (default_top_value == NULL)
	{
		cout << "Success - Top value is correctly set to NULL after default constructor call." << endl;
	}
	else
	{
		cout << "FAIL - Top value not set to NULL following default constructor call." << endl;
		test_success = false;
	}

	auto top_node_ptr = stack_default_constructor->Peek();
	if(top_node_ptr == nullptr)
	{
		cout << "Success - The top value of the stack is nullptr as expected." << endl;
	}
	else
	{
		cout << "FAIL - The top value of an empty stack is not nullptr" << endl;
		test_success = false;
	}


	//****** Single Parameter Constructor Test
	auto char_stack = make_shared<CSC382_Stack<char>>('u');
	int char_stack_size = char_stack->GetSize();
	if(char_stack_size == 1)
	{
		cout << "Success - Size correctly reported of new stack using single parameter constructor." << endl;
	}
	else
	{
		cout << "FAIL - Size incorrectly reported of new stack using single parameter constructor. Size reported as " << char_stack_size << endl;
		test_success = false;
	}

	char one_param_top_value = char_stack->PeekValue();
	if (one_param_top_value == 'u')
	{
		cout << "Success - Top is correctly set to u after one parameter constructor call." << endl;
	}
	else
	{
		cout << "FAIL - Top not set to u following one parameter constructor call." << endl;
		test_success = false;
	}

	//************************************
	//****** Function Tests ******
	// Push Tests
	stack_default_constructor->Push(5);
	if(stack_default_constructor->GetSize() == 1)
	{
		cout << "Success - Stack size is now 1 as expected." << endl;
	}
	else
	{
		cout << "FAIL - Stack size is not 1 as expected." << endl;
		test_success = false;
	}

	int top_value = stack_default_constructor->PeekValue();
	if(top_value == 5)
	{
		cout << "Success - Top value of stack is 5 as expected." << endl;
	}
	else
	{
		cout << "FAIL - Top value of stack is " << top_value << ". Expected a value of 5." << endl;
		test_success = false;
	}


	// PushNode Tests
	auto new_stack_node = make_shared<StackNode<int>>(4);
	stack_default_constructor->PushNode(new_stack_node);
	if(stack_default_constructor->GetSize() == 2)
	{
		cout << "Success - Stack is size 2 after PushNode function called." << endl;
	}
	else
	{
		cout << "FAIL - Stack is not size 2 after PushNode function call." << endl;
		test_success = false;
	}

	top_value = stack_default_constructor->PeekValue();
	if (top_value == 4)
	{
		cout << "Success - Top value of stack is 4 as expected after PushNode function call." << endl;
	}
	else
	{
		cout << "FAIL - Top value of stack is " << top_value << ". Expected a value of 4 after PushNode function call." << endl;
		test_success = false;
	}


	// Print Stack Tests
	cout << "Printing the current state of the stack to the screen." << endl;
	cout << "Expected output is:\n4\n5" << endl;
	cout << "Actual output is:" << endl;
	stack_default_constructor->PrintStack();
	

	// Pop Test
	auto pop_node = stack_default_constructor->Pop();
	if(pop_node != nullptr)
	{
		if (pop_node->GetData() == 4)
		{
			cout << "Success - Node successfully poped off the stack." << endl;
		}
		else
		{
			cout << "FAIL - Correct value was not found for popped value." << endl;
			test_success = false;
		}
	}
	else
	{
		cout << "FAIL - Nullptr was received from pop when the value of 4 should have been found." << endl;
		test_success = false;
	}

	if(stack_default_constructor->GetSize() == 1)
	{
		cout << "Success - Stack is the correct size after Pop function call." << endl;
	}
	else
	{
		cout << "FAIL - Stack is the wrong size after Pop function call." << endl;
		test_success = false;
	}


	// PopValue Tests
	auto pop_value = stack_default_constructor->PopValue();
	if(pop_value == 5)
	{
		cout << "Success - PopValue returned 5 as expected." << endl;
	}
	else
	{
		cout << "FAIL - PopValue returned incorrect value. Expected 5, received " << pop_value << endl;
		test_success = false;
	}

	if (stack_default_constructor->GetSize() == 0)
	{
		cout << "Success - The stack is empty following PopValue." << endl;
	}
	else
	{
		cout << "FAIL - Following the PopValue function call, the stack reports the wrong size. " << stack_default_constructor->GetSize() << endl;
		test_success = false;
	}



	// Load Testing Stack with many Push function calls
	for(int counter = 0; counter < 10000; counter++)
	{
		stack_default_constructor->Push(counter);
	}
	if(stack_default_constructor->GetSize() == 10000)
	{
		cout << "Success - 10000 nodes now found in the stack after load testing." << endl;
	}
	else
	{
		cout << "FAIL - Incorrect number of nodes found in the stack after load testing." << endl;
	}


	return test_success;
}


bool NodeTestingSuite()
{
	// This should be implemented. Try building the test suite for the node class as practice.
	return true;
}


bool TestingSuite()
{
	system("CLS");
	bool node_test_status = NodeTestingSuite();

	bool stack_test_status = StackTestingSuite();

	cout << endl << endl << endl;
	if(node_test_status && stack_test_status)
	{
		cout << "~~~~~~~~~ All Test Successfully Passed! ~~~~~~~~~~~~" << endl;
		return true;
	}
	else
	{
		cout << "~~~~~~~~~ Some or all tests FAILED! ~~~~~~~~~~~~~~~~" << endl;
		return false;
	}
}

void Menu()
{
	CSC382_Stack<int> menu_stack;
	int selection = -1;
	while (selection != 0)
	{
		cout << "Welcome to the CSC382 Stack Class. Please specify the operation you would like to perform." << endl;
		cout << "(1) Construct Stack using default constructor." << endl;
		cout << "(2) Construct Stack when initial value provided." << endl;
		cout << "(3) Push a value on the stack." << endl;
		cout << "(4) Push existing node on the stack." << endl;
		cout << "(5) Pop a value off the stack." << endl;
		cout << "(6) Peek at the top value of the stack." << endl;
		cout << "(7) Print the size of the stack." << endl;
		cout << "(8) Print the stack." << endl;
		cout << "(9) Automated Testing Suite." << endl;
		cout << "(0) Exit" << endl;

		cout << "What operation would you like to perform (specify the number)? ";
		cin >> selection;

		int user_specified_value;
		if (selection == 1)		// Construct Stack using default constructor
		{
			menu_stack = CSC382_Stack<int>();
		}
		else if(selection == 2)		// Construct Stack when initial value provided
		{
			cout << "What integer value would you like to add to the new stack? ";
			cin >> user_specified_value;
			menu_stack = CSC382_Stack<int>(user_specified_value);
		}
		else if (selection == 3)		// Push a value on the stack
		{
			cout << "What integer value would you like to add to the stack? ";
			cin >> user_specified_value;
			menu_stack.Push(user_specified_value);
		}
		else if (selection == 4)		// Push existing node on the stack
		{
			cout << "What integer value would you like to add to the stack? ";
			cin >> user_specified_value;
			shared_ptr<StackNode<int>> node_to_add = make_shared<StackNode<int>>(user_specified_value);
			menu_stack.PushNode(node_to_add);
		}
		else if (selection == 5)		// Pop a value off the stack
		{
			auto pop_value = menu_stack.PopValue();
			if (pop_value)
			{
				cout << "Pop Value = " << pop_value << endl;
			}
		}
		else if (selection == 6)		// Peek at the top value of the stack
		{
			auto peek_value = menu_stack.PeekValue();
			if (peek_value)
			{
				cout << "Peek Value = " << peek_value << endl;
			}
		}
		else if (selection == 7)		// Print the size of the stack
		{
			cout << "The stack contains " << menu_stack.GetSize() << " nodes." << endl;
		}
		else if (selection == 8)		// Print the stack
		{
			cout << "The stack contains the following values: " << endl;
			menu_stack.PrintStack();
		}
		else if (selection == 9)		// Automated Testing Suite
		{
			TestingSuite();
		}

		cout << endl << endl;
	}
}

int main()
{
	Menu();
	system("pause");
	return 0;
}
