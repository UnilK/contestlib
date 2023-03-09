"indentaton setup
set tabstop=4
set softtabstop=4
set shiftwidth=4
set expandtab
set autoindent
filetype indent on

"makefiles want tabs
autocmd FileType make setlocal noexpandtab

"Måliére
set encoding=utf-8

"shut up shut up shut up
set belloff=all

"still use the mouse sometimes
set mouse=a

"alt gr + space generates this wierd c2 a0. Inspect with g8 to see what's going on.
inoremap   <Space>

"possibly better movement? ALT + wasd
execute "set <C-S-M-w>=\ew"
execute "set <C-S-M-a>=\ea"
execute "set <C-S-M-s>=\es"
execute "set <C-S-M-d>=\ed"
inoremap <C-S-M-w> <Up>
inoremap <C-S-M-a> <Left>
inoremap <C-S-M-s> <Down>
inoremap <C-S-M-d> <Right>
vnoremap <C-S-M-w> <Up>
vnoremap <C-S-M-a> <Left>
vnoremap <C-S-M-s> <Down>
vnoremap <C-S-M-d> <Right>
nnoremap <C-S-M-w> <Up>
nnoremap <C-S-M-a> <Left>
nnoremap <C-S-M-s> <Down>
nnoremap <C-S-M-d> <Right>

"colors :)
syntax on

"highlight search results
set hlsearch
map hh :noh<CR>

"default complile binding
map mk :silent !make<CR><C-l>

"use global clipboard
set clipboard=unnamedplus

"sometimes I accidentally press the arrow keys when still holding shift
"- page up and page down buttons exist too, so delete these bindings.
noremap <S-up> <Nop>
noremap <S-down> <Nop>
inoremap <S-up> <Nop>
inoremap <S-down> <Nop>

"don't autoindent namespaces or private/public/protected in C++
set cino=N-s,g0

"moar tabs!!!!
set tabpagemax=32

"compile
map mk :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2 -f n/"<Bar>xargs dev/compile<CR><C-l>

"heavy compile
map mi :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2 -f v/"<Bar>xargs dev/compile<CR><C-l>

"compile for debugging
map mo :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2 -f d/"<Bar>xargs dev/compile<CR><C-l>

"compile for speed
map mu :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2 -f o/"<Bar>xargs dev/compile<CR><C-l>

"run
map ml :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2/"<Bar>xargs dev/run<CR><C-l>

"debug with gdb
map mj :silent !echo %<Bar>sed -r "s/.+\/.+\/(.+)\..+/\1/"<Bar>xargs dev/debug<CR><C-l>

"create test files
map kn :silent !dev/createtest<Space>

"write tests
map nk :silent !echo %<Bar>sed -r "s/.+\/.+\/(.+)\..+/\1/"<Bar>xargs dev/writetest<CR><C-l>

"run the written tests
map nl :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2/"<Bar>xargs dev/runtest<CR><C-l>

"save task for upsolving. save <file name without extension> -m <message>
map sa :silent !echo %<Bar>sed -r "s/.+\/(.+)\/(.+)\..+/-l \1 -t \2/"<Bar>xargs dev/save<CR><C-l>

"append a file from lib to the cursor position

map ld :r lib/
au BufEnter,BufNew,VimEnter *.cpp map ld :r lib/cpp/
au BufEnter,BufNew,VimEnter *.rs map ld :r lib/rs/
au BufEnter,BufNew,VimEnter *.py map ld :r lib/py/

" switch between languages

au BufEnter,BufNew,VimEnter *.cpp map ll :e tasks/rust/%:t:r.rs<CR>
au BufEnter,BufNew,VimEnter *.rs map ll :e tasks/python/%:t:r.py<CR>
au BufEnter,BufNew,VimEnter *.py map ll :e tasks/cpp/%:t:r.cpp<CR>

"close tabs by holding down q
nmap qqq :qa<CR>

