
// ImageProcessing_2020108251Doc.cpp: CImageProcessing2020108251Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcessing_2020108251.h"
#endif

#include "ImageProcessing_2020108251Doc.h"

#include <propkey.h>
#include "CDownSampleDlg.h"
#include "CConstantDlg.h"
#include "CUpSampleDlg.h"
#include "CimageScale.h"
#include "CImageTranslation.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcessing2020108251Doc

IMPLEMENT_DYNCREATE(CImageProcessing2020108251Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcessing2020108251Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcessing2020108251Doc 생성/소멸


CImageProcessing2020108251Doc::CImageProcessing2020108251Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageProcessing2020108251Doc::~CImageProcessing2020108251Doc()
{
}


BOOL CImageProcessing2020108251Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcessing2020108251Doc serialization

void CImageProcessing2020108251Doc::Serialize(CArchive& ar)
{
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
void CImageProcessing2020108251Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageProcessing2020108251Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcessing2020108251Doc::SetSearchContent(const CString& value)
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

// CImageProcessing2020108251Doc 진단

#ifdef _DEBUG
void CImageProcessing2020108251Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcessing2020108251Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcessing2020108251Doc 명령


BOOL CImageProcessing2020108251Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

	//이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.
	if (File.GetLength() == 256 * 256) { //RAW 파일 크기 결정

		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) { //RAW 파일의 크기 결정
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox("Not Support Image Size");
		return 0;
	}
	m_size = m_width * m_height;

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i<m_size; i++)
		m_InputImage[i] = 255;
	File.Read(m_InputImage, m_size);
	File.Close();

	return TRUE;
}


BOOL CImageProcessing2020108251Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CFile File; //파일 객체 선언
	CFileDialog SaveDlg(FALSE, "raw", NULL, OFN_HIDEREADONLY);
	//raw 파일을 다른 이름으로 저장하기를 위한 대화상자 객체 선언

	if (SaveDlg.DoModal() == IDOK) {
		//DoModel 멤버 함수에서 저장하기 수행
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate |
			CFile::modeWrite);
		//파일 열기
		File.Write(m_InputImage, m_size); //파일 쓰기
		File.Close(); //  파일 닫기
	}
	return CDocument::OnSaveDocument(lpszPathName);
}


void CImageProcessing2020108251Doc::OnDownSampling()
{
	int i, j;
	CDownSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_Re_height = m_height / dlg.m_DownSampleRate;
		m_Re_width = m_width / dlg.m_DownSampleRate;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0; i < m_Re_height; i++) {
			for (j = 0; j < m_Re_width; j++) {
				m_OutputImage[i * m_Re_width + j]
					= m_InputImage[(i * dlg.m_DownSampleRate * m_width) + dlg.m_DownSampleRate * j];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnSumConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;
	int i;
	
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;

			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnSubConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] - dlg.m_Constant < 0)
				m_OutputImage[i] = 0;

			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] - dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnMulConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] * dlg.m_Constant >255)
				m_OutputImage[i] = 255;
			else if (m_InputImage[i] * dlg.m_Constant <0)
				m_OutputImage[i] = 0;

			else
				m_OutputImage[i]
				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
		}
	}
}


void CImageProcessing2020108251Doc::OnDivConstant()
{
	// TODO: 여기에 구현 코드 추가.
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] / dlg.m_Constant > 255)
				m_OutputImage[i] = 255;
			else if (m_InputImage[i] / dlg.m_Constant < 0)
				m_OutputImage[i] = 0;

			else {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
			}
		}
	}
}


void CImageProcessing2020108251Doc::OnUpSampling()
{
	int i, j;
	CUpSampleDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_Re_height = m_height * dlg.m_UpSampleRate;
		m_Re_width = m_width * dlg.m_UpSampleRate;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0;

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[(i * dlg.m_UpSampleRate * m_Re_width) + dlg.m_UpSampleRate * j]
					= m_InputImage[i * m_width + j];
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnAndOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i]= (m_InputImage[i] & (unsigned char)dlg.m_Constant);
					
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnOrOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] | (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);

			}
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnXorOperate()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] ^ (unsigned char) dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}

			else {
				m_OutputImage[i] = (m_InputImage[i]	^ (unsigned char)dlg.m_Constant);

			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnNegaTransform()
{
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = 255 - m_InputImage[i];
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnGammaCorrection()
{
	CConstantDlg dlg;

	int i;
	double temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);

			if (temp < 0)
				m_OutputImage[i] = 0;
			else if (temp > 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)temp;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnBinarization()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnQuantization()
{
	CConstantDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int i, j, value, LEVEL;
		double HIGH, * TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];
		
		TEMP = new double[m_size];

		LEVEL = 256;
		HIGH = 256;

		value = (int)pow(2, dlg.m_Constant);

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value) * j &&
					m_InputImage[i] < (LEVEL / value) * (j + 1)) {
					TEMP[i] = (double)(HIGH / value) * j;
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
		}
	}
	
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHistoStrech()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnEndInStrech()
{
	int i;
	unsigned char LOW, HIGH, MAX, MIN;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	MIN = m_InputImage[0];
	MAX = m_InputImage[0];

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] < MIN)
			MIN = m_InputImage[i];
	}

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] > MAX)
			MAX = m_InputImage[i];
	}

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_size; i++)
		m_OutputImage[i] = (unsigned char)((m_InputImage[i] -
			MIN) * HIGH / (MAX - MIN));

	for (i = 0; i < m_size; i++) {
		if (m_InputImage[i] <= MIN) {
			m_OutputImage[i] = 0;
		}

		else if (m_InputImage[i] >= MAX) {
			m_OutputImage[i] = 255;
		}

		else
			m_OutputImage[i] = (unsigned char)((m_InputImage[i]) -
				MIN) * HIGH / (MAX - MIN);
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHistoEqual()
{
	int i, value;
	unsigned char LOW, HIGH, Temp;
	double SUM = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	LOW = 0;
	HIGH = 255;

	for (i = 0; i < 256; i++)
		m_HIST[i] = LOW;

	for (i = 0; i < m_size; i++) {
		value = (int)m_InputImage[i];
		m_HIST[value]++;
	}

	for (i = 0; i < 256; i++) {
		SUM += m_HIST[i];
		m_Sum_Of_HIST[i] = SUM;
	}

	
	m_OutputImage = new unsigned char[m_Re_size];


	for (i = 0; i < m_size; i++) {
		Temp = m_InputImage[i];
		m_OutputImage[i]
			= (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnEmbossing()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double EmboMask[3][3] = { {-1.,0.,0.},{0.,0.,0.},{0.,0.,1.} };   //까맣게
	//마스크 선택 -> 마스크 값 변경으로 인해 블러 처리 가능(부드럽게 등)
	//double EmboMask[3][3] = { {0.,0.,0.},{0.,1.,0.},{0.,0.,0.} };   //
	//double EmboMask[3][3] = { {1.,1.,1.},{-1.,8.,1.},{1.,1.,1.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	//OnMaskProcess 함수를 호출하여 회선 처리를 한다.
	//m_tempImage = OnMaskProcess(&m_InputImage[0], &EmboMask[0]);



	//회선 처리 결과가 0~255 사이 값이 되도록 한다.
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0)
				m_tempImage[i][j] = 0;
		}
	}

	//회선 처리 결과나 정규화 처리는 2차원 배열 값이 되므로
	//2차원 배열을 1차원 배열로 바꾸어 출력하도록 한다.
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}

}


//회선 처리가 일어나는 함수
double** CImageProcessing2020108251Doc::OnMaskProcess(unsigned char* Target, double Mask[3][3])
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double** tempInputImage, ** tempOutputImage, S = 0.0;

	//입력 값을 위한 메모리 할당
	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	//출력 값을 위한 메모리 할당
	tempOutputImage = Image2DMem(m_height, m_width);

	//1차원 입력 영상의 값을 2차원 배열에 할당한다.
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1] = (double)Target[i * m_width + j];
		}
	}

	//회선연산
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					S += Mask[n][m] * tempInputImage[i + n][j + m];
				}
			}//회선 마스크의 크기 만큼 이동하면서 값을 누적
			tempOutputImage[i][j] = S;   //누적된 값을 출력 메모리에 저장
			S = 0.0;   //다음 블록으로 이동하면 누적 값을 초기화
		}
	}
	//입력 값을 위한 메모리 할당

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	return tempOutputImage;   //결과 값 반환
}

//2차원 형태의 메모리로 만들어주는 함수
double** CImageProcessing2020108251Doc::Image2DMem(int height, int width)
{
	//2차원 메모리 할당을 위한 함수
	double** temp;
	int i, j;
	temp = new double* [height];
	for (i = 0; i < height; i++) {
		temp[i] = new double[width];
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			temp[i][i] = 0.0;
		}
	}   //할당된 2차원 메모리를 초기화

	return temp;
}



double** CImageProcessing2020108251Doc::OnScale()
{
	// TODO: 여기에 구현 코드 추가.
	return nullptr;
}


void CImageProcessing2020108251Doc::OnBlurr()
{
	int i, j;
	//double BlurMask[5][5] = { {1. / 25.,1. / 25.,1. / 25.,1. / 25.,1. / 25.} ,
		//{1. / 25.,1. / 25.,1. / 25.,1. / 25.,1. / 25.},{1. / 25.,1. / 25.,1. / 25.,1. / 25.,1. / 25.},{1. / 25.,1. / 25.,1. / 25.,1. / 25.,1. / 25.},{1. / 25.,1. / 25.,1. / 25.,1. / 25.,1. / 25.} };
	// TODO: 여기에 구현 코드 추가.

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	
	m_OutputImage = new unsigned char[m_Re_size];
	//m_tempImage = OnMaskProcess(m_InputImage, BlurMask);



	
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0)
				m_tempImage[i][j] = 0;
		}
	}

	
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
}


void CImageProcessing2020108251Doc::OnGaussianFilter()
{
	int i, j;
	double GaussianMask[3][3] = { {1. / 16.,1. / 8.,1. / 16.},{1. / 8.,1. / 4. ,1. / 8.},
		{1. / 16.,1. / 8.,1. / 16.} };
	// TODO: 여기에 구현 코드 추가.

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);




	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0)
				m_tempImage[i][j] = 0;
		}
	}


	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnSharpening()
{
	int i, j;
	double SharpeningMask[3][3] = { {-1.,1.,-1.},{-1.,9.,-1.},{-1.,-1.,-1. } };
	
	// TODO: 여기에 구현 코드 추가.

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];


	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);




	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0)
				m_tempImage[i][j] = 0;
		}
	}


	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHpfSharp()
{
	int i, j;
	double HpfSharpMask[3][3] = { {-1. / 9.,-1. / 9.,-1. / 9. },{-1. / 9.,8. / 9.,-1. / 9.}, {-1. / 9.,-1. / 9.,-1. / 9. } };
	
	// TODO: 여기에 구현 코드 추가.

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];


	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);




	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_tempImage[i][j] = 255;
			if (m_tempImage[i][j] < 0)
				m_tempImage[i][j] = 0;
		}
	}


	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)m_tempImage[i][j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnDiffOperatorHor()
{
	int i, j;
	double DiffHorMask[3][3]
		= { {0., -1., 0.}, {0., 1., 0.}, {0., 0., 0.} };
	// 수평 필터 선택
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, DiffHorMask);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255.)
				m_tempImage[i][j] = 255.;
			if (m_tempImage[i][j] < 0.)
				m_tempImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}
	// TODO: 여기에 구현 코드 추가.



void CImageProcessing2020108251Doc::OnNearest()
{
	int i, j;
	int ZoomRate = 2;
	double** tempArray;

	m_Re_height = int(ZoomRate * m_height);
	m_Re_width = int(ZoomRate * m_width);
	m_Re_size = m_Re_height * m_Re_width;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j <m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
}

	
	// TODO: 여기에 구현 코드 추가.



void CImageProcessing2020108251Doc::OnHomogenOperator()
{
	int i, j, n, m;
	double max, ** tempOutputImage;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (DoubleABS(m_tempImage[i + 1][j + 1] -
						m_tempImage[i + n][j + m]) >= max)
						// 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값
						// 중에서 최대값을 찾는다.
						max = DoubleABS(m_tempImage[i + 1]
							[j + 1] - m_tempImage[i + n][j + m]);
				}
			}
			tempOutputImage[i][j] = max; // 찾은 최대값을 출력 값으로 지정
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempOutputImage[i][j];
		}
	}
}
	// TODO: 여기에 구현 코드 추가.



double CImageProcessing2020108251Doc::DoubleABS(double X)
{
	// 실수의 절대 값 연산 함수
	if (X >= 0)
		return X;
	else
		return -X;
}


void CImageProcessing2020108251Doc::OnBilinear()
{
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double ZoomRate, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;
	CimageScale dlg;

	if (dlg.DoModal() == IDOK) {
		ZoomRate = dlg.m_Scale;
	}

	m_Re_height = (int)(m_height * ZoomRate);
	m_Re_width = (int)(m_width * ZoomRate);
	m_Re_size = m_Re_height * m_Re_width;

	m_tempImage = Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;

			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;
			s_W = r_W - i_W;

			if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0
				|| i_W >= (m_width - 1))
			{
				point = i * m_Re_width + j;
				m_OutputImage[point] = 255;
			}

			else
			{
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W+1];
				C3 = (double)m_tempImage[i_H+1][i_W+1];
				C4 = (double)m_tempImage[i_H+1][i_W];

				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W)
					+ C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				point = i * m_Re_width + j;
				m_OutputImage[point] = newValue;
			}
		}
	}
}


void CImageProcessing2020108251Doc::OnNearestx4()
{
	int i, j;
	int ZoomRate = 4;
	double** tempArray;

	m_Re_height = int(ZoomRate * m_height);
	m_Re_width = int(ZoomRate * m_width);
	m_Re_size = m_Re_height * m_Re_width;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			tempArray[i][j] = m_tempImage[i / ZoomRate][j / ZoomRate];
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j] = (unsigned char)tempArray[i][j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnBilinearx4()
{
	int i, j, point, i_H, i_W;
	unsigned char newValue;
	double ZoomRate = 4.0, r_H, r_W, s_H, s_W;
	double C1, C2, C3, C4;

	m_Re_height = (int)(m_height * ZoomRate);
	m_Re_width = (int)(m_width * ZoomRate);
	m_Re_size = m_Re_height * m_Re_width;

	m_tempImage = Image2DMem(m_height, m_width);
	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			r_H = i / ZoomRate;
			r_W = j / ZoomRate;

			i_H = (int)floor(r_H);
			i_W = (int)floor(r_W);

			s_H = r_H - i_H;
			s_W = r_W - i_W;

			if (i_H < 0 || i_H >= (m_height - 1) || i_W < 0
				|| i_W >= (m_width - 1))
			{
				point = i * m_Re_width + j;
				m_OutputImage[point] = 255;
			}

			else
			{
				C1 = (double)m_tempImage[i_H][i_W];
				C2 = (double)m_tempImage[i_H][i_W + 1];
				C3 = (double)m_tempImage[i_H + 1][i_W + 1];
				C4 = (double)m_tempImage[i_H + 1][i_W];

				newValue = (unsigned char)(C1 * (1 - s_H) * (1 - s_W)
					+ C2 * s_W * (1 - s_H) + C3 * s_W * s_H + C4 * (1 - s_W) * s_H);
				point = i * m_Re_width + j;
				m_OutputImage[point] = newValue;
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnHomogenoperator_Threshold()
{
	int i, j, n, m;
	double max, ** tempOutputImage;
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_Re_height, m_Re_width);
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i + 1][j + 1] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			max = 0.0; // 블록이 이동할 때마다 최대값 초기화
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (DoubleABS(m_tempImage[i + 1][j + 1] -
						m_tempImage[i + n][j + m]) >= max)
						// 블록의 가운데 값 - 블록의 주변 픽셀 값의 절대 값
						// 중에서 최대값을 찾는다.
						max = DoubleABS(m_tempImage[i + 1]
							[j + 1] - m_tempImage[i + n][j + m]);
				}
			}
			tempOutputImage[i][j] = max; // 찾은 최대값을 출력 값으로 지정
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (tempOutputImage[i][j] > 255.)
				tempOutputImage[i][j] = 255.;
			if (tempOutputImage[i][j] < 0.)
				tempOutputImage[i][j] = 0.;
		}
	}
	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempOutputImage[i][j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnMedianSub()
{
	int i, j, n, m, M = 4, index = 0;
	double* Mask, Value;

	Mask = new double[M * M];

	m_Re_height = m_height/M;
	m_Re_width = m_width/M;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
					//입력 영상을 블록으로 잘라 마스크 배열에 저장
				}
			}
			OnBubleSort(Mask, M * M); //마스크에 저장된 값을 정렬
			Value = Mask[(int)(M * M / 2)]; //정렬된 값 중 가운데 값을 선택
			m_OutputImage[index] = (unsigned char)Value;
			//가운데 값을 출력

			index++;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnBubleSort(double *A, int MAX)
{
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnSwap(double *a, double *b)
{
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnMeanSub()
{
	int i, j, n, m, M = 0, index = 0,k;
	double* Mask, Value, Sum = 0.0;
	CimageScale dlg;

	if (dlg.DoModal() == IDOK) {
		M = dlg.m_Scale;
	}
	Mask = new double[M * M];

	m_Re_height = m_height/M;
	m_Re_width = m_width/M;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = Image2DMem(m_height + 1, m_width + 1);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height - 1; i = i + M) {
		for (j = 0; j < m_width - 1; j = j + M) {
			for (n = 0; n < M; n++) {
				for (m = 0; m < M; m++) {
					Mask[n * M + m] = m_tempImage[i + n][j + m];
					//입력 영상을 블록으로 잘라 마스크 배열에 저장
				}
			}
			for (k = 0; k < M * M; k++)
				Sum = Sum + Mask[k];

			Value = (Sum / (M * M));
			m_OutputImage[index] = (unsigned char)Value;

			index++;
			Sum = 0.0;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CImageProcessing2020108251Doc::OnTranslation()
{
	int i, j;
	int h_pos = 30, w_pos = 130;
	double **tempArray;

	CImageTranslation dlg;

	if (dlg.DoModal() == IDOK) {
		h_pos = dlg.m_TranslationX;
	}

	if (dlg.DoModal() == IDOK) {
		w_pos = dlg.m_TranslationY;
	}

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i * m_width + j];

		}
	}

	for (i = 0; i < m_height - h_pos; i++) {
		for (j = 0; j < m_width - w_pos; j++) {
			tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}

	delete[]m_tempImage;
	delete[]tempArray;
	// TODO: 여기에 구현 코드 추가.
}
