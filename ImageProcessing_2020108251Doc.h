
// ImageProcessing_2020108251Doc.h: CImageProcessing2020108251Doc 클래스의 인터페이스
//


#pragma once


class CImageProcessing2020108251Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcessing2020108251Doc() noexcept;
	DECLARE_DYNCREATE(CImageProcessing2020108251Doc)

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
	virtual ~CImageProcessing2020108251Doc();
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
	unsigned char* m_InputImage;
	int m_height;
	int m_width;
	int m_size;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnDownSampling();
	unsigned char* m_OutputImage;
	int m_Re_width;
	int m_Re_height;
	int m_Re_size;
	void OnSumConstant();
	void OnSubConstant();
	void OnMulConstant();
	void OnDivConstant();
	void OnUpSampling();
	void OnAndOperate();
	void OnOrOperate();
	void OnXorOperate();
	void OnNegaTransform();
	void OnGammaCorrection();
	void OnBinarization();
	void OnQuantization();
	void OnHistoStrech();
	void OnEndInStrech();
	void OnHistoEqual();
	double m_HIST[256];
	double m_Sum_Of_HIST[256];
	unsigned char m_Scale_HIST[256];
	void OnEmbossing();
	double** OnMaskProcess(unsigned char* Target, double Mask[3][3]);
	double** OnScale();
	double** Image2DMem(int height, int width);
	double** m_tempImage;
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpening();
	void OnHpfSharp();
	void OnDiffOperatorHor();
	void OnNearest();
	void OnHomogenOperator();
	double DoubleABS(double X);
	void OnBilinear();
	void OnNearestx4();
	void OnBilinearx4();
	void OnHomogenoperator_Threshold();
	void OnMedianSub();
	void OnBubleSort(double *A,int MAX);
	void OnSwap(double *a,double *b);
	void OnMeanSub();
	void OnmScale();
	void OnTranslation();
};
