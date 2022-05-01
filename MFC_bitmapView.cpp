
// MFC_bitmapView.cpp: CMFCbitmapView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFC_bitmap.h"
#endif

#include "MFC_bitmapDoc.h"
#include "MFC_bitmapView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCbitmapView

IMPLEMENT_DYNCREATE(CMFCbitmapView, CView)

BEGIN_MESSAGE_MAP(CMFCbitmapView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CMFCbitmapView 생성/소멸

CMFCbitmapView::CMFCbitmapView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCbitmapView::~CMFCbitmapView()
{
}

BOOL CMFCbitmapView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCbitmapView 그리기

void CMFCbitmapView::OnDraw(CDC* pDC)
{
	CMFCbitmapDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	Graphics g(pDC->m_hDC);
	Image image(pDoc->m_ImgPath);


	g.DrawImage(&image, pDoc->m_imgStartPt.x, pDoc->m_imgStartPt.y,
		pDoc->m_imgEndPt.x-pDoc->m_imgStartPt.x, pDoc->m_imgEndPt.y- pDoc->m_imgStartPt.y);


	//image.RotateFlip(Rotate90FlipNone);


	


}


// CMFCbitmapView 인쇄

BOOL CMFCbitmapView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCbitmapView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCbitmapView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCbitmapView 진단

#ifdef _DEBUG
void CMFCbitmapView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCbitmapView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCbitmapDoc* CMFCbitmapView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCbitmapDoc)));
	return (CMFCbitmapDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCbitmapView 메시지 처리기


void CMFCbitmapView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMFCbitmapDoc* pDoc = GetDocument();
	SetCapture();

	pDoc->m_imgStartPt = point;

	CView::OnLButtonDown(nFlags, point);
}


void CMFCbitmapView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CMFCbitmapDoc* pDoc = GetDocument();
	ReleaseCapture();

	//pDoc->SetModifiedFlag();


	pDoc->m_imgEndPt = point;

	Invalidate(FALSE);


	CView::OnLButtonUp(nFlags, point);
}
