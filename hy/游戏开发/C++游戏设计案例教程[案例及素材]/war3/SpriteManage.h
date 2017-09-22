/*********************************
	�������ͷ�ļ�SpriteManage.h
*********************************/

#ifndef DEF_SpriteManage

#define DEF_SpriteManage

#include "Sprite.h"

#include <vector>		//����vector
using namespace std;	// ���ñ�׼ģ���std


class SpriteManage
{      
private:
	vector<Sprite*>     m_vSprites;		//vector���������洢����ָ��

public:

    SpriteManage();

    ~SpriteManage();
	
    BOOL AddSprite(Sprite * pSprite,int nZorder=0);		//��Ӿ���ָ��

    void Release(BOOL bDelSprite=FALSE);				//ɾ�����о��飬�ͷž�����Դ

    void DelSprite(Sprite * pSprite,BOOL bDelSprite=FALSE,BOOL bCompress=FALSE);	//ɾ��ָ���ľ���

	void SetSpriteVisible(Sprite * pSprite,BOOL bVisible);	//���þ����Ƿ�ɼ�

	BOOL FindSprite(Sprite * pSprite);  	//���Ҿ����Ƿ����    
		
	void Draw(HDC hDC);			//�������о���

	void SetZOrder(Sprite * pSprite,int nZorder);	//���þ����Z˳��
};

#endif