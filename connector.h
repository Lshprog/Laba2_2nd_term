#pragma once

namespace mathfunc {

	struct Part {
		int coef;
		int pow_x;
		Part(int coef, int pow_x);
	};
	
	struct NodeList {
	private:
		struct Node {
			Part* data;
			Node* next;
			Node* prev;
			Node(Part* data);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		Node* middle = nullptr;
	public:
		void factorization();
		int go_down(int x);
		int calc_formula(int x);
		void output_final();
		void read_from_file();
	};
	
}
