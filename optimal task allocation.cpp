#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

class student_class{
    int id;
    string name;
    int reliability;
public:
    int get_reliability() {
        return reliability;
    }
    vector<student_class> read_students();

};

class task_class{
    int id;
    string name;
    int difficulty;
public:
    int get_difficulty(){
        return difficulty;
    } 
    vector<task_class> read_tasks();
};

class edge_class{
    int student_id;
    int cost;
    int task_id;
public:
    vector<vector<float>> read_edges(float , float );
};

vector<student_class> student_class:: read_students(){
    vector<student_class> students;
    ifstream in("students.csv");

    while(!in.eof()){
        string id, name, reliability;
        getline(in,id,',');
        getline(in,name,',');
        getline(in,reliability,'\n');
        int sid = stoi(id);
        int reliability = stoi(reliability);
        students.emplace_back(sid, name, reliability);
    }
    in.close();
    return students;
}

vector<task_class> task_class :: read_tasks(){
    vector<task_class> task;
    ifstream in("tasks.csv");

    while(!in.eof()){
        string id, name, difficulty;
        getline(in,id,',');
        getline(in,name,',');
        getline(in,difficulty,'\n');
        int tid = stoi(id);
        int difficulty = stoi(difficulty);
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
    vector<vector<float>> final_cost(students.size(), vector<float>(tasks.size(),1e6));
    
    ifstream in("edges.csv");
    while(!in.eof()){
        string ssid,stid,scost;
        getline(in,ssid,',');
        getline(in,stid,',');
        getline(in, scost, '\n');
        float sid = stof(ssid) - 1.0;
        float tid = stof(stid) - 1.0;
        float cost = stof(scost);
        final_cost[sid][tid] = beta * cost + alpha * abs(students[sid].get_reliability() - tasks[tid].get_difficulty());
    }
    return final_cost;
}



int main(){
    float weightage_reliability = 0;
    float weightage_cost = 0;

    cout << "what should be the weightage of reliability? (0 - 1) "<< endl;
    cout << "The point which will left after subtracting the reliability from 1 will be given to weightage of cost" << endl;
    cin >> weightage_reliability;
    weightage_cost = 1 - weightage_reliability;
    cout << "So, after subtracting the weightage of reliability, weightage_cost is :" << weightage_cost << endl;

    return 0;
}