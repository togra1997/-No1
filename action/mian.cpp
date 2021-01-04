#include "DxLib.h"
#include "math.h"

#define g 9.8067
#define y_max 2.000


int x = 50;
int y = 0;


int hantei[20] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1 };


typedef struct{
    int muki;
    int jump_flag;
}ch_t;








int Is_Able_To_Go(int x, int y, int muki) {//進む方向が通れるか通れないかを判定
 int color = GetColor(255, 255, 255);
    DrawFormatString(0, 36, color, "%d",x); // 文字を描画する

    if (muki == 1)//左向きなら
        if (hantei[x / 32 - 1] == 1)//通れないなら
            return 1;//エラー
    if (muki == 0)//右向きなら
        if (hantei[x / 32 + 1] == 1)//通れないなら
            return 1;//エラー


   

    return 0;//正常
}





int player;
int back;


void Text() {

    int color = GetColor(255, 255, 255);

    DrawFormatString(225, 36, color, "あなたは死ぬ"); // 文字を描画する


}


void Picture() {


    player = LoadGraph("player.png"); // 画像のロード
    back = LoadGraph("wall.png"); // 画像のロード



}




int Key[256]; // キーが押されているフレーム数を格納する

// キーの入力状態を更新する
int gpUpdateKey() {
    char tmpKey[256]; // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
            Key[i]++;     // 加算
        }
        else {              // 押されていなければ
            Key[i] = 0;   // 0にする
        }
    }
    return 0;
}


void Calc_Input() {
    ch_t ch;

    ch.muki = 0;
    if (Key[KEY_INPUT_RIGHT] >= 1) {
        ch.muki = 0;

    }

    if (Key[KEY_INPUT_LEFT] >= 1) {
        ch.muki = 1;

    }

    if (Key[KEY_INPUT_SPACE] == 1) {

        ch.jump_flag = 1;

    }

    
    if (Is_Able_To_Go(x, y, ch.muki) == 1) {

        if (Key[KEY_INPUT_RIGHT] >= 1) x += 8;//右向きならch.y座標を減らす

        if (Key[KEY_INPUT_LEFT] >= 1)  x -= 8; //左向きならch.x座標を減らす

           
    }

}



void Draw() {




    for (int i = 0; i < 20; ++i) {
        if (hantei[i] == 1) {
            DrawGraph(i * 32, 128, back, TRUE); //画像の描画

        }


    }







    // DrawGraph(0, 0, back, TRUE); //画像の描画
    DrawGraph(x, 100 + y, player, TRUE); //画像の描画
    Text();
    ScreenFlip(); //裏画面を表画面に反映
}






// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ch_t ch;

    ch.jump_flag = 0;


    ChangeWindowMode(TRUE); // ウィンドウモードに設定
    DxLib_Init(); // DXライブラリ初期化処理



    SetDrawScreen(DX_SCREEN_BACK);





    Picture();
    while (1 && gpUpdateKey() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0) {

        Calc_Input();
        Draw();



    }


    DxLib_End(); // DXライブラリ終了処理

    return 0;


}