
// 20212156_연제찬Doc.h: CMy20212156연제찬Doc 클래스의 인터페이스
//


#pragma once


class CMy20212156연제찬Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMy20212156연제찬Doc() noexcept;
	DECLARE_DYNCREATE(CMy20212156연제찬Doc)

// 특성입니다.
public:

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
	virtual ~CMy20212156연제찬Doc();
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
	unsigned char** Inputimg; //[y][x]
	unsigned char** InputImg2; //[y][x]
	unsigned char** Resultimg; //[y][x]
	int ImageWidth;
	int ImageHeight;
	int depth;  //흑백 = 1, 칼라=3

	int gImageWidth;			// 추가
	int gImageHeight;			// 추가
	unsigned char** gResultImg;	// 추가
	void loadimagefile(CArchive& ar);
	void loadsecondimgfile(CArchive& ar);
};
