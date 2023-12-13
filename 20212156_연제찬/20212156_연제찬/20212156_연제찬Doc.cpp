
// 20212156_연제찬Doc.cpp: CMy20212156연제찬Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "20212156_연제찬.h"
#endif

#include "20212156_연제찬Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMy20212156연제찬Doc

IMPLEMENT_DYNCREATE(CMy20212156연제찬Doc, CDocument)

BEGIN_MESSAGE_MAP(CMy20212156연제찬Doc, CDocument)
END_MESSAGE_MAP()


// CMy20212156연제찬Doc 생성/소멸

CMy20212156연제찬Doc::CMy20212156연제찬Doc() noexcept
{
	Inputimg = NULL;
	InputImg2 = NULL;
	Resultimg = NULL;
	gResultImg = NULL;

}

CMy20212156연제찬Doc::~CMy20212156연제찬Doc()
{
	if (Inputimg != NULL) {
		for (int i = 0;i < ImageHeight;i++) {
			free(Inputimg[i]);
		}
		free(Inputimg);
	}

	if (InputImg2 != NULL) {
		for (int i = 0;i < ImageHeight;i++) {
			free(InputImg2[i]);
		}
		free(InputImg2);
	}

	if (Resultimg != NULL) {
		for (int i = 0;i < ImageHeight;i++) {
			free(Resultimg[i]);
		}
		free(Resultimg);
	}
	if (gResultImg != NULL)
	{
		for (int i = 0;i < gImageHeight;i++) {
			free(gResultImg[i]);
		}
		free(gResultImg);
	}
}

BOOL CMy20212156연제찬Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMy20212156연제찬Doc serialization

void CMy20212156연제찬Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		loadimagefile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMy20212156연제찬Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMy20212156연제찬Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMy20212156연제찬Doc::SetSearchContent(const CString& value)
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

// CMy20212156연제찬Doc 진단

#ifdef _DEBUG
void CMy20212156연제찬Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy20212156연제찬Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMy20212156연제찬Doc 명령


void CMy20212156연제찬Doc::loadimagefile(CArchive& ar)
{
	int i, j, maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".PGM") == 0 || strcmp(strchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) depth = 1;
		else depth = 3;

	}

	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 ||
		strcmp(strchr(fname, '.'), ".BMP") == 0) {
		// bitmap file 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		// BMP화일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))    return;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));

		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1)
		{   // palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;
	}

	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}
	Inputimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	Resultimg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (i = 0; i < ImageHeight; i++) {
		Inputimg[i] = (unsigned char*)malloc(ImageWidth * depth);
		Resultimg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp)
	{
		// 파일에서 읽어서 저장
		for (i = 0;i < ImageHeight;i++)
			ar.Read(Inputimg[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;
		for (j = 0;j < ImageHeight;j++)
		{
			if (depth == 1)
				ar.Read(Inputimg[ImageHeight - 1 - j], ImageWidth * depth);
			else {
				for (int i = 0;i < ImageWidth;i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);     ar.Read(&g, 1);     ar.Read(&r, 1);
					Inputimg[ImageHeight - 1 - j][3 * i + 0] = r;
					Inputimg[ImageHeight - 1 - j][3 * i + 1] = g;
					Inputimg[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}
	}
}


void CMy20212156연제찬Doc::loadsecondimgfile(CArchive& ar)
{
	int i, j, maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	int imgw, imgh, imgd;
	bool isbmp = false;


	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".PGM") == 0 || strcmp(strchr(fname, '.'), ".pgm") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imgw, &imgh);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);
		if (strcmp(type, "P5") == 0) imgd = 1;
		else imgd = 3;

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 ||
		strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		// bitmap file 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		// BMP화일임을 나타내는 "BM" 마커가 있는지 확인
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B'))    return;

		//bitmap info 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));

		imgw = bih.biWidth;
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8;

		if (imgd == 1)
		{   // palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}


	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 사용가능합니다.");
			return;
		}
		imgw = 256;
		imgh = 256;
		imgd = 1;
	}
	if (imgw != ImageWidth || imgh != ImageHeight || imgd != depth)
	{
		AfxMessageBox("동일한 크기의 화일만 읽어들일 수 있습니다.");
		return;
	}

	//메모리 할당
	InputImg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < ImageHeight; i++)
	{
		InputImg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp)
	{
		// 파일에서 읽어서 저장
		for (i = 0;i < ImageHeight;i++)
			ar.Read(InputImg2[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;
		for (j = 0;j < ImageHeight;j++)
		{
			if (depth == 1)
				ar.Read(InputImg2[ImageHeight - 1 - j], ImageWidth * depth);
			else {
				for (int i = 0;i < ImageWidth;i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);     ar.Read(&g, 1);     ar.Read(&r, 1);
					InputImg2[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImg2[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImg2[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0)
				ar.Read(nu, (widthfile - ImageWidth) * depth);
		}
	}
}
