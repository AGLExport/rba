/// @file  RBASceneMaker.hpp
/// @brief Sceneオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBASCENEMAKER_HPP
#define RBASCENEMAKER_HPP

#include "RBARuleObjectMaker.hpp"

namespace rba
{

/// @brief Sceneオブジェクト生成クラス
class RBASceneMaker : public RBARuleObjectMaker
{
public:
  RBASceneMaker();
  RBASceneMaker(const RBASceneMaker&)=delete;
  RBASceneMaker(const RBASceneMaker&&)=delete;
  RBASceneMaker& operator=(const RBASceneMaker&)=delete;
  RBASceneMaker& operator=(const RBASceneMaker&&)=delete;
  virtual ~RBASceneMaker()=default;

protected:
  /// @brief 空のインスタンス生成
  /// @details 派生クラスでunique_ptrの空のインスタンスを生成する。
  /// @return インスタンスのunique_ptr
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief 派生クラスごとにモデルエレメントの属性をセットする
  /// @param[in] jsonElem ModelElementのJSONエレメント
  /// @param[in] model 生成したオブジェクトを保存するモデル
  /// @param[in,out] owner 親オブジェクト（未使用）
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
