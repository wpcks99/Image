
// 20212156_연제찬View.cpp: CMy20212156연제찬View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20212156_연제찬.h"
#endif

#include "20212156_연제찬Doc.h"
#include "20212156_연제찬View.h"
#include"COpenCVDlg.h"

#include <vfw.h>    

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy20212156연제찬View

IMPLEMENT_DYNCREATE(CMy20212156연제찬View, CScrollView)

BEGIN_MESSAGE_MAP(CMy20212156연제찬View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMy20212156연제찬View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CMy20212156연제찬View::OnPixelAdd)
	ON_COMMAND(ID_PIXEL_SUB, &CMy20212156연제찬View::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CMy20212156연제찬View::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CMy20212156연제찬View::OnPixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CMy20212156연제찬View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRETCHING, &CMy20212156연제찬View::OnPixelContrastStretching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CMy20212156연제찬View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CMy20212156연제찬View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CMy20212156연제찬View::OnPixelTwoImageSub)
	ON_COMMAND(ID_REGION_SMOOTHING, &CMy20212156연제찬View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_SHARPENING, &CMy20212156연제찬View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_EMBOSSING, &CMy20212156연제찬View::OnRegionEmbossing)
	ON_COMMAND(ID_REGION_PREWITT, &CMy20212156연제찬View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_ROBERTS, &CMy20212156연제찬View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CMy20212156연제찬View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CMy20212156연제찬View::OnRegionAverageFiltering)
	ON_COMMAND(ID_REGION_MEDIAN_FILTERING, &CMy20212156연제찬View::OnRegionMedianFiltering)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CMy20212156연제찬View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CMy20212156연제찬View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CMy20212156연제찬View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CMy20212156연제찬View::OnMopologyDilation)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CMy20212156연제찬View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CMy20212156연제찬View::OnMopologyClosing)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CMy20212156연제찬View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CMy20212156연제찬View::OnGeometryZoominBilinearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CMy20212156연제찬View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CMy20212156연제찬View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_AVG_FILTERING, &CMy20212156연제찬View::OnGeometryZoomoutAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATE, &CMy20212156연제찬View::OnGeometryRotate)
	ON_COMMAND(ID_GEOMETRY_VERTICAL_FLIP, &CMy20212156연제찬View::OnGeometryVerticalFlip)
	ON_COMMAND(ID_GEOMETRY_HOLIZONTAL_FLIP, &CMy20212156연제찬View::OnGeometryHolizontalFlip)
	ON_COMMAND(ID_GEOMETRY_WARPING, &CMy20212156연제찬View::OnGeometryWarping)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_AVI_VIEW, &CMy20212156연제찬View::OnAviView)
	ON_COMMAND(ID_OPENCV, &CMy20212156연제찬View::OnOpencv)
END_MESSAGE_MAP()

// CMy20212156연제찬View 생성/소멸

CMy20212156연제찬View::CMy20212156연제찬View() noexcept
{
	bAviMode = false;

}

CMy20212156연제찬View::~CMy20212156연제찬View()
{
}

BOOL CMy20212156연제찬View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMy20212156연제찬View 그리기

void CMy20212156연제찬View::OnDraw(CDC* pDC)
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (bAviMode) {
		LoadAviFile(pDC);
		bAviMode = false;
		return;
	}
	int x, y;
	if (pDoc->Inputimg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth;x++) {
					pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][x], pDoc->Inputimg[y][x], pDoc->Inputimg[y][x]));
				}
		}
		else {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth;x++) {
					pDC->SetPixel(x, y, RGB(pDoc->Inputimg[y][3 * x + 0], pDoc->Inputimg[y][3 * x + 1], pDoc->Inputimg[y][3 * x + 2]));
				}
		}
	}

	if (pDoc->Resultimg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth;x++) {
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->Resultimg[y][x], pDoc->Resultimg[y][x], pDoc->Resultimg[y][x]));
				}
		}
		else {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth;x++) {
					pDC->SetPixel(pDoc->ImageWidth + 20 + x, y, RGB(pDoc->Resultimg[y][3 * x + 0], pDoc->Resultimg[y][3 * x + 1], pDoc->Resultimg[y][3 * x + 2]));
				}
		}
	}

	if (pDoc->InputImg2 != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImg2[y][x], pDoc->InputImg2[y][x], pDoc->InputImg2[y][x]));
				}
		}
		else {
			for (y = 0;y < pDoc->ImageHeight; y++)
				for (x = 0;x < pDoc->ImageWidth;x++) {
					pDC->SetPixel(2 * (pDoc->ImageWidth + 20) + x, y, RGB(pDoc->InputImg2[y][3 * x + 0], pDoc->InputImg2[y][3 * x + 1], pDoc->InputImg2[y][3 * x + 2]));
				}
		}
	}

	if (pDoc->gResultImg != NULL)
	{
		if (pDoc->depth == 1)
		{
			for (y = 0;y < pDoc->gImageHeight;y++)
				for (x = 0;x < pDoc->gImageWidth;x++)
				{
					pDC->SetPixel(x, y + pDoc->ImageHeight + 20, RGB(pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x], pDoc->gResultImg[y][x]));
				}
		}
		else
		{
			for (y = 0;y < pDoc->gImageHeight;y++)
				for (x = 0;x < pDoc->gImageWidth;x++)
				{
					pDC->SetPixel(x, y + pDoc->ImageHeight + 20, RGB(pDoc->gResultImg[y][3 * x + 0],
						pDoc->gResultImg[y][3 * x + 1], pDoc->gResultImg[y][3 * x + 2]));
				}
		}
	}
}

void CMy20212156연제찬View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 2048; // 수정된 코드
	sizeTotal.cy = 1024; // 수정된 코드
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMy20212156연제찬View 인쇄


void CMy20212156연제찬View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMy20212156연제찬View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy20212156연제찬View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy20212156연제찬View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy20212156연제찬View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMy20212156연제찬View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMy20212156연제찬View 진단

#ifdef _DEBUG
void CMy20212156연제찬View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMy20212156연제찬View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMy20212156연제찬Doc* CMy20212156연제찬View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy20212156연제찬Doc)));
	return (CMy20212156연제찬Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy20212156연제찬View 메시지 처리기


void CMy20212156연제찬View::OnPixelAdd()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				value = pDoc->Inputimg[y][x] + 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else {
				value = pDoc->Inputimg[y][3 * x + 0] + 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] + 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] + 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnPixelSub()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				value = pDoc->Inputimg[y][x] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else {
				value = pDoc->Inputimg[y][3 * x + 0] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] - 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] + 50;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnPixelMul()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				value = pDoc->Inputimg[y][x] * 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else {
				value = pDoc->Inputimg[y][3 * x + 0] * 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] * 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] * 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnPixelDiv()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	if (pDoc->Inputimg == NULL) return;
	int x, y, value;
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				value = pDoc->Inputimg[y][x] / 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else {
				value = pDoc->Inputimg[y][3 * x + 0] / 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = pDoc->Inputimg[y][3 * x + 1] / 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = pDoc->Inputimg[y][3 * x + 2] / 1.5;
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnPixelHistoEq()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int hist[256], sum[256];
	int histR[256], histG[256], histB[256], sumR[256], sumG[256], sumB[256];
	int SUMR = 0;
	int SUMG = 0;
	int SUMB = 0;
	int x, y, i, k;
	int acc_hist;
	int N = pDoc->ImageWidth * pDoc->ImageHeight;

	if (pDoc->depth == 1) {
		for (i = 0, i < 256;i++;) hist[i] = 0;
		//히스토그램 구하기

		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				k = pDoc->Inputimg[y][x];
				hist[k]++;
			}
		//누적분포 구하기
		acc_hist = 0;
		for (i = 0; i < 256;i++)
		{
			acc_hist += hist[i];
			sum[i] = acc_hist;
		}

		//평활화 화소값저장
		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				k = pDoc->Inputimg[y][x];
				pDoc->Resultimg[y][x] = (float)sum[k] / N * 255;
			}
	}
	else {
		// 히스토그램 초기화
		for (i = 0; i < 256; i++) {
			histR[i] = 0;
			histG[i] = 0;
			histB[i] = 0;
		}

		// 히스토그램 구하기
		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++) {
				k = pDoc->Inputimg[y][3 * x + 0];
				histR[k]++;
				k = pDoc->Inputimg[y][3 * x + 1];
				histG[k]++;
				k = pDoc->Inputimg[y][3 * x + 2];
				histB[k]++;
			}

		// 누적 분포 구하기
		for (i = 0; i < 256; i++) {
			SUMR += histR[i];
			sumR[i] = SUMR;

			SUMG += histG[i];
			sumG[i] = SUMG;

			SUMB += histB[i];
			sumB[i] = SUMB;
		}

		// 평활화 화소값 저장
		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++) {
				k = pDoc->Inputimg[y][3 * x + 0];
				pDoc->Resultimg[y][3 * x + 0] = (float)sumR[k] / N * 255;
				k = pDoc->Inputimg[y][3 * x + 1];
				pDoc->Resultimg[y][3 * x + 1] = (float)sumG[k] / N * 255;
				k = pDoc->Inputimg[y][3 * x + 2];
				pDoc->Resultimg[y][3 * x + 2] = (float)sumB[k] / N * 255;
			}
	}

	Invalidate();
}


void CMy20212156연제찬View::OnPixelContrastStretching()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	if (pDoc->depth == 1) {
		int lowR = pDoc->Inputimg[0][0], highR = pDoc->Inputimg[0][0];
		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				if (pDoc->Inputimg[y][x] < lowR)
					lowR = pDoc->Inputimg[y][x];
				if (pDoc->Inputimg[y][x] > highR)
					highR = pDoc->Inputimg[y][x];
			}
		}

		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				pDoc->Resultimg[y][x] = (double)(pDoc->Inputimg[y][x] - lowR) / (highR - lowR) * 255.0;
			}
		}
	}
	else {
		int LOW = 0;
		int HIGH = 255;
		// 최소값 초기화
		unsigned char minR = (unsigned char)HIGH;
		unsigned char minG = (unsigned char)HIGH;
		unsigned char minB = (unsigned char)HIGH;
		// 최대값 초기화
		unsigned char maxR = (unsigned char)LOW;
		unsigned char maxG = (unsigned char)LOW;
		unsigned char maxB = (unsigned char)LOW;

		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				if (pDoc->Inputimg[y][3 * x + 0] < minR)
					minR = pDoc->Inputimg[y][3 * x + 0];
				if (pDoc->Inputimg[y][3 * x + 0] > maxR)
					maxR = pDoc->Inputimg[y][3 * x + 0];
			}
		}

		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				if (pDoc->Inputimg[y][3 * x + 1] < minG)
					minG = pDoc->Inputimg[y][3 * x + 1];
				if (pDoc->Inputimg[y][3 * x + 1] > maxG)
					maxG = pDoc->Inputimg[y][3 * x + 1];
			}
		}

		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				if (pDoc->Inputimg[y][3 * x + 2] < minB)
					minB = pDoc->Inputimg[y][3 * x + 2];
				if (pDoc->Inputimg[y][3 * x + 2] > maxB)
					maxB = pDoc->Inputimg[y][3 * x + 2];
			}
		}

		for (int y = 0; y < pDoc->ImageHeight; y++) {
			for (int x = 0; x < pDoc->ImageWidth; x++) {
				pDoc->Resultimg[y][3*x+0] = (double)(pDoc->Inputimg[y][3 * x + 0] - minR) / (maxR - minR) * 255.0;
				pDoc->Resultimg[y][3 * x + 1] = (double)(pDoc->Inputimg[y][3 * x + 1] - minG) / (maxG - minG) * 255.0;
				pDoc->Resultimg[y][3 * x + 2] = (double)(pDoc->Inputimg[y][3 * x + 2] - minB) / (maxB - minB) * 255.0;

			}
		}
	}
	

	Invalidate();
}


void CMy20212156연제찬View::OnPixelBinarization()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, value;
	int threshold = 128;
	if (pDoc->depth == 1) {
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			value = pDoc->Inputimg[y][x];
			if (value >= threshold) pDoc->Resultimg[y][x] = 255;
			else  pDoc->Resultimg[y][x] = 0;
		}
	}
	else {
		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				value = pDoc->Inputimg[y][3*x+0];
				if (value >= threshold) pDoc->Resultimg[y][3 * x + 0] = 255;
				else  pDoc->Resultimg[y][3 * x + 0] = 0;

				value = pDoc->Inputimg[y][3 * x + 1];
				if (value >= threshold) pDoc->Resultimg[y][3 * x + 1] = 255;
				else  pDoc->Resultimg[y][3 * x + 1] = 0;

				value = pDoc->Inputimg[y][3 * x + 2];
				if (value >= threshold) pDoc->Resultimg[y][3 * x + 2] = 255;
				else  pDoc->Resultimg[y][3 * x + 2] = 0;
			}
	}
	Invalidate();
}


void CMy20212156연제찬View::OnPixelTwoImageAdd()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK)
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->loadsecondimgfile(ar);
	file.Close();



	int x, y, value;
	if (pDoc->depth == 1) {
		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				value = 0.3 * pDoc->Inputimg[y][x] + 0.7 * pDoc->InputImg2[y][x];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}
	}
	else {
		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				value = 0.3 * pDoc->Inputimg[y][3*x+0] + 0.7 * pDoc->InputImg2[y][3 * x + 0];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = 0.3 * pDoc->Inputimg[y][3 * x + 1] + 0.7 * pDoc->InputImg2[y][3 * x + +1];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + +1] = value;

				value = 0.3 * pDoc->Inputimg[y][3 * x + 2] + 0.7 * pDoc->InputImg2[y][3 * x + 2];
				if (value > 255) value = 255;
				else if (value < 0) value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
	}
	
	Invalidate();
}


void CMy20212156연제찬View::OnPixelTwoImageSub()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() != IDOK)
	{
		return;;
	}
	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	pDoc->loadsecondimgfile(ar);
	file.Close();

	int x, y, value;
	if (pDoc->depth == 1) {
		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				value = abs(pDoc->Inputimg[y][x] - pDoc->InputImg2[y][x]);
				if (value > 64) value = 255;
				else value = 0;
				if (value > 255) value = 255;
				else if (value < 0)value = 0;
				pDoc->Resultimg[y][x] = value;
			}
	}
	else {

		for (y = 0;y < pDoc->ImageHeight;y++)
			for (x = 0;x < pDoc->ImageWidth;x++)
			{
				value = abs(pDoc->Inputimg[y][3*x+0] - pDoc->InputImg2[y][3 * x + 0]);
				if (value > 64) value = 255;
				else value = 0;
				if (value > 255) value = 255;
				else if (value < 0)value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = abs(pDoc->Inputimg[y][3 * x + 1] - pDoc->InputImg2[y][3 * x + 1]);
				if (value > 64) value = 255;
				else value = 0;
				if (value > 255) value = 255;
				else if (value < 0)value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = abs(pDoc->Inputimg[y][3 * x + 2] - pDoc->InputImg2[y][3 * x + 2]);
				if (value > 64) value = 255;
				else value = 0;
				if (value > 255) value = 255;
				else if (value < 0)value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
	}
	
	Invalidate();
}


void CMy20212156연제찬View::OnRegionSmoothing()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float kerenl[3][3]{ {0, -1 , 0},
						{-1 , 5, -1},
						{0, -1,  0} };

	Convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kerenl, 0, pDoc->depth);
	Invalidate();
}


void CMy20212156연제찬View::OnRegionSharpening()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float kernel[3][3] = { {0,	 -1,	0},
							{-1,  5,   -1},
							{0,	 -1,	0} };

	Convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();

	Invalidate();
}


void CMy20212156연제찬View::OnRegionEmbossing()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float kerenl[3][3]{ {-1 , 0 , 0},
						{0 , 0, 0},
						{0,0 , 1} };

	Convolve(pDoc->Inputimg, pDoc->Resultimg, pDoc->ImageWidth, pDoc->ImageHeight, kerenl, 0, pDoc->depth);
	Invalidate();
}


void CMy20212156연제찬View::Convolve(unsigned char** inimg, unsigned char** outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y, value, i, j;
	float sum, redsum, greensum, bluesum;

	for (y = 1;y < rows - 1;y++)
		for (x = 1;x < cols - 1;x++)
		{
			if (depth == 1) {
				sum = 0;
				for (j = 0;j < 3;j++)
					for (i = 0;i < 3;i++)
					{
						sum += inimg[y - 1 + j][x - 1 + i] * mask[j][i];
					}
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0) sum = 0;
				outimg[y][x] = sum;
			}
			else {
				redsum = 0, greensum = 0, bluesum = 0;
				for (j = 0;j < 3;j++)
					for (i = 0;i < 3;i++)
					{
						redsum += inimg[y - 1 + j][3 * (x - 1 + i) + 0] * mask[j][i];
						greensum += inimg[y - 1 + j][3 * (x - 1 + i) + 1] * mask[j][i];
						bluesum += inimg[y - 1 + j][3 * (x - 1 + i) + 2] * mask[j][i];
					}
				redsum += bias;
				greensum += bias;
				bluesum += bias;
				if (redsum > 255) redsum = 255;
				else if (redsum < 0) redsum = 0;
				if (greensum > 255) greensum = 255;
				else if (greensum < 0) greensum = 0;
				if (bluesum > 255) bluesum = 255;
				else if (bluesum < 0) bluesum = 0;

				outimg[y][3 * x + 0] = redsum;
				outimg[y][3 * x + 1] = greensum;
				outimg[y][3 * x + 2] = bluesum;
			}
		}
}


void CMy20212156연제찬View::OnRegionPrewitt()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float Hmask[3][3] = { {-1, -1, -1},
							{ 0,  0,  0},
							{ 1,  1,  1} };
	float Vmask[3][3] = { {-1,  0,  1},
							{-1,  0,  1},
							{-1,  0,  1} };

	unsigned char** Er, ** Ec;
	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][x] = value;
			}
			else {
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 * x + 0]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;
				pDoc->Resultimg[y][3 * x + 2] = value;

				value = sqrt(pDoc->Resultimg[y][3 * x + 0] * pDoc->Resultimg[y][3 * x + 0] +
					pDoc->Resultimg[y][3 * x + 1] * pDoc->Resultimg[y][3 * x + 1] +
					pDoc->Resultimg[y][3 * x + 2] * pDoc->Resultimg[y][3 * x + 2]);
				if (value > 255)	value = 255;
				else if (value < 0)	value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;


			}
		}

	//메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CMy20212156연제찬View::OnRegionRoberts()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float Vmask[3][3]{ {-1,0,0},
						{0,1,0},
						{0,0,0} };
	float Hmask[3][3]{ {0,0,-1},
						{0,1,0},
						{0,0,1} };
	unsigned char** Er, ** Ec;
	int x, y, value;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	Convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);
	Convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {

			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}

			else
			{
				value = sqrt(Er[y][x * 3 + 0] * Er[y][3 * x + 0] + Ec[y][x * 3 + 0] * Ec[y][x * 3 + 0]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = sqrt(Er[y][x * 3 + 1] * Er[y][x * 3 + 1] + Ec[y][x * 3 + 1] * Ec[y][x * 3 + 1]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = sqrt(Er[y][x * 3 + 2] * Er[y][x * 3 + 2] + Ec[y][x * 3 + 2] * Ec[y][x * 3 + 2]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 2] = value;

				value = sqrt(pDoc->Resultimg[y][x * 3 + 0] * pDoc->Resultimg[y][x * 3 + 0] +
					pDoc->Resultimg[y][x * 3 + 1] * pDoc->Resultimg[y][x * 3 + 1] +
					pDoc->Resultimg[y][x * 3 + 2] * pDoc->Resultimg[y][x * 3 + 2]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	}

	for (int i = 0;i < pDoc->ImageHeight;i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CMy20212156연제찬View::OnRegionSobel()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	float Hmask[3][3] = { {-1, -2, -1},
							{ 0,  0,  0},
							{ 1,  2,  1} };
	float Vmask[3][3] = { {-1,  0,  1},
							{-2,  0,  2},
							{-1,  0,  1} };
	unsigned char** Er, ** Ec;
	int x, y, value;
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->ImageHeight; i++) {
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}


	Convolve(pDoc->Inputimg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);
	Convolve(pDoc->Inputimg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);

	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {

			if (pDoc->depth == 1) {
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x] = value;
			}

			else
			{
				value = sqrt(Er[y][x * 3 + 0] * Er[y][3 * x + 0] + Ec[y][x * 3 + 0] * Ec[y][x * 3 + 0]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 0] = value;

				value = sqrt(Er[y][x * 3 + 1] * Er[y][x * 3 + 1] + Ec[y][x * 3 + 1] * Ec[y][x * 3 + 1]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 1] = value;

				value = sqrt(Er[y][x * 3 + 2] * Er[y][x * 3 + 2] + Ec[y][x * 3 + 2] * Ec[y][x * 3 + 2]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;
				pDoc->Resultimg[y][x * 3 + 2] = value;

				value = sqrt(pDoc->Resultimg[y][x * 3 + 0] * pDoc->Resultimg[y][x * 3 + 0] +
					pDoc->Resultimg[y][x * 3 + 1] * pDoc->Resultimg[y][x * 3 + 1] +
					pDoc->Resultimg[y][x * 3 + 2] * pDoc->Resultimg[y][x * 3 + 2]);
				if (value > 255) value = 255;
				if (value < 0) value = 0;

				pDoc->Resultimg[y][3 * x + 0] = value;
				pDoc->Resultimg[y][3 * x + 1] = value;
				pDoc->Resultimg[y][3 * x + 2] = value;
			}
		}
	}


	for (int i = 0;i < pDoc->ImageHeight;i++) {
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CMy20212156연제찬View::OnRegionAverageFiltering()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, ycor, xcor;
	int sum, count;
	for (int y = 0; y < pDoc->ImageHeight; y++) {
		for (int x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) {
				sum = 0;
				count = 0;
				for (int j = -3;j < 3;j++) {
					for (int i = -3;i < 3;i++) {

						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1) {
							sum += pDoc->Inputimg[ycor][xcor];
							count++;
						}
					}
				}
				pDoc->Resultimg[y][x] = sum / count;
			}
			else {

				int rsum = 0;
				int gsum = 0;
				int bsum = 0;
				count = 0;
				for (int j = -3;j < 3;j++) {
					for (int i = -3;i < 3;i++) {

						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1) {
							rsum += pDoc->Inputimg[ycor][3 * xcor + 0];
							gsum += pDoc->Inputimg[ycor][3 * xcor + 1];
							bsum += pDoc->Inputimg[ycor][3 * xcor + 2];
							count++;
						}
					}
				}
				pDoc->Resultimg[y][3 * x + 0] = rsum / count;
				pDoc->Resultimg[y][3 * x + 1] = gsum / count;
				pDoc->Resultimg[y][3 * x + 2] = bsum / count;
			};

		}
	}
	Invalidate();
}


void CMy20212156연제찬View::OnRegionMedianFiltering()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, i, j;
	int n[9];
	for (int y = 1; y < pDoc->ImageHeight - 1; y++) {
		for (int x = 1; x < pDoc->ImageWidth - 1; x++) {
			if (pDoc->depth == 1) {
				n[0] = pDoc->Inputimg[y - 1][x - 1];
				n[1] = pDoc->Inputimg[y - 1][x];
				n[2] = pDoc->Inputimg[y - 1][x + 1];
				n[3] = pDoc->Inputimg[y][x - 1];
				n[4] = pDoc->Inputimg[y][x];
				n[5] = pDoc->Inputimg[y][x + 1];
				n[6] = pDoc->Inputimg[y + 1][x - 1];
				n[7] = pDoc->Inputimg[y + 1][x];
				n[8] = pDoc->Inputimg[y + 1][x + 1];

				for (i = 8; i > 0;i--) {
					for (j = 0; j < i;j++) {
						if (n[j] > n[j + 1]) {
							int temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
						pDoc->Resultimg[y][x] = n[4];
					}
				}
			}
			else
			{
				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->Inputimg[y - 1][3 * x + 0];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->Inputimg[y][3 * (x - 1) + 0];
				n[4] = pDoc->Inputimg[y][3 * x + 0];
				n[5] = pDoc->Inputimg[y][3 * (x + 1) + 0];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->Inputimg[y + 1][3 * x + 0];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 0];

				for (i = 8; i > 0;i--) {
					for (j = 0; j < i;j++) {
						if (n[j] > n[j + 1]) {
							int temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
						pDoc->Resultimg[y][3 * x + 0] = n[4];
					}
				}
				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->Inputimg[y - 1][3 * x + 1];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->Inputimg[y][3 * (x - 1) + 1];
				n[4] = pDoc->Inputimg[y][3 * x + 1];
				n[5] = pDoc->Inputimg[y][3 * (x + 1) + 1];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->Inputimg[y + 1][3 * x + 1];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 1];

				for (i = 8; i > 0;i--) {
					for (j = 0; j < i;j++) {
						if (n[j] > n[j + 1]) {
							int temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
						pDoc->Resultimg[y][3 * x + 1] = n[4];
					}
				}
				n[0] = pDoc->Inputimg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->Inputimg[y - 1][3 * x + 2];
				n[2] = pDoc->Inputimg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->Inputimg[y][3 * (x - 1) + 2];
				n[4] = pDoc->Inputimg[y][3 * x + 2];
				n[5] = pDoc->Inputimg[y][3 * (x + 1) + 2];
				n[6] = pDoc->Inputimg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->Inputimg[y + 1][3 * x + 2];
				n[8] = pDoc->Inputimg[y + 1][3 * (x + 1) + 2];

				for (i = 8; i > 0;i--) {
					for (j = 0; j < i;j++) {
						if (n[j] > n[j + 1]) {
							int temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
						pDoc->Resultimg[y][3 * x + 2] = n[4];
					}
				}
			}
		}
	}
	Invalidate();
}


void CMy20212156연제찬View::OnMopologyColorGray()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	if (pDoc->depth == 1) return;

	int x, y;
	int gray;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3;
			pDoc->Inputimg[y][3 * x + 0] = gray;
			pDoc->Inputimg[y][3 * x + 1] = gray;
			pDoc->Inputimg[y][3 * x + 2] = gray;
		}
	Invalidate();
}


void CMy20212156연제찬View::OnMopologyBinarization()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y;
	int thresh = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->Inputimg[y][x] > thresh)
					pDoc->Inputimg[y][x] = 255;
				else
					pDoc->Inputimg[y][x] = 0;
			}
			else
			{
				if ((pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2]) / 3
	> thresh)
				{
					pDoc->Inputimg[y][3 * x + 0] = 255;
					pDoc->Inputimg[y][3 * x + 1] = 255;
					pDoc->Inputimg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->Inputimg[y][3 * x + 0] = 0;
					pDoc->Inputimg[y][3 * x + 1] = 0;
					pDoc->Inputimg[y][3 * x + 2] = 0;
				}

			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnMopologyErosion()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, i, j;
	int min, rmin, gmin, bmin = 255;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->Inputimg[y + j][x + i] < min)
							min = pDoc->Inputimg[y + j][x + i];
					}
				pDoc->Resultimg[y][x] = min;
			}
			else
			{
				rmin = 255;	gmin = 255;	bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}
				pDoc->Resultimg[y][3 * x + 0] = rmin;
				pDoc->Resultimg[y][3 * x + 1] = gmin;
				pDoc->Resultimg[y][3 * x + 2] = bmin;
			}
		}

	Invalidate();
}


void CMy20212156연제찬View::OnMopologyDilation()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, i, j;
	int max, rmax, gmax, bmax = 0;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->Inputimg[y + j][x + i] > max)
							max = pDoc->Inputimg[y + j][x + i];
					}
				pDoc->Resultimg[y][x] = max;
			}
			else
			{
				rmax = 0;	gmax = 0;	bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->Inputimg[y + j][3 * (x + i) + 2];
					}
				pDoc->Resultimg[y][3 * x + 0] = rmax;
				pDoc->Resultimg[y][3 * x + 1] = gmax;
				pDoc->Resultimg[y][3 * x + 2] = bmax;
			}
		}

	Invalidate();
}


void CMy20212156연제찬View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();

	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
}


void CMy20212156연제찬View::OnMopologyClosing()
{
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
}


void CMy20212156연제찬View::OnGeometryZoominPixelCopy()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0;y < pDoc->gImageHeight;y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->Inputimg[y / yscale][x / xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->Inputimg[y / yscale][3 * (x / xscale) + 2];
			}
		}

	/*	// 전방향사상
		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth; x++)
			{
				pDoc->gResultImg[y*yscale][x*xscale] = pDoc->InputImg[y][x];

			}
	*/
	Invalidate();
}


void CMy20212156연제찬View::OnGeometryZoominBilinearInterpolation()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y;

	float xscale = 2.3;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->Inputimg[Ay][Ax] + alpha * pDoc->Inputimg[By][Bx];
				F = (1 - alpha) * pDoc->Inputimg[Cy][Cx] + alpha * pDoc->Inputimg[Dy][Dx];

				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else
			{
				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 0] + alpha * pDoc->Inputimg[By][3 * Bx + 0];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 0] + alpha * pDoc->Inputimg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 1] + alpha * pDoc->Inputimg[By][3 * Bx + 1];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 1] + alpha * pDoc->Inputimg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				E = (1 - alpha) * pDoc->Inputimg[Ay][3 * Ax + 2] + alpha * pDoc->Inputimg[By][3 * Bx + 2];
				F = (1 - alpha) * pDoc->Inputimg[Cy][3 * Cx + 2] + alpha * pDoc->Inputimg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}

		}

	Invalidate();
}


void CMy20212156연제찬View::CopyResultToInput()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y;
	if (pDoc->depth==1) {
		for (y = 0; y < pDoc->ImageHeight; y++)
			for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
				pDoc->Inputimg[y][x] = pDoc->Resultimg[y][x];
	}
}


void CMy20212156연제찬View::OnGeometryZoomoutSubsampling()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int xscale = 3;		// 1/3
	int yscale = 2;		// 1/2
	int x, y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->Inputimg[y * yscale][x * xscale];
			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->Inputimg[y * yscale][3 * (x * xscale) + 2];
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();

}


void CMy20212156연제찬View::OnGeometryZoomoutAvgFiltering()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int xscale = 3;		// 1/3
	int yscale = 2;		// 1/2
	int x, y, i, j;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//전방향사상
	for (y = 0; y < pDoc->ImageHeight; y += yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale)
		{
			if (pDoc->depth == 1)
			{
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->Inputimg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else
			{
				rsum = 0;	gsum = 0;	bsum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->Inputimg[src_y][3 * src_x + 0];
						gsum += pDoc->Inputimg[src_y][3 * src_x + 1];
						bsum += pDoc->Inputimg[src_y][3 * src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}
	Invalidate();
}

#define PI 3.1416926521
#include "CAngleDialog.h"
void CMy20212156연제찬View::OnGeometryRotate()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	CAngleDialog dlg;

	int angle = 30;	//degree
	float radian;
	int Hy;
	int Cx, Cy;
	int x, y, xdiff, ydiff;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)	return;
	angle = dlg.m_iAngle;

	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageHeight * fabs(cos(PI / 2 - radian)) + pDoc->ImageWidth * fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	// 메모리할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for (y = -ydiff;y < pDoc->gImageHeight - ydiff;y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1)
			{

				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->ImageHeight - 1)
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->Inputimg[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source<0 || y_source>pDoc->ImageHeight - 1)
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else
				{
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->Inputimg[y_source][3 * x_source + 0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->Inputimg[y_source][3 * x_source + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->Inputimg[y_source][3 * x_source + 2];
				}
			}
		}
	Invalidate();
}

void CMy20212156연제찬View::OnGeometryHolizontalFlip()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->Resultimg[y][x] = pDoc->Inputimg[y][pDoc->ImageWidth - 1 - x];
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
}

void CMy20212156연제찬View::OnGeometryVerticalFlip()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int x, y;

	for (int y = 0;y < pDoc->ImageHeight;y++)
		for (int x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1) {
				pDoc->Resultimg[y][x] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][x];
			}
			else {
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	Invalidate();
}

typedef struct
{
	int Px;
	int Py;
	int Qx;
	int Qy;
}control_line;

control_line mctrl_source = { 100,100,150,150 };
control_line mctrl_dest = { 100,100,200,200 };

void CMy20212156연제찬View::OnGeometryWarping()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	control_line source_lines[5] = { {100,100,150,150},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };
	control_line dest_lines[5] = { {100,100,200,200},
		{0,0,pDoc->ImageWidth - 1,0},{pDoc->ImageWidth - 1,0,pDoc->ImageWidth - 1,pDoc->ImageHeight - 1},
		{pDoc->ImageWidth - 1,pDoc->ImageHeight - 1,0,pDoc->ImageHeight - 1},{0,pDoc->ImageHeight - 1,0,0} };

	source_lines[0] = mctrl_source;
	dest_lines[0] = mctrl_dest;
	int x, y;

	double u;	// 수직 교차점의 위치  
	double h;	// 제어선으로부터 픽셀의 수직 변위 
	double d;	// 제어선과 픽셀 사이의 거리
	double tx, ty;	//결과영상 픽셀에 대응되는 입력 영상 픽셀 사이의 변위의 합
	double xp, yp;	//각 제어선에 대해 계산된 입력 영상의 대응되는 픽셀 위치 
	double weight;	//각 제어선의 가중치
	double totalweight;	// 가중치의 합   
	double a = 0.001;
	double b = 2.0;
	double p = 0.75;

	int x1, y1, x2, y2;
	int src_x1, src_y1, src_x2, src_y2;
	double src_line_length, dest_line_length;

	int num_lines = 5; // 제어선의 개수
	int line;
	int source_x, source_y;
	int last_row, last_col;

	last_col = pDoc->ImageWidth - 1;
	last_row = pDoc->ImageHeight - 1;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			tx = 0.0;
			ty = 0.0;
			totalweight = 0.0;

			for (line = 0; line < num_lines; line++)
			{
				x1 = dest_lines[line].Px;
				y1 = dest_lines[line].Py;
				x2 = dest_lines[line].Qx;
				y2 = dest_lines[line].Qy;

				dest_line_length = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				u = (double)((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) /
					(double)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

				h = ((y - y1) * (x2 - x1) - (x - x1) * (y2 - y1)) / dest_line_length;

				if (u < 0)		d = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
				else if (u > 1)	d = sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
				else			d = fabs(h);

				src_x1 = source_lines[line].Px;
				src_y1 = source_lines[line].Py;
				src_x2 = source_lines[line].Qx;
				src_y2 = source_lines[line].Qy;

				src_line_length = sqrt((src_x2 - src_x1) * (src_x2 - src_x1) + (src_y2 - src_y1) * (src_y2 - src_y1));

				xp = src_x1 + u * (src_x2 - src_x1) - h * (src_y2 - src_y1) / src_line_length;
				yp = src_y1 + u * (src_y2 - src_y1) + h * (src_x2 - src_x1) / src_line_length;

				weight = pow(pow(dest_line_length, p) / (a + d), b);

				tx += (xp - x) * weight;
				ty += (yp - y) * weight;
				totalweight += weight;
			}

			source_x = x + (tx / totalweight);
			source_y = y + (ty / totalweight);

			if (source_x < 0)			source_x = 0;
			if (source_x > last_col)	source_x = last_col;
			if (source_y < 0)			source_y = 0;
			if (source_y > last_row)	source_y = last_row;

			if (pDoc->depth == 1)
				pDoc->Resultimg[y][x] = pDoc->Inputimg[source_y][source_x];
			else
			{
				pDoc->Resultimg[y][3 * x + 0] = pDoc->Inputimg[source_y][3 * source_x + 0];
				pDoc->Resultimg[y][3 * x + 1] = pDoc->Inputimg[source_y][3 * source_x + 1];
				pDoc->Resultimg[y][3 * x + 2] = pDoc->Inputimg[source_y][3 * source_x + 2];
			}
		}
	Invalidate();
}

CPoint mpos_st, mpos_end;

void CMy20212156연제찬View::OnLButtonDown(UINT nFlags, CPoint point)
{
	mpos_st = point;


	CScrollView::OnLButtonDown(nFlags, point);
}


void CMy20212156연제찬View::OnLButtonUp(UINT nFlags, CPoint point)
{
	mpos_end = point;

	CDC* pDC = GetDC();
	CPen rpen;
	rpen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
	pDC->SelectObject(&rpen);

	pDC->MoveTo(mpos_st);
	pDC->LineTo(mpos_end);
	ReleaseDC(pDC);

	int Ax, Ay, Bx, By;
	Ax = mpos_st.x;
	Ay = mpos_st.y;
	Bx = mpos_end.x;
	By = mpos_end.y;

	if (Ax < Bx) mctrl_source.Px = Ax - (Bx - Ax) / 2;
	else mctrl_source.Px = Ax + (Bx - Ax) / 2;

	if (Ay < By) mctrl_source.Px = Ay - (By - Ay) / 2;
	else mctrl_source.Px = Ay + (By - Ay) / 2;

	mctrl_dest.Px = mctrl_source.Px;
	mctrl_dest.Py = mctrl_source.Py;

	mctrl_source.Qx = mpos_st.x;
	mctrl_source.Qy = mpos_st.y;
	mctrl_dest.Qx = mpos_end.x;
	mctrl_dest.Qy = mpos_end.y;

	CScrollView::OnLButtonUp(nFlags, point);
}


void CMy20212156연제찬View::OnAviView()
{
	CFileDialog dlg(TRUE,"","",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"Avi파일(*.avi)|*.avi|모든파일|*.*|");
	if (dlg.DoModal() == IDOK) {
		AviFileName = dlg.GetPathName();
		bAviMode=true;
		Invalidate();
	}

}


void CMy20212156연제찬View::LoadAviFile(CDC* pDC)
{
	PAVIFILE pavi;
	AVIFILEINFO fi;
	int stm;
	PAVISTREAM pstm = NULL;
	AVISTREAMINFO si;
	PGETFRAME pfrm = NULL;
	int frame;
	LPBITMAPINFOHEADER pbmpih;
	unsigned char* image;
	int x, y;

	AVIFileInit();
	AVIFileOpen(&pavi, AviFileName, OF_READ | OF_SHARE_DENY_NONE, NULL);
	AVIFileInfo(pavi, &fi, sizeof(AVIFILEINFO));

	for (stm = 0; stm < fi.dwStreams; stm++)
	{
		AVIFileGetStream(pavi, &pstm, 0, stm);
		AVIStreamInfo(pstm, &si, sizeof(si));
		if (si.fccType == streamtypeVIDEO)
		{
			pfrm = AVIStreamGetFrameOpen(pstm, NULL);
			for (frame = 0; frame < si.dwLength; frame++)		//si.dwLength
			{
				pbmpih = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pfrm, frame);
				if (!pbmpih)	continue;

				image = (unsigned char*)((LPSTR)pbmpih + (WORD)pbmpih->biSize);

				/*
				for(y=0;y<fi.dwHeight;y++)
					for (x = 0; x < fi.dwWidth; x++)
					{
						pDC->SetPixel(x, fi.dwHeight-1-y,
							RGB(image[(y * fi.dwWidth + x)*3+2],
								image[(y * fi.dwWidth + x)*3+1],
								image[(y * fi.dwWidth + x)*3+0]));
					}
				*/
				::SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, fi.dwWidth, fi.dwHeight,
					0, 0, 0, fi.dwWidth, image, (BITMAPINFO*)pbmpih, DIB_RGB_COLORS);
				Sleep(33);
			}
		}

	}

	AVIStreamGetFrameClose(pfrm);
	AVIStreamRelease(pstm);
	AVIFileRelease(pavi);
	AVIFileExit();



}


void CMy20212156연제찬View::OnOpencv()
{
	COpenCVDlg dlg;
	dlg.DoModal();
}
