#include <iostream>
#include <fstream>
#include "connector.h"

std::ifstream F;
char FILE_IN_NAME[] = "myfiles\\infile.txt";


void startprog()
{
	mathfunc::NodeList list = mathfunc::NodeList();
	list.read_from_file();
}
void mathfunc::NodeList::read_from_file()
{
	F.open(FILE_IN_NAME,std::ios::in);
	char x;
	if (F) {
		while (!F.eof()) {
			Part* data = new Part(0, 0);
			Node* node = new Node(data);
			if ((head == nullptr) && (tail == nullptr)) {
				F >> node->data->coef;
				F >> x;
				F >> node->data->pow_x;
				head = node;
				tail = node;
			}
			else {
				F >> node->data->coef;
				F >> x;
				F >> node->data->pow_x;
				tail->next = node;
				node->prev = tail;
				tail = node;
				
			}
		
		}
	}
	
	middle = tail;
	factorization();
	return;
}

void mathfunc::NodeList::factorization()
{
	Node* node=head;
	
	int temp=tail->data->coef;
	int result_pos;
	int result_neg;
	
	for (int i = 1;((i <= abs(temp))&&(head->data->pow_x>0)); i++) {
		if (temp % i == 0) {
			result_pos = i;
			result_neg = -i;
			if (calc_formula(result_pos) == 0) {
				temp = go_down(result_pos);
				i = 0;
			}
			else if (calc_formula(result_neg) == 0) {
				temp = go_down(result_neg);
				i = 0;
			}
			else
				continue;
		}
	}
	output_final();
	return;
	
}
int mathfunc::NodeList::go_down(int x)
{
	
	Node* node = head;
	while (true) {
		(node->next)->data->coef = (node->next)->data->coef + x * node->data->coef;
		(node->next)->data->pow_x--;
		if ((node->next)==middle)
			break;
		node = node->next;
	}
	middle = node;
	head->data->pow_x--;
	(node->next)->data->coef = 1;
	(node->next)->data->pow_x = x;

	return middle->data->coef;

}

int mathfunc::NodeList::calc_formula(int x)
{
	Node* node=head;

	int t = 0;
	while(true) {
		t += node->data->coef * pow(x, node->data->pow_x);
		if (node == middle)
			break;
		node = node->next;
	}
	return t;

}

void mathfunc::NodeList::output_final()
{
	Node* node = head;
	if (node->data->pow_x == 0) {
		std::cout << node->data->coef;
		node = node->next;
	}
	else {
		std::cout << "(";
		int iter = head->data->pow_x;
		while (true) {
			std::cout << node->data->coef << "*x^" << node->data->pow_x;
			if (node == tail) {
				std::cout << ")";
				return;
			}
			node = node->next;
			iter--;
			if (iter < 0)
				break;
			std::cout << " + ";
		}
		std::cout << ")";
	}
	while (true) {
		if(node->data->pow_x<0)
			std::cout << "( x + " << -node->data->pow_x << " )";
		else 
			std::cout << "( x - " << node->data->pow_x << " )";
		if (node == tail)
			break;
		node = node->next;
	}
	return;

}

mathfunc::NodeList::Node::Node(mathfunc::Part* data)
{
	this->data = data;
}
mathfunc::Part::Part(int coef,int pow_x)
{
	this->coef = coef;
	this->pow_x = pow_x;
}