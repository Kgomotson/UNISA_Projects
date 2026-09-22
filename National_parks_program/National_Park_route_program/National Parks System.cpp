

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <stack>
#include <queue>
#include <set>
#include <iomanip>      //prompt: we store the distances in an array dist = {0, ∞, ∞, ∞};
#include <climits>      //XAI response: yes, However, ∞ is not a valid value in C++ for an int.
using namespace std;   //Instead, we use a very large number to represent infinity


class Graph{
private:
    //Used a map to create a graph
    map<string, vector<pair<string,int>>> network;

public:

    //prompt: how do i loop through the map
    //XAI response: If you use the map<string, vector<pair<string,int>>> representation, looping through it is very straightforward.
    void adjacencyList(){
        cout<<"\nAdjacency list: "<<endl;
        cout<<"----------------\n";
        for(const auto& [park, weightedPairs] : network){
            cout<<left<<setw(2)<<park<<" -> ";
            for(const auto& edges : weightedPairs){
                cout<<edges.first<<"("<<edges.second<<" km)\n";
            }
            cout<<endl;
        }
    }

    void adjacencyMatrix(){
        cout<<"\n";
        cout<<"Adjacency matrix:"<<endl;
        cout<<"-----------------\n";

        cout<<"\t";
        for(const auto& parks: network){    //this loop displays the column names as parks
            if(parks.first != "Kgalagadi")  //forced formatting
                cout<<parks.first<<"  ";
            else
                cout<<parks.first<<"  ";
        }

        cout<<"\n";
        for(const auto& [parks,pairVector]: network){   //looping through the graphs map
            if(parks != "Kgalagadi")    //This was forced formatting its the only park that has so many letters
                cout<<parks<<"\t  ";       //even formatting wont work, so i hardcoded
            else
                cout<<parks<<" ";
            for(const auto& [pairKey, pairValue]: network){
                int weight = 0;
                for(const auto& edge: pairVector){
                    if(edge.first == pairKey){  //if the park which is the key in the map
                        weight = edge.second;    //matches the pair's first value, print the weight
                        break;                   //else the original weight which 0
                    }
                }
                cout<<weight<<"\t";
            }
            cout<<endl;
        }
    }

    void createGraph(vector<string> parks,vector<vector<pair<string,int>>>weightedPair){

        for(int i = 0; i < parks.size(); i++){              //The map holds as its key the vertex(park)
            network[parks[i]] = weightedPair[i];            //and the value is the edge with weights in a pair
        }
    }

    void BFS(string startStr){
        if(network.find(startStr) == network.end()){
            cout<<startStr<<" not found!";
            return;
        }
        set<string>visited;
        queue<string>q;                       //queue will hold visited node

        visited.insert(startStr);            //inserts user's selection into set
        q.push(startStr);                   //and queue

        cout<<left<<setw(5)<<"BFS Traversal starting from "<<startStr<<":"<<endl;
        bool first = true;

        while(!q.empty()){                  //checks if queue is empty
            string current = q.front();     //initializes current to the user's input
            q.pop();

            if(first){
                cout<<current;              //prints the users input
                first = false;
            }
            else{
                cout<<" -> "<<current;      //follows with the neighbours
            }

            for(const auto& parkName:network[current]){     //loops through the map with the vertex and edges
                string park = parkName.first;

                if(visited.find(park) == visited.end()){
                    visited.insert(park);
                    q.push(park);
                }
            }
        }
        cout<<endl;
    }

    //Prompt: How to implement a Djikstra's algo using a map in this format
    //map<string, vector<pair<string,int>>>
    void djikstrasAlgo(string startStr, string endStr){
        map<string, int>dist;           //map will hold the park's shortest distances as we update
        map<string, bool>visited;       //stores whether parks have been visited
        map<string, string>previous;    //stores previous park

        //XAI response: you also need to initialize all the other parks to infinity.
        for(const auto& park: network){
            dist[park.first] = INT_MAX;
            visited[park.first] = false;
        }
        dist[startStr] = 0;            //set initial distance to 0

        for(int i = 0; i < network.size(); i++){    //visit every park
            string current = "";                    //look for the next park
            int minDistance = INT_MAX;

            for(const auto& park : dist){           //Had XAI to help from this part because i lost track of understanding
                if(!visited[park.first] && park.second < minDistance){
                    minDistance = park.second;
                    current = park.first;
                }
            }

            if(current == " ")
                break;

            visited[current] = true;

            for(const auto& neighbour : network[current]){  //update neighbours
                string next = neighbour.first;
                int weight = neighbour.second;

                if(!visited[next] && dist[current] != INT_MAX){
                    int newDist = dist[current]+weight;

                    if(newDist < dist[next]){
                        dist[next] = newDist;

                        previous[next] = current;
                    }
                }
            }
        }

        cout<<endl;

        if(dist[endStr] == INT_MAX){
            cout<<"No path exists."<<endl;
            return;
        }



        stack<string>path;

        string current = endStr;

        while(current != ""){
            path.push(current);
            current = previous[current];
        }

        cout<<left<<setw(5)<<"Shortest Path from "<<startStr<<" to "<<endStr<<":"<<endl;

        while(!path.empty()){
            cout<<path.top();
            path.pop();

            if(!path.empty()){
                cout<<" -> ";
            }
        }
        cout<<endl;
        cout<<left<<setw(5)<<"\nTotal distance: "<<dist[endStr]<<" km";
        cout<<"\n";
    }

    void displayCorridors(){
        for(const auto& [park, weightedPairs] : network){
            for(const auto& edges : weightedPairs){
                int km = edges.second ;
                if(edges.second != km){
                    cout<<park<<"->"<<edges.first<<"("<<edges.second<<" km)\n";
                    cout<<'\t';
                }
            }
            cout<<endl;
        }
    }
};

string validate(string str){
    if(str == "kruger" || str == "Kruger")
        return "Kruger";
    else if(str == "kgalagadi" || str == "Kgalagadi")
        return "Kgalagadi";
    else if(str == "Limpopo" || str == "limpopo")
        return "Limpopo";
    else if(str == "Chobe" || str == "chobe")
        return "Chobe";
    else if(str == "Hwange" || str == "hwange")
        return "Hwange";
    else if(str == "Etosha" || str == "etosha")
        return "Etosha";
    else{
        cout<<"Input is invalid.\n";
        return "Invalid";
    }
}

int main(){

    Graph graph;

    //defined parks(vertex) using vector
    vector<string> parks = {
        "Kruger",
        "Limpopo",
        "Hwange",
        "Chobe",
        "Etosha",
        "Kgalagadi"
    };

    //defined connections(edges) with distances(weights) between them
    vector<vector<pair<string,int>>>weightedPair = {
        {{"Limpopo", 90}, {"Hwange",570}},
        {{"Kruger",90}},
        {{"Kruger",570},{"Chobe",110}},
        {{"Hwange",110},{"Etosha",900}},
        {{"Chobe",900},{"Kgalagadi",770}},
        {{"Etosha",770}}
    };

    //Create the graph
    graph.createGraph(parks,weightedPair);

    cout<<left<<setw(5)<<"\nSouthern Africa Wildlife Corridor Network"<<endl;
    cout<<left<<setw(5)<<"-----------------------------------------"<<endl;

    cout<<left<<setw(5)<<"Conservation Areas"<<endl;
    for(string str: parks){
        cout<<str;
        if(str != parks.back())
            cout<<" -> ";
    }
    cout<<endl;


    //Display adjacency list
    graph.adjacencyList();

    //Display adjacency matrix
    graph.adjacencyMatrix();

    //graph.displayCorridors();

    string start, end, startingPark, endingPark;

    cout<<"\nEnter starting park:"<<endl;
    cin>>start;
    cout<<endl;

    startingPark = validate(start);

    while(startingPark != "Exit" && startingPark != "exit"){
        if(startingPark != "Invalid"){
            cout<<"\nEnter destination park:"<<endl;
            cin>>end;
            cout<<"\n";
            endingPark = validate(end);
            while(endingPark == "Invalid"){
                cout<<"Enter destination park:"<<endl;
                cin>>end;
                cout<<"\n";
                endingPark = validate(end);
            }
            //cout<<"\n";
            graph.BFS(startingPark);
            graph.djikstrasAlgo(startingPark,endingPark);
        }

        //Asks user all over, til they quit the program
        cout<<"\nEnter starting park (or enter exit to quit):"<<endl;
        cin>>start;
        if(start != "Exit" && start != "exit")
            startingPark = validate(start);
        else
            startingPark = start;

        cout<<endl;
    }

    cout<<left<<setw(5)<<"Program quitted. GoodBye!"<<endl;
    cout<<endl;

    return 0;
}

//AI Reflection

/* XAI use in the project, my prompts asked:
    "Why is my BFS only printing Chobe?"
    "Why is my map empty?"
    "What does an adjacency list actually represent?"
    "How do I show each corridor once?"
    "Why is validate() not working?"
    "How does Dijkstra actually choose the next vertex?"

    XAI response:
    The Dijkstra implementation I gave you is there because
    you've already worked through the algorithm by hand. You calculated:

    Kruger → Hwange = 570
    Hwange → Chobe = 680
    Chobe → Etosha = 1580
    Etosha → Kgalagadi = 2350

    before we ever wrote a line of code. That's the important part.

    XAI comment on what I've done:
    From everything we've worked on together, here's what you've built yourself:

    ✅ Weighted adjacency list
    ✅ Adjacency matrix
    ✅ Graph construction
    ✅ BFS traversal
    ✅ Input validation
    ✅ Displaying the conservation network
    ✅ Understanding why graphs are undirected
    ✅ Understanding how Dijkstra updates distances

    The only thing that became overwhelming was turning the algorithm into C++ syntax.

    My Reflection
    1. Use of AI when coding can be frustrating when not knowing how to prompt it, so to curb this challenge
        I let it know before what my problem was and what I wanted it to help me with specifically to avoid
        unnecessary lengthy explanations.
    2. When it helped with code snippets, I had it explaining line by line what happens with a certain part of code.
    3.  Before prompting Ihad it explaining using a completely different example especially ones using ints or numbers as it was
        easier to follow and try own my own code to implement.
    4. Most of the code it provided when asked for it, would result in unexoected output, so this had me tracking down lines
        changing the output format, not following all suggestions at times and would "as I did in one instance" help it debug my code.
    5. For concepts that were completely new such as the set<> structure and pair, Id ask for examples to really understand how they work, 
        and can say I'm almost certain I can work with these freely, because I understand them with the practice I got from writing the program.
    */