#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "boost/algorithm/string.hpp"
#include "boost/property_tree/json_parser.hpp"
#include<cstdlib>
#include<ctime>
#include <string>

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

int getRand() {
  return rand()%10;
}

string getPhone() {
  string str = "139";
  stringstream ss;
  for (int i = 0; i < 8; i++) {
    ss << getRand();
  }
  return str + ss.str();
}

string getMark() {
  string str = "";
  stringstream ss;
  for (int i = 0; i < 4; i++) {
    ss << getRand();
  }
  return str + ss.str();
}

int main(int argc, char **argv) {
  long vnum = 0;
  string efile = "./test.file";
  string outfilename = "./test";
	if (argc > 3) {
    vnum = atol(argv[1]);
    efile = argv[2];
    outfilename = argv[3];
	} else {
    cout << "input vfile and output file are needed.";
  }
  string out_vefile = outfilename + ".ve";
  string out_vfile = outfilename + "-js.v";
  string out_efile = outfilename + "-js.e";

  ifstream fe(efile.c_str());
	ofstream fout(out_vefile.c_str());
  ofstream foutv(out_vfile.c_str());
  ofstream foute(out_efile.c_str());

  long src, dst, weight;
  vector<string> phone;
  vector<long> v_weight;
  map<long, vector<long> > ids;
  map<long, vector<long> > weights;
  map<long, vector<string> > marks;

  srand(time(NULL));
  for (long i = 0; i < vnum; i++) {
    vector<long> tmp;
    ids[i] = tmp;
    vector<long> tmp2;
    weights[i] = tmp2;
    vector<string> tmp3;
    marks[i] = tmp3;
    phone.push_back(getPhone());
    v_weight.push_back(getRand());
  }

  string line;
  int total = 0;
  while(getline(fe, line)){
    stringstream vss(line);
    vss >> src >> dst >> weight;
    ids.at(src).push_back(dst);
    weights.at(src).push_back(weight);
    marks.at(src).push_back(getMark());
    if (++total % 100000 ==0) {
      cout << "input e " << total << endl;
    }
  }

  cout << "input done" << endl;
  cout << "start output" << endl;

  total = 0;
  for (long i = 0; i < vnum; i++) {
    foutv << i << "\t" << "{\"phone\":\"" << phone[i] <<
    "\",\"weight\":" << v_weight[i] << "}" << endl;
    if (++total % 10000 ==0) {
      cout << "output v " << total << endl;
    }
  }

  total = 0;
  for (long i = 0; i < vnum; i++) {
    int size = ids.at(i).size();
    int j = 0;
    for (; j < size; j++) {
      foute << i << "\t" << ids.at(i)[j] << "\t" << "{\"weight\":" << weights.at(i)[j] <<
      ",\"mark\":\"" << marks.at(i)[j] << "\"}" << endl;
      if (++total % 100000 ==0) {
        cout << "output e " << total << endl;
      }
    }
  }

  total = 0;
  for (long i = 0; i < vnum; i++) {
    fout << i << ":" << phone[i] << ":" << v_weight[i] << " ";
    int size = ids.at(i).size();
    int j = 0;
    for (; j < size - 1; j++) {
      fout << ids.at(i)[j] << ":" << weights.at(i)[j] << ":" << marks.at(i)[j] << ",";
    }
    if (size > 0) {
      fout << ids.at(i)[j] << ":" << weights.at(i)[j] << ":" << marks.at(i)[j] << endl;
    } else {
      fout << endl;
    }

    if (++total % 10000 ==0) {
      cout << "output ve " << total << endl;
    }
  }
}
