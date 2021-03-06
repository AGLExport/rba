/// @file  RBAAndOperatorMaker.cpp
/// @brief AndOperatorオブジェクト生成クラス定義ファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#include "RBAAndOperatorMaker.hpp"
#include "RBAAndOperator.hpp"

namespace rba
{

RBAAndOperatorMaker::RBAAndOperatorMaker()
  : RBAOperatorMaker{"AndOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAAndOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAndOperator>();
}

}
