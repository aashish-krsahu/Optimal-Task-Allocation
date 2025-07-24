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
        getline(in,reliability,',');
        int id = stoi(id);
        int reliability = stoi(reliability);
        students.emplace_back(id, name, reliability);
    }
    in.close();
    return students;
}

int main(){
    

    return 0;
}