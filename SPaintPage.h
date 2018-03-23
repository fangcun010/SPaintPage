//===============================================================================
//类名：SPaintPage(声明文件)
//作者：方寸
//===============================================================================
#ifndef _S_PAINTPAGE_H_
#define _S_PAINTPAGE_H_

#include <stdio.h>
#include <windows.h>

struct SBMP
{
	HBITMAP hBmp;
	int w,h;
};

SBMP LoadBmp(const char *strFileName);
void DeleteBmp(SBMP SBmp);

class SPaintPage
{
//数据
private:
	int m_nPgW,m_nPgH;
public:
	HPEN m_hPen;
	HBRUSH m_hBrush;
	HFONT m_hFont;
	HBITMAP m_hBmp;//页面存储位图
	HDC m_hDC;//页面绘制DC
	enum FontEffect{FE_THIN,FE_NORMAL,FE_BOLD};//字体效果：瘦体，正常，粗体
//子程式
public:
	SPaintPage();//构造函数
	SPaintPage(int w,int h);
	~SPaintPage();
	//设置函数
	void SetPage(int w,int h);
	void SetPen(int nStyle,int nWidth,COLORREF cr);
	void SetBrush(unsigned int nStyle,COLORREF cr,long Hatch);
	void SetFont(const char *strFontName,int nSize,FontEffect fe,
					bool bItalic,bool bUnderline,bool bStrikeout);
	void SetTextColor(COLORREF cr);
	void SetBkColor(COLORREF cr);
	void SetBkMode(int nMode);
	//绘图函数
	void TextOut(int x,int y,const char *str);
	void SetPixel(int x,int y,COLORREF cr);
	void FillRect(int x,int y,int w,int h,COLORREF cr);
	void MoveTo(int x,int y);
	void LineTo(int x,int y);
	void Rectangle(int x,int y,int w,int h);
	void ShowPic(SBMP SBmp,int dx,int dy,int x,int y,int w,int h,COLORREF crTransparent,bool bTransparent);
	//复制函数
	void CopyToDC(HDC hDC);
	void CopyToDC(HDC hDC,int x,int y);
	void CopyToDC(HDC hDC,int nDestX,int nDestY,int nWidth,int nHeight,int nSrcX,int nSrcY);
	void CopyPage(SPaintPage &Pg);
	void CopyPage(SPaintPage &Pg,int x,int y);
	void CopyPage(SPaintPage &Pg,int nDestX,int nDestY,int nWidth,int nHeight,int nSrcX,int nSrcY);
	//获取函数
	HDC GetDC();
	int GetWidth();
	int GetHeight();
	COLORREF GetPixel(int x,int y);
};

#endif
