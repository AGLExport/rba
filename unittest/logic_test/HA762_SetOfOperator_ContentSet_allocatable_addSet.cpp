// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA762_SetOfOperator_ContentSet_allocatable_addSet.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA762_SetOfOperator_ContentSet_allocatable_addSet.hpp"

namespace {

using namespace rba;

HA762_SetOfOperator_ContentSet_allocatable_addSet::HA762_SetOfOperator_ContentSet_allocatable_addSet() {}
HA762_SetOfOperator_ContentSet_allocatable_addSet::~HA762_SetOfOperator_ContentSet_allocatable_addSet() {}

void HA762_SetOfOperator_ContentSet_allocatable_addSet::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA762_SetOfOperator_ContentSet_allocatable_addSet::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA762_SetOfOperator_ContentSet_allocatable_addSet::getAllocated(const std::string& msg,
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

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isCanceled(const std::string& msg,
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

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA762_SetOfOperator_ContentSet_allocatable_addSet::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isEnableContext(const std::string& msg,
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

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA762_SetOfOperator_ContentSet_allocatable_addSet::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1
TEST_F(HA762_SetOfOperator_ContentSet_allocatable_addSet, Test_01)
{
  std::list<std::string> contexts;

  // 0002  CL
  arb_->clearArbitration();
  // 0003  C,on,ContentC1,NORMAL
  result_ = arb_->execute(u8"ContentC1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=3"));
  EXPECT_TRUE(isSatisfiedConstraints("line=3"));
  // 0004  Assert,A,AllocatableA,
  EXPECT_EQ(u8"",getAllocated("line=4", u8"AllocatableA"));
  // 0005  Assert,A,AllocatableB,
  EXPECT_EQ(u8"",getAllocated("line=5", u8"AllocatableB"));
  // 0006  Assert,A,AllocatableC,ContentC1
  EXPECT_EQ(u8"ContentC1",getAllocated("line=6", u8"AllocatableC"));
  // 0007  Assert,A,AllocatableD,
  EXPECT_EQ(u8"",getAllocated("line=7", u8"AllocatableD"));
  // 0008  Assert,A,AllocatableE,
  EXPECT_EQ(u8"",getAllocated("line=8", u8"AllocatableE"));
  // 0009  C,on,ContentD1,NORMAL
  result_ = arb_->execute(u8"ContentD1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=9"));
  EXPECT_TRUE(isSatisfiedConstraints("line=9"));
  // 0010  Assert,A,AllocatableA,
  EXPECT_EQ(u8"",getAllocated("line=10", u8"AllocatableA"));
  // 0011  Assert,A,AllocatableB,
  EXPECT_EQ(u8"",getAllocated("line=11", u8"AllocatableB"));
  // 0012  Assert,A,AllocatableC,ContentC1
  EXPECT_EQ(u8"ContentC1",getAllocated("line=12", u8"AllocatableC"));
  // 0013  Assert,A,AllocatableD,
  EXPECT_EQ(u8"",getAllocated("line=13", u8"AllocatableD"));
  // 0014  Assert,A,AllocatableE,
  EXPECT_EQ(u8"",getAllocated("line=14", u8"AllocatableE"));
  // 0015  C,on,ContentA1,NORMAL
  result_ = arb_->execute(u8"ContentA1/NORMAL", true);
  EXPECT_TRUE(isSuccess("line=15"));
  EXPECT_TRUE(isSatisfiedConstraints("line=15"));
  // 0016  Assert,A,AllocatableA,ContentA1
  EXPECT_EQ(u8"ContentA1",getAllocated("line=16", u8"AllocatableA"));
  // 0017  Assert,A,AllocatableB,ContentA1
  EXPECT_EQ(u8"ContentA1",getAllocated("line=17", u8"AllocatableB"));
  // 0018  Assert,A,AllocatableC,
  EXPECT_EQ(u8"",getAllocated("line=18", u8"AllocatableC"));
  // 0019  Assert,A,AllocatableD,ContentD1
  EXPECT_EQ(u8"ContentD1",getAllocated("line=19", u8"AllocatableD"));
  // 0020  Assert,A,AllocatableE,ContentA1
  EXPECT_EQ(u8"ContentA1",getAllocated("line=20", u8"AllocatableE"));
}

}
