# Node WinForm Demo

## Node + WinForm 的測試

這個小專案目的是為了將 node.js 與 winform 的結合的測試

1. 先利用 C# 寫完 winform 編譯成 dll
2. 再利用 c++/cli 的 System::Runtime::Reflection 讀取第 1 步的 dll 進行呼叫，然後在 export api 出來，編譯成 dll 與 lib
3. 用 Napi.h link 第 2 步的 lib 編譯為 .node 供 nodejs 使用

## 主要的難點

1. delegate 怎麼從 nodejs -> node binding -> c++/cli -> c# 一層一層傳下去
2. C# 怎麼呼叫從 nodejs 傳下來的 delegate

## 編譯

必須安裝 python, nodejs 以及 msvc 2019，都要 AMD64
運行 python set.py

## 清除

運行 python clear.py
