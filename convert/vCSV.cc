#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "boost/algorithm/string.hpp"
#include "boost/property_tree/json_parser.hpp"

using namespace std;

string getValue(const string &json_str, const string &key) {
  try {
    stringstream ss(json_str);
    boost::property_tree::ptree json_root;
    boost::property_tree::read_json(ss, json_root);
    return json_root.get<string>(key);
  } catch (boost::exception &e) {
    cout << "Can't find key: " << key.c_str() << endl;
    return "";
  }
}

int main(int argc, char **argv) {
  string infilename = "./test.file";
  string outfilename = "./test.csv";
	if (argc > 2) {
		infilename = argv[1];
    outfilename = argv[2];
	} else {
    cout << "input vfile and output file are needed.";
  }
	ifstream fin(infilename.c_str());
	ofstream fout(outfilename.c_str());

  string id, content;
	string line;
  const string name = "name", age = "age", phone = "phone", weight = "weight";
  fout << ":ID,name:string,age:int,phone:string,weight:int" << endl;
	while(getline(fin, line)){
		stringstream ss(line);
    ss >> id >> content;
    fout << id << "," << getValue(content, name) << "," << getValue(content, age)
    << "," << getValue(content, phone) << "," << getValue(content, weight) << endl;
	}
}
