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








int Is_Able_To_Go(int x, int y, int muki) {//�i�ޕ������ʂ�邩�ʂ�Ȃ����𔻒�
 int color = GetColor(255, 255, 255);
    DrawFormatString(0, 36, color, "%d",x); // ������`�悷��

    if (muki == 1)//�������Ȃ�
        if (hantei[x / 32 - 1] == 1)//�ʂ�Ȃ��Ȃ�
            return 1;//�G���[
    if (muki == 0)//�E�����Ȃ�
        if (hantei[x / 32 + 1] == 1)//�ʂ�Ȃ��Ȃ�
            return 1;//�G���[


   

    return 0;//����
}





int player;
int back;


void Text() {

    int color = GetColor(255, 255, 255);

    DrawFormatString(225, 36, color, "���Ȃ��͎���"); // ������`�悷��


}


void Picture() {


    player = LoadGraph("player.png"); // �摜�̃��[�h
    back = LoadGraph("wall.png"); // �摜�̃��[�h



}




int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
    char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            Key[i]++;     // ���Z
        }
        else {              // ������Ă��Ȃ����
            Key[i] = 0;   // 0�ɂ���
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

        if (Key[KEY_INPUT_RIGHT] >= 1) x += 8;//�E�����Ȃ�ch.y���W�����炷

        if (Key[KEY_INPUT_LEFT] >= 1)  x -= 8; //�������Ȃ�ch.x���W�����炷

           
    }

}



void Draw() {




    for (int i = 0; i < 20; ++i) {
        if (hantei[i] == 1) {
            DrawGraph(i * 32, 128, back, TRUE); //�摜�̕`��

        }


    }







    // DrawGraph(0, 0, back, TRUE); //�摜�̕`��
    DrawGraph(x, 100 + y, player, TRUE); //�摜�̕`��
    Text();
    ScreenFlip(); //����ʂ�\��ʂɔ��f
}






// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ch_t ch;

    ch.jump_flag = 0;


    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ɐݒ�
    DxLib_Init(); // DX���C�u��������������



    SetDrawScreen(DX_SCREEN_BACK);





    Picture();
    while (1 && gpUpdateKey() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ProcessMessage() == 0) {

        Calc_Input();
        Draw();



    }


    DxLib_End(); // DX���C�u�����I������

    return 0;


}