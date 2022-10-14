
// ImageProcessing_2020108251View.cpp: CImageProcessing2020108251View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_2020108251.h"
#endif

#include "ImageProcessing_2020108251Doc.h"
#include "ImageProcessing_2020108251View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessing2020108251View

IMPLEMENT_DYNCREATE(CImageProcessing2020108251View, CView)

BEGIN_MESSAGE_MAP(CImageProcessing2020108251View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DownSample, &CImageProcessing2020108251View::OnDownsample)
	ON_COMMAND(ID_SUM_CONSTANT, &CImageProcessing2020108251View::OnSumConstant)
//	ON_COMMAND(ID_32776, &CImageProcessing2020108251View::OnMulConstant)
	ON_COMMAND(ID_SUB_CONSTANT, &CImageProcessing2020108251View::OnSubConstant)
	ON_COMMAND(ID_DIV_CONSTANT, &CImageProcessing2020108251View::OnDivConstant)
	ON_COMMAND(ID_MUL_CONSTANT, &CImageProcessing2020108251View::OnMulConstant)
	ON_COMMAND(ID_UP_SAMPLING, &CImageProcessing2020108251View::OnUpSampling)
	ON_COMMAND(ID_AND_OPERATE, &CImageProcessing2020108251View::OnAndOperate)
	ON_COMMAND(ID_OR_OPERATE, &CImageProcessing2020108251View::OnOrOperate)
	ON_COMMAND(ID_XOR_OPERATE, &CImageProcessing2020108251View::OnXorOperate)
	ON_COMMAND(ID_NEGA_TRANSFORM, &CImageProcessing2020108251View::OnNegaTransform)
	ON_COMMAND(ID_GAMMA_CORRECTION, &CImageProcessing2020108251View::OnGammaCorrection)
	ON_COMMAND(ID_BINARIZATION, &CImageProcessing2020108251View::OnBinarization)
END_MESSAGE_MAP()

// CImageProcessing2020108251View 생성/소멸

CImageProcessing2020108251View::CImageProcessing2020108251View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProcessing2020108251View::~CImageProcessing2020108251View()
{
}

BOOL CImageProcessing2020108251View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageProcessing2020108251View 그리기

void CImageProcessing2020108251View::OnDraw(CDC* pDC)
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i, j;
	unsigned char R, G, B;

	for (i = 0; i < pDoc->m_height; i++) {
		for (j = 0; j < pDoc->m_width; j++) {
			R = G = B = pDoc->m_InputImage[i * pDoc->m_width + j];
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
		}
	}

	//축소된 영상 출력
	for (i = 0; i < pDoc->m_Re_height; i++) {
		for (j = 0; j<pDoc->m_Re_width; j++) {
			R = pDoc->m_OutputImage[i * pDoc->m_Re_width + j];
			G = B = R;
			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
		}
	}
}


// CImageProcessing2020108251View 인쇄

BOOL CImageProcessing2020108251View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageProcessing2020108251View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageProcessing2020108251View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CImageProcessing2020108251View 진단

#ifdef _DEBUG
void CImageProcessing2020108251View::AssertValid() const
{
	CView::AssertValid();
}

void CImageProcessing2020108251View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageProcessing2020108251Doc* CImageProcessing2020108251View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProcessing2020108251Doc)));
	return (CImageProcessing2020108251Doc*)m_pDocument;
}
#endif //_DEBUG


// CImageProcessing2020108251View 메시지 처리기


void CImageProcessing2020108251View::OnDownsample()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDownSampling();

	Invalidate(TRUE);
	
}


//void CImageProcessing2020108251View::OnDownSampling()
//{
//	CImageProcessing2020108251Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnDownSampling();
//
//	Invalidate(TRUE);
//	// TODO: 여기에 구현 코드 추가.
//}


void CImageProcessing2020108251View::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSumConstant();

	Invalidate(TRUE);
}

void CImageProcessing2020108251View::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnSubConstant();

	Invalidate(TRUE);
}



//void CImageProcessing2020108251View::OnMulConstant()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CImageProcessing2020108251Doc* pDoc = GetDocument();
//
//	ASSERT_VALID(pDoc);
//	pDoc->OnMulConstant();
//
//	Invalidate(TRUE);
//}




void CImageProcessing2020108251View::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnDivConstant();

	Invalidate(TRUE);
}


void CImageProcessing2020108251View::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnMulConstant();

	Invalidate(TRUE);
}


void CImageProcessing2020108251View::OnUpSampling()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnUpSampling();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnAndOperate()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnAndOperate();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnOrOperate()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnOrOperate();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnXorOperate()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnXorOperate();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnNegaTransform()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnGammaCorrection()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnGammaCorrection();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CImageProcessing2020108251View::OnBinarization()
{
	CImageProcessing2020108251Doc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();

	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}
