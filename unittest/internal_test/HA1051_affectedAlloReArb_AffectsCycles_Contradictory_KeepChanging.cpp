// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging.cpp
 */

#include <vector>
#include <string>
#include "RBAJsonParser.hpp"
#include "TestCommon.hpp"
#include "HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging.hpp"

namespace {

using namespace rba;

HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging() {}
HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::~HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging() {}

void HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::SetUp()
{
  RBAJsonParser parser;
  model_ = parser.parse(GET_JSON_PATH(JSONFILE));
  ASSERT_NE(nullptr, model_);
  arb_ = new RBAArbitrator(model_);
}

void HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::TearDown()
{
  delete arb_;
  delete model_;
  arb_ = nullptr;
  model_ = nullptr;
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isSuccess(const std::string& msg)
{
  return RBAResultStatusType::SUCCESS == result_->getStatusType();
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isSatisfiedConstraints(const std::string& msg)
{
  return result_->satisfiesConstraints();
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isTrue(const std::string& msg, bool res)
{
  return res;
}

std::string HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::getAllocated(const std::string& msg,
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

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isCanceled(const std::string& msg,
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

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isActive(const std::string& msg, const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return false;
  }

  return result_->isActive(scene);
}

int32_t HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::getProperty(const std::string& msg,
                           const std::string& sceneName,
                           const std::string& propertyName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  if(scene == nullptr) {
    return -9999;
  }

  return result_->getSceneProperty(scene, propertyName);
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isEnableAllocatable(const std::string& msg,
                                const std::string& allocName)
{
  const RBAArea* area = model_->findArea(allocName);
  if(area) {
    return true;
  }
  const RBAZone* zone = model_->findZone(allocName);
  return zone != nullptr;
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isEnableContext(const std::string& msg,
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

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isEnableScene(const std::string& msg,
                          const std::string& sceneName)
{
  const RBAScene* scene = model_->findScene(sceneName);
  return scene != nullptr;
}

bool HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging::isAttenuated(const std::string& msg,
                         const std::string& zoneName)
{
  const RBAZone* zone = model_->findZone(zoneName);
  return result_->isAttenuated(zone);
}

// 0001  #start 1 無限ループにならないことを確認
TEST_F(HA1051_affectedAlloReArb_AffectsCycles_Contradictory_KeepChanging, Test_01)
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
  // 0006  C,on,D1,NORMAL
  contexts.push_back(u8"D1/NORMAL");
  result_ = arb_->execute(contexts, true);
  contexts.clear();
  EXPECT_TRUE(isSuccess("line=6"));
//  EXPECT_TRUE(isSatisfiedConstraints("line=6"));
}

}
