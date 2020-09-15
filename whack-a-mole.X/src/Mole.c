#include "Mole.h"
#include "Input.h"
#include "Timer.h"
#include "Score.h"

void MoleManager(void){
    MoleXProcess(&mole1);
    MoleXProcess(&mole2);
    MoleXProcess(&mole3);
    MoleXProcess(&mole4);
}

void MoleXProcess(MoleType* i_moleX){
    switch(i_moleX->state){
        //���O�����o�����̏���
        case HOLE:
            //���O���o������
            if(i_moleX->popFlag){
                OutOfHole(&i_moleX);
                i_moleX->popFlag = 0; //(OFF)
            }
            //�y�i���e�B����
            else{
                SWState = 0x00;
                if(SWState && i_moleX->valueForCompareSW){
                    Penalty();
                }
                else{
                    //�������Ȃ�
                }
            }
            break;
        //���O���o�����̏���
        case MOLE:
            //���O�����ޏ���
            if(i_moleX->popTime){
                if(SWState && i_moleX->valueForCompareSW){
                    SWState = 0x00;
                    Attacked(&i_moleX);
                }
                else{
                    //�������Ȃ�
                }
            }
            //���O�����o��(���ɖ߂�)����
            else{
                BackToHole(&i_moleX);
            }
            break;
        //���O�����ގ�����
        case HIT:
            //���O�����o��(���ɖ߂�)����
            if(!i_moleX->popTime){
                BackToHole(&i_moleX);
            }
            else{
                //�������Ȃ�
            }
            break;
        default:
            break;  
    }
}

//���O���o������
void OutOfHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)MOLE;
    //SetpopTime() �o�����Ԑݒ�
    //WriteToBuffer
}

//���O�����ޏ���
void Attacked(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HIT;
    i_moleX->popTime = 30;
    IncScore();
    //WriteToBuffer
}

//���O�����o��(���ɖ߂�)����
void BackToHole(MoleType* i_moleX){
    i_moleX->state = (uint8_t)HOLE;
    //WriteToBuffer
}
