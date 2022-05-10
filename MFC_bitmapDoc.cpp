
// MFC_bitmapDoc.cpp: CMFCbitmapDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_bitmap.h"
#endif

#include "MFC_bitmapDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCbitmapDoc

IMPLEMENT_DYNCREATE(CMFCbitmapDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCbitmapDoc, CDocument)
	ON_COMMAND(IDM_IMAGE_LOAD, &CMFCbitmapDoc::OnImageLoad)
	ON_COMMAND(IDM_RECT, &CMFCbitmapDoc::OnRect)
	ON_UPDATE_COMMAND_UI(IDM_RECT, &CMFCbitmapDoc::OnUpdateRect)
	ON_COMMAND(IDM_COLOR_RED, &CMFCbitmapDoc::OnColorRed)
	ON_COMMAND(IDM_COLOR_GREEN, &CMFCbitmapDoc::OnColorGreen)
	ON_COMMAND(IDM_COLOR_BLUE, &CMFCbitmapDoc::OnColorBlue)
	ON_COMMAND(IDM_CIRCLE, &CMFCbitmapDoc::OnCircle)
	ON_COMMAND(IDM_THICK_1, &CMFCbitmapDoc::OnThick1)
	ON_COMMAND(IDM_THICK_2, &CMFCbitmapDoc::OnThick2)
	ON_COMMAND(IDM_THICK_3, &CMFCbitmapDoc::OnThick3)
	ON_COMMAND(IDM_IMAGE_ROTATE, &CMFCbitmapDoc::OnImageRotate)
	ON_COMMAND(IDM_IMAGE_ROTATE_2, &CMFCbitmapDoc::OnImageRotate2)
	ON_COMMAND(IDM_IMAGE_FLIP, &CMFCbitmapDoc::OnImageFlip)
	ON_COMMAND(IDM_LINE_DRAW, &CMFCbitmapDoc::OnLineDraw)
END_MESSAGE_MAP()


// CMFCbitmapDoc 생성/소멸

CMFCbitmapDoc::CMFCbitmapDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCbitmapDoc::~CMFCbitmapDoc()
{
}

BOOL CMFCbitmapDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	m_penColor = Color(255, 255, 0, 0);
	m_penThick = 10;
	m_figureType = 0;
	m_drawMode = 1;
	 
	
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCbitmapDoc serialization

void CMFCbitmapDoc::Serialize(CArchive& ar)
{
	int lines_size = m_lines.size();
	int array_size;



	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.


	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCbitmapDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCbitmapDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCbitmapDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCbitmapDoc 진단

#ifdef _DEBUG
void CMFCbitmapDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCbitmapDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCbitmapDoc 명령


void CMFCbitmapDoc::OnImageLoad()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawMode = 0;

	TCHAR szFilter[] = _T("Image(*.png, *.gif, *.jpg)|*.png;*.gif;*.jpg|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if (IDOK == dlg.DoModal()) {
		m_ImgPath = dlg.GetPathName();
		AfxMessageBox(m_ImgPath);
	}
}


void CMFCbitmapDoc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Imgs.clear();
	m_figures.clear();
	m_sequence.clear();
	m_line.clear();
	m_lines.clear();
	

	CDocument::DeleteContents();
}


void CMFCbitmapDoc::OnRect()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawMode = 1;
	m_figureType = 0;


}

void CMFCbitmapDoc::OnCircle()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawMode = 1;
	m_figureType = 1;

}


void CMFCbitmapDoc::OnUpdateRect(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}


void CMFCbitmapDoc::OnColorRed()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penColor = Color(255, 255, 0, 0);

}


void CMFCbitmapDoc::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penColor = Color(255, 0, 255, 0);

}


void CMFCbitmapDoc::OnColorBlue()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penColor = Color(255, 0, 0, 255);

}





void CMFCbitmapDoc::OnThick1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penThick = 3;
}


void CMFCbitmapDoc::OnThick2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penThick = 10;
}


void CMFCbitmapDoc::OnThick3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_penThick = 20;

}


void CMFCbitmapDoc::OnImageRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (CDrawImg& img : m_Imgs) {
		int tmp;

		tmp = img.m_imgEndPt.x - img.m_imgStartPt.x;
		img.m_imgEndPt.x = img.m_imgEndPt.y;
		img.m_imgEndPt.y = tmp;

		img.m_image->RotateFlip(Rotate90FlipNone);

	}
	UpdateAllViews(NULL);
}


void CMFCbitmapDoc::OnImageRotate2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (CDrawImg& img : m_Imgs) {

		int tmp;

		tmp = img.m_imgEndPt.x;
		img.m_imgEndPt.x = img.m_imgEndPt.y;
		img.m_imgEndPt.y = tmp;

		img.m_image->RotateFlip(Rotate270FlipNone);


	}
	UpdateAllViews(NULL);
}


void CMFCbitmapDoc::OnImageFlip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (CDrawImg& img : m_Imgs) {
		img.m_image->RotateFlip(RotateNoneFlipX);
	}
	UpdateAllViews(NULL);
}


void CMFCbitmapDoc::OnLineDraw()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_drawMode = 2;
}
