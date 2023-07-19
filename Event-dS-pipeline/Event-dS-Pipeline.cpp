#include <bits/stdc++.h>

using namespace std;

enum NodeType {
	FETCH,
	DECODE,
	EXECUTE,
	STORE
};

class Node {
	public:
	NodeType type;
	int instruction;
	Node(NodeType t, int l);
};

Node::Node(NodeType t, int l) {
	type = t;
	instruction = l;
}

queue<Node> q;

int main() {
	
	int i = 1;
	int stalls = 0;
	int instructionLine = 1;
	
	q.push(Node(NodeType::FETCH, 1));
	
	int x = 20;
	bool c1=false, c2=false, c3=false, c4=false, c5=false;
	
	while(x>0) {
		cout<<"clock :"<<i<<" ";
		queue<Node> tmp;
		if(stalls > 1) {
			stalls--;
			cout<<"stalled \n";
			i++;
			continue;
		} else if (stalls > 0) {
			stalls--;
		}
		while(!q.empty()) {
			Node top = q.front();
			q.pop();
			if(top.type == NodeType::FETCH) {
				cout<<"fetch( ";
				switch (top.instruction) {
					case 1:
						cout<<"lw x1="<<x;
						top.type = NodeType::DECODE;
						tmp.push(top);
						break;
					case 2:
						cout<<"add 0 0 "<<x;
						top.type = NodeType::DECODE;
						tmp.push(top);
						break;
					case 3:
						cout<<"fsd "<<x;
						if(stalls == 0) {
							top.type = NodeType::DECODE;
						}
						tmp.push(top);
						break;
					case 4:
						cout<<"addi "<<x;
						if(c2) {
							top.type = NodeType::DECODE;
							tmp.push(top);
						} else {
							stalls++;
							tmp.push(top);
						}
						break;
					case 5:
						cout<<"bne "<<x;
						top.type = NodeType::DECODE;
						tmp.push(top);
						break;
				}
				cout<<" ) ";
			} else if (top.type == NodeType::DECODE) {
				cout<<"decode( ";
				switch (top.instruction) {
					case 1:
						cout<<"lw x1="<<x;
						top.type = NodeType::EXECUTE;
						tmp.push(top);
						break;
					case 2:
						cout<<"add 0 0 "<<x;
						if(c1) {
							top.type = NodeType::EXECUTE;
							tmp.push(top);
						} else {
							stalls++;
							tmp.push(top);
						}
						break;
					case 3:
						cout<<"fsd "<<x;
						if(c2) {
							top.type = NodeType::EXECUTE;
							tmp.push(top);
						} else {
							stalls++;
							tmp.push(top);
						}
						break;
					case 4:
						cout<<"addi "<<x;
						top.type = NodeType::EXECUTE;
						tmp.push(top);
						break;
					case 5:
						cout<<"bne "<<x;
						top.type = NodeType::EXECUTE;
						tmp.push(top);
						break;
				}
				cout<<" ) ";
			} else if (top.type == NodeType::EXECUTE) {
				cout<<"execute( ";
				switch (top.instruction) {
					case 1:
						cout<<"lw x1="<<x;
						top.type = NodeType::STORE;
						tmp.push(top);
						break;
					case 2:
						cout<<"add 0 0 "<<x;
						top.type = NodeType::STORE;
						tmp.push(top);
						break;
					case 3:
						cout<<"fsd "<<x;
						top.type = NodeType::STORE;
						tmp.push(top);
						break;
					case 4:
						cout<<"addi "<<x;
						top.type = NodeType::STORE;
						tmp.push(top);
						break;
					case 5:
						cout<<"bne "<<x;
						top.type = NodeType::STORE;
						tmp.push(top);
						break;
				}
				cout<<" ) ";
			} else {
				cout<<"store( ";
				switch (top.instruction) {
					case 1:
						cout<<"lw x1="<< x;
						c1 = true;
						break;
					case 2:
						cout<<"add 0 0 "<< x;
						c2 = true;
						break;
					case 3:
						cout<<"fsd "<< x;
						c3 = true;
						break;
					case 4:
						cout<<"addi "<< x;
						x = x - 4;
						c4 = true;
						break;
					case 5:
						cout<<"bne "<< x;
						c5 = true;
						break;
				}
				cout<<" ) ";
			}
		} 
		q.swap(tmp);
		
		if(stalls == 0) {
			instructionLine++;
			if(instructionLine > 5) instructionLine = 1;
			q.push(Node(NodeType::FETCH, instructionLine));
			switch(instructionLine) {
				case 1: 
					c1=false;
					break;
				case 2: 
					c2=false;
					break;
				case 3: 
					c3=false;
					break;
				case 4: 
					c4=false;
					break;
				case 5: 
					c5=false;
					break;
			}
		}
		
		cout<<"\n";
		i++;
	}
	return 0;
}







OUTPUT


clock :1 fetch( lw x1=20 ) 
clock :2 decode( lw x1=20 ) fetch( add 0 0 20 ) 
clock :3 execute( lw x1=20 ) decode( add 0 0 20 ) fetch( fsd 20 ) 
clock :4 store( lw x1=20 ) decode( add 0 0 20 ) fetch( fsd 20 ) 
clock :5 execute( add 0 0 20 ) decode( fsd 20 ) fetch( addi 20 ) 
clock :6 stalled 
clock :7 store( add 0 0 20 ) decode( fsd 20 ) fetch( addi 20 ) 
clock :8 execute( fsd 20 ) decode( addi 20 ) fetch( bne 20 ) 
clock :9 store( fsd 20 ) execute( addi 20 ) decode( bne 20 ) fetch( lw x1=20 ) 
clock :10 store( addi 20 ) execute( bne 16 ) decode( lw x1=16 ) fetch( add 0 0 16 ) 
clock :11 store( bne 16 ) execute( lw x1=16 ) decode( add 0 0 16 ) fetch( fsd 16 ) 
clock :12 store( lw x1=16 ) decode( add 0 0 16 ) fetch( fsd 16 ) 
clock :13 execute( add 0 0 16 ) decode( fsd 16 ) fetch( addi 16 ) 
clock :14 stalled 
clock :15 store( add 0 0 16 ) decode( fsd 16 ) fetch( addi 16 ) 
clock :16 execute( fsd 16 ) decode( addi 16 ) fetch( bne 16 ) 
clock :17 store( fsd 16 ) execute( addi 16 ) decode( bne 16 ) fetch( lw x1=16 ) 
clock :18 store( addi 16 ) execute( bne 12 ) decode( lw x1=12 ) fetch( add 0 0 12 ) 
clock :19 store( bne 12 ) execute( lw x1=12 ) decode( add 0 0 12 ) fetch( fsd 12 ) 
clock :20 store( lw x1=12 ) decode( add 0 0 12 ) fetch( fsd 12 ) 
clock :21 execute( add 0 0 12 ) decode( fsd 12 ) fetch( addi 12 ) 
clock :22 stalled 
clock :23 store( add 0 0 12 ) decode( fsd 12 ) fetch( addi 12 ) 
clock :24 execute( fsd 12 ) decode( addi 12 ) fetch( bne 12 ) 
clock :25 store( fsd 12 ) execute( addi 12 ) decode( bne 12 ) fetch( lw x1=12 ) 
clock :26 store( addi 12 ) execute( bne 8 ) decode( lw x1=8 ) fetch( add 0 0 8 ) 
clock :27 store( bne 8 ) execute( lw x1=8 ) decode( add 0 0 8 ) fetch( fsd 8 ) 
clock :28 store( lw x1=8 ) decode( add 0 0 8 ) fetch( fsd 8 ) 
clock :29 execute( add 0 0 8 ) decode( fsd 8 ) fetch( addi 8 ) 
clock :30 stalled 
clock :31 store( add 0 0 8 ) decode( fsd 8 ) fetch( addi 8 ) 
clock :32 execute( fsd 8 ) decode( addi 8 ) fetch( bne 8 ) 
clock :33 store( fsd 8 ) execute( addi 8 ) decode( bne 8 ) fetch( lw x1=8 ) 
clock :34 store( addi 8 ) execute( bne 4 ) decode( lw x1=4 ) fetch( add 0 0 4 ) 
clock :35 store( bne 4 ) execute( lw x1=4 ) decode( add 0 0 4 ) fetch( fsd 4 ) 
clock :36 store( lw x1=4 ) decode( add 0 0 4 ) fetch( fsd 4 ) 
clock :37 execute( add 0 0 4 ) decode( fsd 4 ) fetch( addi 4 ) 
clock :38 stalled 
clock :39 store( add 0 0 4 ) decode( fsd 4 ) fetch( addi 4 ) 
clock :40 execute( fsd 4 ) decode( addi 4 ) fetch( bne 4 ) 
clock :41 store( fsd 4 ) execute( addi 4 ) decode( bne 4 ) fetch( lw x1=4 ) 
clock :42 store( addi 4 ) execute( bne 0 ) decode( lw x1=0 ) fetch( add 0 0 0 ) 
