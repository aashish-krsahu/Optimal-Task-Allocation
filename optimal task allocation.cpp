#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
using namespace std;

class student_class{
    int id;
    string name;
    int reliability;
public:
    vector<student_class> read_students();

};

class task_class{
    int id;
    string name;
    int difficulty;
public:
    vector<task_class> read_tasks();
};

class edge_class{
    int student_id;
    int cost;
    int task_id;
};

vector<student_class> student_class:: read_students(){
    vector<student_class> students;
    ifstream in("students.csv");

    while(!in.eof()){
        string id, name, reliability;
        getline(in,id,',');
        getline(in,name,',');
        getline(in,reliability,'\n');
        int id = stoi(id);
        int reliability = stoi(reliability);
        students.emplace_back(id, name, reliability);
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
        int id = stoi(id);
        int difficulty = stoi(difficulty);
        task.emplace_back(id,name,difficulty);
    }
    in.close();
    return task;
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