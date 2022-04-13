#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <DirectXMath.h>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText* debugText = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	//テクスチャ
	uint32_t textureHandle = 0;

	//スプライト
	Sprite* sprite = nullptr;

	//3Dモデル
	Model* model = nullptr;


	//ワールドトランスフォーム
	WorldTransform worldTransform;
	//ビュープロジェクション
	ViewProjection viewProjection;

	//サウンドデータハンドル
	uint32_t soundDataHandle = 0;

	//音声再生ハンドル
	uint32_t voiceHandle = 0;

	//値を表示したい変数
	int32_t value = 0;

};
