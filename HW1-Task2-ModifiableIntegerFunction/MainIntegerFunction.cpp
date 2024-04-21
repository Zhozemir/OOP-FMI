#include "ModifiableIntegerFunction.h"

int16_t singleX(int16_t x) {
    return x;
}

int16_t singleY(int16_t y) {
    return y;
}


int16_t addPlus(int16_t x) {
    return x + 3;
}


int16_t square(int16_t x) {
    return x * x;
}

int16_t lin1(int16_t x) {
    return 4 * x + 3;
}

int16_t lin2(int16_t x) {
    return 4 * x + 3;
}




int main() {

    //ModifiableIntegerFunction func1(addPlus);
    //ModifiableIntegerFunction func2(square);

    //func1+=func2; // return 23 
    //std::cout<<func1(4)<<std::endl;
    //func1-=func2; // return -9 
    //std::cout<<func1(4)<<std::endl;

   // ModifiableIntegerFunction func3 = func1 + func2; // 33
    //modifiableIntegerFunction func3 = func1 - func2; // -17
    //std::cout<<func3(5)<<std::endl;

    //std::cout<<func1.isSurjective()<<std::endl; // true
    //std::cout<<func1.isInjective()<<std::endl; // true
    //std::cout<<func1.isBijective()<<std::endl; // true

    //func2.excludePoint(3);
    //std::cout<<func2.isSurjective()<<std::endl;// should return false
    //std::cout<<func2.isInjective()<<std::endl; //should return false
    //std::cout<<func2.isBijective()<<std::endl; //should return false

    //ModifiableIntegerFunction funckiq1(linear5);
    //ModifiableIntegerFunction funkciq2(linear8);

    //bool flag1 = funckiq1 || funkciq2;

    //std::cout<<flag1<<std::endl; // true


    //ModifiableIntegerFunction func5 = func1 * func2; 
    //std::cout<<func5(3)<<std::endl; //12
    //std::cout<<func5(2)<<std::endl; //7



    //ModifiableIntegerFunction func6(singleX); 
    //std::cout<<func6.isSurjective()<<std::endl; //true
    //std::cout<<func6.isInjective()<<std::endl; //true
    //std::cout<<func6.isBijective()<<std::endl; //true


   /* ModifiableIntegerFunction func1(lin1);
    func1.printPoints(0, 20, 0, 20);*/

}
