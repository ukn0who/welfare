/*********************************
	�����������ļ�SpriteManage.cpp
*********************************/

#include "SpriteManage.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*���캯��*/
SpriteManage::SpriteManage()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*��������*/
SpriteManage::~SpriteManage()
{
	Release();	//�ͷ���Դ
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*��Ӿ���*/
BOOL SpriteManage::AddSprite(Sprite * pSprite,int nZorder)
{
	if (pSprite != NULL)			
	{
		pSprite->SetZOrder(nZorder);	//���þ����Z˳��
		if (!m_vSprites.empty())		//�жϾ����������Ƿ�Ϊ��
		{
			//�������������Ϊ�գ���Z˳�򽫾�����뵽����λ��
			vector<Sprite *>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
				if (nZorder < (*siSprite)->GetZOrder())
				{
					m_vSprites.insert(siSprite, pSprite);
					return TRUE;
				}
		}		
//�������������Ϊ�ջ�nZorderΪ����Z��ţ��򽫾�����ӵ�����������β��
		m_vSprites.push_back(pSprite);
		return TRUE;

	  }
	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*�ͷ���Դ*/
void SpriteManage::Release(BOOL bDelSprite)
{
	if (!m_vSprites.empty())	//�ж������Ƿ�Ϊ��
	{
		if(bDelSprite)
		{
			vector<Sprite *>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
				delete *siSprite;	//ɾ���������
		}
		m_vSprites.clear();			//ɾ�������еľ������ָ��
		vector<Sprite *>(m_vSprites).swap(m_vSprites);	//ѹ������
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*ɾ��ָ���ľ���*/
void SpriteManage::DelSprite(Sprite * pSprite,BOOL bDelSprite,BOOL bCompress)
{
	if (!m_vSprites.empty())	//�ж������Ƿ�Ϊ��
	{
		vector<Sprite*>::iterator siSprite;
		for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
			if((*siSprite)->GetID()==pSprite->GetID())	//ѭ������ָ���ľ���
			{	
				if(bDelSprite)
					delete pSprite;				//ɾ���������			
				m_vSprites.erase(siSprite);		//ɾ������ָ��
				break;
			}
		if(bCompress)
			vector<Sprite *>(m_vSprites).swap(m_vSprites);	//ѹ������
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���Ҿ���*/
BOOL SpriteManage::FindSprite(Sprite * pSprite)
{
	if (!m_vSprites.empty())
	{
		vector<Sprite*>::iterator siSprite;
		for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
			if((*siSprite)->GetID()==pSprite->GetID())	//ѭ�����Ҿ���
				return TRUE;
	}
	return FALSE;	
}            

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���þ����Ƿ�ɼ�*/
void SpriteManage::SetSpriteVisible(Sprite * pSprite,BOOL bVisible)
{
	pSprite->SetVisible(bVisible);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���ƾ���*/
void SpriteManage::Draw(HDC hDC)
{
	if (!m_vSprites.empty())
	{
	  vector<Sprite *>::iterator siSprite;
	  for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); siSprite++)
	  {
		(*siSprite)->DrawSprite(hDC);	//ѭ�����þ�������ͼ����	
	  }
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*���þ����Z˳��*/
void SpriteManage::SetZOrder(Sprite * pSprite,int nZorder)
{
	DelSprite(pSprite);			//ɾ������
	AddSprite(pSprite,nZorder);	//������Ӿ���
}