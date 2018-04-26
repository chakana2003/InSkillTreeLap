#pragma once

// 메모리 헤제용 도움 함수(help Function).
namespace Memory {
	template <class T>  // 제너릭 이라고도 한다.
	void SafeRelease(T& t) {  // DX 인터페이스 해제용.
		if (t) {
			t->Release();
			t = nullptr;
		}
	}

	// 동적 할당한 인스턴스 헤제용.
	template <class T>
	void SafeDelete(T& t) {
		if (t) {
			delete t;
			t = nullptr;
		}
	}

	// 배열 헤제용.
	template <class T>
	void SafeDeleteArr(T& t) {
		if (t) {
			delete[] t;
			t = nullptr;
		}
	}
}