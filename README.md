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

## 注意事项

1. 请确保加密密钥（0x5A）在加解密过程中保持一致
2. 测试时建议关闭杀毒软件的实时监控
3. 仅供合法授权测试使用

## 已知限制

- 使用基础 XOR 加密，对抗高级杀毒软件效果有限
- 未实现反沙箱和反调试功能

## 授权信息

本项目仅用于测试目的，禁止用于非法用途。

