#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names, vector<int> &scores, vector<char> &grades){
    ifstream file(filename.c_str());
    string textline;
    
    while(getline(file, textline)){

        if (!textline.empty() && textline.back() == '\r') {
            textline.pop_back();
        }
        
        size_t pos = textline.find(':');
        if(pos != string::npos){
            string name = textline.substr(0, pos);
            name.erase(name.find_last_not_of(" \n\r\t") + 1);
            names.push_back(name);

            string scores_str = textline.substr(pos + 1);
            int a = 0, b = 0, c = 0;
            sscanf(scores_str.c_str(), "%d %d %d", &a, &b, &c);
            
            int total_score = a + b + c;
            scores.push_back(total_score);
            grades.push_back(score2grade(total_score));
        }
    }
    file.close();
}

void getCommand(string &command, string &key){

    cout << "Please input your command:\n"; 
    string line;
    getline(cin, line);
    
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    
    size_t pos = line.find_first_of(" \t");
    if(pos != string::npos){
        command = line.substr(0, pos);
        key = line.substr(pos + 1);
        
        size_t key_start = key.find_first_not_of(" \t");
        if(key_start != string::npos) {
            key = key.substr(key_start);
        } else {
            key = "";
        }
    } else {
        command = line;
        key = "";
    }
}

void searchName(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string> &names, const vector<int> &scores, const vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        string g = "";
        g += grades[i]; 
        if(g == key){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades;
    importDataFromFile(filename, names, scores, grades);

    do{
        string command, key;
        getCommand(command, key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);

    return 0;
}