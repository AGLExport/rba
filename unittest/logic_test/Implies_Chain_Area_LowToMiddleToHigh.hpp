// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.
/**
 * Implies_Chain_Area_LowToMiddleToHigh.hpp
 */

#ifndef IMPLIES_CHAIN_AREA_LOWTOMIDDLETOHIGH_HPP
#define IMPLIES_CHAIN_AREA_LOWTOMIDDLETOHIGH_HPP

#include <string>
#include "gtest/gtest.h"
#include "RBAArbitrator.hpp"

#define JSONFILE  "Implies_Chain_Area_LowToMiddleToHigh.json"

namespace {

class Implies_Chain_Area_LowToMiddleToHigh : public ::testing::Test {
protected:
  Implies_Chain_Area_LowToMiddleToHigh(void);
  virtual ~Implies_Chain_Area_LowToMiddleToHigh(void);

  virtual void SetUp(void);
  virtual void TearDown(void);

protected:
  rba::RBAModel* model=nullptr;
  rba::RBAArbitrator* arb=nullptr;
  std::string testName="";

};

}

#endif
