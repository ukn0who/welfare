================================================================================
    MICROSOFT ������⣺ DisplaySquareBezier ��Ŀ����
===============================================================================

Ӧ�ó�������Ϊ�������˴� DisplaySquareBezier Ӧ�ó��򡣴�Ӧ�ó���
����������ʹ�� Microsoft ������Ļ���֪ʶ��
�����Ǳ�дӦ�ó������㡣

���ļ�������� DisplaySquareBezier Ӧ�ó����ÿ���ļ�������ժҪ��

DisplaySquareBezier.vcproj
    ����ʹ�á�Ӧ�ó����򵼡����ɵ� VC++ ��Ŀ������Ŀ�ļ��� 
    �������й������ļ��� Visual C++ �汾����Ϣ���Լ�
    �й��á�Ӧ�ó����򵼡���ѡ���ƽ̨�����ú�
    ��Ŀ���ܵ���Ϣ��

DisplaySquareBezier.h
    ����Ӧ�ó������ͷ�ļ���  ����������
    ��Ŀ�ض���ͷ�ļ������� Resource.h����������
    CDisplaySquareBezierApp Ӧ�ó����ࡣ

DisplaySquareBezier.cpp
    ���ǰ���Ӧ�ó���
    �� CDisplaySquareBezierApp ����Ӧ�ó���Դ�ļ���

DisplaySquareBezier.rc
    ���ǳ���ʹ�õ����� Microsoft Windows ��Դ
    ���б�  �������洢�� RES ��Ŀ¼��
    ��ͼ�ꡢλͼ�͹�ꡣ  ��ֱ���� Microsoft 
    Visual C++ �б༭���ļ��� ��Ŀ��Դ������ 2052 �С�

res\DisplaySquareBezier.ico
    ����һ��ͼ���ļ�������Ӧ�ó����ͼ�ꡣ  ��
    ͼ�����������Դ�ļ� DisplaySquareBezier.rc �С�

res\DisplaySquareBezier.rc2
    ���ļ��������� Microsoft 
    Visual C++ �༭����Դ�� Ӧ�����в�����
    ��Դ�༭���༭����Դ���ڴ��ļ��С�
/////////////////////////////////////////////////////////////////////////////

��������ܴ��ڣ�
    ��Ŀ��������׼�� MFC ���档
MainFrm.h, MainFrm.cpp
    ��Щ�ļ���������� CMainFrame������������
    CFrameWnd ���������е� SDI ��ܹ��ܡ�
res\Toolbar.bmp
    ��λͼ�ļ����ڴ�����������ƽ��ͼ��
    ��ʼ��������״̬���� CMainFrame 
    ���й��졣 ʹ����Դ�༭���༭�˹�����λͼ����
    ���� DisplaySquareBezier.rc �е� IDR_MAINFRAME TOOLBAR ���������
    ��������ť��
/////////////////////////////////////////////////////////////////////////////

Ӧ�ó����򵼽�����һ���ĵ����ͺ�һ����ͼ��

DisplaySquareBezierDoc.h��DisplaySquareBezierDoc.cpp - �ĵ�
    ��Щ�ļ����� CDisplaySquareBezierDoc �ࡣ  �༭��Щ�ļ�
    �����������ĵ����ݲ�ʵ���ļ��ı���ͼ���
    ��ͨ�� CDisplaySquareBezierDoc::Serialize����
DisplaySquareBezierView.h��DisplaySquareBezierView.cpp - �ĵ���ͼ
    ��Щ�ļ����� CDisplaySquareBezierView �ࡣ
    CDisplaySquareBezierView �������ڲ鿴 CDisplaySquareBezierDoc ����
/////////////////////////////////////////////////////////////////////////////

�������ܣ�

ActiveX �ؼ�
    Ӧ�ó���֧��ʹ�� ActiveX �ؼ���

��ӡ֧�ֺʹ�ӡԤ��֧��
    Ӧ�ó�������������һЩ���룬ͨ���� MFC ����� CView ���еĳ�Ա������
    �����ӡ����ӡ���úʹ�ӡԤ�����
/////////////////////////////////////////////////////////////////////////////

������׼�ļ���

StdAfx.h��StdAfx.cpp
    ��Щ�ļ�����������Ϊ DisplaySquareBezier.pch ��Ԥ����ͷ�ļ� (PCH)
    ����Ϊ StdAfx.obj ��Ԥ���������ļ���

Resource.h
    ���Ǳ�׼ͷ�ļ�������������Դ ID��
    Microsoft Visual C++ ����ȡ�����´��ļ���

/////////////////////////////////////////////////////////////////////////////

����˵����

Ӧ�ó�����ʹ�á�TODO:�� ��ָʾ
Ӧ��ӻ��Զ����Դ���벿�֡�

���Ӧ�ó����ڹ��� DLL ��ʹ�� MFC����Ӧ�ó���ʹ�õ����Բ���
����ϵͳ�ĵ�ǰ���ԣ�����Ҫ�� Microsoft Visual C++ ������ 
Win\System Ŀ¼�½���Ӧ�ı��ػ���Դ MFC70XXX.DLL 
���Ƶ�������� system �� system32 Ŀ¼�£�
������������Ϊ MFCLOC.DLL��  ����XXX������
������д��  ���磬MFC70DEU.DLL ���������
�������Դ����  �������������Ӧ�ó����ĳЩ UI Ԫ��
������Ϊ����ϵͳ�����ԡ�

/////////////////////////////////////////////////////////////////////////////
