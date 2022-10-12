#ifndef INTEGER_
#define INTEGER_

class Integer{

private:
    int val;


public:

    Integer() : val(42){}

    int getInt() const {return val;};
    Integer(int val) : val(val){}

    


};

inline  int sum(const Integer& a, const Integer& b){
    return (a.getInt()+b.getInt());
  }



#endif