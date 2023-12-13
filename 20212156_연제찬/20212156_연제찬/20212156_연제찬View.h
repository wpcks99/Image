
// 20212156_연제찬View.h: CMy20212156연제찬View 클래스의 인터페이스
//

#pragma once


class CMy20212156연제찬View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMy20212156연제찬View() noexcept;
	DECLARE_DYNCREATE(CMy20212156연제찬View)

// 특성입니다.
public:
	CMy20212156연제찬Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy20212156연제찬View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	void Convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	void CopyResultToInput();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryZoomoutAvgFiltering();
	afx_msg void OnGeometryRotate();
//	afx_msg void OnGeometryHolizantialFlip();
//	afx_msg void OnGeometryHolizontialFlip();
	afx_msg void OnGeometryVerticalFlip();
	afx_msg void OnGeometryHolizontalFlip();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAviMode;
	CString AviFileName;
	void LoadAviFile(CDC* pDC);
	afx_msg void OnOpencv();
};

#ifndef _DEBUG  // 20212156_연제찬View.cpp의 디버그 버전
inline CMy20212156연제찬Doc* CMy20212156연제찬View::GetDocument() const
   { return reinterpret_cast<CMy20212156연제찬Doc*>(m_pDocument); }
#endif

