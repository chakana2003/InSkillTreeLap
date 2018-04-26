#pragma once

// �޸� ������ ���� �Լ�(help Function).
namespace Memory {
	template <class T>  // ���ʸ� �̶�� �Ѵ�.
	void SafeRelease(T& t) {  // DX �������̽� ������.
		if (t) {
			t->Release();
			t = nullptr;
		}
	}

	// ���� �Ҵ��� �ν��Ͻ� ������.
	template <class T>
	void SafeDelete(T& t) {
		if (t) {
			delete t;
			t = nullptr;
		}
	}

	// �迭 ������.
	template <class T>
	void SafeDeleteArr(T& t) {
		if (t) {
			delete[] t;
			t = nullptr;
		}
	}
}