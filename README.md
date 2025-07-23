# Bypass_Shellcode_loader

## 项目概述

一个简单的 Shellcode 加载器，使用 XOR 加密技术实现基本的免杀功能。

## 文件结构

project/
├── loader.cpp        # Shellcode 加载器
├── xor_encrypt.py    # Shellcode 加密工具
└── shellcode.bin     # 加密后的 Shellcode 文件（生成）


## 功能特性

- **XOR 加密**：使用 0x5A 密钥加密 Shellcode
- **内存加载**：直接在内存中解密并执行 Shellcode
- **简单易用**：只需两个文件即可完成加解密和加载流程

## 使用说明

### 1. 加密 Shellcode

```bash
python xor_encrypt.py input.bin shellcode.bin
```

参数说明：

- `input.bin`：原始 Shellcode 文件
- `shellcode.bin`：输出加密后的文件

### 2. 编译加载器

使用 MinGW 编译：

```bash
g++ loader.cpp -o loader.exe -static -mwindows -s -Os
```

编译选项说明：

- `-static`：静态链接
- `-mwindows`：隐藏控制台窗口
- `-s`：移除符号表
- `-Os`：优化大小

### 3. 运行加载器

将 `shellcode.bin` 与 `loader.exe` 放在同一目录下，直接运行：

```bash
loader.exe
```

## 技术细节

### 加密原理

使用简单的 XOR 运算加密 Shellcode：

```python
encrypted_byte = original_byte ^ 0x5A
```

### 加载流程

1. 读取加密的 shellcode.bin 文件
2. 在内存中进行 XOR 解密
3. 分配可执行内存
4. 创建线程执行 Shellcode

## 绕过效果
截止时间为2025年7月23日
<img width="2859" height="137" alt="06b09e5a509bd5568becb56b7f132b9" src="https://github.com/user-attachments/assets/552c87f2-827f-4583-a91b-75e25dfc7ab3" />
### 360安全卫士
<img width="2503" height="1481" alt="acb33abb2190b35dc660395b72fd096" src="https://github.com/user-attachments/assets/509fbcf5-02a0-46f9-8cd0-b14a8a535d97" />

### 火绒
<img width="2503" height="1481" alt="8140b0facb661b5ccae51c5cea68a68" src="https://github.com/user-attachments/assets/17415830-950c-435f-ad41-5ee68151d729" />


## 授权信息

本项目仅用于测试目的，禁止用于非法用途。

