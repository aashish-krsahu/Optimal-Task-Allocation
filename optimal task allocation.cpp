#include <bits/stdc++.h>
#include <fstream>  

using namespace std;


class student_class{
    int id;
    string name;
    float reliability;
    public:
    student_class() = default;
    student_class(int _id, const string& _name, float _r)
    {
        id = _id;
        name= _name;
        reliability = _r;
    }
    
    string get_name() {
        return name;
    }
    float get_reliability() {
        return reliability;
    }
    vector<student_class> read_students();
};

class task_class{
    int id;
    string name;
    float difficulty;
    public:
    task_class() = default;
    task_class(int _id, const string& _name, float _d)
    {
        id = _id;
        name = _name;
        difficulty = _d;
    }
    
    string get_name() {
        return name;
    }
    float get_difficulty(){
        return difficulty;
    } 
    vector<task_class> read_tasks();
};

class edge_class{
    int student_id;
    int task_id;
    public:
    static vector<vector<float>> cost;
    vector<vector<float>> read_edges(float , float );
};

vector<vector<float>> edge_class::cost;

vector<student_class> student_class:: read_students(){
    vector<student_class> students;
    ifstream in("students.csv");
    string header;
    getline(in,header);
    
    while(getline(in,header)){
        if(header.empty()) continue;
        stringstream ss(header);
        
        string id, name, rel;
        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,rel,'\n');

        if (id.empty() || name.empty() || rel.empty()) continue;
        int sid = stoi(id);
        float reliability = stof(rel);
        students.emplace_back(sid, name, reliability);
    }
    in.close();
    return students;
}

vector<task_class> task_class :: read_tasks(){
    vector<task_class> task;
    ifstream in("tasks.csv");
    string header;
    getline(in,header);

    while(getline(in,header)){
        if(header.empty()) continue;
        stringstream ss(header);

        string id, name, dif;
        getline(ss,id,',');
        getline(ss,name,',');
        getline(ss,dif,'\n');

        if (id.empty() || name.empty() || dif.empty()) continue;
        int tid = stoi(id);
        float difficulty = stof(dif);
        task.emplace_back(tid,name,difficulty);
    }
    in.close();
    return task;
}

vector<vector<float>> edge_class:: read_edges(float alpha, float beta){
    student_class obj1;
    task_class obj2;
    vector<student_class> students = obj1.read_students();
    vector<task_class> tasks = obj2.read_tasks();
    vector<vector<float>> final_cost(students.size(), vector<float>(tasks.size(),1000000));
    cost.resize(students.size(), vector<float>(tasks.size(),1e6));
    
    ifstream in("edges.csv");
    string line;
    getline(in, line); // skip header

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string ssid, stid, scost;

        getline(ss, ssid, ',');
        getline(ss, stid, ',');
        getline(ss, scost, '\n');

        if (ssid.empty() || stid.empty() || scost.empty()) continue;

        int sid = stoi(ssid) - 1;
        int tid = stoi(stid) - 1;
        float ost = stof(scost);

        cost[sid][tid] = ost;
        final_cost[sid][tid] = beta * ost + alpha * abs(students[sid].get_reliability() - tasks[tid].get_difficulty());
    }

    return final_cost;
}

vector<int> hungarian(float alpha = 0.5, float beta = 0.5) {
    edge_class obj;
    vector<vector<float>> costMatrix = obj.read_edges(alpha, beta);
    int numRows = costMatrix.size(), numCols = costMatrix[0].size();
    vector<float> rowPotential(numRows + 1), colPotential(numCols + 1);
    vector<int> columnMatch(numCols + 1), path(numCols + 1);

    for (int currentRow = 1; currentRow <= numRows; ++currentRow) {
        columnMatch[0] = currentRow;
        int currentCol = 0;
        vector<float> minReducedCost(numCols + 1, FLT_MAX);
        vector<bool> visited(numCols + 1, false);

        do {
            visited[currentCol] = true;
            int matchedRow = columnMatch[currentCol];
            float minDelta = FLT_MAX;
            int nextCol = 0;

            for (int candidateCol = 1; candidateCol <= numCols; ++candidateCol) {
                if (!visited[candidateCol]) {
                    float reducedCost = costMatrix[matchedRow - 1][candidateCol - 1]
                                      - rowPotential[matchedRow] - colPotential[candidateCol];
                    if (reducedCost < minReducedCost[candidateCol]) {
                        minReducedCost[candidateCol] = reducedCost;
                        path[candidateCol] = currentCol;
                    }
                    if (minReducedCost[candidateCol] < minDelta) {
                        minDelta = minReducedCost[candidateCol];
                        nextCol = candidateCol;
                    }
                }
            }

            for (int col = 0; col <= numCols; ++col) {
                if (visited[col]) {
                    rowPotential[columnMatch[col]] += minDelta;
                    colPotential[col] -= minDelta;
                } else {
                    minReducedCost[col] -= minDelta;
                }
            }
            currentCol = nextCol;
        } while (columnMatch[currentCol] != 0);

        do {
            int prevCol = path[currentCol];
            columnMatch[currentCol] = columnMatch[prevCol];
            currentCol = prevCol;
        } while (currentCol);
    }

    vector<int> assignment(numRows, -1);
    for (int col = 1; col <= numCols; ++col)
        if (columnMatch[col] > 0 && columnMatch[col] <= numRows)
            assignment[columnMatch[col] - 1] = col - 1;
    return assignment;
}

int main(){
    float weightage_reliability = 0.0;
    float weightage_cost = 0.0;
    student_class obj1;
    task_class obj2;
    edge_class obj3;
    
    cout << "what should be the weightage of reliability? (0 - 1) "<< endl;
    cout << "The point which will left after subtracting the reliability from 1 will be given to weightage of cost" << endl;
    cin >> weightage_reliability;
    weightage_cost = 1 - weightage_reliability;
    cout << "So, after subtracting the weightage of reliability, weightage_cost is :" << weightage_cost << endl;
    
    vector<int> assignment = hungarian(weightage_reliability, weightage_cost);

    vector<vector<float>> prize = obj3.read_edges(weightage_reliability, weightage_cost);
    vector<student_class> students = obj1.read_students();
    vector<task_class> tasks = obj2.read_tasks();


    cout << "Assignment:\n";
    for (int i = 0; i < assignment.size(); ++i) {
        if (assignment[i] != -1 && prize[i][assignment[i]] < 1000000) {
            cout << students[i].get_name() << " -> " << tasks[assignment[i]].get_name()
                 << " (cost: " << prize[i][assignment[i]] << ")\n";
        } else {
            cout << students[i].get_name() << " -> No task assigned\n";
        }
    }

    return 0;
}