#ifndef __JKDEFRAGGUI_H__
#define __JKDEFRAGGUI_H__

const COLORREF Colors[9] = {
	RGB(150,150,150),     /* 0 COLOREMPTY         Empty diskspace. */
	RGB(200,200,200),     /* 1 COLORALLOCATED     Used diskspace / system files. */
	RGB(0,150,0),         /* 2 COLORUNFRAGMENTED  Unfragmented files. */
	RGB(128,0,0),         /* 3 COLORUNMOVABLE     Unmovable files. */
	RGB(200,200,100),     /* 4 COLORFRAGMENTED    Fragmented files. */
	RGB(0,0,255),         /* 5 COLORBUSY          Busy color. */
	RGB(255,0,255),       /* 6 COLORMFT           MFT reserved zones. */
	RGB(0,150,150),         /* 7 COLORSPACEHOG      Spacehogs. */
	RGB(255,255,255)      /* 8 background      */
};

struct clusterSquareStruct {
	bool dirty;
	byte color;
} ;

class JKDefragGui
{
//	static JKDefragGui *m_jkDefragGui;
public:
	JKDefragGui();
	~JKDefragGui();

	static JKDefragGui *getInstance();

	void ClearScreen(WCHAR *Format, ...);
	void DrawCluster(struct DefragDataStruct *Data, ULONG64 ClusterStart, ULONG64 ClusterEnd, int Color);

	void FillSquares( int clusterStartSquareNum, int clusterEndSquareNum );
	void ShowDebug(int Level, struct ItemStruct *Item, WCHAR *Format, ...);
	void ShowStatus(struct DefragDataStruct *Data);
	void ShowAnalyze(struct DefragDataStruct *Data, struct ItemStruct *Item);
	void ShowMove(struct ItemStruct *Item, ULONG64 Clusters, ULONG64 FromLcn, ULONG64 ToLcn, ULONG64 FromVcn);

	int Initialize(HINSTANCE hInstance, int nCmdShow, JKDefragLog *jkLog, int debugLevel);
	void setDisplayData(HDC hdc);

	int DoModal();

	void OnPaint(HDC hdc);

	static LRESULT CALLBACK ProcessMessagefn(HWND WindowHandle,	UINT Message, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
	WNDCLASSEX WindowClass;
	MSG Message;

	WCHAR Messages[6][50000];        /* The texts displayed on the screen. */
	int m_debugLevel;

	ULONG64 ProgressStartTime;       /* The time at percentage zero. */
	ULONG64 ProgressTime;            /* When ProgressDone/ProgressTodo were last updated. */
	ULONG64 ProgressTodo;            /* Number of clusters to do. */
	ULONG64 ProgressDone;            /* Number of clusters already done. */

	JKDefragStruct *jkStruct;

	/* graphics data */

	int m_topHeight;
	int m_squareSize;

	int m_offsetX;
	int m_offsetY;

	int m_realOffsetX;
	int m_realOffsetY;

	int m_diskAreaWidth;
	int m_diskAreaHeight;

	int m_numDiskSquaresX;
	int m_numDiskSquaresY;
	int m_numDiskSquares;

	struct clusterSquareStruct *m_clusterSquares;

	byte *clusterInfo;
	UINT64 m_numClusters;
	int RedrawScreen;                /* 0:no, 1:request, 2: busy. */

	Rect m_clientWindowSize;         /* Window width/height. */

	HANDLE m_displayMutex;             /* Mutex to make the display single-threaded. */
	HDC m_hDC;

protected:
private:
	JKDefragLog *m_jkLog;

	static JKDefragGui *m_jkDefragGui;
};

//static JKDefragGui *m_jkDefragGui;

#endif