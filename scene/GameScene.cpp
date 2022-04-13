#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene() {}

GameScene::~GameScene() { 
	delete sprite; 
	delete model;
}

void GameScene::Initialize() {

	dxCommon = DirectXCommon::GetInstance();
	input = Input::GetInstance();
	audio = Audio::GetInstance();
	debugText = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle = TextureManager::Load("testBox.png");

	//スプライトの生成
	sprite = Sprite::Create(textureHandle, {100, 50});

	//3Dモデルの生成
	model = Model::Create();


	//ワールドトランスフォームの初期化
	worldTransform.Initialize();
	//ビュープロジェクションの初期化
	viewProjection.Initialize();

	//サウンドデータ読み込み
	soundDataHandle = audio->LoadWave("mokugyo.wav");

	//音声再生
	//audio->PlayWave(soundDataHandle);

	voiceHandle = audio->PlayWave(soundDataHandle, true);

	// audio->SetVolume(音声データハンドル,ボリューム);
	audio->SetVolume(voiceHandle, 0.2f);

}

void GameScene::Update() { 
	
	XMFLOAT2 position = sprite->GetPosition();

	position.x += 5;
	position.y += 2;

	sprite->SetPosition(position);
	
	//音声
	if (input->TriggerKey(DIK_SPACE)) {
	
	//音声停止
		audio->StopWave(voiceHandle);
	}

	//デバッグ
	value++;
	debugText->Print("explosion", 50, 50, 1.0f);
	debugText->SetPos(50, 70);
	debugText->Printf("Value:%d", value);

	//value++;
	//std::string strDebug = std::string("Value:") + std::to_string(value);
	//debugText->Print(strDebug, 50, 50, 1.0f);
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	//回転:worldTransform、カメラ:viewProjection
	model->Draw(worldTransform, viewProjection, textureHandle);


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite->Draw();

	// デバッグテキストの描画
	debugText->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
