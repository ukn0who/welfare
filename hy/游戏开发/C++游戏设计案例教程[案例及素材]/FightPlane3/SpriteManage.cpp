/*********************************
	精灵管理程序文件SpriteManage.cpp
*********************************/

#include "SpriteManage.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*构造函数*/
SpriteManage::SpriteManage()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*析构函数*/
SpriteManage::~SpriteManage()
{
	Release();	//释放资源
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*添加精灵*/
BOOL SpriteManage::AddSprite(Sprite * pSprite,int nZorder)
{
	if (pSprite != NULL)			
	{
		pSprite->SetZOrder(nZorder);	//设置精灵的Z顺序
		if (!m_vSprites.empty())		//判断精灵管理对象是否为空
		{
			//如果精灵管理对象不为空，则按Z顺序将精灵插入到合适位置
			vector<Sprite *>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
				if (nZorder < (*siSprite)->GetZOrder())
				{
					m_vSprites.insert(siSprite, pSprite);
					return TRUE;
				}
		}		
//如果精灵管理对象为空或nZorder为最大的Z序号，则将精灵添加到精灵管理对象尾部
		m_vSprites.push_back(pSprite);
		return TRUE;

	  }
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*释放资源*/
void SpriteManage::Release(BOOL bDelSprite)
{
	if (!m_vSprites.empty())	//判断容器是否为空
	{
		if(bDelSprite)
		{
			vector<Sprite *>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
				delete *siSprite;	//删除精灵对象
		}
		m_vSprites.clear();			//删除容器中的精灵对象指针
		vector<Sprite *>(m_vSprites).swap(m_vSprites);	//压缩容器
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*删除指定的精灵*/
void SpriteManage::DelSprite(Sprite * pSprite,BOOL bDelSprite,BOOL bCompress)
{
	if (!m_vSprites.empty())	//判断容器是否为空
	{
		vector<Sprite*>::iterator siSprite;
		for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
			if((*siSprite)->GetID()==pSprite->GetID())	//循环查找指定的精灵
			{	
				if(bDelSprite)
					delete pSprite;				//删除精灵对象			
				m_vSprites.erase(siSprite);		//删除精灵指针
				break;
			}
		if(bCompress)
			vector<Sprite *>(m_vSprites).swap(m_vSprites);	//压缩容器
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*查找精灵*/
BOOL SpriteManage::FindSprite(Sprite * pSprite)
{
	if (!m_vSprites.empty())
	{
		vector<Sprite*>::iterator siSprite;
		for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
			if((*siSprite)->GetID()==pSprite->GetID())	//循环查找精灵
				return TRUE;
	}
	return FALSE;	
}            

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*设置精灵是否可见*/
void SpriteManage::SetSpriteVisible(Sprite * pSprite,BOOL bVisible)
{
	pSprite->SetVisible(bVisible);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*绘制精灵*/
void SpriteManage::Draw(HDC hDC)
{
	if (!m_vSprites.empty())
	{
	  vector<Sprite *>::iterator siSprite;
	  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
	  {
		(*siSprite)->DrawSprite(hDC);	//循环调用精灵对象绘图函数	
	  }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*设置精灵的Z顺序*/
void SpriteManage::SetZOrder(Sprite * pSprite,int nZorder)
{
	DelSprite(pSprite);			//删除精灵
	AddSprite(pSprite,nZorder);	//重新添加精灵
}