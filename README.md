[![Codacy Badge](https://api.codacy.com/project/badge/Grade/fd0ec010520447c597207fcdb0acc57a)](https://www.codacy.com/app/KuangLei/Base32?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Globefishp/Base32&amp;utm_campaign=Badge_Grade)  

# Base32
A simple Base32 Enc/Decoder in C++  

## Usage for Windows user

* First, clone this repo to your local disk.
* Then, open your Visual Studio with the `Base32.sln`.
* At last, click the `Build` button on the Visual Studio.

Usage: Base32 [-Enc|-Dec|-fEnc|fDec(Unfinished)] "String/File" ["OutputFile"]
### 1.1.3 Updata log  
Fix:  
修复了计算分配内存大小时的错误.  
Add:  
添加文件编码功能,简易版未完工.  

## Usage for Linux user
This Base32 Enc/Decoder is **still in development**.  
The Base32 on Linux's encoding can only be decoded on Linux, not available for Windows or other tools.  
But at present the Linux developer (@KLsz) has focused on the branch GUI\_dev, so I'm sorry that it may not be fixed in a while.  

First, download it through git:  
```
git clone git@github.com:Globefishp/Base32.git
```
And install it with make:  
```
cd Base32/Base32
make
```
Then you can run it with  
```
./a.out
```

