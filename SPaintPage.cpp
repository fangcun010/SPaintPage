//===============================================================================
//类名：SPaintPage(实现文件)
//作者：任杰
//===============================================================================
#include "SPaintPage.h"


SPaintPage::SPaintPage()
{
	m_hPen=NULL;
	m_hFont=NULL;
	m_hBrush=NULL;
}

SPaintPage::SPaintPage(int w,int h)
{
	HDC hDC;

	m_hPen=NULL;
	m_hFont=NULL;
	m_hBrush=NULL;

	m_nPgW=w;
	m_nPgH=h;
	hDC=::GetDC(NULL);
	m_hDC=CreateCompatibleDC(hDC);
	m_hBmp=CreateCompatibleBitmap(hDC,w,h);
	SelectObject(m_hDC,m_hBmp);

	ReleaseDC(NULL,hDC);
}

SPaintPage::~SPaintPage()
{
	if(m_hDC)
		DeleteDC(m_hDC);
	if(m_hBmp)
		DeleteObject(m_hBmp);
	if(m_hPen)
		DeleteObject(m_hPen);
	if(m_hFont)
		DeleteObject(m_hFont);
	if(m_hBrush)
		DeleteObject(m_hBrush);
}

void SPaintPage::SetPage(int w,int h)
{
	HDC hDC;

	m_nPgW=w;
	m_nPgH=h;
	hDC=::GetDC(NULL);
	m_hDC=CreateCompatibleDC(hDC);
	m_hBmp=CreateCompatibleBitmap(hDC,w,h);
	SelectObject(m_hDC,m_hBmp);

	ReleaseDC(NULL,hDC);
}

void SPaintPage::SetFont(const char *strFontName,int nSize,FontEffect fe,
							bool bItalic,bool bUnderline,bool bStrikeout)
{
	if(m_hFont)
		DeleteObject(m_hFont);

	if(fe==FE_THIN)
	{
		m_hFont=CreateFont(nSize,0,0,0,FW_THIN,
					bItalic,bUnderline,bStrikeout,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					strFontName);
	}
	else if(fe==FE_NORMAL)
	{
		m_hFont=CreateFont(nSize,0,0,0,FW_NORMAL,
					bItalic,bUnderline,bStrikeout,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					strFontName);
	}
	else if(fe==FE_BOLD)
	{
		m_hFont=CreateFont(nSize,0,0,0,FW_BOLD,
					bItalic,bUnderline,bStrikeout,
					DEFAULT_CHARSET,
					OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY,
					DEFAULT_PITCH|FF_DONTCARE,
					strFontName);
	}

	SelectObject(m_hDC,m_hFont);
}

void SPaintPage::SetTextColor(COLORREF cr)
{
	::SetTextColor(m_hDC,cr);
}

void SPaintPage::TextOut(int x,int y,const char *str)
{
	::TextOut(m_hDC,x,y,str,strlen(str));
}

void SPaintPage::CopyToDC(HDC hDC)
{
	BitBlt(hDC,0,0,m_nPgW,m_nPgH,m_hDC,0,0,SRCCOPY);
}

void SPaintPage::CopyToDC(HDC hDC,int nDestX,int nDestY,int nWidth,int nHeight,int nSrcX,int nSrcY)
{
	BitBlt(hDC,nDestX,nDestY,nWidth,nHeight,m_hDC,nSrcX,nSrcY,SRCCOPY);
}

void SPaintPage::CopyToDC(HDC hDC,int x,int y)
{
	BitBlt(hDC,x,y,m_nPgW,m_nPgH,m_hDC,0,0,SRCCOPY);
}

int SPaintPage::GetWidth()
{
	return m_nPgW;
}

int SPaintPage::GetHeight()
{
	return m_nPgH;
}

void SPaintPage::CopyPage(SPaintPage &Pg)
{
	BitBlt(m_hDC,0,0,Pg.GetWidth(),Pg.GetHeight(),Pg.GetDC(),0,0,SRCCOPY);
}

void SPaintPage::CopyPage(SPaintPage &Pg,int x,int y)
{
	BitBlt(m_hDC,x,y,Pg.GetWidth(),Pg.GetHeight(),Pg.GetDC(),0,0,SRCCOPY);
}

void SPaintPage::CopyPage(SPaintPage &Pg,int nDestX,int nDestY,int nWidth,int nHeight,int nSrcX,int nSrcY)
{
	BitBlt(m_hDC,nDestX,nDestY,nWidth,nHeight,Pg.GetDC(),nSrcX,nSrcY,SRCCOPY);
}

void SPaintPage::SetPixel(int x,int y,COLORREF cr)
{
	::SetPixel(m_hDC,x,y,cr);
}

COLORREF SPaintPage::GetPixel(int x,int y)
{
	return ::GetPixel(m_hDC,x,y);
}

void SPaintPage::SetBkColor(COLORREF cr)
{
	::SetBkColor(m_hDC,cr);
}

void SPaintPage::SetBkMode(int nMode)
{
	::SetBkMode(m_hDC,nMode);
}

void SPaintPage::FillRect(int x,int y,int w,int h,COLORREF cr)
{
	LOGBRUSH lBr;
	HBRUSH hBr;
	RECT rt;

	rt.left=x;
	rt.top=y;
	rt.bottom=rt.top+h;
	rt.right=rt.left+w;

	lBr.lbColor=cr;
	lBr.lbStyle=BS_SOLID;

	hBr=CreateBrushIndirect(&lBr);

	::FillRect(m_hDC,&rt,hBr);

	DeleteObject(hBr);
}

HDC SPaintPage::GetDC()
{
	return m_hDC;
}

void SPaintPage::SetPen(int nStyle,int nWidth,COLORREF cr)
{
	if(m_hPen)
		DeleteObject(m_hPen);

	m_hPen=CreatePen(nStyle,nWidth,cr);

	SelectObject(m_hDC,m_hPen);
}

void SPaintPage::SetBrush(unsigned int nStyle,COLORREF cr,long Hatch)
{
	LOGBRUSH lBr;

	lBr.lbStyle=nStyle;
	lBr.lbColor=cr;
	lBr.lbHatch=Hatch;

	if(m_hBrush)
		DeleteObject(m_hBrush);

	m_hBrush=CreateBrushIndirect(&lBr);

	SelectObject(m_hDC,m_hBrush);
}

void SPaintPage::MoveTo(int x,int y)
{
	::MoveToEx(m_hDC,x,y,NULL);
}

void SPaintPage::LineTo(int x,int y)
{
	::LineTo(m_hDC,x,y);
}

void SPaintPage::Rectangle(int x,int y,int w,int h)
{
	::Rectangle(m_hDC,x,y,x+w,y+h);
}

void SPaintPage::ShowPic(SBMP SBmp,int dx,int dy,int x,int y,int w,int h,COLORREF crTransparent,bool bTransparent)
{
	HDC htDC;
	HDC hDC;
	HBITMAP hOldBmp;

	htDC=::GetDC(NULL);
	hDC=CreateCompatibleDC(htDC);

	hOldBmp=(HBITMAP)SelectObject(hDC,SBmp.hBmp);

	if(bTransparent)
		TransparentBlt(m_hDC,dx,dy,w,h,hDC,x,y,w,h,crTransparent);
	else
		BitBlt(m_hDC,dx,dy,w,h,hDC,x,y,SRCCOPY);

	SelectObject(hDC,hOldBmp);
	DeleteDC(hDC);
	ReleaseDC(NULL,htDC);
}

SBMP LoadBmp(const char *strFileName)
{
	SBMP SBmp;

	FILE *fp;

	fp=fopen(strFileName,"rb");

	fseek(fp,18,SEEK_SET);

	fread(&SBmp.w,4,1,fp);
	fread(&SBmp.h,4,1,fp);

	fclose(fp);

	SBmp.hBmp=(HBITMAP)LoadImage(NULL,strFileName,IMAGE_BITMAP,SBmp.w,SBmp.h,LR_LOADFROMFILE);

	return SBmp;
}

void DeleteBmp(SBMP SBmp)
{
	DeleteObject(SBmp.hBmp);
}
