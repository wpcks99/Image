
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
END_MESSAGE_MAP()

// CMy20212156연제찬View 생성/소멸

CMy20212156연제찬View::CMy20212156연제찬View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

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
	int x, y, i, k;
	int acc_hist;
	int N = pDoc->ImageWidth * pDoc->ImageHeight;
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

	Invalidate();
}


void CMy20212156연제찬View::OnPixelContrastStretching()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
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

	Invalidate();
}


void CMy20212156연제찬View::OnPixelBinarization()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, value;
	int threshold = 128;
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			value = pDoc->Inputimg[y][x];
			if (value >= threshold) pDoc->Resultimg[y][x] = 255;
			else  pDoc->Resultimg[y][x] = 0;
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
	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			value = 0.3 * pDoc->Inputimg[y][x] + 0.7 * pDoc->InputImg2[y][x];
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->Resultimg[y][x] = value;
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
	float Vmask[3][3]{ {1,0,-1},
						{1,0,-1},
						{1,0,-1} };
	float Hmask[3][3]{ {-1,-1,-1},
						{0,0,0},
						{1,1,1} };
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
	float Vmask[3][3]{ {1,0,-1},
						{1,0,-1},
						{1,0,-1} };
	float Hmask[3][3]{ {-1,-1,-1},
						{0,0,0},
						{1,1,1} };
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
	float Vmask[3][3]{ {1,0,-1},
						{2,0,-2},
						{1,0,-1} };
	float Hmask[3][3]{ {-1,-2,-1},
						{0,0,0},
						{1,2,1} };
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
	int th = 128;

	for (y = 0;y < pDoc->ImageHeight;y++)
		for (x = 0;x < pDoc->ImageWidth;x++)
		{
			if (pDoc->depth == 1)
			{
				if (pDoc->Inputimg[y][x] > th)
					pDoc->Inputimg[y][x] = 255;
				else
					pDoc->Inputimg[y][x] = 0;
			}
			else
			{
				if (pDoc->Inputimg[y][3 * x + 0] + pDoc->Inputimg[y][3 * x + 1] + pDoc->Inputimg[y][3 * x + 2] / 3 > th)
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
	int min, minr, ming, minb = 255;

	for (y = 1;y < pDoc->ImageHeight - 1;y++)
		for (x = 1;x < pDoc->ImageWidth - 1;x++)
		{
			if (pDoc->depth == 1) {
				min = 255;
				for (j = -1;j <= 1;j++)
					for (i = -1;i <= 1;i++)
					{
						if (pDoc->Inputimg[y + j][x + i] < min) {
							min = pDoc->Inputimg[y + j][x + i];
						}
					}
				pDoc->Resultimg[y][x] = min;
			}
			else
			{
				minr = 255; ming = 255; minb = 255;
				for (j = -1;j <= 1;j++)
					for (i = -1;i <= 1;i++)
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] < minr) {
							minr = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						}
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] < ming) {
							ming = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						}
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] < minb) {
							minb = pDoc->Inputimg[y + j][3 * (x + i) + 2];
						}
					}
				pDoc->Resultimg[y][3 * (x + i) + 0] = minr;
				pDoc->Resultimg[y][3 * (x + i) + 1] = ming;
				pDoc->Resultimg[y][3 * (x + i) + 2] = minb;
			}
		}
	Invalidate();
}


void CMy20212156연제찬View::OnMopologyDilation()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y, i, j;
	int max, maxr, maxg, maxb = 255;

	for (y = 1;y < pDoc->ImageHeight - 1;y++)
		for (x = 1;x < pDoc->ImageWidth - 1;x++)
		{
			if (pDoc->depth == 1) {
				max = 0;
				for (j = -1;j <= 1;j++)
					for (i = -1;i <= 1;i++)
					{
						if (pDoc->Inputimg[y + j][x + i] > max) {
							max = pDoc->Inputimg[y + j][x + i];
						}
					}
				pDoc->Resultimg[y][x] = max;
			}
			else
			{
				maxr = 255; maxg = 255; maxb = 255;
				for (j = -1;j <= 1;j++)
					for (i = -1;i <= 1;i++)
					{
						if (pDoc->Inputimg[y + j][3 * (x + i) + 0] > maxr) {
							maxr = pDoc->Inputimg[y + j][3 * (x + i) + 0];
						}
						if (pDoc->Inputimg[y + j][3 * (x + i) + 1] > maxg) {
							maxg = pDoc->Inputimg[y + j][3 * (x + i) + 1];
						}
						if (pDoc->Inputimg[y + j][3 * (x + i) + 2] > maxb) {
							maxb = pDoc->Inputimg[y + j][3 * (x + i) + 2];
						}
					}
				pDoc->Resultimg[y][3 * (x + i) + 0] = maxr;
				pDoc->Resultimg[y][3 * (x + i) + 1] = maxg;
				pDoc->Resultimg[y][3 * (x + i) + 2] = maxb;
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
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
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
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
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
	float A, B;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
	int E, F;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0;i < pDoc->gImageHeight;i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	//메모리할당
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (y = 0;pDoc->gImageHeight;y++)
		for (x = 0;pDoc->gImageWidth;x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			A = src_x - (int)src_x;
			B = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;

			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) By = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1) {
				E = (1 - A) * pDoc->Inputimg[Ay][Ax] + A * pDoc->Inputimg[By][Bx];
				F = (1 - A) * pDoc->Inputimg[Cy][Cx] + A * pDoc->Inputimg[Dy][Dx];
				pDoc->gResultImg[y][x] = (1 - B) * E + B * F;
			}
			else {
				E = (1 - A) * pDoc->Inputimg[Ay][3 * Ax + 0] + A * pDoc->Inputimg[By][3 * Bx + 0];
				F = (1 - A) * pDoc->Inputimg[Cy][3 * Cx + 0] + A * pDoc->Inputimg[Dy][3 * Dx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - B) * E + B * F;

				E = (1 - A) * pDoc->Inputimg[Ay][3 * Ax + 1] + A * pDoc->Inputimg[By][3 * Bx + 1];
				F = (1 - A) * pDoc->Inputimg[Cy][3 * Cx + 1] + A * pDoc->Inputimg[Dy][3 * Dx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - B) * E + B * F;

				E = (1 - A) * pDoc->Inputimg[Ay][3 * Ax + 2] + A * pDoc->Inputimg[By][3 * Bx + 2];
				F = (1 - A) * pDoc->Inputimg[Cy][3 * Cx + 2] + A * pDoc->Inputimg[Dy][3 * Dx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - B) * E + B * F;
			}

			pDoc->gResultImg[y][x] = (1 - B) * E + B * F;
		}
	Invalidate();
}


void CMy20212156연제찬View::CopyResultToInput()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();
	int x, y;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
			pDoc->Inputimg[y][x] = pDoc->Resultimg[y][x];
}


void CMy20212156연제찬View::OnGeometryZoomoutSubsampling()
{
	CMy20212156연제찬Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0;i < pDoc->gImageHeight;i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (int y = 0;y < pDoc->gImageHeight ;y++)
		for (int x = 0;x < pDoc->gImageWidth ;x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->Inputimg[y * yscale][x / xscale];
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

	int xscale = 3;
	int yscale = 2;
	int x, y, sum,i,j,g,rsum,gsum,bsum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0;i < pDoc->gImageHeight;i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	for (int y = 0;y < pDoc->ImageHeight;y+=yscale)
		for (int x = 0;x < pDoc->ImageWidth;x+=xscale)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0;j < yscale;j++)
					for (i = 0;i < xscale;i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->Inputimg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else{
				rsum = 0;
				gsum = 0;
				bsum = 0;
				for (j = 0;j < yscale;j++)
					for (i = 0;i < xscale;i++)
					{
						src_x = x + i;
						src_y = y + j;

						rsum += pDoc->Inputimg[src_y][3*src_x+0];
						gsum += pDoc->Inputimg[src_y][3*src_x + 1];
						bsum += pDoc->Inputimg[src_y][3*src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3*(x / xscale)+0] = rsum / (yscale * xscale);
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

	int angle = 30;
	float radian;
	int Hy, Cx,Cy;
	int x,y,xdiff, ydiff;
	int src_x, src_y;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)	return;
	angle = dlg.m_iAngle;



	radian = PI / 180 * angle;
	//y의 마지막
	Hy = pDoc->ImageHeight - 1;
	//중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL) {
		for (int i = 0;i < pDoc->gImageHeight;i++) {
			free(pDoc->gResultImg[i]);
		}
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * fabs(cos(PI / 2 - radian))+pDoc->ImageWidth* fabs(cos(radian));
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth * fabs(cos(PI / 2 - radian));
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth)/2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y=-ydiff;y<pDoc->gImageHeight-ydiff;y++)
		for (x = -xdiff;x < pDoc->gImageWidth - xdiff;x++)
		{
			src_x = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			src_y = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);

			if (pDoc->depth == 1) {
				if (src_x<0 || src_x>pDoc->ImageWidth - 1 || src_y<0 || src_y>pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][x + xdiff] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->Inputimg[src_y][src_x];
				}
			}
			else {
				if (src_x<0 || src_x>pDoc->ImageWidth - 1 || src_y<0 || src_y>pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3*(x + xdiff)+0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff)+0] = pDoc->Inputimg[src_y][3*src_x+0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->Inputimg[src_y][3 * src_x + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->Inputimg[src_y][3 * src_x + 2];
				}
			}
		}
			
Invalidate();
}
