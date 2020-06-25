/// @file  RBAIsOnMaker.hpp
/// @brief IsOnオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAISONMAKER_HPP
#define RBAISONMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsOnオブジェクト生成クラス
class RBAIsOnMaker : public RBAOperatorMaker
{
public:
  RBAIsOnMaker();
  RBAIsOnMaker(const RBAIsOnMaker&)=delete;
  RBAIsOnMaker(const RBAIsOnMaker&&)=delete;
  RBAIsOnMaker& operator=(const RBAIsOnMaker&)=delete;
  RBAIsOnMaker& operator=(const RBAIsOnMaker&&)=delete;
  virtual ~RBAIsOnMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif