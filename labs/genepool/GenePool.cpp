#include "GenePool.h"
#include <iostream>
#include <stdexcept>

// GenePool Member Functions
std::string section(std::string line, size_t& start){
	std::string data = "";
	while(line[start] != '\t' && start < line.size()){
			data += line[start];
		start++;
	}
	start++;
	return data;
} 

GenePool::GenePool(std::istream& stream){
	std::string line;
	std::string name;
	std::string gender;
	std::string mom;
	std::string dad;
	size_t iterator;
	while(getline(stream, line)){
		iterator = 0;
		if(line == "" || line[0] == '#'){
		continue;
		}
		else{
			name = section(line, iterator);
			gender = section(line, iterator);
			mom = section(line, iterator);
			dad = section(line, iterator);
			//std::cout << name << " " << gender << " " << mom << " " << dad << "\n";
			if(gender != "male" && gender != "female"){
				throw(std::invalid_argument("wrong gender"));
			}
			else if(name == "" || gender == "" || mom == "" || dad ==""){
				throw(std::invalid_argument("missing arguements"));
			}
			family[name] = new Person(name, gender, find(mom), find(dad));
		}
	}
	}

GenePool::~GenePool(){
	for(auto& [name, person] : family){
                delete person;
        }
}

Person* GenePool::find(const std::string& name) const{
	Person* result = nullptr;
	for(auto& [KnownName, person] : family){
		if(KnownName == name){
			return person;
		}
	}
	return result;
}

std::set<Person*> GenePool::everyone() const{
	std::set<Person*> all;
	for(auto& [name, person] : family){
               all.insert(person);
        }
	return all;
}
