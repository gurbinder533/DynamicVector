#include <iostream>
#include <cstdint>
#include "Vector_Project1c.h"

using namespace epl;
using namespace std;
 class Foo {
  public:
    bool alive;
    
    static uint64_t constructions;
    static uint64_t destructions;
    static uint64_t copies;
    static void reset(){ copies=destructions=constructions=0; }

    Foo(void) { alive = true; ++constructions; }
    ~Foo(void) { destructions += alive; }
    Foo(const Foo&) noexcept { alive = true; ++copies; }
    Foo(Foo&& that) noexcept { that.alive = false; this->alive = true; }
    Foo& operator=(const Foo& that) noexcept { alive=true; copies += 1; return *this; }
    //Foo& operator=(Foo&& that) noexcept { that.alive = false; this->alive = true; return *this; }
  };

  uint64_t Foo::constructions = 0;
  uint64_t Foo::destructions = 0;
  uint64_t Foo::copies = 0;


int main() 
{
    
    Vector<int> v(10);
    v.push_front(1);
    v.push_front(3);
    v.push_back(2);
    v.push_back(4);
    
    const char* prefix = "";
    for(int i = 0; i < v.size(); i++)
    {
	
	cout << prefix << v[i];
	prefix = ", ";
    }
	
    cout << endl;
    auto it = v.begin();
    auto it_e = v.end();
	prefix = "";
    for(; it != it_e; ++it){
    
	cout << prefix << *it;
	prefix = ", ";
    }
    
    ++it_e;
    cout << endl;

    return 0;


}
