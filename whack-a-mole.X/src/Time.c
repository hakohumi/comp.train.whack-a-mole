#include "../header/Time.h"

void Penalty(void){
    //�c�莞��2�ȉ��̏���
    if(Time <= 2){
        //�c�莞�Ԃ�0�ɂ���
        Time = 0;
    }
    //�c�莞��60�ȉ��̏���
    else if(Time <= 60){
        //�c�莞�Ԃ�3��������
        Time -= 3;
    }
    else{
        //�������Ȃ�
    } 
}

void CountDown(void){
    //�c�莞�Ԃ�0�łȂ��Ƃ�
    if(Time){
        //�c�莞�Ԃ�1����������
        Time--;
    }
    else{
        //�������Ȃ�
    }
}