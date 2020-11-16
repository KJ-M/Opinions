配置vim：在/etc/vim下有vimrc文件，公用配置文件，对所有用户有效
在个人目录下创建~/.vimrc对本用户有效，配置会覆盖上面的配置文件



## 以下为vim的基本快捷键

x删除光标所在的内容

dw删除一个单词，dnw,向后删除n个单词

dd删除光标所在行，ndd删除n行

d$删除至行尾，

ce或cw删除光标所在位置到这个单词最后，并进入插入模式
cne或cnw删除光标所在位置到n个单词最后，c$直接删除光标后面的本行内容

c和d作用差不多，只不过c删除了之后会进入插入模式

w向后面移动一个单词并定位到单词前，
e向后面移动一个单词并定位到单词后，
we前面加数字可以一次移动多个，
0将光标移动到行首,

u撤销最后执行的命令，U撤销对整行的修改ctrl+r撤销以前的撤销，回复操作结果
r/R,r后输入一个字符，可修改为输入的字符,R后更改光标之后内容，esc退出替换

p将已删除的文本置于光标之后
ctrl+g显示当前行号，gg跳转到第一行，G跳转到最后一行，nG跳转到n行
/xxx搜索xxx内容，n往下查找上一次输入的xxx，N往上查找xxx,输入:set ic可忽略大小写，:set noic禁用忽略大小写，:set hls is搜索会高亮显示，:nohls暂时关闭高亮，
set nohls永久关闭高亮
%，选中一个括号，输入%跳转到配对的括号
:s/old/new/g替换光标所在行所有的old为new
:#,#s/old/new/g替换##两行之间的old为new
:%s/old/new/g替换整个文件所有的old为new
:%s/old/new/gc替换整个文件所有的old为new，但换之前要询问一下
:!+shell命令，执行外部shell命令，如:!ls
:w name.c 将正在编辑的文档另存为name.c
v使vim进入可视模式进行选取，可使用d等操作命令删除或更改
使用v进行选取文件内容，然后按:，输入w name.c即可将选中内容保存到name.c
:r !ls 可将ls执行后的内容插入到光标位置
:r name.c 可将name.c文件内容插入到光标所在位置
o/O在光标所在行输入o/O可在光标所在行下方/上方插入一行并进入输入模式
a/i/A 光标后插入/光标所在位置插入/行尾插入
y/p复制粘贴，y$/yw复制光标之后所有/一个单词
:help w查看关于w的帮助信息，使用两次ctrl+w切换帮助和本文档，:q退出帮助
vimrc文件可以配置vim的设置



使用ctrl+shift++增大窗口字体，ctrl+-减小字体

## vim进阶快捷键：

### 插入模式

- i：在当前字符的左边插入
- I：在当前行首插入
- a：在当前字符的右边插入
- A：在当前行尾插入
- o：在当前行下面插入一个新行
- O：在当前行上面插入一个新行
- c{motion}：删除motion命令跨过的字符，并且进入插入模式。比如：c$，这将会删除从光标位置到行尾的字符并且进入插入模式。ct！，这会删除从光标位置到下一个叹号（但不包括），然后进入插入模式。被删除的字符被存在了剪贴板里面，且可以再粘贴出来。
- d{motion}：和上面差不多，但是不进入插入模式。
- c和d都是删除作用，单c删除了会直接进入插入模式
- s删除选中的并进入插入模式，比c一次删除的多

### 光标移动

使用*,#自动移动到光标所在单词的下一个或上一个

使用ctrl+n自动补全

## ctags使用：

使用ctags -R *生成tags文件

在vim中输入ts main就能找到main函数所在位置，其他函数类似

ctrl+]跳转到定义ctrl+t跳转回去

## cscope使用：

使用cscope -Rbkq（cscope -r）

在vim命令窗口输入:cs add ./cscope.out

使用:cs find -option label搜索，可以在vim中使用:help cscope-find来查看参数，可以搜函数名，函数引用，函数定义，文件名等

在配置文件中输入set cscopequickfix=c-,d-,e-,g-,i-,s-,t-即可在vim中输入copen打开quickfix窗口，输入cclose关闭该窗口



## Nerdtree快捷键

​          o 打开关闭文件或者目录
​          t 在标签页中打开
​          T 在后台标签页中打开
​          ! 执行此文件
​          p 到上层目录
​          P 到根目录
​          K 到第一个节点
​          J 到最后一个节点
​          u 打开上层目录
​          m 显示文件系统菜单（添加、删除、移动操作）
​          ? 帮助
​          q 关闭

## neovim配置：

配置文件目录：/home/mkj/.config/nvim/init.vim

## 安装插件vim-plug:

将git中的plug.vim文件放在目录`/home/mkj/.local/share/nvim/site/autoload`中（neovim），`/home/mkj/.vim/autoload`中（vim）在配置文件中输入

```shell
call plug#begin('~/.vim/plugged')
Plug 'scrooloose/nerdtree'
Plug 'vim-airline/vim-airline'
call plug#end()
```

即可使用PlugInstall安装插件，插件目录为`~/.vim/plugged`

vim+cscope浏览代码`https://www.bilibili.com/video/BV1q64y1M7sW?from=search&seid=9144590342453117242`

## 可供参考的vim配置：

```c
"相比于第一个优化了自动生成文件的功能插入代码段的功能，例如插入头文件和自己习惯的一些设置


"允许插件  
filetype plugin on
" 设置行号
set number
" 语法高亮。自动识别代码，使用多种颜色表示
syntax enable
" 支持使用鼠标
set mouse=a
" 按下回车键后，下一行的缩进会自动跟上一行的缩进保持一致
set autoindent
" 按下Tab键后，vim显示的空格数
set tabstop=4
" normal模式下，>>增加一级缩进、<<取消一级缩进、==取消全部缩进时，每一级缩进的空格数
set shiftwidth=4
" 自动将Tab转为空格(防止Tab键在不同编辑器缩进不一致导致问题)
set expandtab
" Tab转为多少个空格
set softtabstop=4

"设置文件的代码形式 utf8
set encoding=utf-8
set termencoding=utf-8
set fileencoding=utf-8
set fileencodings=ucs-bom,utf-8,chinese,cp936



"新建.c,.h,.cpp文件，自动插入文件头 
autocmd BufNewFile *.h,*.c,*.cpp exec ":call SetTitle()" 
""定义函数SetTitle，自动插入文件头 
func SetTitle() 

if expand("%:e")== 'c'
    call setline(1,"#include<stdio.h>")
	call append(line("."), "#include<stdlib.h>")
    call append(line(".")+1, "#include<unistd.h>")
    call append(line(".")+2, "#include<fcntl.h>")
    call append(line(".")+3, "#include<string.h>")
    call append(line(".")+4, "")
endif

if expand("%:e")== 'cpp'
 	call setline(1,"#include<iostream>")
	call append(line("."), "using namespace std;")
	call append(line(".")+1, "")
endif

if expand("%:e")== 'h'
 	call setline(1,"#ifndef __".expand("%:r")."_H__")
 	call append(line("."),"#define __".expand("%:r")."_H__")
	call append(line(".")+1, "")
	call append(line(".")+2, "")
	call append(line(".")+3, "")
	call append(line(".")+4, "")
	call append(line(".")+5, "")
	call append(line(".")+6, "")
	call append(line(".")+7, "#endif")

    
endif



	"新建文件后，自动定位到文件末尾
    "autocmd BufNewFile * normal G
endfunc 


"补全括号和花括号（换行四次）   
:inoremap ( ()<ESC>i
:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {<CR>}<ESC>O
:inoremap } <c-r>=ClosePair('}')<CR>
:inoremap [ []<ESC>i
:inoremap ] <c-r>=ClosePair(']')<CR>
:inoremap " ""<ESC>i
:inoremap ' ''<ESC>i

function! ClosePair(char)
	if getline('.')[col('.') - 1] == a:char
		return "\<Right>"
	else
		return a:char
	endif
endfunction
filetype plugin indent on 

"使用tab自动补全的设定
function! CleverTab()
        if strpart( getline('.'), 0, col('.')-1 ) =~ '^\s*$'
                return "\<Tab>"
        else
                return "\<C-N>"
        endif
endfunction
inoremap <Tab> <C-R>=CleverTab()<CR>

"C，C++ 按F5编译运行
map <F5> :call CompileRunGcc()<CR>
func! CompileRunGcc()
	exec "w"
	if &filetype == 'c'
		exec "!g++ % -o %<"
		exec "! %<"
	elseif &filetype == 'cpp'
		exec "!g++ % -o %<"
		exec "! %<"
	elseif &filetype == 'java' 
		exec "!javac %" 
		exec "!java %<"
	elseif &filetype == 'sh'
		:!./%
	elseif &filetype == 'py'
		exec "!python %"
		exec "!python %<"
	endif
endfunc

"C,C++的调试
map <F8> :call Rungdb()<CR>
func! Rungdb()
	exec "w"
	exec "!g++ % -g -o %<"
	"exec "!gdb ./%<"
endfunc


"set tags+=/home/dd/vim配置/cpp_src/cpp          c++代码的ctags 找到头文件执行相应的命令
"set tags+=/usr/include/ccctag                                c代码的ctags

" OmniCppComplete
let OmniCpp_DisplayMode=1           "显示类成员
let OmniCpp_NamespaceSearch = 1
let OmniCpp_GlobalScopeSearch = 1
let OmniCpp_ShowAccess = 1
let OmniCpp_ShowPrototypeInAbbr = 1 " 显示函数参数列表
let OmniCpp_MayCompleteDot = 1   " 输入 .  后自动补全
let OmniCpp_MayCompleteArrow = 1 " 输入 -> 后自动补全
let OmniCpp_MayCompleteScope = 1 " 输入 :: 后自动补全
let OmniCpp_DefaultNamespaces = ["std", "_GLIBCXX_STD"]
" 自动关闭补全窗口
au CursorMovedI,InsertLeave * if pumvisible() == 0|silent! pclose|endif
set completeopt=menuone,menu,longest

set autowriteall
set updatetime=500

"按下F12自动更新tags
map <F10> :call Rungdbe()<CR>
func! Rungdbe()
	exec "w"                
	exec "!ctags -R --c++-kinds=+p --fields=+iaS --extra=+q"     
endfunc

我目前的配置：
    	
set ts=4	"tab键vim对应空格数
set softtabstop=4	"tab转为多少个空格
set mouse=a		"支持鼠标
set nu	"设置显示行号
set autoindent	"按下回车后下一行缩进自动跟上一行保持一致
set shiftwidth=4	"normal模式下>>增加一级缩进，<<取消一级缩进，==取消全部缩进时，每一级缩进的空格数
set shiftwidth=4	"自动缩进空白字符个数
set noexpandtab
set norelativenumber
set cursorline
set wrap
set showcmd
set wildmenu
set ruler
"将leader键映射为空格
let mapleader=" "	
"映射leader+;为进入normal模式
inoremap jj <ESC>
inoremap ( ()<esc>i
inoremap { {}<esc>i
inoremap [ []<esc>i
inoremap <leader>" ""<esc>i

"插件安装部分开始----------------------------------------

call plug#begin('~/.vim/plugged')

Plug 'scrooloose/nerdtree'
Plug 'vim-airline/vim-airline'
Plug 'vim-scripts/taglist.vim'

call plug#end()
"插件安装部分结束-------------------------------------------

"NerdTree插件配置信息
"将f2设置为开关快捷键
map <f2> :NERDTreeToggle<cr>
"修改树的显示图标
let g:NERDTreeDirArrowExpandable = '+'
let g:NERDTreeDirArrowCollapsible = '-'
"窗口位置
let g:NERDTreeWinPos='left'
"窗口尺寸
let g:NERDTreeSize=30
"窗口是否显示行号
let g:NERDTreeShowLineNumbers=1
"不显示隐藏文件
let g:NERDTreeHidden=1

"taglist配置信息
let Tlist_Show_One_File           = 1    " 只显示当前文件的tags
let Tlist_GainFocus_On_ToggleOpen = 1    " 打开 Tlist 窗口时，光标跳到 Tlist 窗口
let Tlist_Exit_OnlyWindow         = 1    " 如果 Tlist 窗口是最后一个窗口则退出 Vim
let Tlist_Use_Left_Window         = 1    " 在左侧窗口中显示
let Tlist_File_Fold_Auto_Close    = 1    " 自动折叠
let Tlist_Auto_Update             = 1    " 自动更新
 
" <leader>tl 打开 Tlist 窗口，在左侧栏显示
map <F3> :TlistToggle<CR>

"调整当前窗口的大小
map <F5> :vertical resize-1<CR>
map <F6> :vertical resize+1<CR>

"使用cscope多次查看搜索结果
set cscopequickfix=c-,d-,e-,g-,i-,s-,t-
```







