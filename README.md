# N503 Abi Library - Error Handling System

N503プロジェクトにおける、DLL境界を越えた安全な通信と堅牢なエラーハンドリングを実現するための基盤ライブラリです。

---

## 核心的な設計思想

* **ABI 安全性の確保**
    DLL間でのデータ受け渡しにおいて、例外（Exception）が境界を越えることによるクラッシュを防ぐため、すべてのAPIは `Result<T>` 構造体を通じて成否を報告します。
* **モダンなエラー伝搬**
    C++20 の `std::source_location` を活用し、エラー発生時のソースファイル名、行数、関数名を自動的に記録します。
* **柔軟な利用形態**
    戻り値によるチェック（Cスタイル）と、マクロによる例外スロー（C++スタイル）の両方をサポートしており、プロジェクトのフェーズや箇所に応じて使い分けが可能です。

---

## 主要コンポーネント

| コンポーネント | ファイル | 役割 |
| :--- | :--- | :--- |
| **Status** | `Status.hpp` | エラー状態を定義する列挙型。Win32エラーからの翻訳関数を含む。 |
| **Result<T>** | `Result.hpp` | 値とステータスをペアにする戻り値用コンテナ。`[[nodiscard]]` 指定。 |
| **Exception** | `Exception.hpp` | ABIエラーをラップした例外クラス。詳細な位置情報を保持。 |
| **Macros** | `Macros.hpp` | 失敗時に即座に例外を投げるためのユーティリティマクロ。 |

---

## 使用例 (Usage)

### 1. 基本的な戻り値チェック
APIを呼び出し、ステータスを確認してから値にアクセスする標準的な方法です。

```cpp
#include <N503/Abi/Result.hpp>

using namespace N503::Abi;

auto GetValue() -> Result<int>
{
    // 成功時
    return { .Value = 42, .Status = Status::Success };
}

void Sample()
{
    auto result = GetValue();
    if (result.IsSuccess()) // または if (result)
    {
        int val = result.Value;
    }
}
```

### 2. マクロを使用した例外による伝搬
エラーハンドリングを簡略化し、失敗時に自動的に `N503::Abi::Exception` を投げる方法です。

```cpp
#include <N503/Abi/Macros.hpp>

void ImportantTask()
{
    // 失敗した場合は例外が投げられ、成功した場合は Value が取り出される
    int val = N503_THROW_IF_FAILED_AND_GET(GetValue());
    
    // 戻り値が void の場合
    N503_THROW_IF_FAILED(SomeVoidFunction());
}
```

---

## 実装上の特徴

* **Win32エラーの翻訳**: `CreateStatusFromWin32Error` により、`ERROR_ACCESS_DENIED` や `WAIT_TIMEOUT` などのWin32固有エラーをライブラリ共通の `Status` へ安全に変換します。
* **演算子オーバーロード**: `Result<T>` は `operator->` や `operator*` をオーバーロードしており、エラー時にアクセスしようとすると自動的に例外を投げる安全装置が組み込まれています。
* **ムーブ専用型のサポート**: `Result<T>` は `std::is_move_constructible_v` を要求しており、リソースハンドルなどのムーブ専用型も安全に返却可能です。

---
※エラーコードは開発途中です。
