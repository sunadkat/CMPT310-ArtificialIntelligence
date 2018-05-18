#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <queue>
#include <deque>
#include <fstream>
#include <sstream>


// Structs and Classes

using namespace std;
struct atom {
	char c;
	bool value;
};

class statement {
public:
	deque<atom> body;
	char head;
	bool fact;
};

// Helper Functions 

bool Contains(atom x, deque<atom> &Goals) {
	for (int i = 0; i < Goals.size(); ++i) {
		if (Goals[i].c == x.c) return true;
	} return false;
}
bool fact(char c, deque<statement> &KB) {
	for (int i = 0; i < KB.size(); ++i) {
		if (KB[i].head == c) {
			if (KB[i].fact == true) return true;
		}
	} return false;
}

bool Contains2(atom x, deque<statement> KB) {
	for (int i = 0; i < KB.size(); ++i) {
		if (KB[i].head == x.c) return true;
	} return false;
}

// Backward Chaining 
bool Solve_Goals(atom &x, deque<statement> &KB, deque<atom> &Entailed) {
	int head1;
	// If the goal atom cannot be found in the KB, we return false
	if (!Contains2(x, KB)) {
		cout << "\t (" << x.c << ") cannot be proven because it cannot be found in the KB \n";
		return false;
	}

	while (!Contains(x, Entailed)) { // While our goal atom is not found in our Entailed Queue
		for (int i = 0; i < KB.size(); ++i) { // Go through all the queries in KB
			if (KB[i].head == x.c) { // If the goal atom is equal to the head of the Query. 
				if (KB[i].fact == true) { // If the head is a fact that it is we can add it onto our entailed queue. 
					cout << "\t(" << KB[i].head << ") is entailed because (" << x.c << ") is a fact\n";
					Entailed.push_back(x);
					return true;
				}
				else { // Otherwise we must be able Solve each of the atoms in the body of the query
					cout << "(" << x.c << ") can be proven by : ";
					for (int k = 0; k < KB[i].body.size(); ++k) {
						cout << KB[i].body[k].c << " ";
					}
					cout << "\n";
					deque<atom> Check; // 
					for (int j = 0; j < KB[i].body.size(); ++j) {
						if (Solve_Goals(KB[i].body[j], KB, Entailed)){ // Recursion, if we can solve for that atom we can add it not only to the entailed list but also the check list
							KB[i].body[j].value = true;
							Check.push_back(KB[i].body[j]);
						}
					}
					if (Check.size() == KB[i].body.size()) { // IF all the atoms can be derived, then our query is entailed. 
						Entailed.push_back(x);
						return true;
					}
				}
			}
		} return false;
	} 
	cout << "\t (" << x.c << ") which is already entailed.\n"; 
	return true; // If we can remove from the entailed loop, then the query entails.
}
bool Backtracking(char& choice, deque<statement> &KB, deque<atom> &Goals) {
	cout << "Query : (" << choice << ") \n";
	atom query;
	query.c = choice;
	query.value = false;
	return Solve_Goals(query,KB, Goals);
}

void initialize_rule(string line, deque<statement>& KB)
{
	statement check;
	if (line.size() == 1) {
		check.fact = true;
	}
	else {
		check.fact = false;
	}

	for (int i = 0; i < line.size(); ++i) {
		char c = line[i];
		if (i == 0) {
			check.head = c;
		}
		else if(i != 0 && line[i] != ' ') {
			atom x;
			x.c = line[i];
			x.value = false;
			check.body.push_back(x);

		}// else
		
	}KB.push_back(check);
	
}

// Main Function
int main() {
	// Initialize variables and File Intake process.
	deque<statement> KB;
	deque <atom> Goals;
	string file_name;
	cout << "Please enter your file name :";
	cin >> file_name;
	// Intialization List 
	string line = "";
	ifstream data_file(file_name);
	// Error Handling
	if (!data_file.is_open()) {
		cout << "Cannot Retrieve File! Please ensure that the file is in the same directory and try again \n";
		return 0;
	}

	getline(data_file, line); // Get the Goal Query
	char choice = line[0];

	// initializing the the KB
	while (getline(data_file, line)){
		if (line != "") { // * if string does not equal 
			initialize_rule(line, KB);
		}

	}
	// Solve the Query
	if (Backtracking(choice, KB, Goals)) {
		cout << "Your Query Entails \n";
	}
	else {
		cout << "Sorry, the Query does not Entail \n";
	}
		
}

