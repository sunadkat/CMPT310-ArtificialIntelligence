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
struct Color {
	int color_number;
	int constrain_value;
	bool available;
};

class States {
public:
	int state_number;
	bool coloured;
	vector<int> neighbours;
	vector<Color> colors;
	int colour_number;
	int degree;
	int remaining_values;
	States() {
		state_number = 0;
		coloured = false;
		colour_number = -1;
		degree = neighbours.size();
		remaining_values = 0;
	}
};

// General Helper Functions
int find_color(int colornum, States x) {
	for (int i = 0; i < x.colors.size(); ++i) {
		if (x.colors[i].color_number == colornum) return i;
	} return -1;
}

bool contains_color(int color_number, States x) {
	for (int i = 0; i < x.colors.size(); ++i){
		if (x.colors[i].color_number == color_number) {
			if (x.colors[i].available == true) return true;
		}
	} return false;
}

void print_map(deque<States> Coloured_map) {

	for (int i = 0; i < Coloured_map.size(); ++i){
		cout << "State Number: " << Coloured_map[i].state_number + 1 << "     ";
		cout << "Color Number: " << Coloured_map[i].colour_number + 1<< "\n";
	}
}

int find_position(int state, deque<States> &OpenList1) {
	int i = -1;
	for (int j = 0; j < OpenList1.size(); ++j) {
		if (OpenList1[j].state_number == state) return j;
	} return i;
}

bool is_Map_Coloured(deque<States> Coloured_map,int number_of_States) {
	if (Coloured_map.size() != number_of_States) return false;
	else {
		for (int i = 0; i < Coloured_map.size(); ++i)
			if (Coloured_map[i].coloured == false) return false;
	} return true;
	// check if all neighbours are different from each other. 

}

// Combination of MRV and Degree Heuristics and Helper Functions
// We will sort on MRV, and if we have multiple states with the same values, we will use degree has a tie breaker (ie. Choose the State with the highest degree).

States tie_breaker_all(deque<States> OpenList,int remaining_value) {
	int highest = -1;
	int x = 0;
	int number = 0;
	for (int i = 0; i < OpenList.size(); ++i){
		if (OpenList[i].remaining_values == remaining_value) {
			 x = OpenList[i].neighbours.size();
			if (x > highest){
				highest = x;
				number = i;
			}
		}
	}
	return OpenList[number];
}

bool lowestScore(States x, States y) { // Used to sort our Frontier, for the next shortest cost.
	if (x.remaining_values < y.remaining_values)return true;
	return false;
}

int find_best_variable(deque<States> OpenList) {
	States next_state;
	sort(OpenList.begin(), OpenList.end(), lowestScore); // Sorts our List by the number of Remaining Values
	if (OpenList[0].remaining_values == OpenList[OpenList.size() -1 ].remaining_values) { // Case 1 : All remaining values are the same or the first node to color. Degree Heuristic
		next_state = tie_breaker_all(OpenList,OpenList[0].remaining_values);
	}
	else if (OpenList[0].remaining_values == OpenList[1].remaining_values) { // Case 2 : We have multiple minimum values, since sorted, use degree heuristic to find the highest degree
		next_state = tie_breaker_all(OpenList,OpenList[0].remaining_values);
	}
	else {
		next_state = OpenList[0]; // Last case, the lowest minimum remaining values is one, so we we just return the lowest State
	}
	return next_state.state_number;

}

// Least Constraining Heuristic and Helper Functions

bool lowestconstrainvalue(Color x, Color y) { // Used to sort our Frontier, for the next shortest cost.
	if (x.constrain_value > y.constrain_value)return true;
	return false;
}

int Get_Constrain_Value(deque<States> &OpenList, int statenum, int colornum) {
	int sum = 0;
	int position = find_position(statenum, OpenList);
	for (int i = 0; i < OpenList[position].neighbours.size(); ++i) { // for every neighbour
		int state = OpenList[position].neighbours[i] - 1;
		int check = find_position(state, OpenList);
		if (check != -1) {
			if (contains_color(colornum, OpenList[check])) {
				sum +=  (OpenList[check].remaining_values - 1);
			}
		}
	}
	return sum;
}

void find_next_color(deque <States> &OpenList, int statenum){
	int position = find_position(statenum, OpenList);
	for (int i = 0; i < OpenList[position].colors.size(); ++i) {
		if (OpenList[position].colors[i].available) { // if the colour is available to color
			OpenList[position].colors[i].constrain_value = Get_Constrain_Value(OpenList, OpenList[position].state_number, OpenList[position].colors[i].color_number);
		}
	}
	sort(OpenList[position].colors.begin(), OpenList[position].colors.end(), lowestconstrainvalue);
}



// Simple Form of Foward Checking
// Part 1 : Checks to see that each arc has different allocated colors 
// Part 2 : Checks to see if after assigning state x = color value, all neighbours have some legal color left/ remaining. It will cause our Map to Backtrack
bool adjacent_nodes(deque<States> &Coloured_map, deque<States> OpenList, int check, int colour_number) {
	int position = find_position(check, Coloured_map);
	for (int i = 0; i < Coloured_map[position].neighbours.size(); ++i) {
		int neighbour = Coloured_map[position].neighbours[i] -1;
		int position2 = find_position(neighbour, Coloured_map);
			if (position2 != -1) {
				if (Coloured_map[position2].colour_number == colour_number) return false;
			}
	} return true;

}
bool any_zero_values(deque<States> &Coloured_map, deque<States> OpenList, int check, int colour_number) {
	int position = find_position(check, Coloured_map);
	for (int i = 0; i < Coloured_map[position].neighbours.size(); ++i) {
		int neighbour = Coloured_map[position].neighbours[i] - 1;
		int position2 = find_position(neighbour, OpenList);
		if (position2 != -1) {
			if (OpenList[position2].remaining_values == 0) return false;
		}
	}
	return true;
}
bool check_arc_consistency(deque<States> &Coloured_map, deque<States> OpenList, int check, int colour_number) {
	if (!adjacent_nodes(Coloured_map, OpenList, check, colour_number)) return false; // Checks if the assigned value is different from all adjacent nodes
	if (!any_zero_values(Coloured_map, OpenList, check, colour_number)) return false; // check if 
	return true;	
}

// Value Assignments / Helper Functions for Backtracking 
// Once a state is assigned a value, or re-assigned another value it will have to update the availability of that same value in it's neighbours

void Update_Neighbour_Colors(deque<States> &Coloured_map, deque<States> &OpenList, int statenum, int colornum){
	int position = find_position(statenum, OpenList);
	for (int i = 0; i < OpenList[position].neighbours.size(); ++i) { // for every neighbour
		int state = OpenList[position].neighbours[i] -1;
		int check = find_position(state, OpenList);
		if (check != -1) {
			if (contains_color(colornum, OpenList[check])) {
				int color = find_color(colornum, OpenList[check]);
				OpenList[check].colors[color].available = false;
				OpenList[check].remaining_values = OpenList[check].remaining_values - 1;

			}

		}
	}
}

void Re_Map_Colors(deque<States> &Coloured_map, deque<States> &OpenList, int statenum, int colornum){
	int position = find_position(statenum, Coloured_map);
	for (int i = 0; i < Coloured_map[position].neighbours.size(); ++i) { // for every neighbour
		int state = Coloured_map[position].neighbours[i] - 1;
		int check = find_position(state, OpenList);
		if (check != -1) {
			if (!contains_color(colornum, OpenList[check])) {
				int color = find_color(colornum, OpenList[check]);
				OpenList[check].colors[color].available = true;
				OpenList[check].remaining_values = OpenList[check].remaining_values + 1;
			}
		}
	}
}

// Recursive Backtracking Function 

bool Backtrack_Map(deque<States> &Coloured_map, deque<States> &OpenList, int number_of_colour) {
	bool result = false; 
	if (is_Map_Coloured(Coloured_map, OpenList.size() + Coloured_map.size())) { 
		cout << "Solution Exist! \n";
		print_map(Coloured_map);
		return true; }
	int next_state_to_colour = find_best_variable(OpenList); // MRV and Degree Heuristics to find the correct algorithm
	int position = find_position(next_state_to_colour, OpenList);
	find_next_color(OpenList, OpenList[position].state_number); // Least Constraining value; will sort each of X's remaining colors in order of least constraining value
	for (int i = 0; i < OpenList[position].colors.size(); ++i) { // For every available color
		if (OpenList[position].colors[i].available) {
			int colour_number = OpenList[position].colors[i].color_number; // give x that color value
			OpenList[position].colour_number = colour_number;
			OpenList[position].coloured = true;
			
			Update_Neighbour_Colors(Coloured_map, OpenList, OpenList[position].state_number, colour_number);
			int statenum = OpenList[position].state_number;
			Coloured_map.push_back(OpenList[position]);
			OpenList.erase(OpenList.begin() + position);

			if (!check_arc_consistency(Coloured_map, OpenList, statenum , colour_number)) return false; // if given that color, check consistency
			result = Backtrack_Map(Coloured_map, OpenList, number_of_colour);
			if (result != false) return true;
			int position2 = find_position(Coloured_map[Coloured_map.size()-1].state_number, Coloured_map);
			if (position2 != -1){
				Re_Map_Colors(Coloured_map, OpenList, Coloured_map[position2].state_number, colour_number);
				Coloured_map[position2].colour_number = -1;
				Coloured_map[position2].coloured = false;
				int statenum2 = Coloured_map[position2].state_number;
				OpenList.push_back(Coloured_map[position2]);
				Coloured_map.erase(Coloured_map.begin() + position2);
				position = find_position(statenum2, OpenList);
			}
		}
	}
	return false;
}

bool solution_exists(deque<States> &Coloured_map, deque<States> OpenList, int number_of_colours) {
	if (Backtrack_Map(Coloured_map, OpenList, number_of_colours)) return true;
	return false;
}


// Helper Function that reads in every line in our text document and assigns neighbours to each state
void get_adjacent_states(string line, deque<States>&types)
{
	stringstream check(line);
	int state_update;
	check >> state_update;
	state_update = state_update - 1;
	int x;
	
	while (check >> x) {
		types[state_update].neighbours.push_back(x);
	}
	int degreenum = types[state_update].neighbours.size();
	types[state_update].degree = degreenum;
	
}

void intialize_states(int number_states, int number_colors, deque<States> &OpenList) {
	for (int i = 0; i < number_states; ++i) {
		States x;
		x.state_number = i;
		x.remaining_values = number_colors;
		for (int l = 0; l < number_colors; ++l) {
			Color xxx;
			xxx.color_number = l;
			xxx.available = true;
			x.colors.push_back(xxx);
		}
		OpenList.push_back(x);

	}

}

// Main Function
int main() {

	string file_name; 
	cout << "Please enter your file name :"; 
	cin >> file_name;
	// Intialization List 
	string line = "";
	char x;
	int number_states = 0;
	int number_colors = 0;
	deque <States> OpenList;
	deque<States> Coloured_Map;
	ifstream data_file(file_name);
// Error Handling

	if (!data_file.is_open()) {
		cout << "Cannot Retrieve File! Please ensure that the file is in the same directory and try again \n";
		return 0;
	}

// Opening Text File and Retrieving our CSP variables and  Values
	data_file.get(x);
	getline(data_file, line);

	stringstream ss(line);
	ss >> number_states;
	ss >> number_colors;

// Intializing our CSP problem
	intialize_states(number_states, number_colors, OpenList);

// initializing the Neighbours in our CSP problem (Constraints)
	while (getline(data_file, line)){
			string line2 = line.substr(1,line.length() - 2);
			if (line2 != "") { // * if string does not equal 
				get_adjacent_states(line2, OpenList);
			}
			
	}

// Find if Solution Exists. 
		// Case 1: Solution Exists, our BackTrack map will return a solution to our CSP
		// Case 2 : No solution Exists

	bool result = false;
	result = solution_exists(Coloured_Map, OpenList, number_colors);
	if (!result) cout << "Solution does not exist \n";
	
	
	
}

