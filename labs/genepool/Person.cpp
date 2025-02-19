	#include "Person.h"

// Person Member Functions
std::set<Person*> betterAncestors(Person* p);
std::set<Person*> halfCheck(std::set<Person*> people, std::string name, Person* f, Person* m, SMod smod);
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
	std::set<Person*> ma;
        std::set<Person*> da;
        std::set<Person*> aunt;
        if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                da = father()->sisters(PMod::ANY,smod);
                }
        }
        else if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                ma = mother()->sisters(PMod::ANY,smod);
                }
        }
        else{
                if(father() != nullptr){
                da = father()->sisters(PMod::ANY,smod);
                }
                if(mother() != nullptr){
                ma = mother()->sisters(PMod::ANY,smod);
                }
        }
        aunt.merge(ma);
        aunt.merge(da);
        return aunt;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod){
        std::set<Person*> momKids;
        std::set<Person*> dadKids;
        std::set<Person*> son;
        if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                dadKids = father()->sons();
                }
        }
        else if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                momKids = mother()->sons();
                }
        }
        else{
                if(father() != nullptr){
                dadKids = father()->sons();
                }
                if(mother() != nullptr){
                momKids = mother()->sons();
                }
        }
        son.merge(dadKids);
        son.merge(momKids);
        son = halfCheck(son, name(), father(), mother(), smod);
        return son;
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
        std::set<Person*> d;
        for(auto child: pchildren){
                d.insert(child);
                d.merge(child->descendants());
        }
        return d;
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
        std::set<Person*> family;
        std::set<Person*> nephews;
        family = siblings(pmod,smod);
        for(auto sibling: family){
                nephews.merge(sibling->sons());
        }
        return nephews;
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
        std::set<Person*> family;
        std::set<Person*> nieces;
        family = siblings(pmod,smod);
        for(auto sibling: family){
                nieces.merge(sibling->daughters());
        }
        return nieces;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod){
        std::set<Person*> momKids;
        std::set<Person*> dadKids;
        std::set<Person*> sibs;
        if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                dadKids = father()->children();
                }
        }
        else if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                momKids = mother()->children();
                }
        }
        else{
                if(father() != nullptr){
                dadKids = father()->children();
                }
                if(mother() != nullptr){
                momKids = mother()->children();
                }
        }
        sibs.merge(dadKids);
        sibs.merge(momKids);
        sibs = halfCheck(sibs, name(), father(), mother(), smod);
        return sibs;
}

std::set<Person*> halfCheck(std::set<Person*> people, std::string name, Person* f, Person* m, SMod smod){
        std::set<Person*> newSiblings;
        if(smod == SMod::HALF){
        for(auto sibling: people){
                if(f != nullptr && f == sibling->father() && m != sibling->mother()){
                        newSiblings.insert(sibling);
                }
                if(m != nullptr && f != sibling->father() && m == sibling->mother()){
                        newSiblings.insert(sibling);
                }
        }
        }
        else if(smod == SMod::FULL){
        for(auto sibling: people){
                if(sibling->name() != name && f != nullptr && m != nullptr && f == sibling->father() && m == sibling->mother()){
                        newSiblings.insert(sibling);
                }
        }
        }
        else{
        for(auto sibling: people){
                if(sibling->name() != name){
                        newSiblings.insert(sibling);
                }
        }
        }
        return newSiblings;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod){
        std::set<Person*> momKids;
        std::set<Person*> dadKids;
        std::set<Person*> sis;
        if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                dadKids = father()->daughters();
                }
        }
        else if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                momKids = mother()->daughters();
                }
        }
        else{
                if(father() != nullptr){
                dadKids = father()->daughters();
                }
                if(mother() != nullptr){
                momKids = mother()->daughters();
                }
        }
        sis.merge(dadKids);
        sis.merge(momKids);
        sis = halfCheck(sis, name(), father(), mother(), smod);
        return sis;
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
	std::set<Person*> mb;
        std::set<Person*> db;
        std::set<Person*> unc;
        if(pmod == PMod::PATERNAL){
                if(father() != nullptr){
                db = father()->brothers(PMod::ANY,smod);
                }
        }
        else if(pmod == PMod::MATERNAL){
                if(mother() != nullptr){
                mb = mother()->brothers(PMod::ANY,smod);
                }
        }
        else{
                if(father() != nullptr){
                db = father()->brothers(PMod::ANY,smod);
                }
                if(mother() != nullptr){
                mb = mother()->brothers(PMod::ANY,smod);
                }
        }
        unc.merge(mb);
        unc.merge(db);
        return unc;
}
