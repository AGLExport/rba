// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * IfStatement_Implies_rearbitration.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "IfStatement_Implies_rearbitration.hpp"
#include "TestCommon.hpp"

namespace {

using namespace rba;

IfStatement_Implies_rearbitration::IfStatement_Implies_rearbitration(void)
{
}

IfStatement_Implies_rearbitration::~IfStatement_Implies_rearbitration(void)
{
}

void IfStatement_Implies_rearbitration::SetUp(void)
{
  rba::RBAJsonParser parser;
  model = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model);
  arb = new rba::RBAArbitrator(model);
}

void IfStatement_Implies_rearbitration::TearDown(void)
{
  delete arb;
  delete model;
  arb = nullptr;
  model = nullptr;
}

TEST_F(IfStatement_Implies_rearbitration, Test_1) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"InterruptContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_2) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"InterruptContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_3) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"UserContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_4) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"InterruptContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_5) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"UserContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"UserContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_6) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"UserContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"InterruptContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_7) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"UserContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"UserContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }


}
TEST_F(IfStatement_Implies_rearbitration, Test_8) {
  std::vector<std::string> elems;
  std::unique_ptr<RBAResult> result;

  elems = {u8"C",u8"ON",u8"UserContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"LOW"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"UserContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"C",u8"ON",u8"InterruptContent",u8"HIGH"};
  {
    std::string kind = elems[1];
    std::string cont = elems[2];
    std::string state = elems[3];
    std::string unique_name = cont + "/" + state;
    result = arb->execute(unique_name.c_str(), true); // ON
    EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"execute"};
  {
    //result = arb->execute(nullptr, true); // empty
    //EXPECT_EQ(rba::RBAResultStatusType::SUCCESS, result->getStatusType());
  }

  elems = {u8"Assert",u8"A",u8"InterruptArea",u8"InterruptContent"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check visible
      EXPECT_TRUE(result->isVisible(area));
      if(result->isVisible(area) == false) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
      const rba::RBAViewContentState* state = result->getContentState(area);
      ASSERT_NE(nullptr, state);
      const rba::RBAViewContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check sounding
      EXPECT_TRUE(result->isSounding(zone));
      if(result->isSounding(zone) == false) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
      const rba::RBASoundContentState* state = result->getContentState(zone);
      ASSERT_NE(nullptr, state);
      const rba::RBASoundContent* content = state->getOwner();
      ASSERT_NE(nullptr, content);
      EXPECT_STREQ(expect.c_str(), content->getName().c_str());
    }
  }

  elems = {u8"Assert",u8"A",u8"UserArea",u8"NULL"};
  {
    std::string kind = elems[1];
    std::string target = elems[2];
    std::string expect = elems[3];
    // check area
    const rba::RBAArea* area = arb->getModel()->findArea(target);
    if(area) {
      // check invisible
      EXPECT_FALSE(result->isVisible(area));
      if(result->isVisible(area) == true) {
	std::cerr << "AREA: " << area->getName() << std::endl;
      }
    }
    else {
      // check zone
      const rba::RBAZone* zone = arb->getModel()->findZone(target);
      ASSERT_NE(nullptr, zone);
      // check invisible
      EXPECT_FALSE(result->isSounding(zone));
      if(result->isSounding(zone) == true) {
	std::cerr << "ZONE: " << zone->getName() << std::endl;
      }
    }
  }


}

}
