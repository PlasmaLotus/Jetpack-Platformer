


#include <string>
#include <stdio.h>
#include <math.h>
//#include <tuple>
#include "gmock\gmock.h"
#include "gtest\gtest.h"
using ::testing::Return;
using ::testing::Eq;
//using ::testing::Ex

class BaseC{
public:
	
	BaseC(int ok=0): _lmao(ok){}
	virtual ~BaseC();
	int lmao();
protected:
	int _lmao;

};

class BaseI{
public:
	BaseI(){}
	virtual std::string doStuff()=0;
	virtual void changeLMAO() = 0;
};

class BB: public BaseC, BaseI{
public:
	BB(int ok=0): BaseC(ok){}
	virtual ~BB();
	virtual std::string doStuff(){return "LMAO";}
};


class MockBB: public BB{
public:
	MOCK_METHOD0(doStuff, std::string());
	MOCK_METHOD0(changeLMAO, void());
};

TEST(BBTest, DefaultStuff) {
  MockBB bb;                          // #2
  EXPECT_CALL(bb, changeLMAO())              // #3
      .WillOnce(Return());

            // #4

	bb.changeLMAO();
	//EXPECT_EQ(420, bb.lmao());
}      

int main(int argc, char** argv){
	//::testing::InitGoogleMock(&argc, argv);
	::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
