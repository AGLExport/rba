// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1051_affectedAlloReArb_Exists_Lhs.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1051_affectedAlloReArb_Exists_Lhs.hpp"

namespace {

using namespace rba;

HA1051_affectedAlloReArb_Exists_Lhs::HA1051_affectedAlloReArb_Exists_Lhs() {}
HA1051_affectedAlloReArb_Exists_Lhs::~HA1051_affectedAlloReArb_Exists_Lhs() {}

void HA1051_affectedAlloReArb_Exists_Lhs::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1051_affectedAlloReArb_Exists_Lhs::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1051_affectedAlloReArb_Exists_Lhs::getAllocated(const std::string& msg,
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

bool HA1051_affectedAlloReArb_Exists_Lhs::isCanceled(const std::string& msg,
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

bool HA1051_affectedAlloReArb_Exists_Lhs::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1051_affectedAlloReArb_Exists_Lhs::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isEnableContext(const std::string& msg,
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

bool HA1051_affectedAlloReArb_Exists_Lhs::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1051_affectedAlloReArb_Exists_Lhs::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA1051_affectedAlloReArb_Exists_Lhs, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0004  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0005  C,on,P1,NORMAL
  contexts.push_back(u8"P1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=5"));
  EXPECT_TRUE(isSatisfiedConstraints("line=5"));
  // 0006  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=6", u8"A"));
  // 0007  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=7", u8"C"));
  // 0008  Assert,A,P,P1
  EXPECT_EQ(u8"P1",getAllocated("line=8", u8"P"));
}

// 0010  #start 2
TEST_F(HA1051_affectedAlloReArb_Exists_Lhs, Test_02)
{
  std::list<std::string> contexts;

  // 0011  CL
  arb_->clearArbitration();
  // 0012  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0013  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0014  C,on,Q1,NORMAL
  contexts.push_back(u8"Q1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=14"));
  EXPECT_TRUE(isSatisfiedConstraints("line=14"));
  // 0015  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=15", u8"B"));
  // 0016  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=16", u8"C"));
  // 0017  Assert,A,Q,Q1
  EXPECT_EQ(u8"Q1",getAllocated("line=17", u8"Q"));
}

// 0019  #start 3
TEST_F(HA1051_affectedAlloReArb_Exists_Lhs, Test_03)
{
  std::list<std::string> contexts;

  // 0020  CL
  arb_->clearArbitration();
  // 0021  C,on,A1,NORMAL,continue
  contexts.push_back(u8"A1/NORMAL");
  // 0022  C,on,B1,NORMAL,continue
  contexts.push_back(u8"B1/NORMAL");
  // 0023  C,on,C1,NORMAL,continue
  contexts.push_back(u8"C1/NORMAL");
  // 0024  C,on,R1,NORMAL
  contexts.push_back(u8"R1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=24"));
  EXPECT_TRUE(isSatisfiedConstraints("line=24"));
  // 0025  Assert,A,A,
  EXPECT_EQ(u8"",getAllocated("line=25", u8"A"));
  // 0026  Assert,A,B,
  EXPECT_EQ(u8"",getAllocated("line=26", u8"B"));
  // 0027  Assert,A,C,C1
  EXPECT_EQ(u8"C1",getAllocated("line=27", u8"C"));
  // 0028  Assert,A,R,R1
  EXPECT_EQ(u8"R1",getAllocated("line=28", u8"R"));
}

}
