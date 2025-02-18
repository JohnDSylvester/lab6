#include "Person.h"

// Person Member Functions
std::set<Person*> betterAncestors(Person* p);
Person::Person(std::string n, std::string g, Person* m, Person* f){
	pname = n;
	pmother = m;
	pfather = f;
	if(g == "male"){
		pgender = Gender::MALE;
	}
	else if(g == "female"){
		pgender = Gender::FEMALE;
	}
	else{
		pgender = Gender::ANY;	
	}
}

void Person::addChild(Person* p){
	pchildren.insert(p);
}

const std::string& Person::name() const{
	return pname;
}
Gender Person::gender() const{
	return pgender;
}

Person* Person::mother(){
	return pmother;
}

Person* Person::father(){
	return pfather;
}

std::set<Person*> Person::parents(PMod pmod){
<<<<<<< HEAD
	std::set<Person*> par;
	if(pmod == PMod::MATERNAL){
		if(mother() != nullptr){
		par.insert(mother());
		}
	}
	else if(pmod == PMod::PATERNAL){
		if(father() != nullptr){
		par.insert(father());
		}
	}
	else{
		if(mother() != nullptr){
		par.insert(mother());
		}
		if(father() != nullptr){
		par.insert(father());
		}
	}
	return par;
=======
        std::set<Person*> par;
        if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                par.insert(mother());
                }
        }
        else if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                par.insert(father());
                }
        }
        else{
                if(mother() != nullptr){
                par.insert(mother());
                }
                if(father() != nullptr){
                par.insert(father());
                }
        }
        return par;
>>>>>>> d6d59ed251acc5e1ba357b07c22c315773a08ea0
}

std::set<Person*> Person::children(){
	return pchildren;
}
std::set<Person*> Person::grandparents(PMod pmod){
	std::set<Person*> gp;
	if(pmod == PMod::PATERNAL){
		 std::set<Person*> pp;
		 if(father() != nullptr){
		 pp = father()->parents(PMod::ANY);
		 }
		 gp = pp;
	}
	else if (pmod == PMod::MATERNAL){
		std::set<Person*> mp;
		if(mother() != nullptr){
		mp = mother()->parents(PMod::ANY);
		}
		gp = mp;
	}
	else{
		std::set<Person*> pp;
		if(father() != nullptr){
                pp = father()->parents(PMod::ANY);
		}
		std::set<Person*> mp;
                if(mother() != nullptr){
		mp = mother()->parents(PMod::ANY);
		}
		pp.merge(mp);
		gp = pp;
	}
	return gp;
}
std::set<Person*> Person::ancestors(PMod pmod){
	std::set<Person*> a;
	if(pmod == PMod::PATERNAL){
		if(father() != nullptr){
		a = betterAncestors(father());
		}
	}
	else if(pmod == PMod::MATERNAL){
		if(mother() != nullptr){
		 a = betterAncestors(mother());
		}
	}
	else{
		std::set<Person*> fa;
		std::set<Person*> ma;
		if(father() != nullptr){
			fa = betterAncestors(father());
		}
		if(mother() != nullptr){
			ma = betterAncestors(mother());
		}
		a.merge(fa);
		a.merge(ma);
	}
        return a;
}

std::set<Person*> betterAncestors(Person* p){
	std::set<Person*> an;
	if(p->father() == nullptr && p->mother() == nullptr){
	an.insert(p);
	}
	else if(p->father() == nullptr && p->mother() != nullptr){
		an.merge(betterAncestors(p->mother()));
		an.insert(p);
	}
	else if(p->father() != nullptr && p->mother() == nullptr){
		an.merge(betterAncestors(p->father()));
		an.insert(p);
	}
	else{
		an.merge(betterAncestors(p->mother()));
		an.merge(betterAncestors(p->father()));
		an.insert(p);
	}
	return an;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::daughters(){
	std::set<Person*> d;
        for(auto child: pchildren){
                if(child->gender() == Gender::FEMALE){
                d.insert(child);
                }
        }
        return d;
}
std::set<Person*> Person::descendants(){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::grandchildren(){
	std::set<Person*> gc;
	for(auto child: pchildren){
		gc.merge(child->children());
	}
	return gc;
}

std::set<Person*> Person::granddaughters(){
	std::set<Person*> gd;
        for(auto child: pchildren){
                gd.merge(child->daughters());
        }
        return gd;
}
std::set<Person*> Person::grandfathers(PMod pmod){
	std::set<Person*> gf;
        if(pmod == PMod::PATERNAL){
                 std::set<Person*> pp;
                 if(father() != nullptr){
                 pp = father()->parents(PMod::PATERNAL);
                 }
                 gf = pp;
        }
        else if (pmod == PMod::MATERNAL){
                std::set<Person*> mp;
                if(mother() != nullptr){
                mp = mother()->parents(PMod::PATERNAL);
                }
                gf = mp;
        }
        else{
                std::set<Person*> pp;
                if(father() != nullptr){
                pp = father()->parents(PMod::PATERNAL);
                }
                std::set<Person*> mp;
                if(mother() != nullptr){
                mp = mother()->parents(PMod::PATERNAL);
                }
                pp.merge(mp);
                gf = pp;
        }
        return gf;
}
std::set<Person*> Person::grandmothers(PMod pmod){
	std::set<Person*> gm;
        if(pmod == PMod::PATERNAL){
                 std::set<Person*> pp;
                 if(father() != nullptr){
                 pp = father()->parents(PMod::MATERNAL);
                 }
                 gm = pp;
        }
        else if (pmod == PMod::MATERNAL){
                std::set<Person*> mp;
                if(mother() != nullptr){
                mp = mother()->parents(PMod::MATERNAL);
                }
                gm = mp;
        }
        else{
                std::set<Person*> pp;
                if(father() != nullptr){
                pp = father()->parents(PMod::MATERNAL);
                }
                std::set<Person*> mp;
                if(mother() != nullptr){
                mp = mother()->parents(PMod::MATERNAL);
                }
                pp.merge(mp);
                gm = pp;
        }
        return gm;
}
std::set<Person*> Person::grandsons(){
	std::set<Person*> gs;
        for(auto child: pchildren){
                gs.merge(child->sons());
        }
        return gs;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;

}
std::set<Person*> Person::siblings(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
std::set<Person*> Person::sons(){
	std::set<Person*> s;
	for(auto child: pchildren){
		if(child->gender() == Gender::MALE){
		s.insert(child);
		}
	}	
        return s;
}
std::set<Person*> Person::uncles(PMod pmod, SMod smod){
	std::set<Person*> stub;
        return stub;
}
