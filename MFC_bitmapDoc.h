
// MFC_bitmapDoc.h: CMFCbitmapDoc 클래스의 인터페이스
//


#pragma once

#include <vector>
using namespace std;

class CFigure {
public:

	Color m_FrameColor;

	int m_FrameTick;

	int type; // 0 이면 사각형 1이면 원

	CPoint m_imgStartPt;
	CPoint m_imgEndPt;

public:

	void Draw(Graphics& g) const {
		Pen pen(m_FrameColor, m_FrameTick);


		if (type == 0) {	//사각형
			g.DrawRectangle(&pen, m_imgStartPt.x, m_imgStartPt.y,
				m_imgEndPt.x - m_imgStartPt.x,
				m_imgEndPt.y - m_imgStartPt.y);
		}
		else {				//원
			g.DrawEllipse(&pen, m_imgStartPt.x, m_imgStartPt.y,
				m_imgEndPt.x - m_imgStartPt.x,
				m_imgEndPt.y - m_imgStartPt.y);
		}

	}

};

class CDrawImg {
public:

	Image *m_image;
	CPoint m_imgStartPt;
	CPoint m_imgEndPt;


public:
	void imgLoad(CString const m_ImgPath) {
		m_image = Image::FromFile(m_ImgPath);
	}


	void Draw(Graphics &g) const {


		g.DrawImage(m_image,
					m_imgStartPt.x, m_imgStartPt.y,
					m_imgEndPt.x - m_imgStartPt.x, m_imgEndPt.y - m_imgStartPt.y);

	}


};


class CMFCbitmapDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCbitmapDoc() noexcept;
	DECLARE_DYNCREATE(CMFCbitmapDoc)

// 특성입니다.
public:
	CString m_ImgPath;
	int m_penThick;
	Color m_penColor;

	int m_drawMode;
	int m_figureType;

	CDrawImg m_Img;
	vector<CDrawImg> m_Imgs;

	CFigure m_figure;
	vector<CFigure> m_figures;

	vector<int> m_sequence;


// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCbitmapDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnImageLoad();
	virtual void DeleteContents();
	afx_msg void OnRect();
	afx_msg void OnUpdateRect(CCmdUI* pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnColorGreen();
	afx_msg void OnColorBlue();
	afx_msg void OnCircle();
	afx_msg void OnThick1();
	afx_msg void OnThick2();
	afx_msg void OnThick3();
	afx_msg void OnImageRotate();
	afx_msg void OnImageRotate2();
	afx_msg void OnImageFlip();
};
