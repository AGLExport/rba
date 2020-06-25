// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1051_affectedAlloReArb_BasicPattern_2on2.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1051_affectedAlloReArb_BasicPattern_2on2.hpp"


namespace {

using namespace rba;

HA1051_affectedAlloReArb_BasicPattern_2on2::HA1051_affectedAlloReArb_BasicPattern_2on2() {}
HA1051_affectedAlloReArb_BasicPattern_2on2::~HA1051_affectedAlloReArb_BasicPattern_2on2() {}

void HA1051_affectedAlloReArb_BasicPattern_2on2::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1051_affectedAlloReArb_BasicPattern_2on2::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1051_affectedAlloReArb_BasicPattern_2on2::getAllocated(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  std::string contentName;
  if(area) {
    if(result_->isVisible(area)) {
      const RBAViewContentState* allocState = result_->getContentState(area);
      if(allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  }
  else {
    const RBAZone* zone = model_->findZone(allocName);
    if(result_->isSounding(zone)) {
      const RBASoundContentState* allocState = result_->getContentState(zone);
      if(allocState) {
        contentName = allocState->getOwner()->getName();
      }
    }
  }
  return contentName;
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isCanceled(const std::string& msg,
                       const std::string& contentName)
{
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {
    // ビューの場合
    for(const RBAViewContentState* state : viewContent->getContentStates()) {
      if(result_->isCancel(state)) {
        return true;
      }
    }
  }
  else {
    // サウンドの場合
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    for(const RBASoundContentState* state : soundContent->getContentStates()) {
      if(result_->isCancel(state)) {
        return true;
      }
    }
  }

  return false;
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1051_affectedAlloReArb_BasicPattern_2on2::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isEnableContext(const std::string& msg,
                            const std::string& contextName)
{
  // コンテントチェック
  std::string contentName
     = RBAViewContentState::getContentNameByContext(contextName);
  const RBAViewContent* viewContent = model_->findViewContent(contentName);
  if(viewContent) {
    std::string stateName
      = RBAViewContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {
      return true;
    }
    const RBAViewContentState* state = model_->findViewContentState(contextName);
    return state != nullptr;
  }
  else {
    const RBASoundContent* soundContent = model_->findSoundContent(contentName);
    if(soundContent == nullptr) {
      return false;
    }
    std::string stateName
      = RBASoundContentState::getContentStateNameByContext(contextName);
    if(stateName.empty()) {
      return true;
    }
    const RBASoundContentState* state = model_->findSoundContentState(contextName);
    return state != nullptr;
  }
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1051_affectedAlloReArb_BasicPattern_2on2::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1051_affectedAlloReArb_BasicPattern_2on2, Test_01)
{
  std::list<std::string> contexts;
  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0004  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0005  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0006  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0007  C,on,P1,NORMAL
  contexts.push_back(u8"P1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=7"));
  EXPECT_TRUE(isSatisfiedConstraints("line=7"));
  // 0008  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"A"));
  // 0009  Assert,A,B,B1
  EXPECT_EQ(u8"B1",getAllocated("line=9", u8"B"));
  // 0010  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=10", u8"C"));
  // 0011  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=11", u8"D"));
  // 0012  Assert,A,P,P1
  EXPECT_EQ(u8"P1",getAllocated("line=12", u8"P"));
}

// 0014  #start 2
TEST_F(HA1051_affectedAlloReArb_BasicPattern_2on2, Test_02)
{
  std::list<std::string> contexts;
  // 0015  CL
  arb_->clearArbitration();
  // 0016  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0017  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0018  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0019  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0020  C,on,Q1,NORMAL
  contexts.push_back(u8"Q1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=20"));
  EXPECT_TRUE(isSatisfiedConstraints("line=20"));
  // 0021  Assert,A,A,A1
  EXPECT_EQ(u8"A1",getAllocated("line=21", u8"A"));
  // 0022  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=22", u8"B"));
  // 0023  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=23", u8"C"));
  // 0024  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=24", u8"D"));
  // 0025  Assert,A,Q,Q1
  EXPECT_EQ(u8"Q1",getAllocated("line=25", u8"Q"));
}

// 0027  #start 3
TEST_F(HA1051_affectedAlloReArb_BasicPattern_2on2, Test_03)
{
  std::list<std::string> contexts;
  // 0028  CL
  arb_->clearArbitration();
  // 0029  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0030  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0031  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0032  C,on,D1,NORMAL,continue
  contexts.push_back(u8"D1/NORMAL");
  // 0033  C,on,R1,NORMAL
  contexts.push_back(u8"R1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=33"));
  EXPECT_TRUE(isSatisfiedConstraints("line=33"));
  // 0034  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=34", u8"A"));
  // 0035  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=35", u8"B"));
  // 0036  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=36", u8"C"));
  // 0037  Assert,A,D,D1
  EXPECT_EQ(u8"D1",getAllocated("line=37", u8"D"));
  // 0038  Assert,A,R,R1
  EXPECT_EQ(u8"R1",getAllocated("line=38", u8"R"));
}

}