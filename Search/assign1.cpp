#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <queue>
#include <deque>

// list of things to consider : 
// keep the next best node to compare too
// keep total cost
// global inadmissable landmarks vectors, that is hard-wired into code
// tree or vector

using namespace std;


// Structs and Classes 

struct coordinates {
	int x, y;
};

class Node
{
public:
	coordinates current;
	coordinates parent;
	int heuristic;
	int cost_from_start;
	int total_cost;
	Node() {
		
		heuristic = 0;
		cost_from_start = 0;
		total_cost = 0;
		current.x = -1;
		current.y = -1;

	}
	// parameterized constructor
	Node(coordinates x)
	{

		current = x;
		heuristic = 0;
		total_cost = 0;
		cost_from_start = 0;
	}

};

// Helper FUnctions

// Prints Coordinates
void print_coordinates(coordinates &x) { 
	cout <<"("<< x.x << "," << x.y << ")\n";
}

// Estimates Cost from two points
int get_heuristic(coordinates &current_state, coordinates &goal) {
	return abs(goal.x - current_state.x) + abs(goal.y - current_state.y);
}

// Checks coordinates if two coordinates are equal
bool check_coordinates(const coordinates &s, const coordinates &t) {
	if (s.x == t.x && s.y == t.y) {
		return true;
	} return false;
}

// Check if two nodes are equal

bool check_node(Node check1, Node check2) {
	coordinates checkpoint1 = check1.current;
	coordinates checkpoint2 = check2.current;
	if (check_coordinates(checkpoint1, checkpoint2)) {
		return true;
	}
	return false;
}

// CHecks if node belongs on our Queue  (Frontier or Closed)
bool Search(Node x, deque<Node> OpenList) {
	for (int i = 0; i < OpenList.size(); ++i) {
		if (check_node(x, OpenList[i])){
			return true;
		}
	} return false;
}

// Checks if Node belongs on Vector ( Specifically Inaccessible Nodes)

bool Search_Vector(coordinates x, vector<Node> blocked) {
	for (int i = 0; i < blocked.size(); i++)
	{
		if (check_coordinates(x, blocked[i].current)) return true;
	} return false;
}

// Checks if coordinates are allowable coordinates

bool check_real_coordinates(Node x) {
	coordinates y;
	y.x = -1;
	y.y = -1;
	if (check_coordinates(x.current, y)) return true;
	return false;
}

// Compares Total Score - used to sort our Frontier, for the smallest cost to our goal
bool lowestFScore(Node x, Node y) { // Used to sort our Frontier, for the next shortest cost.
	if (x.total_cost < y.total_cost)return true;
	return false;
}

// Returns a node if it is on our List
Node FindNode(Node x, deque<Node> OpenList) {
	for (int i = 0; i < OpenList.size(); ++i) {
		if (check_node(x, OpenList[i])){
			return OpenList[i];
		}
	}
}

// Returns the Node if the node belongs on our list
Node FindNodeCoordinate(coordinates x, deque<Node> OpenList) {
	for (int i = 0; i < OpenList.size(); ++i) {
		if (check_node(x, OpenList[i].current)){
			return OpenList[i];
		}
	}
}

//  Initialization Functions : Initializing our Blocked and Landmarks
void board_initialization(vector<Node> &blocked) {
	coordinates temp;// use to initialize our vector of blocked/inadmissable nodes
	for (int i = 5; i <= 9; ++i) {
		temp.x = 7;
		temp.y = i;
		Node temp1(temp);
		blocked.push_back(temp1);
	}
	for (int l = 10; l <= 15; ++l) {
		temp;
		temp.x = l;
		temp.y = 13;
		Node temp1(temp);
		blocked.push_back(temp1);
	}
	temp.y = 12;
	Node temp1(temp);
	blocked.push_back(temp1);
}

void landmark_initialization(vector<coordinates> &Landmarks) {
	coordinates a;
	coordinates b;
	coordinates c;
	coordinates d;

	a.x = 5; a.y = 12;
	b.x = 12; b.y = 12;
	c.x = 5; c.y = 5;
	d.x = 12; d.y = 5;

	Landmarks.push_back(a);
	Landmarks.push_back(b);
	Landmarks.push_back(c);
	Landmarks.push_back(d);
}

// This is our main functions for searching using an A* search 
// We use this search strategy because it is the most optimal, as it's search mechanisms are dependent on heuristics.
// We will also retrace our path of nodes, after we find out goal node.

int find_my_path(coordinates trial,Node x, deque<Node> List,vector<coordinates> &Path) {
	Node temp = x;
	int distance = 1;
	Path.push_back(x.current);
	if (check_coordinates(x.current, trial)) { return 1; }
	else {
		while (!check_coordinates(temp.parent, trial)) {
			Path.push_back(temp.current);
			temp = FindNode(temp.parent, List);
		} 
		Path.push_back(temp.current);
		return Path.size();
	}	
}

// A* search Algorithm : 
int Find_the_Goal(coordinates intial_coordinates,coordinates goal_coordinates, vector<Node> &blocked) {
// Initializes our Nodes from our user inputs
	Node goal;
	Node intial;
	vector<coordinates> Path;
	goal.current.x = goal_coordinates.x;
	goal.current.y = goal_coordinates.y;

	intial.current.x = intial_coordinates.x;
	intial.current.y = intial_coordinates.y;
	intial.cost_from_start = 0;
	intial.heuristic = get_heuristic(intial_coordinates, goal_coordinates);
	intial.total_cost = intial.cost_from_start + intial.heuristic;
// Initializes our Queues/ Vectors
	deque<Node> OpenList;
	deque<Node> ClosedList;
	int totalcost = 0;
	int number_of_node_expanded = 0;

// Initialize our Frontier Queue with the first Node
	OpenList.push_back(intial);

// Evaluate until there is still nodes to evaluate
	while (OpenList.size() != 0) {
		Node current;
		int distance;
		sort(OpenList.begin(), OpenList.end(), lowestFScore); // Sort for the lowest estimated cost in our Frontier. We will expand the smallest F. to find the lowest cost
		current = OpenList[0];
		if (check_node(current, goal)) { // Check if this is the goal node we are looking for. 
			
			distance = find_my_path(intial_coordinates,current,ClosedList,Path) -1; // Reconstruct the shortest path
			
			cout << "Number of nodes added to the Frontier : " << number_of_node_expanded << "\n";
			cout << "Shortest Distance(Leghnth) : " << distance << "\n";
			cout << "Shortest Path \n";
			cout << "Start:";
			print_coordinates(intial_coordinates);
			for (int i = Path.size() - 1; i > 0; --i) {
				print_coordinates(Path[i]);
			}
			
			return distance;
			
		}
		else { // If it is not our goal node, we will create our neighbour nodes and add them to our frontier accordingly
			for (int i = 0; i < 4; ++i) {
				Node neighbour;
				neighbour.current.x = -1;
				neighbour.current.y = -1;
				if (i == 0) {
					int x = current.current.x + 1;
					if (x < 18) {
						neighbour.current.x = x;
						neighbour.current.y = current.current.y;
					}
				} // if
				else if (i == 1) { // before allocating coordinates to adjacent nodes, we will check that the node is allocated in-range coordinates
					int x = current.current.x - 1;
					if (x >= 0) {  // an example of in-range coordinates, we will only allocate coordinates if it a positive number.  
						neighbour.current.x = x;
						neighbour.current.y = current.current.y;
					}
				}
				else if (i == 2) {
					int x = current.current.y + 1;
					if (x < 18) {
						neighbour.current.x = current.current.x;
						neighbour.current.y = x;
					}
				}
				else if (i == 3) {
					int x = current.current.y - 1;
					if (x >= 0) {
						neighbour.current.x = current.current.x;
						neighbour.current.y = x;
					}
				}
				neighbour.parent = current.current; // Allocate the parent node to the current node.
	// Case 1 : Our Nodes are either are out of range, or belong to the blocked list
				if (check_real_coordinates(neighbour))  {} // do nothing, the neighbour has not been allocated a viable coordinates 
				else if (Search_Vector(neighbour.current, blocked)) {} // check if it is a blocked node if it is not, we will update its parameters, and check if it is 
	// Case 2: Our node has not been evaluated before
				else if (!Search(neighbour, ClosedList))  {
						neighbour.heuristic = get_heuristic(neighbour.current, goal.current);
						neighbour.cost_from_start = current.cost_from_start + 1; // calculate cost from current cost.
						neighbour.total_cost = neighbour.cost_from_start + neighbour.heuristic;
						if (!Search(neighbour, OpenList)) { // this will also ensure that we do not add duplicated nodes
								OpenList.push_back(neighbour);
								number_of_node_expanded++;
						}
				}
	// Case 3: our Node has already been evaluated, we will compare total_cost, and updates if the new node is contains the shorter distance
				else { 
						Node Node_temp;
						Node_temp = FindNode(neighbour, ClosedList);
					if (Node_temp.cost_from_start > neighbour.cost_from_start) { 
						Node_temp.cost_from_start = neighbour.cost_from_start;
						Node_temp.parent = neighbour.parent; // This is important as it updates the shortest path.
								
					}
				}
			}// else
		}  // for
		OpenList.pop_front();
		totalcost++;
		ClosedList.push_back(current);
	} // While//  After we have created all adjacent nodes, we will take take the current node of interest from the Open List to the evaluated Node List. 
} 


// Main Helper Functions

int main()
{
	// Board Initializations
	int size_of_board = 17;
	vector<Node> blocked; // keeps tracks of all the inadmissable nodes
	board_initialization(blocked);
	coordinates intial_coordinates;
	coordinates goal_coordinates;
	int x, y;
	char program;

	// Initialize our Intial and Goal Coordinates

	cout << "Please enter your intial state: ";
	cin >> x >> y;

	if ((x > size_of_board) || (x < 0) ||( y > size_of_board) || (y < 0) ){
		cout << " Sorry your inputs lie outside the range of the board\n";
		system("pause");
		return 0;
	}
	
		intial_coordinates.x = x;
		intial_coordinates.y = y;
	
	
	cout << "Please enter your goal coordinates : ";

	cin >> x >> y;
	if (x > size_of_board || x < 0 || y > size_of_board || y < 0) {
		cout << " Sorry your inputs lie outside the range of the board\n";
		system("pause");
		return 0;
	}
	else {
		goal_coordinates.x = x;
		goal_coordinates.y = y;

	}


	if (Search_Vector(goal_coordinates, blocked)) {
		cout << " Sorry, your inputs lie on an inadmissable node\n";
		system("pause");
		
		return 0;
	}

	if (Search_Vector(intial_coordinates, blocked)) {
		cout << " Sorry, your inputs lie on an inadmissable node\n";
		system("pause");
		return 0;
	}

	cout << "Would you like to run this program with Landmarks? (Y/N) ";
	cin >> program;
	if (program == 'Y' || program == 'y') {
		int landmark_cost;
		vector<coordinates> Landmarks;
		landmark_initialization(Landmarks);

// 	Compare heuristics between the our Input coordinates and our landmarks. 
// Initial coordinates with our Landmark Coordinates
		
		int initial_landmark_estimated_cost = get_heuristic(intial_coordinates, Landmarks[0]);
		int landmark_initial = 0;
		for (int i = 1; i < 4; ++i) {
			int temp;
			temp = get_heuristic(intial_coordinates, Landmarks[i]);
			if (temp < initial_landmark_estimated_cost){
				initial_landmark_estimated_cost = temp;
				landmark_initial = i;
			}
		}
// Goal Coordinates compared to our Landmark Coordinates
	
		int goal_landmark_estimated_cost = get_heuristic(goal_coordinates, Landmarks[0]);
		int landmark_goal = 0;
		for (int i = 1; i < 4; ++i) {
			int temp;
			temp = get_heuristic(goal_coordinates, Landmarks[i]);
			if (temp < goal_landmark_estimated_cost){
				goal_landmark_estimated_cost = temp;
				landmark_goal = i;
			}
		}
// Allocated Cost between the chosen Landmarks
		if (landmark_goal == landmark_initial) { landmark_cost = 0; }
		else if ((landmark_goal == 0 && landmark_initial == 3) || (landmark_goal == 3 && landmark_initial == 0) ) {
			landmark_cost = 14;
		}
		else if ((landmark_goal == 1 && landmark_initial == 2) || (landmark_goal == 2 && landmark_initial == 1)) {
			landmark_cost = 14;
		}
		else {
			landmark_cost = 6;
		}
// Calculate estimated costs too conclude whether or not the usage of 1, 2  or no landmarks would calculate the shortest distance
		// Estimated cost of using two landmarks
		int estimated_cost = goal_landmark_estimated_cost + initial_landmark_estimated_cost; 
		int compare_total = estimated_cost + landmark_cost;
		// Estimated cost to go straight to goal.
		int estimated_cost2 = get_heuristic(intial_coordinates, goal_coordinates); 
		// estimated cost of using only one landmark
		int estimated_cost_start_to_goallandmarks = get_heuristic(intial_coordinates, Landmarks[landmark_goal]); 
		int compare = estimated_cost_start_to_goallandmarks + goal_landmark_estimated_cost;

// Case 1: Cheaper to go to the closest landmark near the goal
		if (compare < compare_total) {
			cout << "The shortest path is attained by going to the landmark closest near the goal \n";
			cout << "From our initial coordinates to Landmark: "; print_coordinates(Landmarks[landmark_goal]);
			int x = Find_the_Goal(intial_coordinates, Landmarks[landmark_goal],blocked);
			cout << "From our goal coordinates to the Goal Landmark"; print_coordinates(Landmarks[landmark_goal]);
			int y = Find_the_Goal(goal_coordinates, Landmarks[landmark_goal],blocked);
			cout << "Total Cost is : " << y + x << "\n"; // because they are going to the same landmark, there the landmark cost is 0;
		}
// Case 2 : using landmarks is cheapeast option ( shortest distance)
		else if (estimated_cost2 > estimated_cost) {
			cout << "Shortest Path from our Intial Coordinates to Landmark is : "; print_coordinates(Landmarks[landmark_initial]); 
		
			int y = Find_the_Goal(intial_coordinates, Landmarks[landmark_initial], blocked);
			cout << "Shortest Path from our Goal Coordinates to Landmark is : "; print_coordinates(Landmarks[landmark_goal]);
		
			int z = Find_the_Goal(goal_coordinates, Landmarks[landmark_goal], blocked);
			cout << "Total Cost is : " << y + z + landmark_cost << "\n";
		}
// Case 3 : going directly is to the goal is cheaper than using landmarks
		else {
			cout << " The shortest path is attained by going to the goal directly, without the use of landmarks \n";
			int y = Find_the_Goal(intial_coordinates, goal_coordinates, blocked);
		}

}
	else if(program == 'N'|| program == 'n'){ // if the user decides not to use landmarks ( part 2 of the program)
		int x = Find_the_Goal(intial_coordinates, goal_coordinates, blocked);
	}
	else { // if the user inputs wrong choice
		cout << "Wrong Inputs : Sorry Please Try Again \n";
	}
	system("pause");
	return 0;

}