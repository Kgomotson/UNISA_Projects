

#include <iostream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include <functional>

using namespace std;

const unsigned int SEED = 2011;      //Hard-coded seed number for fixed operations data

struct Assign{
    int  id1;
    char id2;
};

struct Location{
    int l_id;
    string name;
    bool operator==(const Location& other)const{
        return l_id == other.l_id;
    }
};

struct LocationHash{
    std::size_t operator()(const Location &loc)const{
        return hash<int>{}(loc.l_id);
    }
};

struct Teams{
    char teamid;
    string responseCapability;
    Location currentLocation;
    string currentStatus;

    bool operator==(const Teams& other)const{
        return teamid == other.teamid;
    }
};


struct TeamHash{
    std::size_t operator()(const Teams &t)const{
        return hash<int>{}(t.teamid);
    }
};


struct Incidents{
    int num;
    Location loc;
    string category;
    string level;
    string status;

    bool operator==(const Incidents& other)const{
        return num == other.num;
    }
};

struct IncidentHash{
    std::size_t operator()(const Incidents &inc)const{
        return hash<int>{}(inc.num);
    }
};

struct Networks{
    Location l1;
    Location l2;
    int duration;
};

template <class T, class U>
void setLocations(unordered_set<T, U>&areas, int num1, string str){
    areas.insert({num1,str});
}

template <class T, class X, class U>
void createNetwork(vector<X> &network, unordered_set<T, U>&areas, int num1, int num2, int time){

    //function creates a network between 2 areas and swaps these as well because the roads are undirected
    string str3, str4;
    for(const auto& region: areas){
        if(region.l_id == num1){
            str3 = region.name;
        }
    }

    for(const auto& region: areas){
        if(region.l_id == num2){
            str4 = region.name;
        }
    }

    network.push_back({{num1,str3},{num2,str4},time});          //stores the first direction
    network.push_back({{num2,str4},{num1,str3},time});          //stores the swapped direction of the first one

}


template <class T>
void displayNetwork(vector<T>& network){

    //Displays the road network between locations and the distance in minutes.

    cout<<left<<setw(10)<<"Locations and roads:\n"
        <<"---------------------------------------------------------------\n"
        <<left<<setw(22)<<"Starting Location "
        <<left<<setw(2)<<" | "
        <<left<<setw(22)<<" Destination "
        <<left<<setw(2)<<" | "
        <<left<<setw(11)<<" Duration "
        <<left<<setw(2)<<" | \n"
        <<"---------------------------------------------------------------"
        <<endl;

    int i = 0;
    while(i < network.size()){
        cout<<left<<setw(3)<<network[i].l1.l_id<<" "
            <<left<<setw(2)<<" | "
            <<left<<setw(15)<<network[i].l1.name
            <<left<<setw(2)<<" | "
            <<left<<setw(3)<<network[i].l2.l_id<<" "
            <<left<<setw(2)<<" | "
            <<left<<setw(15)<<network[i].l2.name
            <<left<<setw(5)<<" | "
            <<left<<setw(9)<<network[i].duration
            <<left<<setw(2)<<" | "<<endl;
        i++;    
    }
    cout<<"---------------------------------------------------------------\n"<<endl;
        
}


template <class U, class T, class K, class L>
void createIncident(unordered_set<T, U>&areas, string categories[], string status[], unordered_set<L, K>&incident){
    //Creates all 10 incidents
    Incidents in;
    string severityLevels[] = {"Low","Medium","High"};

    //Enusres generated numbers are not duplicate
    unordered_set<int> numbers(10);

    while(numbers.size() != 10){
        numbers.insert(11+rand()%99);
    }

    //temp stores areas temporarily to use as incident locations
    vector<Location>temp;

    for(const auto& a: areas){
        temp.push_back(a);
    }

    for(int num : numbers){
        int j = rand()%9;
            in.num = num;
            in.loc.l_id = temp[j].l_id;
            in.loc.name = temp[j].name;
            in.category = categories[rand() %5];  //Selects a random incident issue
            in.level = severityLevels[rand() %3]; //Selects a random severity level
            in.status = status[rand() %3];        //Selects a random incident status

            incident.insert(in);
        
    }
}

template <class T, class K>
void displayIncident(unordered_set<T, K>&incident){
   //displays incidents
        cout<<left<<setw(10)<<"Incidents:\n"
        <<"------------------------------------------------------------------------------------\n"
        <<"Incident ID |"
        <<left<<setw(18)<<" Location "
        <<left<<setw(2)<<" | "
        <<left<<setw(17)<<" Incident Type "
        <<left<<setw(2)<<" | "
        <<left<<setw(8)<<" Level "
        <<left<<setw(2)<<" | "
        <<left<<setw(2)<<" Incident Status "
        <<left<<setw(20)<<" | "
        <<endl;
    cout<<"------------------------------------------------------------------------------------"<<endl;
    
    for(const auto& incidentInfo : incident){
        cout<<left<<setw(12)<<incidentInfo.num
        <<left<<setw(2)<<" | "
        <<incidentInfo.loc.l_id<<" "
        <<left<<setw(13)<<incidentInfo.loc.name
        <<left<<setw(2)<<"\t| "
        <<left<<setw(17)<<incidentInfo.category
        <<left<<setw(2)<<" | "
        <<left<<setw(8)<<incidentInfo.level
        <<left<<setw(5)<<" | "
        <<left<<setw(15)<<incidentInfo.status
        <<left<<setw(2)<<" | "<<endl;
    }

    cout<<"------------------------------------------------------------------------------------"<<endl;
}

template <class T, class K>
void prioritise(unordered_set<T, K>&incident, unordered_set<T,K>&openIncidents){
    //Displays all open incidents
    
    int i = 0;
    //Stores incidents with an "open" status
    
    for(const auto& incidentInfo : incident){
        if(incidentInfo.status == "Open")
            openIncidents.insert(incidentInfo);
    }
    
}

template <class T, class U, class X, class Y>
void createTeams(unordered_set<T, U>&areas, string categories[],unordered_set<X, Y>&team){
    //Function creates the response teams
     
    Teams t;
    vector<char> teamIDs = {'A','B','C','D','E','F'};   

    //team's statuses                
    string status[] = {"Available","Assigned","Unavailable"};       


    //Ensure numbers generated are unique
    unordered_set<int> uniqueNumbers(6);                            
    
    while(uniqueNumbers.size() != 6){
        uniqueNumbers.insert(rand() % 6);
    }

    vector<Location>temp;
    for(const auto& a: areas){
        temp.push_back(a);
    }


    for(int num : uniqueNumbers){
        int j = rand() % 9;
        t.teamid = teamIDs[num];                              //index selects a random location for a team
        t.responseCapability = categories[rand() %5];
        t.currentLocation.l_id = temp[j].l_id;
        t.currentLocation.name = temp[j].name;
        t.currentStatus = status[rand() %3];

        team.insert(t);

    }
}

template <class X, class Y>
void displayTeam(unordered_set<X, Y>&team){
    
    //Displays teams
    cout<<left<<setw(10)<<"Response teams:\n"
        <<"-------------------------------------------------------------------\n";
        cout<<left<<setw(5)<<"Team ID "
        <<left<<setw(2)<<" | "
        <<left<<setw(10)<<"Response Capability"
        <<left<<setw(2)<<" | "
        <<left<<setw(10)<<"Current Location"
        <<left<<setw(2)<<" | "
        <<left<<setw(10)<<"Current Status"
        <<left<<setw(2)<<" | "
        <<endl;

    cout<<"-------------------------------------------------------------------"<<endl;
    
    
    for(const auto& teamInfo: team){
        cout<<left<<setw(8)<<teamInfo.teamid
        <<left<<setw(4)<<" | "
        <<left<<setw(19)<<teamInfo.responseCapability
        <<left<<setw(2)<<" | "
        <<left<<setw(2)<<teamInfo.currentLocation.l_id<<" "
        <<left<<setw(13)<<teamInfo.currentLocation.name
        <<left<<setw(2)<<" | "
        <<left<<setw(13)<<teamInfo.currentStatus
        <<left<<setw(2)<<" | "
        <<endl;
     
    }
    cout<<"-------------------------------------------------------------------"<<endl;
    
    
        
}


template <class T, class X, class K, class A, class B, class Y, class D, class E>
void investigateIncident(unordered_set<T, K>&incident, unordered_set<X, Y>&team, unordered_set<A, B>&selectedID, 
                        unordered_set<D,E>&selectedTeams, Assign &delegate){
    
    //Allows operator to find out more about an incident

    int inputID;

    //displays all incident ID's to select and display info
    cout<<"Incident ID's: (";
    
    for(const auto& incidentInfo : incident){
        cout<<incidentInfo.num<<" ";
    }
    cout<<")"<<endl;
    
    cout<<"\nTo get more information about an incident in the list above, enter Incident ID: ";
    cin>>inputID;
    
    string idStatus, idType;
    int idLocation;


    //selectedID will store the info for the seleceted incident
    for(const auto& incidentInfo : incident){
        if(inputID == incidentInfo.num){
            idLocation = incidentInfo.num;
            idStatus = incidentInfo.status;
            idType = incidentInfo.category;
            selectedID.insert(incidentInfo);
                break;
        }
    }

        cout<<"\nSelected ";
        displayIncident(selectedID);
        
    

    //Stores the selected team's current status
    string teamStatus;


    //selectedTeams will store a list of all teams dealing with the category of the selected incident id
    for(const auto& teamInfo : team){
            if(teamInfo.responseCapability == idType){
                teamStatus = teamInfo.currentStatus;
                selectedTeams.insert(teamInfo);
                break;
            }
        }
    

    //Displays all potential teams that are suitable to attend to the selected incident
    if(selectedTeams.size() != 0){
        if(idStatus == "Open"){
            cout<<"\nSuitable ";
            displayTeam(selectedTeams);
        }
        else{
            cout<<"Incident "<<inputID<<", is "<<idStatus<<" ."<<endl;
        }
    }else
        cout<<"There's no team available that works on "<<idType<<" issues.\n"<<endl;

    
    char response;

    //Below the program will ask the user if they want to assign a team to an open task, if any teams are available
    if(selectedTeams.size() != 0 && idStatus == "Open" && teamStatus != "Unavailable"){
        cout<<"\nWould you like to assign a team for Incident "<<idLocation<<"?\nEnter 'Y' for yes or 'N' for no:"<<endl;
        cin>>response;

        if(response == 'Y' || response == 'y') {
            updateOperationalData(incident,idLocation, team, delegate, selectedID, selectedTeams);
        }else
            cout<<"No team assigned. GoodBye!"<<endl;
    }else{
        cout<<"\n***** Teams are \"Unavailable\" or non were selected...goodbye! *****"<<endl;
    }

}

template <class T, class X, class Y, class K, class A, class B, class D, class E>
void updateOperationalData(unordered_set<T, K>&incident,int &idLocation,  unordered_set<X, Y>&team, Assign &delegate,
                    unordered_set<A, B>&selectedID,unordered_set<D,E>&selectedTeams){
    
    //displayIncident(incident);

    char assignedTeam;


    //Operator will be prompted to enter the ID of the team he wants to assign to the open incident
    cout<<"\nTo assign a team to attend to incident "<<idLocation<<", Enter team ID from list above or N to exit:"<<endl;
    cin>>assignedTeam;
    
    //Delegate will store the ID's of the incident and team selected
    delegate = {idLocation,assignedTeam};
    
    cout<<"Incident "<<delegate.id1<<", has been assigned to team "<<delegate.id2<<".\n"<<endl;
    
    Incidents a;
    a.num = delegate.id1;
    auto change = selectedID.extract(a);
   
    //Stores data of the selected incident
    if(!change.empty()){

        //Changes the incident status to "Assigned"
        change.value().status = "Assigned";

        //Populates the selectedID set with the team with a new status
        selectedID.insert(move(change));
    }


    Teams b;
    b.teamid = delegate.id2;
    auto update = selectedTeams.extract(b);

    //Stores data of the selected Team
    if(!update.empty()){
        //Changes the selected Team status to "Assigned"
        update.value().currentStatus = "Assigned";

        //Populates the selecetedTeam set with the team with a new status
        selectedTeams.insert(move(update));
    }
    

    int num;
    //The incident and team selected status will be changed to "Assigned"
    changeIncident(incident,selectedID,delegate,num);
    changeTeam(team,selectedTeams,delegate);
}


template <class A, class B>
void changeIncident(unordered_set<A, B>&incident,unordered_set<A, B>&selectedID, Assign &delegate, int &total){

    //This function removes the selected incidents data from the incidents list and replaces it with the new data with the "assigned" status

    Incidents a;
    a.num = delegate.id1;
    auto findID = incident.find(a);


    //Searches for the id of the incident in the incident list
    if(findID != incident.end()){
        Incidents updatedData = *findID;

        //Stores the copy of that incident to updatedData
        for(const auto& incidentInfo: selectedID){
            updatedData = incidentInfo;
        }

        //Deletes the old incident data of the ID
        incident.erase(findID);

        //Insert the new one into the incidents list.
        incident.insert(updatedData);
    }

    total = selectedID.size();
}

template <class A, class B>
void changeTeam(unordered_set<A, B>&team,unordered_set<A, B>&selectedTeam, Assign &delegate){

    //This function removes the selected team data from the team list and replaces it with the new data with the "assigned" status

    Teams a;
    a.teamid = delegate.id2;
    auto findID = team.find(a);


    //Searches for the id of the team in the team list
    if(findID != team.end()){
        Teams updatedData = *findID;

        //Stores the copy of that team to updatedData
        for(const auto& teamInfo: selectedTeam){
            updatedData = teamInfo;
        }

        //Deletes the old team data of the selecetd teamID
        team.erase(findID);

        //Insert the new one into the team list.
        team.insert(updatedData);
    }
}


template <class T, class U, class A, class B>
void summary(unordered_set<T, U>& openIncidents, int &a,unordered_set<A, B>&team){
    int count = 0;
    cout<<"summary of the current operational situation.\n"<<endl;

    cout<<"Number of open incidents: "<<openIncidents.size()<<"."<<endl;
    cout<<"Number of assigned incidents: "<<a<<"."<<endl;
    cout<<"Number of available teams: ";
    for(const auto& t: team){
        if(t.currentStatus == "Available")
            count++;
    }
    cout<<count<<endl;
    

    
}


template <class Z, class T, class U, class X, class Y, class  A, class B>
void menu(vector<Z>& network, unordered_set<T, U>& incident, unordered_set<T, U>& openIncidents,
             unordered_set<X, Y>&team, unordered_set<T, U>&selectedID, unordered_set<A, B>selectedTeams, Assign delegate, int total){

    cout<<"========================================\n"
        <<"MUNICIPAL INCIDENT RESPONSE SYSTEM\n"
        <<"========================================\n"
        <<"1. Display Locations and Roads\n"
        <<"2. Display Incidents\n"
        <<"3. Prioritise Open Incidents\n"
        <<"4. Display Response Teams\n"
        <<"5. Investigate Incident\n"
        <<"6. Find Route\n"
        <<"7. Update Incident\n"
        <<"8. Display Summary\n"<<endl;
    cout<<"Enter your choice: "<<endl;
    
    int option;
    cin>>option;

    cout<<"\n"<<endl;
    switch(option){
        case 1:
            displayNetwork(network);
        break;
        case 2:
            displayIncident(incident);
        break;
        case 3:
            prioritise(incident,openIncidents);
            cout<<"Priority ";
            displayIncident(openIncidents);
        break;
        case 4:
            displayTeam(team);
        break;
        case 5:case 7:
            investigateIncident(incident, team, selectedID,selectedTeams, delegate);
        break;
        case 6:
            //findRoute(areas, network);
        break;
        case 8:
            prioritise(incident,openIncidents);
            changeIncident(incident,selectedID,delegate, total);
            summary(openIncidents, total, team);
        break;
        default:
            cout<<"Invalid entry.\nTry again:";
            cin>>option;
            cout<<"\n"<<endl;
            menu(network, incident ,openIncidents, team, selectedID,selectedTeams,delegate, total);
    }
    
}


int main(){

    //statuses, categories and severityLevels
    string incidentStatus[] = {"Open","Assigned","Resolved"};
    string categories[] = {"Water","Electricity","Roads","Sanitation","Public Facilities"};

    //areas stores hard-coded locations with unique ID's
    unordered_set<Location, LocationHash> areas;

    setLocations(areas,1,"Halfway House");
    setLocations(areas,2,"Sunninghill");
    setLocations(areas,3,"Chartwell");
    setLocations(areas,4,"Beverley");
    setLocations(areas,5,"Ivory Park");
    setLocations(areas,6,"Austin View");
    setLocations(areas,7,"Diepsloot");
    setLocations(areas,8,"Ebony Park");
    setLocations(areas,9,"Mayibuye");
    setLocations(areas,10,"Country View");


    //networks stores road connection between locations
    vector<Networks> network;
    createNetwork(network, areas,1,10,10);
    createNetwork(network, areas,1,6,8);
    createNetwork(network, areas,1,2,15);
    createNetwork(network, areas,10,7,22);
    createNetwork(network, areas,6,8,8);
    createNetwork(network, areas,7,3,15);
    createNetwork(network, areas,7,4,15);
    createNetwork(network, areas,3,4,10);
    createNetwork(network, areas,5,8,5);
    createNetwork(network, areas,5,9,8);
    createNetwork(network, areas,2,4,15);
    createNetwork(network, areas,4,10,10);
    
    //Incident stores list of incidents with unique ID's
    unordered_set<Incidents, IncidentHash> incident, openIncidents, selectedID;
    createIncident(areas, categories, incidentStatus, incident);

    //team stores list of teams with unique ID's
    unordered_set<Teams,TeamHash>team, selectedTeams;
    createTeams(areas, categories, team);

    Assign delegate;
    
    char response = 'Y';
    int num;
    
    while(response != 'N' || response != 'n'){
        char ans;
        if((response == 'Y' || response == 'y')){
            menu(network, incident ,openIncidents, team, selectedID,selectedTeams,delegate,num);
            cout<<"\nWould you like to continue? Enter 'Y' to continue or 'N' to quit: \n";
            cin>>ans;
        }else if(response == 'N' || response == 'n'){
            cout<<"Program quitted. Goodbye!"<<endl;
            break;
        }else{
            cout<<"Invalid input. Try again.\nEnter 'Y' to continue or 'N' to quit: \n"<<endl;
            cin>>ans;
        }
        response = ans;
    }
    

    return 0;
}





/*SOURCE COMMENTS:
1. Locations and road connections: With regard to locations and the roads between them, i figured since the request was to 
include a unique ID for every location, I sought to use those ID's to create a network between
the roads. The program can Identify the key from the list of locations that were added and could
find the name of the key and connect its time between the other location as well. Then I swapped 
as these roads are undirected.
The location distances in minutes is data pick from google maps too. The rlocations in Region A were more than 10 so i seleceted randomly 10 locations and a part of their roads connections.
I used google to find out the locations.

I decided to use a unordered set as it could store the unique id's for incidents, teams and locations, I tried with a map but found that accessing it was hard as most of my data is stored in structs with multiple 
values.

Couldnt finish up the findRoute function and summary function.

Road connections, I had them stored in a vector as they had duplicates.

With pruiritising I used the incident set and filtered by "Open " incidents only.

For testing I used fixed data values, one by one before filling up to requested level. 
I used an online compiler to compile my code as it compiled faster than vscode.

I used the response team's responsibility status and current work status to serve as tehir suitability matrix. Then the findRoute function wouldve helped to calculate the time it wouyld take to leave fro  their location to the incident location.

*/
