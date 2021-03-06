/// @file  RBAMinOperatorMaker.hpp
/// @brief MinOperatorオブジェクト生成クラスヘッダファイル
///
/// Copyright (c) 2019 DENSO CORPORATION. All rights reserved.

#ifndef RBAMINOPERATORMAKER_HPP
#define RBAMINOPERATORMAKER_HPP

#include "RBALambdaContextMaker.hpp"

namespace rba
{

/// @brief MinOperatorオブジェクト生成クラス
class RBAMinOperatorMaker : public RBALambdaContextMaker
{
public:
  RBAMinOperatorMaker();
  RBAMinOperatorMaker(const RBAMinOperatorMaker&)=delete;
  RBAMinOperatorMaker(const RBAMinOperatorMaker&&)=delete;
  RBAMinOperatorMaker& operator=(const RBAMinOperatorMaker&)=delete;
  RBAMinOperatorMaker& operator=(const RBAMinOperatorMaker&&)=delete;
  virtual ~RBAMinOperatorMaker()=default;

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
                                       RBAModelElement* owner) override;

  /// @brief LambdaContextの空のオブジェクト生成
  /// @details unique_ptrの空のオブジェクトを生成する。
  /// @return LambdaContextオブジェクトのunique_ptr
  std::unique_ptr<RBALambdaContext> createLambdaContext() override;

};

}

#endif
