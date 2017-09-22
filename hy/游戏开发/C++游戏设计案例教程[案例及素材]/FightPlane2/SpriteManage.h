/*********************************
	精灵管理头文件SpriteManage.h
*********************************/

#ifndef DEF_SpriteManage

#define DEF_SpriteManage

#include "Sprite.h"

#include <vector>		//包含vector
using namespace std;	// 引用标准模板库std


class SpriteManage
{      
private:
	vector<Sprite*>     m_vSprites;		//vector对象，用来存储精灵指针

public:

    SpriteManage();

    ~SpriteManage();
	
    BOOL AddSprite(Sprite * pSprite,int nZorder=0);		//添加精灵指针

    void Release(BOOL bDelSprite=FALSE);				//删除所有精灵，释放精灵资源

    void DelSprite(Sprite * pSprite,BOOL bDelSprite=FALSE,BOOL bCompress=FALSE);	//删除指定的精灵

	void SetSpriteVisible(Sprite * pSprite,BOOL bVisible);	//设置精灵是否可见

	BOOL FindSprite(Sprite * pSprite);  	//查找精灵是否存在    
		
	void Draw(HDC hDC);			//绘制所有精灵

	void SetZOrder(Sprite * pSprite,int nZorder);	//设置精灵的Z顺序
};

#endif